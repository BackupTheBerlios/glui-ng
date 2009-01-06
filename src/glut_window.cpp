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

///////////////////////////////////////////////////////////////////////
void  GlutWindow::XMapWindow()
{
  glutSetWindow(GlutWindowId);
  glutShowWindow();
}

void XMapRaised()
{
#warning "TODO"
}

void XMapSubwindows()
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

void XUnmapSubwindows()
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

    if ( win == NULL ) {  // not a subwindow, creating a new top-level window
        int old_glut_window = glutGetWindow();

        glutInitWindowSize( width, height);
        if ( x >= 0 || y >= 0 )
            glutInitWindowPosition( x, y );
        glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
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
    glutIdleFunc (NULL);

}

GlutWindow::~GlutWindow()
{
#warning "Todo : delete childs. close the window"
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
    ::XResizeRequestEvent *theEvent = (::XResizeRequestEvent*) &event;
    CurrentSize.size.w = theEvent->width;
    CurrentSize.size.h = theEvent->height;

    this->pack(0, 0);

    if ( theEvent->width  != CurrentSize.size.w ||
            theEvent->height != CurrentSize.size.h ) {
        glutSetWindow( this->GlutWindowId );
        glutReshapeWindow( CurrentSize.size.w, CurrentSize.size.h );
    }
    else {
    }

    glViewport( 0, 0, CurrentSize.size.w, CurrentSize.size.h);

    debug::Instance()->print( __FILE__, __LINE__, _level,
            "%d: %d\n", glutGetWindow(), this->flags );

    glutPostRedisplay();
    return 0;
}


int GlutWindow::AddEvent(::XExposeEvent *event)
{
    debug::Instance()->print( __FILE__, __LINE__, _level,
            "display\n");
    int       win_w, win_h;

    // SUBTLE: on freeGLUT, the correct window is always already set.
    // But older versions of GLUT need this call, or else subwindows
    // don't update properly when resizing or damage-painting.
    glutSetWindow( this->GlutWindowId );

    // Set up OpenGL state for widget drawing
    glEnable( GL_DEPTH_TEST );
    //glDisable( GL_DEPTH_TEST );
    glCullFace( GL_BACK );
    glDisable( GL_CULL_FACE );
    //glEnable( GL_LIGHTING );
    glDisable(GL_LIGHTING);

    this->SetCurrentDrawBuffer();

    //update sizes and positions
    this->update_size();
    this->pack(0, 0);


    // Check here if the window needs resizing
    win_w = glutGet( GLUT_WINDOW_WIDTH );
    win_h = glutGet( GLUT_WINDOW_HEIGHT );
    if ( win_w != this->Width() || win_h != this->Height() ) {
        glutReshapeWindow( this->Width(), this->Height() );
        return 0;
    }

    //    Draw GLUI window
    glClearColor( theme::Instance()->bkgd_color[0] / 255.0f,
            theme::Instance()->bkgd_color[1] / 255.0f,
            theme::Instance()->bkgd_color[2] / 255.0f,
            1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    this->set_ortho_projection();

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Recursively draw the main panel
    this->AddEvent(event);
    switch (drawinghelpers::get_buffer_mode()) {
        case drawinghelpers::buffer_front: // Make sure drawing gets to screen
            glFlush();
            break;
        case drawinghelpers::buffer_back: // Bring back buffer to front
            glutSwapBuffers();
            break;
    }
    glutPostRedisplay();
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






/********************************************** glui_display_func() ********/
#warning "reput y axis up on event"
void GlutWindow::display_func (void)
{
    ::XExposeEvent event;
        event.type   = Expose;

    debug::Instance()->print (__FILE__, __LINE__, 0 , "display func\n");
    GlutWindow* win= MasterObject::Instance()->FindWindow(glutGetWindow ());

    if (win)
    {
        win->AddEvent(&event);
    }
}



/********************************************** glui_reshape_func() ********/
#warning "reput y axis up on event"
void GlutWindow::reshape_func (int w, int h)
{
    ::XResizeRequestEvent event;
        event.type   = ResizeRequest;
        event.width  = w;
        event.height = h;


    debug::Instance()->print (__FILE__, __LINE__, 0, "glui_reshape_func(): %d  w/h: %d/%d\n", glutGetWindow (), w, h);

    /***  First check if this is main glut window ***/
    GlutWindow* glut_window = MasterObject::Instance()->FindWindow(glutGetWindow ());
    if (glut_window)
    {
        glut_window->AddEvent(&event);
    }
}





#warning "factorise
/********************************************** glui_keyboard_func() ********/
#warning "reput y axis up on event"
void GlutWindow::keyboard_func (unsigned char key, int x, int y)
{

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

    debug::Instance ()->print (__FILE__, __LINE__, 0, "key: %d\n", current_window);

    if (glut_window)
    {
        event.state=glut_window->KeyModifierState;
        glut_window->AddEvent(&event);
    }
}


/************************************************ glui_special_func() ********/
#warning "reput y axis up on event"
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
#warning "reput y axis up on event"
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
#warning "reput y axis up on event"
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
#warning "reput y axis up on event"
void GlutWindow::passive_motion_func (int x, int y)
{
    motion_func (x,y);
}


/********************************************** glui_entry_func() ********/
#warning "reput y axis up on event"
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
#warning "reput y axis up on event"
void GlutWindow::visibility_func (int state)
{
    ::XMapEvent mapevent;
    ::XUnmapEvent unmapevent;

    mapevent.type = MapNotify;
    unmapevent.type = UnmapNotify;
    #warning "complete the structure with other information"


    debug::Instance ()->print (__FILE__, __LINE__, 0, "IN GLUI VISIBILITY()\n");
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


}


/********************************************** glui_idle_func() ********/
/* Send idle event to each glui, then to the main window            */
/*
#warning "reput y axis up on event"
void GlutWindow::idle_func (void)
{
#warning "don't know what to do with that"
    GlutWindow* win = MasterObject::Instance()->FindWindow(glutGetWindow());
    while (glui)
    {
        debug::Instance()->print( __FILE__, __LINE__, _level,
                "IDLE \t" );

        if ( active_control != NULL ) {
            // First we check if the control actually needs the idle right now.
            // Otherwise, let's avoid wasting cycles and OpenGL context switching

            if ( active_control->needs_idle() ) {
                // Set the current glut window to the glui window
                // But don't change the window if we're already at that window

                if ( GlutWindowId > 0 && glutGetWindow() != GlutWindowId ) {
                    glutSetWindow( GlutWindowId );
                }

                active_control->idle();
            }
        }

        finish_drawing ();

        glui = (GLUI *) glui->next ();
    }

    if (MasterObject::Instance()->glut_idle_CB)
    {
        // We set the current glut window before calling the user's
        //idle function, even though glut explicitly says the window id is
        //undefined in an idle callback.

        // Check what the current window is first

        // Arbitrarily set the window id to the main gfx window of the
        //first glui window
        //   int current_window, new_window;
        //   current_window = glutGetWindow();
        //   if (MasterObject::Instance()->gluis.first_child() != NULL ) {
        //      new_window = ((GLUI_Main*)MasterObject::Instance()->gluis.first_child())->
        //   main_gfx_window_id;
        //   if ( new_window > 0 && new_window != old_window ) {
        //   --- Window is changed only if its not already the current window ---
        //  glutSetWindow( new_window );
        // }
        //}

        MasterObject::Instance()->glut_idle_CB ();
    }
}
*/
/****************************** GLUI_Main::idle() **************/

