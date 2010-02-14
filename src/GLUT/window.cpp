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
#include <GL/glui/window.h>
#include <GL/glui/MasterObject.h>
#include <GL/glui/debug.h>
#include <GL/glui/themes.h>

#define XK_MISCELLANY
#define XK_LATIN1
#include <X11/keysymdef.h>
using namespace GLUI;

#define MODULE_KEY  "GLUI_DEBUG_GLUTWINDOW"

///////////////////////////////////////////////////////////////////////
bool GlutWindow::glutinitialized = false;
pthread_mutex_t GlutWindow::glut_mutex = PTHREAD_MUTEX_INITIALIZER;
///////////////////////////////////////////////////////////////////////
GlutDisplay::GlutDisplay(char* name)
{
}

///////////////////////////////////////////////////////////////////////
WindowId GlutWindow::GetWindowId()
{
    return GlutWindowId;
}


///////////////////////////////////////////////////////////////////////
int GlutScreen::Depth()
{
#warning "implement real Depth check"
    return 24;
}

//////////////////////////////////////////////////////////////////////
WindowId GlutScreen::RootWindow()
{
     return 0;
}

///////////////////////////////////////////////////////////////////////
_Screen* GlutDisplay::DefaultScreen()
{
    return     &defaultscreen;
}


///////////////////////////////////////////////////////////////////////
void  GlutWindow::XMapWindow()
{
        MasterObject::Instance()->pack(0, 0); //repack all master windows
        int err = pthread_mutex_lock (&glut_mutex);
        if (err)
        {
                throw Exception(err,"glut_mutex locking error");
        }
        else
        {

                glutSetWindow(GlutWindowId);
                glutShowWindow();
                mapped = true;
                pthread_mutex_unlock (&glut_mutex);
        }
        ::XExposeEvent expose;
        expose.type = Expose;
        this->AddEvent(&expose);
}
///////////////////////////////////////////////////////////////////////////////
void GlutWindow::XMapRaised()
{
#warning "TODO"
}
///////////////////////////////////////////////////////////////////////////////
void GlutWindow::XMapSubwindows()
{
#warning "TODO"
}

///////////////////////////////////////////////////////////////////////
void GlutWindow::XUnmapWindow( void )
{
        if (mapped)
        {
                this->focussed = NULL;
                int err = pthread_mutex_lock (&glut_mutex);
                if (err)
                {
                        throw Exception(err,"glut_mutex locking error");
                }
                else
                {

                        glutSetWindow(GlutWindowId);
                        glutHideWindow();
                        mapped      = false;
                        pthread_mutex_unlock (&glut_mutex);
                }
        }
}
///////////////////////////////////////////////////////////////////////////////
void GlutWindow::XUnmapSubwindows()
{
#warning "TODO"
}



//////////////////////////////////////////////////////////////////////
GlutWindow::GlutWindow(Display* display, WindowId parent,
        int x, int y,
        unsigned int width, unsigned int height,
        unsigned int border_width,
        int depth,
        class_type _class,
        Visual *visual,
        unsigned long valuemask,
        XSetWindowAttributes *attributes )
{
    _GlutWindow(display, parent, x, y,
        width, height, border_width, depth,
        _class, visual, valuemask,
        attributes );
}
///////////////////////////////////////////////////////////////////////////////
GlutWindow::GlutWindow(Display *display, WindowId parent,
        int x, int y,
        unsigned int width, unsigned int height,
        unsigned int border_width,
        unsigned long border,
        unsigned long background )
{
    _GlutWindow(display, parent,
        x, y,
        width, height,
        border_width,
        24, //int depth,
        InputOutputWin, //class_type _class,
        NULL, //Visual *visual,
        0, //unsigned long valuemask,
        NULL); // XSetWindowAttributes *attributes )
}

