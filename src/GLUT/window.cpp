/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

  glui_glut_window.cpp : a wrapper class to use glut as an event generator

  --------------------------------------------------

  Copyright (c) 2008 MALET Jean-Luc

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

 *****************************************************************************/
#if defined(GLUI_FREEGLUT)

// FreeGLUT does not yet work perfectly with GLUI
//  - use at your own risk.

#include <GL/freeglut.h>

#elif defined(GLUI_OPENGLUT)

// OpenGLUT does not yet work properly with GLUI
//  - use at your own risk.

#include <GL/openglut.h>

#else

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#endif
#include <GL/glui/glut_window.h>
#include <GL/glui/MasterObject.h>
#include <GL/glui/debug.h>
#include <GL/glui/themes.h>
#include <GL/glui/drawinghelpers.h>
using namespace GLUI;

#define MODULE_KEY  "GLUI_DEBUG_GLUTWINDOW"

///////////////////////////////////////////////////////////////////////
GlutDisplay::GlutDisplay(char* name)
{
}
///////////////////////////////////////////////////////////////////////
void GlutWindow::draw()
{
    //    Draw GLUI window
    glLoadIdentity();
    this->SetOrthoProjection();
    glTranslatef(x, y, BOTTOM_VIEWPORT + 1);
    drawinghelpers::draw_box( this->Width(),
            this->Height());
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
//

bool GlutWindow::glutinitialized = false;

///////////////////////////////////////////////////////////////////////
void  GlutWindow::XMapWindow()
{
  glutSetWindow(GlutWindowId);
  MasterObject::Instance()->pack(0, 0); //repack all master windows
  glutShowWindow();
  mapped = true;
  drawinghelpers::PostRedisplay(this);
}

void GlutWindow::XMapRaised()
{
#warning "TODO"
}

void GlutWindow::XMapSubwindows()
{
#warning "TODO"
}

///////////////////////////////////////////////////////////////////////
void GlutWindow::XUnmapWindow( void )
{
  this->focussed = NULL;
  glutSetWindow(GlutWindowId);
  glutHideWindow();
}

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

}

GlutWindow::~GlutWindow()
{
#warning "Todo : delete childs. close the window"
}

int GlutWindow::init(int* argc, char** argv)
{
  if(glutinitialized == false)
    {
        glutInit(argc, argv);
        glutinitialized = true;
    }

}

int GLUIInit(int* argc, char** argv)
{
   return GlutWindow::init(argc, argv);
}

///////////////////////////////////////////////////////////////////////////////
int GlutWindow::AddEvent (::XEvent *event)
{
    switch (event->type)
    {
        case Expose : return AddEvent((::XExposeEvent*) event);
        case DestroyNotify :  return AddEvent((::XDestroyWindowEvent*) event);
        case ResizeRequest: return AddEvent((::XResizeRequestEvent*) event);
    }

    return EINVAL;
}

int GlutWindow::AddEvent(::XResizeRequestEvent *event)
{
    IN("");
    this->pack(x, y);

    if ( event->width  != this->CurrentSize.size.w ||
            event->height != this->CurrentSize.size.h ) {
        this->CurrentSize.size.w = event->width;
        this->CurrentSize.size.h = event->height;
        glutSetWindow( this->GlutWindowId );
        glutReshapeWindow( this->CurrentSize.size.w, this->CurrentSize.size.h );
    }
    else {
    }

    glViewport( 0, 0, this->CurrentSize.size.w, this->CurrentSize.size.h);

    MSG("%d: %d\n", glutGetWindow(), this->flags );

    glutPostRedisplay();
    OUT("");
    return 0;
}


int GlutWindow::AddEvent(::XExposeEvent *event)
{
    IN("");
    if (mapped)
    {
        int       win_w, win_h;

        // SUBTLE: on freeGLUT, the correct window is always already set.
        // But older versions of GLUT need this call, or else subwindows
        // don't update properly when resizing or damage-painting.
        glutSetWindow( this->GlutWindowId );

        // Set up OpenGL state for widget drawing
        glEnable( GL_DEPTH_TEST );
        glDepthFunc(GL_LEQUAL);
        //glCullFace( GL_BACK );
        //glDisable( GL_CULL_FACE );
        glEnable ( GL_COLOR_MATERIAL );
        glEnable ( GL_NORMALIZE );
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glShadeModel(GL_SMOOTH);

        theme::Instance()->DoLightning();
        SetOrthoProjection();


        this->SetCurrentDrawBuffer();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

        //update sizes and positions
        this->update_size();

        // Check here if the window needs resizing
        win_w = glutGet( GLUT_WINDOW_WIDTH );
        win_h = glutGet( GLUT_WINDOW_HEIGHT );
        if ( win_w != this->Width() || win_h != this->Height() ) {
            glutReshapeWindow( this->Width(), this->Height() );
        }

        Container::AddEvent (event);

        switch (drawinghelpers::get_buffer_mode()) {
            case drawinghelpers::buffer_front: // Make sure drawing gets to screen
                glFlush();
                break;
            case drawinghelpers::buffer_back: // Bring back buffer to front
                glutSwapBuffers();
                break;
        }
        glutPostRedisplay();
    }
    OUT("");
    return 0;
}

