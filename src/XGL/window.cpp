/*
   GLUI-ng, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

   This library is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the 
   Free Software Foundation; either version 2.1 of the License, 
   or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License along with this library;
   if not, write to the 
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

   based on the work of Paul Rademacher (orignal software http://glui.sourceforge.net/)
*/
#include <GL/glui/debug.h>
#include <GL/glui/x11_window.h>
#include <string.h>
#undef Display
#define MODULE_KEY "GLUI_DEBUG_XGL"
using namespace GLUI;
/////////////////////////////////////////////////////////////////////
X11Screen::X11Screen(::Screen* screen) : TheScreen(screen)
{
}
int X11Screen::XDefaultDepthOfScreen()
{
        return ::XDefaultDepthOfScreen(TheScreen);
}
NCRC_AutoPtr<_Window> X11Screen::XRootWindowOfScreen()
{
        return NCRC_AutoPtr<_Window>(new ROWindow(::XRootWindowOfScreen(TheScreen)));
}

::Screen* X11Screen::Screen()
{
        return TheScreen;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

X11Display::X11Display()
{
        _X11Display(getenv("DISPLAY"));
}

X11Display::X11Display(char* name)
{
        _X11Display(name);
}

void X11Display::_X11Display(char* name)
{
        disp = XOpenDisplay(name);
        if (! disp) throw Exception(EINVAL,"can't open display");
        if ( NULL != getenv("GLUI_ENABLE_DEBUG") ) 
        {
                XSynchronize(disp, True);
        }
}

X11Display::~X11Display()
{
        XCloseDisplay(disp);
}

NCRC_AutoPtr<_Screen> X11Display::XDefaultScreenOfDisplay()
{
        return new X11Screen(::XDefaultScreenOfDisplay(disp));
}
NCRC_AutoPtr<_Window> X11Display::XDefaultRootWindow()
{
        return new ROWindow(::XDefaultRootWindow(disp));
}
NCRC_AutoPtr<_Window> X11Display::XRootWindow(int screen_number)
{
        return new ROWindow(::XRootWindow(disp,screen_number));
}
::Display* X11Display::Disp()
{
        return disp;
}

/////////////////////////////////////////////////////////////////////
X11Window::X11Window(NCRC_AutoPtr<X11Display> display,
                NCRC_AutoPtr<_Window> parent_window,
                int x, int y,
                unsigned int width, unsigned int height,
                unsigned int border_width,
                int depth,
                unsigned int _class,
                Visual *visual,
                unsigned long valuemask,
                XSetWindowAttributes *attributes ) :
        disp(display)
{
        _X11Window(parent_window,
                x, y,
                width, height,
                border_width,
                depth,
                _class,
                visual,
                valuemask,
                attributes );
}



X11Window::X11Window(NCRC_AutoPtr<X11Display> display,
                NCRC_AutoPtr<_Window> parent_window,
                int x, int y,
                unsigned int width, unsigned int height,
                unsigned int border_width,
                unsigned long border,
                unsigned long background ) :
        disp(display)
{
                // Get a matching FB config
        static int visual_attribs[] =
        {
                GLX_X_RENDERABLE    , True,
                GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
                GLX_RENDER_TYPE     , GLX_RGBA_BIT,
                GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
                GLX_RED_SIZE        , 8,
                GLX_GREEN_SIZE      , 8,
                GLX_BLUE_SIZE       , 8,
                GLX_ALPHA_SIZE      , 8,
                GLX_DEPTH_SIZE      , 24,
                GLX_STENCIL_SIZE    , 8,
                GLX_DOUBLEBUFFER    , True,
                //GLX_SAMPLE_BUFFERS  , 1,
                //GLX_SAMPLES         , 4,
                None
        };
        EventMask = KeyPressMask 
                  | KeyReleaseMask 
                  | ButtonPressMask 
                  | ButtonReleaseMask 
                  | EnterWindowMask
                  | LeaveWindowMask
                  | PointerMotionMask
                  | Button1MotionMask 
                  | Button2MotionMask 
                  | Button3MotionMask
                  | Button4MotionMask
                  | Button5MotionMask
                  | ButtonMotionMask
                  | KeymapStateMask
                  | ExposureMask
                  | VisibilityChangeMask
                  | StructureNotifyMask
                  /*| ResizeRedirectMask */
                  | SubstructureNotifyMask
                  | SubstructureRedirectMask
                  | FocusChangeMask
                  | PropertyChangeMask
                  | ColormapChangeMask
                  | OwnerGrabButtonMask;


        printf( "Getting matching framebuffer configs\n" );
        int fbcount;
        fbc = ::glXChooseFBConfig( disp->Disp(),
                        XScreenNumberOfScreen(disp->XDefaultScreenOfDisplay()->Screen()),
                        visual_attribs,
                        &fbcount );
        if ( !fbc )
        {
                printf( "Failed to retrieve a framebuffer config\n" );
                exit(1);
        }
        printf( "Found %d matching FB configs.\n", fbcount );

        // Pick the FB config/visual with the most samples per pixel
        printf( "Getting XVisualInfos\n" );
        int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

        int i;
        for ( i = 0; i < fbcount; i++ )
        {
                XVisualInfo *vi = glXGetVisualFromFBConfig( disp->Disp(), fbc[i] );
                if ( vi )
                {
                        int samp_buf, samples;
                        glXGetFBConfigAttrib( disp->Disp(), fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
                        glXGetFBConfigAttrib( disp->Disp(), fbc[i], GLX_SAMPLES       , &samples  );

                        printf( "  Matching fbconfig %d, visual ID 0x%2x: SAMPLE_BUFFERS = %d,"
                                        " SAMPLES = %d\n", 
                                        i, (int)(vi -> visualid), samp_buf, samples );

                        if ( best_fbc < 0 || samp_buf && samples > best_num_samp )
                                best_fbc = i, best_num_samp = samples;
                        if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
                                worst_fbc = i, worst_num_samp = samples;
                }
                XFree( vi );
        }

        // Get a visual
        fbc_id = best_fbc;
        //int fbc_id = worst_fbc;

        this->vi = glXGetVisualFromFBConfig( disp->Disp(), fbc[ fbc_id ]  );
        printf( "Chosen visual ID = 0x%x\n", (int)(this->vi->visualid) );

        printf( "Creating colormap\n" );
        XSetWindowAttributes swa;
        swa.colormap = XCreateColormap( disp->Disp(),
                        disp->XRootWindow( this->vi->screen )->GetWindowId(), 
                        this->vi->visual, AllocNone );
        swa.background_pixmap = None ;
        swa.border_pixel      = 0;
        swa.event_mask        = EventMask;

        printf( "Creating window\n" );
        _X11Window( parent_window, 
                        x, y, width, height, border_width, this->vi->depth, InputOutput, 
                        this->vi->visual, 
                        CWBorderPixel|CWColormap|CWEventMask, &swa );


}

void X11Window::_X11Window(NCRC_AutoPtr<_Window> parent_window,
                int x, int y,
                unsigned int width, unsigned int height,
                unsigned int border_width,
                int depth,
                unsigned int _class,
                Visual *visual,
                unsigned long valuemask,
                XSetWindowAttributes *attributes )
{
        window = XCreateWindow (disp->Disp(), parent_window->GetWindowId(),
                x, y,
                width, height,
                border_width,
                depth,
                _class,
                visual,
                valuemask,
                attributes );
        if ( !window )
                throw Exception(EINVAL,"Failed to create window.\n" );

        XSelectInput(disp->Disp(), window, EventMask);
        wm_protocols = ::XInternAtom(disp->Disp(), "WM_PROTOCOLS", False);
        wm_delete_window = ::XInternAtom(disp->Disp(), "WM_DELETE_WINDOW", False);
        XSetWMProtocols(disp->Disp(), window, &wm_delete_window, 1);

        hasContext=false;
        dirty=false;
}


X11Window::~X11Window()
{
        IN("\n");

        XFree(vi);
        XFree( fbc );

        ::XClientMessageEvent wakeup;
        wakeup.type = ClientMessage;
        wakeup.format = 32;
        wakeup.data.l[ 0 ] = XInternAtom(disp->Disp(), "WM_DELETE_WINDOW", False);

        this->XSendEvent ((XEvent&)wakeup); 
        OUT("\n");
}


int X11Window::start_routine()
{
        IN("\n");
        int err = 0;
        ::XEvent event;
        ::memset(&event,0,sizeof(event));

        while(this->thread_enabled && err == 0) 
        {
                if (dirty)
                {
                        ::XExposeEvent EventToForward;
                        //ask for redisplay of window
                        EventToForward.type=Expose;
                        EventToForward.send_event=true;
                        EventToForward.x = X();
                        EventToForward.y = Y();
                        EventToForward.width = Width();
                        EventToForward.height = Height();
                        AddEvent(&EventToForward);
                        dirty=False;
                }
                XNextEvent (disp->Disp(), &event);
                EventCoordToGLCoord(event);
                err = Container::AddEvent(&event);
        }
        this->thread_enabled = False;
        ROUT(err,"\n");


}

///////////////////////////////////////////////////////////////////////////////////
void X11Window::PostRedisplay()
{
        dirty=True;
}


int X11Window::XMapWindow()
{
        IN("\n");
        cerr << "XMapWindow" <<endl;
        int err;
        err = ::XMapWindow(disp->Disp(),window);
        if (err) ROUT(err,"\n");
        err = XFlush( disp->Disp() );
        ROUT(err,"\n");
              
}

int X11Window::XMapRaised()
{
        IN("\n");
        int err;
        err = ::XMapRaised(disp->Disp(),window);
        if (err) ROUT(err,"\n");
        err = XFlush( disp->Disp() );
        ROUT(err,"\n");
}

int X11Window::XMapSubwindows() 
{
        IN("\n");
        int err;
        err = ::XMapSubwindows(disp->Disp(),window);
        if (err) ROUT(err,"\n");
        err = XFlush( disp->Disp() );
        ROUT(err,"\n");
}

int X11Window::XUnmapWindow()
{
        IN("\n");
        cerr << "XUnmapWindow" <<endl;
        int err;
        err = ::XUnmapWindow(disp->Disp(),window);
        if (err) ROUT(err,"\n");
        err = XFlush( disp->Disp() );
        ROUT(err,"\n");
}

int X11Window::XUnmapSubwindows()
{
        IN("\n");
        int err;
        err = ::XUnmapSubwindows(disp->Disp(),window);
        if (err) ROUT(err,"\n");
        err = XFlush( disp->Disp() );
        ROUT(err,"\n");
}

KeySym  X11Window::XLookupKeysym(::XKeyEvent *key_event, int index)
{
        IN("\n");
        int err;
        err = ::XLookupKeysym(key_event, index);
        ROUT(err,"\n");
}

int X11Window::XSendEvent(::XEvent &evt)
{
        IN(" ");
        ::XAnyEvent *evtp = (::XAnyEvent*) &evt;
        
        evtp->display = disp->Disp(); ;
        evtp->window = window;
        EVTMSG(evt);

        ::XSendEvent (evtp->display, evtp->window, True, 0, &evt); 
        ::XFlush(evtp->display);
        ROUT(0,"\n");
}


/*
int X11Window::AddEvent(::XEvent *event)
{
        int err;
        IN("");
        EVTMSG((::XEvent) *event);
        switch (event->type)
        {
                case ClientMessage:
                        err = AddEvent((::XClientMessageEvent*) event); break;
                case MapNotify:
                        err = AddEvent((::XMapEvent*) event); break;
                case UnmapNotify:
                        err = AddEvent((::XUnmapEvent*) event); break;
                case CreateNotify:
                        err = AddEvent((::XCreateWindowEvent*) event); break;
                case ConfigureNotify:
                        err = AddEvent((::XConfigureEvent*) event); break;
                case Expose:
                        err = AddEvent((::XExposeEvent*) event); break;
                case ResizeRequest:
                        err = AddEvent((::XResizeRequestEvent*) event); break;
                case MappingNotify:
                        err = AddEvent((::XMappingEvent*) event); break;
                default: 
                        err = Container::AddEvent(event); break;
        }

        OUT("");
        ROUT(err,"\n");
}
*/

int X11Window::AddEvent(::XClientMessageEvent *event)
{
        IN(debug::Instance()->EventTypeToString(event->type)<<endl);
        /* Destroy the window when the WM_DELETE_WINDOW message arrives */
        if( (Atom) event->data.l[ 0 ] == XInternAtom(disp->Disp(), "WM_DELETE_WINDOW", False))
        {
                int res = XDestroyWindow(disp->Disp(), window);
                this->thread_enabled = false;
                if ( res ) ROUT(res,"\n");
                window = 0;
                ROUT(res,"\n");
        }
        ROUT(0,"\n");
}

int X11Window::AddEvent(::XMappingEvent *event)
{
        // man XRefreshKeyboardMapping
        //       The XRefreshKeyboardMapping function refreshes the stored modifier and keymap information.  You usually call this
        //       function when a MappingNotify event with a request member of MappingKeyboard or MappingModifier occurs.  The result
        //       is to update Xlib’s knowledge of the keyboard.
        int err;
        IN(debug::Instance()->EventTypeToString(event->type)<<endl);
        XRefreshKeyboardMapping( (XMappingEvent *) event );
        err = Container::AddEvent(event);
        ROUT(err,"\n");
}

int X11Window::AddEvent(::XMapEvent *event)
{
        int err;
        IN(debug::Instance()->EventTypeToString(event->type)<<endl);
        printf( "Making context current\n" );
        if(this->hasContext == false) 
        {
                CreateGLContext();
                this->hasContext = true;
        }
        err = glXMakeCurrent( disp->Disp(), window, ctx );
        err = Container::AddEvent(event);
        mapped = True;
        ROUT(err,"\n");
}

int X11Window::AddEvent(::XUnmapEvent *event)
{
        int err;
        IN(debug::Instance()->EventTypeToString(event->type)<<endl);
        printf( "unsetting context\n" );
        err = glXMakeCurrent( disp->Disp(), None, NULL );
        err = Container::AddEvent(event);
        ROUT(err,"\n");
}

int X11Window::AddEvent(::XCreateWindowEvent *event)
{
        int err;
        IN(debug::Instance()->EventTypeToString(event->type)<<endl);
        set_size( Size((unsigned int)event->width,(unsigned int)event->height) );
        err = Container::AddEvent(event);
        ROUT(err,"");
}

int X11Window::AddEvent(::XConfigureEvent *event)
{
        int err;
        IN(debug::Instance()->EventTypeToString(event->type)<<endl);
        set_size( Size((unsigned int)event->width,(unsigned int)event->height) );
        err = Container::AddEvent(event);
        ROUT(err,"\n");
}


int X11Window::AddEvent(::XExposeEvent* event)
{
        int err;
        IN(debug::Instance()->EventTypeToString(event->type)<<endl);
        //err = glXMakeCurrent( disp->Disp(), window, ctx );        
        err = _Window::AddEvent(event);
        switch (get_buffer_mode()) {
                case buffer_front: // Make sure drawing gets to screen
                        glFlush();
                        break;
                case buffer_back: // Bring back buffer to front
                        glXSwapBuffers ( disp->Disp(), this->window );
                        break;
        }

        ROUT(err,"\n");
}

int X11Window::AddEvent(::XResizeRequestEvent *event)
{
        int err;
        IN(debug::Instance()->EventTypeToString(event->type)<<endl);
        set_size( Size((unsigned int)event->width,(unsigned int)event->height) );
        err = _Window::AddEvent(event);
        ROUT(err,"\n");
}

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(::Display*, GLXFBConfig, GLXContext, Bool, const int*);
int X11Window::CreateGLContext()
{
        // See if GL driver supports glXCreateContextAttribsARB()
        //   Create an old-style GLX context first, to get the correct function ptr.
        ::glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;

        glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
                glXGetProcAddress( (const GLubyte *) "glXCreateContextAttribsARB" );

        ctx = 0;

        // If it doesn't, just use the old-style 2.x GLX context
        if ( !glXCreateContextAttribsARB )
        {
                printf( "glXCreateContextAttribsARB() not found\n");
        }

        // If it "does", try to get a GL 3.0 context!
        else
        {
                glXMakeCurrent( disp->Disp(), 0, 0 );

                static int context_attribs[] =
                {
                        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                        GLX_CONTEXT_MINOR_VERSION_ARB, 0,
                        //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                        None
                };

                printf( "Creating context\n" );
                ctx = glXCreateContextAttribsARB( disp->Disp(), fbc[ fbc_id ], 0, 
                                True, context_attribs );
                if ( ctx )
                        printf( "Created GL 3.0 context\n" );
                else
                {
                        // Couldn't create GL 3.0 context.  Fall back to old-style 2.x context.
                        printf( "Failed to create GL 3.0 context");
                }
        }
        if (!ctx)
        {
                printf( " ... using old-style GLX context\n" );
                ctx = glXCreateContext( disp->Disp(), this->vi, 0, True );
        }


        if (!ctx )
                throw Exception(ENOTSUP,"Failed to create GLX context.\n");

        // Verifying that context is a direct context
        printf( "Verifying that context is direct\n" );
        if ( ! glXIsDirect ( disp->Disp(), ctx ) )
        {
                printf( "Indirect GLX rendering context obtained" );
        }

}


void X11Window::EventCoordToGLCoord(::XEvent& evt)
{
        int* X;
        int* Y;
        switch (evt.type)
        {
                case KeyPress :
                case KeyRelease:
                        {
                                ::XKeyEvent* event = (::XKeyEvent*) &evt;
                                X = &(event->x);
                                Y = &(event->y);
                                break;
                        }
                case ButtonPress:
                case ButtonRelease:
                        {
                                ::XButtonEvent* event = (::XButtonEvent*) &evt;
                                X = &(event->x);
                                Y = &(event->y);
                                break;
                        }
                case EnterNotify:
                case LeaveNotify:
                        {
                                ::XCrossingEvent* event = (::XCrossingEvent*) &evt;
                                X = &(event->x);
                                Y = &(event->y);
                                break;
                        }
                case GraphicsExpose:
                        {
                                ::XGraphicsExposeEvent* event = (::XGraphicsExposeEvent*) &evt;
                                X = &(event->x);
                                Y = &(event->y);
                                break;
                        }
                case ReparentNotify: 
                        {
                                ::XReparentEvent* event = (::XReparentEvent*) &evt;
                                X = &(event->x);
                                Y = &(event->y);
                                break;
                        }
                case ConfigureNotify: 
                        {
                                ::XConfigureEvent* event = (::XConfigureEvent*)&evt;
                                X = &(event->x);
                                Y = &(event->y);
                                break;
                        }
                case GravityNotify: 
                        {
                                ::XGravityEvent* event = (::XGravityEvent*)&evt;
                                X = &(event->x);
                                Y = &(event->y);
                                break;
                        }
                case ConfigureRequest: 
                        {
                                ::XConfigureRequestEvent* event = (::XConfigureRequestEvent*)&evt;
                                X = &(event->x);
                                Y = &(event->y);
                                break;
                        }
                default :
                        return;
        }
        *Y = this->Height() - *Y;
}