#warning "TODO: copy constructor using WindowId, throw EINVAL if already registered"
///////////////////////////////////////////////////////////////////////////////
int GlutWindow::_GlutWindow(Display* display, WindowId parent,
                int x, int y,
                unsigned int width, unsigned int height,
                unsigned int border_width,
                int depth,
                class_type _class,
                Visual *visual,
                unsigned long valuemask,
                XSetWindowAttributes *attributes )
{
        GlutWindow* win= MasterObject::Instance()->FindWindow(parent);
        mapped      = false;
        y_off_top   = 0;
        y_off_bot   = 0;
        x_off_left  = 0;
        x_off_right = 0;
        {
                int argc=1;
                char* argv[1] = { "glutnoname" };
                GlutWindow::init(&argc, argv);
        }
        int err = pthread_mutex_lock (&glut_mutex);
        if (err)
        {
                throw Exception(err,"glut_mutex locking error");
        }
        else
        {
                if ( win == NULL ) {  // not a subwindow, creating a new top-level window
                        int old_glut_window = glutGetWindow();

                        glutInitWindowSize( width, height);
                        if ( x >= 0 || y >= 0 )
                                glutInitWindowPosition( x, y );
                        glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
                        this->GlutWindowId = glutCreateWindow(" ");


                        if ( old_glut_window > 0 )
                                glutSetWindow( old_glut_window );
                        else
                                glutSetWindow(GlutWindowId);

                }
                else // *is* a subwindow
                {
                        int old_glut_window = glutGetWindow();

                        GlutWindowId = glutCreateSubWindow(win->GetWindowId(), x, y, width, height);
                        win->add_control(this);

                        if ( old_glut_window > 0 )
                                glutSetWindow( old_glut_window );

                }
                //init glut callbacks
                glutDisplayFunc (display_func);
                glutReshapeFunc (reshape_func);
                glutKeyboardFunc (keyboard_func);
                glutSpecialFunc (special_func);
                glutMouseFunc (mouse_func);
                glutMotionFunc (motion_func);
                glutPassiveMotionFunc (passive_motion_func);
                glutEntryFunc (entry_func);
                glutVisibilityFunc (visibility_func);
                glutIdleFunc (idle_func);

                pthread_mutex_unlock (&glut_mutex);
        }
        int rc = MasterObject::Instance()->add_control(this);
        if (rc)
        {
                throw rc;
        }
        if (width != 0  && height != 0)
        {
                set_resize_policy(FixedSize);
                set_size(Size(width, height));
        }
        else
        {
                update_size();
                pack(x,y);
        }
        Start(NULL);

}
///////////////////////////////////////////////////////////////////////////////
int GlutWindow::start_routine(void* args)
{
        int res=0;
        glutMainLoop ();
        return res;
}
///////////////////////////////////////////////////////////////////////////////
GlutWindow::~GlutWindow()
{
        GlutWindow::XUnmapWindow();
        int err = pthread_mutex_lock (&glut_mutex);
        if (err)
        {
                throw Exception(err,"glut_mutex locking error");
        }
        else
        {
                glutDestroyWindow(this->GlutWindowId);
                pthread_mutex_unlock(&glut_mutex);
        }
        //child deletion is performed by ~Container
}
///////////////////////////////////////////////////////////////////////////////
int GlutWindow::init(int* argc, char** argv)
{
  if(glutinitialized == false)
    {
        glutInit(argc, argv);
        glutinitialized = true;
        int err = pthread_mutex_init (&glut_mutex, NULL);
    }

}

int GLUIInit(int* argc, char** argv)
{
   return GlutWindow::init(argc, argv);
}

///////////////////////////////////////////////////////////////////////////////
int GlutWindow::AddEvent(::XResizeRequestEvent *event)
{
        int err;
    IN("");
    this->pack(x, y);

    if ( event->width  != this->CurrentSize.size.w ||
                    event->height != this->CurrentSize.size.h ) {
            this->CurrentSize.size.w = event->width;
            this->CurrentSize.size.h = event->height;
            err = pthread_mutex_lock (&glut_mutex);
            if (err)
            {
                    throw Exception(err,"glut_mutex locking error");
            }
            else
            {
                    glutSetWindow( this->GlutWindowId );
                    MSG("%d: %d\n", glutGetWindow(), this->flags );
                    glutReshapeWindow( this->CurrentSize.size.w, this->CurrentSize.size.h );
                    pthread_mutex_unlock(&glut_mutex);
            }
    }
    else {
    }

    glViewport( 0, 0, this->CurrentSize.size.w, this->CurrentSize.size.h);

    err = pthread_mutex_lock (&glut_mutex);
    if (err)
    {
            throw Exception(err,"glut_mutex locking error");
    }
    else
    {
            glutPostRedisplay();
            pthread_mutex_unlock(&glut_mutex);
    }
    OUT("");
    return 0;
}