int GlutWindow::AddEvent(::XDestroyWindowEvent *event)
{
#warning "USE container destructor"
    Node* child = first_child();
    while (child)
    {
        Node* next = child->next();
        delete child;
        child = next;
    }
    delete this;
    return 0;
}


int GlutWindow::AddEvent(::XKeyEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int GlutWindow::AddEvent(::XButtonEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int GlutWindow::AddEvent(::XMotionEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int GlutWindow::AddEvent(::XCrossingEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int GlutWindow::AddEvent(::XMapEvent* event)
{
    ::XExposeEvent expose;
    expose.type = Expose;
    Container::AddEvent((::XEvent*) event);
    this->AddEvent(&expose);
}


int GlutWindow::AddEvent(::XUnmapEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}

int GlutWindow::set_size( Size sz, Size min) //replace with a XResizeRequestEvent
{
    Control::set_size(sz,min);
    glutReshapeWindow( this->Width(), this->Height() );
}




/********************************************** glui_display_func() ********/
void GlutWindow::display_func (void)
{
    ::XExposeEvent event;
        event.type   = Expose;
    IN("");
    GlutWindow* win= MasterObject::Instance()->FindWindow(glutGetWindow ());

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
    GlutWindow* glut_window = MasterObject::Instance()->FindWindow(glutGetWindow ());
    if (glut_window)
    {
        glut_window->AddEvent(&event);
    }
    OUT("");
}





#warning "factorise
/********************************************** glui_keyboard_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::keyboard_func (unsigned char key, int x, int y)
{

    IN("");
    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);
    y = win_h - y;
    ::XKeyEvent event;
    event.type=KeyPress;
    event.keycode=key; //first 256 char are reserved for non modifier keys
    event.x=x;
    event.y=y;

    int current_window = glutGetWindow ();
    GlutWindow* glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    MSG("key: %d\n", current_window);

    if (glut_window)
    {
        event.state=glut_window->KeyModifierState;
        glut_window->AddEvent(&event);
    }
    OUT("");
}


/************************************************ glui_special_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::special_func (int key, int x, int y)
{

    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);
    y = win_h - y;
    ::XKeyEvent event;
    event.type = KeyPress;
    event.keycode = key << KeyModifierShift ; //first 256 char are reserved for non modifier keys
    event.x = x;
    event.y = y;



    int current_window = glutGetWindow ();
    GlutWindow* glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
            int glutModifiers = glutGetModifiers();
            glut_window->KeyModifierState &= ! ( ControlMask | ShiftMask | Mod1Mask );
            if ( glutModifiers | GLUT_ACTIVE_SHIFT ) glut_window->KeyModifierState | ShiftMask;
            if ( glutModifiers | GLUT_ACTIVE_CTRL  ) glut_window->KeyModifierState | ControlMask;
            if ( glutModifiers | GLUT_ACTIVE_ALT   ) glut_window->KeyModifierState | Mod1Mask;

            event.state=glut_window->KeyModifierState;
            glut_window->AddEvent(&event);

    }
}

/********************************************** glui_mouse_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::mouse_func (int button, int state, int x, int y)
{
    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);

    y = win_h - y;
    ::XButtonEvent event;
    event.type =

    event.x=x;
    event.y=y;


    int current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
        if (state == GLUT_DOWN)
        {
            event.type = ButtonPress;
            glut_window->KeyModifierState |= (Button1Mask << ( button - Button1 ) );
        }
        else
        {
            event.type = ButtonRelease;
            glut_window->KeyModifierState &= ! (Button1Mask << ( button - Button1 ) );
        }
        int glutModifiers = glutGetModifiers();
        glut_window->KeyModifierState &= ! ( ControlMask | ShiftMask | Mod1Mask );
        if ( glutModifiers | GLUT_ACTIVE_SHIFT ) glut_window->KeyModifierState | ShiftMask;
        if ( glutModifiers | GLUT_ACTIVE_CTRL  ) glut_window->KeyModifierState | ControlMask;
        if ( glutModifiers | GLUT_ACTIVE_ALT   ) glut_window->KeyModifierState | Mod1Mask;

        event.state=glut_window->KeyModifierState;
        glut_window->AddEvent(&event);
    }
}


/********************************************** glui_motion_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::motion_func (int x, int y)
{
        int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);

    y = win_h - y;
    ::XMotionEvent event;
    event.type = MotionNotify;

    event.x=x;
    event.y=y;


    int current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
        event.state=glut_window->KeyModifierState;
        glut_window->AddEvent(&event);
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


    int current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
        event.state=glut_window->KeyModifierState;
        glut_window->AddEvent(&event);
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

    int current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
        if ( state == GLUT_VISIBLE )
        {
            glut_window->AddEvent(&mapevent);
        }
        else
        {
            glut_window->AddEvent(&unmapevent);
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
    int current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
        glut_window->idle();
    }

}