int GlutWindow::AddEvent(::XExposeEvent *event)
{
        IN("");
        int err = pthread_mutex_lock (&glut_mutex);
        if (err)
        {
                throw Exception(err,"glut_mutex locking error");
        }
        else
        {
                if (mapped)
                {
                        int       win_w, win_h;

                        // SUBTLE: on freeGLUT, the correct window is always already set.
                        // But older versions of GLUT need this call, or else subwindows
                        // don't update properly when resizing or damage-painting.
                        glutSetWindow( this->GlutWindowId );
                        // Check here if the window needs resizing
                        win_w = glutGet( GLUT_WINDOW_WIDTH );
                        win_h = glutGet( GLUT_WINDOW_HEIGHT );
                        if ( win_w != this->Width() || win_h != this->Height() ) {
                                glutReshapeWindow( this->Width(), this->Height() );
                        }
                        _Window::AddEvent(event);
                        switch (get_buffer_mode()) {
                                case buffer_front: // Make sure drawing gets to screen
                                        glFlush();
                                        break;
                                case buffer_back: // Bring back buffer to front
#warning "check how other *GL are doing swapbuffer"
                                        glutSwapBuffers();
                                        break;
                        }
                        glutPostRedisplay();
                }
                pthread_mutex_unlock(&glut_mutex);
        }

        OUT("");
        return 0;
}



int GlutWindow::set_size( Size sz, Size min) //replace with a XResizeRequestEvent
{
        Control::set_size(sz,min);
        int err = pthread_mutex_lock (&glut_mutex);
        if (err)
        {
                throw Exception(err,"glut_mutex locking error");
        }
        else
        {
                glutReshapeWindow( this->Width(), this->Height() );
                pthread_mutex_unlock(&glut_mutex);
        }

}



/********************************************** glui_display_func() ********/
void GlutWindow::display_func (void)
{
    ::XExposeEvent event;
        event.type   = Expose;
    IN("");
    GlutWindow* win;
    int err = pthread_mutex_lock (&glut_mutex);
    if (err)
    {
            throw Exception(err,"glut_mutex locking error");
    }
    else
    {
            win= MasterObject::Instance()->FindWindow(glutGetWindow ());
            pthread_mutex_unlock(&glut_mutex);
    }
    if (win)
    {
        win->AddEvent(&event);
    }
    OUT("");
}



/********************************************** glui_reshape_func() ********/
void GlutWindow::reshape_func (int w, int h)
{
    ::XResizeRequestEvent event;
        event.type   = ResizeRequest;
        event.width  = w;
        event.height = h;

    IN("");

    /***  First check if this is main glut window ***/
    GlutWindow* win;
    int err = pthread_mutex_lock (&glut_mutex);
    if (err)
    {
            throw Exception(err,"glut_mutex locking error");
    }
    else
    {
            win= MasterObject::Instance()->FindWindow(glutGetWindow ());
            pthread_mutex_unlock(&glut_mutex);
    }
    if (win)
    {
        win->AddEvent(&event);
    }
    OUT("");
}





#warning "factorise"
/********************************************** glui_keyboard_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::keyboard_func (unsigned char key, int x, int y)
{
	int win_w;
	int win_h;
	::XKeyEvent event;
	GlutWindow* win;
    IN("");
    int err = pthread_mutex_lock (&glut_mutex);
    if (err)
    {
            throw Exception(err,"glut_mutex locking error");
    }
    else
    {
	    int win_w = glutGet (GLUT_WINDOW_WIDTH);
	    int win_h = glutGet (GLUT_WINDOW_HEIGHT);
	    y = win_h - y;
	    event.type=KeyPress;
	    event.keycode=key; //first 256 char are reserved for non modifier keys
	    event.x=x;
	    event.y=y;
	    win= MasterObject::Instance()->FindWindow(glutGetWindow ());
            pthread_mutex_unlock(&glut_mutex);
    }


    if (win)
    {
        MSG("key: %d(%d,%d) modifier %d\n", key, x, y, glutGetModifiers());
        event.state=win->KeyModifierState;
        dynamic_cast<_Window*>(win)->AddEvent(&event);
    }
    OUT("");
}


/************************************************ glui_special_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::special_func (int key, int x, int y)
{

    int win_w;
    int win_h;
    int glutModifiers;
    ::XKeyEvent event;

    GlutWindow* win;
    int err = pthread_mutex_lock (&glut_mutex);
    if (err)
    {
            throw Exception(err,"glut_mutex locking error");
    }
    else
    {
            win= MasterObject::Instance()->FindWindow(glutGetWindow ());
            win_w = glutGet (GLUT_WINDOW_WIDTH);
            win_h = glutGet (GLUT_WINDOW_HEIGHT);
            y = win_h - y;
            event.type = KeyPress;
            event.keycode = key << KeyModifierShift ; //first 256 char are reserved for non modifier keys
            event.x = x;
            event.y = y;
            pthread_mutex_unlock(&glut_mutex);
    }

    if (win)
    {
            win->KeyModifierState &= ! ( ControlMask | ShiftMask | Mod1Mask );
            if ( glutModifiers | GLUT_ACTIVE_SHIFT ) win->KeyModifierState | ShiftMask;
            if ( glutModifiers | GLUT_ACTIVE_CTRL  ) win->KeyModifierState | ControlMask;
            if ( glutModifiers | GLUT_ACTIVE_ALT   ) win->KeyModifierState | Mod1Mask;

            MSG("key: %d(%d,%d) modifier %d\n", key, x, y, glutModifiers/*win->KeyModifierState*/);
            event.state=win->KeyModifierState;
            dynamic_cast<_Window*>(win)->AddEvent(&event);

    }
}

/********************************************** glui_mouse_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::mouse_func (int button, int state, int x, int y)
{
    int win_w;
    int win_h;
    int glutModifiers;

    ::XButtonEvent event;

    GlutWindow* win;
    int err = pthread_mutex_lock (&glut_mutex);
    if (err)
    {
            throw Exception(err,"glut_mutex locking error");
    }
    else
    {
            win= MasterObject::Instance()->FindWindow(glutGetWindow ());
            win_w = glutGet (GLUT_WINDOW_WIDTH);
            win_h = glutGet (GLUT_WINDOW_HEIGHT);
            y = win_h - y;
            event.type = ButtonPressMask;
            event.button = button ; //first 256 char are reserved for non modifier keys
            event.x = x;
            event.y = y;
            pthread_mutex_unlock(&glut_mutex);
    }

    if (win)
    {
        if (state == GLUT_DOWN)
        {
            event.type = ButtonPress;
            win->KeyModifierState |= (Button1Mask << ( button - Button1 ) );
        }
        else
        {
            event.type = ButtonRelease;
            win->KeyModifierState &= ! (Button1Mask << ( button - Button1 ) );
        }
        win->KeyModifierState &= ! ( ControlMask | ShiftMask | Mod1Mask );
        if ( glutModifiers | GLUT_ACTIVE_SHIFT ) win->KeyModifierState | ShiftMask;
        if ( glutModifiers | GLUT_ACTIVE_CTRL  ) win->KeyModifierState | ControlMask;
        if ( glutModifiers | GLUT_ACTIVE_ALT   ) win->KeyModifierState | Mod1Mask;

        event.state=win->KeyModifierState;
        dynamic_cast<_Window*>(win)->AddEvent(&event);
    }
}


/********************************************** glui_motion_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::motion_func (int x, int y)
{
	int win_w;
	int win_h;

	::XMotionEvent event;
	GlutWindow* win;
    int err = pthread_mutex_lock (&glut_mutex);
    if (err)
    {
            throw Exception(err,"glut_mutex locking error");
    }
    else
    {
	    win_w = glutGet (GLUT_WINDOW_WIDTH);
	    win_h = glutGet (GLUT_WINDOW_HEIGHT);
	    y = win_h - y;
	    event.type = MotionNotify;
	    event.x=x;
	    event.y=y;
            win= MasterObject::Instance()->FindWindow(glutGetWindow ());
            pthread_mutex_unlock(&glut_mutex);
    }

    if (win)
    {
        event.state=win->KeyModifierState;
        dynamic_cast<_Window*>(win)->AddEvent(&event);
    }
}


/**************************************** glui_passive_motion_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::passive_motion_func (int x, int y)
{
    motion_func (x,y);
}


/********************************************** glui_entry_func() ********/
void GlutWindow::entry_func (int state)
{
    ::XCrossingEvent event;
    if ( state == GLUT_LEFT )
    {
        event.type = EnterNotify;
    }
    else
    {
        event.type = LeaveNotify;
    }
#warning "complete the structure with other information"

    GlutWindow* win;
    int err = pthread_mutex_lock (&glut_mutex);
    if (err)
    {
            throw Exception(err,"glut_mutex locking error");
    }
    else
    {
            win= MasterObject::Instance()->FindWindow(glutGetWindow ());
            pthread_mutex_unlock(&glut_mutex);
    }

    if (win)
    {
        event.state=win->KeyModifierState;
        dynamic_cast<_Window*>(win)->AddEvent(&event);
    }

}




/******************************************** glui_visibility_func() ********/
void GlutWindow::visibility_func (int state)
{
    ::XMapEvent mapevent;
    ::XUnmapEvent unmapevent;

    mapevent.type = MapNotify;
    unmapevent.type = UnmapNotify;
    #warning "complete the structure with other information"


    IN("");
    /*  fflush( stdout );          */
    GlutWindow* win;
    int err = pthread_mutex_lock (&glut_mutex);
    if (err)
    {
            throw Exception(err,"glut_mutex locking error");
    }
    else
    {
            win= MasterObject::Instance()->FindWindow(glutGetWindow ());
            pthread_mutex_unlock(&glut_mutex);
    }

    if (win)
    {
        if ( state == GLUT_VISIBLE )
        {
            dynamic_cast<_Window*>(win)->AddEvent(&mapevent);
        }
        else
        {
            dynamic_cast<_Window*>(win)->AddEvent(&unmapevent);
        }
    }
    OUT("");


}


/********************************************** glui_idle_func() ********/
/* Send idle event to each glui, then to the main window            */
void GlutWindow::idle (void)
{
        struct timespec sleeptime = { 0, 100000000 };
        nanosleep(&sleeptime, NULL);
}


void GlutWindow::idle_func (void)
{
        GlutWindow* win;
    int err = pthread_mutex_lock (&glut_mutex);
    if (err)
    {
            throw Exception(err,"glut_mutex locking error");
    }
    else
    {
            win= MasterObject::Instance()->FindWindow(glutGetWindow ());
            pthread_mutex_unlock(&glut_mutex);
    }

    if (win)
    {
        win->idle();
    }

}

////////////////////////////////////////////////////////////////////
KeySym GlutWindow::XLookupKeysym(::XKeyEvent *key_event, int index)
{
/*    switch (key_event->keycode)
    {

        case GLUT_KEY_F1 << KeyModifierShift : return XK_F1;
        case GLUT_KEY_F2 << KeyModifierShift : return XK_F2;
        case GLUT_KEY_F3 << KeyModifierShift : return XK_F3;
        case GLUT_KEY_F4 << KeyModifierShift : return XK_F4;
        case GLUT_KEY_F5 << KeyModifierShift : return XK_F5;
        case GLUT_KEY_F6 << KeyModifierShift : return XK_F6;
        case GLUT_KEY_F7 << KeyModifierShift : return XK_F7;
        case GLUT_KEY_F8 << KeyModifierShift : return XK_F8;
        case GLUT_KEY_F9 << KeyModifierShift : return XK_F9;
        case GLUT_KEY_F10 << KeyModifierShift : return XK_F10;
        case GLUT_KEY_F11 << KeyModifierShift : return XK_F11;
        case GLUT_KEY_F12 << KeyModifierShift : return XK_F12;
        case GLUT_KEY_UP << KeyModifierShift : return XK_Up;
        case GLUT_KEY_RIGHT << KeyModifierShift : return XK_Right;
        case GLUT_KEY_DOWN << KeyModifierShift : return XK_Down;
        case GLUT_KEY_PAGE_UP << KeyModifierShift : return XK_Page_Up;
        case GLUT_KEY_PAGE_DOWN << KeyModifierShift : return XK_Page_Down;
        case GLUT_KEY_HOME << KeyModifierShift : return XK_Home;
        case GLUT_KEY_END << KeyModifierShift : return XK_End;
        case GLUT_KEY_INSERT << KeyModifierShift : return XK_Insert;
        case ' ' : return XK_space;
        case '!' : return XK_exclam;
        case '"' : return XK_quotedbl;
        case '#' : return XK_numbersign;
        case '$' : return XK_dollar;
        case '%' : return XK_percent;
        case '&' : return XK_ampersand;
        case '\'': return XK_apostrophe;
        case '(' : return XK_parenleft;
        case ')' : return XK_parenright;
        case '*' : return XK_asterisk;
        case '+' : return XK_plus;
        case ',' : return XK_comma;
        case '-' : return XK_minus;
        case '.' : return XK_period;
        case '/' : return XK_slash;
        case '0' : return XK_0;
        case '1' : return XK_1;
        case '2' : return XK_2;
        case '3' : return XK_3;
        case '4' : return XK_4;
        case '5' : return XK_5;
        case '6' : return XK_6;
        case '7' : return XK_7;
        case '8' : return XK_8;
        case '9' : return XK_9;
        case ':' : return XK_colon;
        case ';' : return XK_semicolon;
        case '<' : return XK_less;
        case '=' : return XK_equal;
        case '>' : return XK_greater;
        case '?' : return XK_question;
        case '@' : return XK_at;
        case 'A' : return XK_A;
        case 'B' : return XK_B;
        case 'C' : return XK_C;
        case 'D' : return XK_D;
        case 'E' : return XK_E;
        case 'F' : return XK_F;
        case 'G' : return XK_G;
        case 'H' : return XK_H;
        case 'I' : return XK_I;
        case 'J' : return XK_J;
        case 'K' : return XK_K;
        case 'L' : return XK_L;
        case 'M' : return XK_M;
        case 'N' : return XK_N;
        case 'O' : return XK_O;
        case 'P' : return XK_P;
        case 'Q' : return XK_Q;
        case 'R' : return XK_R;
        case 'S' : return XK_S;
        case 'T' : return XK_T;
        case 'U' : return XK_U;
        case 'V' : return XK_V;
        case 'W' : return XK_W;
        case 'X' : return XK_X;
        case 'Y' : return XK_Y;
        case 'Z' : return XK_Z;
        case '[' : return XK_bracketleft;
        case '\\': return XK_backslash;
        case ']' : return XK_bracketright;
        case '^' : return XK_asciicircum;
        case '_' : return XK_underscore;
        case '`' : return XK_grave;
        case 'a' : return XK_a;
        case 'b' : return XK_b;
        case 'c' : return XK_c;
        case 'd' : return XK_d;
        case 'e' : return XK_e;
        case 'f' : return XK_f;
        case 'g' : return XK_g;
        case 'h' : return XK_h;
        case 'i' : return XK_i;
        case 'j' : return XK_j;
        case 'k' : return XK_k;
        case 'l' : return XK_l;
        case 'm' : return XK_m;
        case 'n' : return XK_n;
        case 'o' : return XK_o;
        case 'p' : return XK_p;
        case 'q' : return XK_q;
        case 'r' : return XK_r;
        case 's' : return XK_s;
        case 't' : return XK_t;
        case 'u' : return XK_u;
        case 'v' : return XK_v;
        case 'w' : return XK_w;
        case 'x' : return XK_x;
        case 'y' : return XK_y;
        case 'z' : return XK_z;
        case '{' : return XK_braceleft;
        case '|' : return XK_bar;
        case '}' : return XK_braceright;
        case '~' : return XK_asciitilde;
        default: return XK_VoidSymbol;

    }
*/
}

