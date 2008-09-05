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

GlutWindow::GlutWindow(Display* display, Window parent,
        int x, int y,
        unsigned int width, unsigned int height,
        unsigned int border_width,
        int depth,
        class_type _class,
        Visual *visual,
        unsigned long valuemask,
        XSetWindowAttributes *attributes )
{

    if ( parent == NULL ) {  /* not a subwindow, creating a new top-level window */
        int old_glut_window = glutGetWindow();

        glutInitWindowSize( 100, 100 );
        if ( x >= 0 || y >= 0 )
            glutInitWindowPosition( x, y );
        glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
        this->GlutWindowId = glutCreateWindow(" ");

        if ( old_glut_window > 0 )
            glutSetWindow( old_glut_window );
        else
            glutSetWindow(GlutWindowId);

    }
    else /* *is* a subwindow */
    {
        int old_glut_window = glutGetWindow();
        GlutWindow* win= MasterObject::Instance()->FindWindow(parent);

        GlutWindowId = glutCreateSubWindow(win->GetGlutWindowId(), 0,0, 100, 100);
        win->add_control(this);

        if ( old_glut_window > 0 )
            glutSetWindow( old_glut_window );

    }
    MasterObject::Instance()->Register(this);

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
    //glutIdleFunc (idle_func);	// FIXME!  100% CPU usage!

}

GlutWindow::GlutWindow(Display *display, Window parent,
        int x, int y,
        unsigned int width, unsigned int height,
        unsigned int border_width,
        unsigned long border,
        unsigned long background )
{
}

int GlutWindow::AddEvent (::XEvent event)
{
    if (Expose == event.type)
    {
        debug::Instance()->print( __FILE__, __LINE__,
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
        this->translate_and_draw();
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
    else if (DestroyNotify == event.type)
    {
        Node* child = first_child();
        Control* control = dynamic_cast<Control*>(child);
        while (control)
        {
            control->AddEvent(event);
            control =  dynamic_cast<Control*>(next());
        }
        delete this;
        return 0;
    }
    else if (ResizeRequest == event.type)
    {
        ::XResizeRequestEvent *theEvent = (::XResizeRequestEvent*) &event;
        CurrentSize.size.w = theEvent->width;
        CurrentSize.size.h = theEvent->height;

        this->pack(0, 0);

        if ( theEvent->width  != CurrentSize.size.w ||
             theEvent->height != CurrentSize.size.h ) {
            glutReshapeWindow( CurrentSize.size.w, CurrentSize.size.h );
        }
        else {
        }

        glViewport( 0, 0, CurrentSize.size.w, CurrentSize.size.h);

        debug::Instance()->print( __FILE__, __LINE__,
                "%d: %d\n", glutGetWindow(), this->flags );

        glutPostRedisplay();
        return 0;
    }
    return EINVAL;
}





/********************************************** glui_display_func() ********/

void GlutWindow::display_func (void)
{
    XResizeRequestEvent event = {
        .type   = Expose,
    };
    debug::Instance()->print (__FILE__, __LINE__, "display func\n");
    GlutWindow* win= MasterObject::Instance()->FindWindow(glutGetWindow ());

    if (win)
    {
        glut_window->AddEvent(event);
    }
}



/********************************************** glui_reshape_func() ********/

void GlutWindow::reshape_func (int w, int h)
{
    XResizeRequestEvent event = {
        .type   = ResizeRequest,
        .width  = w,
        .height = h
    };


    debug::Instance()->print (__FILE__, __LINE__, "glui_reshape_func(): %d  w/h: %d/%d\n", glutGetWindow (), w, h);

    /***  First check if this is main glut window ***/
    GlutWindow* glut_window = MasterObject::Instance()->FindWindow(glutGetWindow ());
    if (glut_window)
    {
        glut_window->AddEvent(event);
    }
}





#error "continue modification from here"

/********************************************** glui_keyboard_func() ********/

void GlutWindow::keyboard_func (unsigned char key, int x, int y)
{

    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);
    y = win_h - y;

    current_window = glutGetWindow ();
    GlutWindow* glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    debug::Instance ()->print (__FILE__, __LINE__, "key: %d\n", current_window);

    if (glut_window)
    {		       /**  Was event in a GLUT window?  **/
        if (MasterObject::Instance()->active_control_glui && MasterObject::Instance()->active_control)
        {
            glutSetWindow (glut_window->GlutWindowId);

            MasterObject::Instance()->active_control_glui->keyboard (key, x, y);
            finish_drawing ();

        }
        else
        {
            if (glut_window->glut_keyboard_CB)
                glut_window->glut_keyboard_CB (key, x, y);
        }
    }
    else
    {	   /***  Nope, event was in a standalone GLUI window  **/
        glui = MasterObject::Instance()->find_glui_by_window_id (glutGetWindow ());

        if (glui)
        {
            glui->keyboard (key, x, y);
            finish_drawing ();
        }
    }
}


/************************************************ glui_special_func() ********/

void GlutWindow::special_func (int key, int x, int y)
{

    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);
    y = win_h - y;

    current_window = glutGetWindow ();
    GlutWindow* glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window) /**  Was event in a GLUT window?  **/
    {
        if (MasterObject::Instance()->active_control_glui && MasterObject::Instance()->active_control)
        {
            glutSetWindow (MasterObject::Instance()->active_control_glui->get_glut_window_id ());

            MasterObject::Instance()->active_control_glui->special (key, x, y);
            finish_drawing ();

            glutSetWindow (current_window);
        }
        else
        {
            if (glut_window->glut_special_CB)
                glut_window->glut_special_CB (key, x, y);
        }
    }
    else		   /***  Nope, event was in a standalone GLUI window  **/
    {
        glui = MasterObject::Instance()->find_glui_by_window_id (glutGetWindow ());

        if (glui)
        {
            glui->special (key, x, y);
            finish_drawing ();
        }
    }
}

/********************************************** glui_mouse_func() ********/

void GlutWindow::mouse_func (int button, int state, int x, int y)
{
    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);
    y = win_h - y;

    current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {		       /**  Was event in a GLUT window?  **/
        if (MasterObject::Instance()->active_control_glui != NULL)
            MasterObject::Instance()->active_control_glui->deactivate_current_control ();

        if (glut_window->glut_mouse_CB)
            glut_window->glut_mouse_CB (button, state, x, y);
        finish_drawing ();
    }
    else
    {		       /**  Nope - event was in a GLUI standalone window  **/
        glui = MasterObject::Instance()->find_glui_by_window_id (glutGetWindow ());
        if (glui)
        {
            glui->passive_motion (0, 0);
            glui->mouse (button, state, x, y);
            finish_drawing ();
        }
    }
}


/********************************************** glui_motion_func() ********/

void GlutWindow::motion_func (int x, int y)
{
    GLUI *glui;
    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);
    y = win_h - y;

    glui = MasterObject::Instance()->find_glui_by_window_id (glutGetWindow ());

    if (glui)
    {
        glui->motion (x, y);
        finish_drawing ();
    }

}


/**************************************** glui_passive_motion_func() ********/

void GlutWindow::passive_motion_func (int x, int y)
{
    GLUI *glui;
    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);
    y = win_h - y;

    glui = MasterObject::Instance()->find_glui_by_window_id (glutGetWindow ());

    if (glui)
    {
        glui->passive_motion (x, y);
        finish_drawing ();
    }
}


/********************************************** glui_entry_func() ********/

void GlutWindow::entry_func (int state)
{
    GLUI *glui;

    glui = MasterObject::Instance()->find_glui_by_window_id (glutGetWindow ());

    if (glui)
    {
        glui->entry (state);
    }
}




/****************************** GLUI_Main::entry() **************/

void    GLUI_Main::entry(int state)
{
    /*if ( NOT active_control || ( active_control && ( active_control->type == GLUI_CONTROL_EDITTEXT
      || active_control->type == GLUI_CONTROL_SPINNER) ) )*/
    glutSetCursor( GLUT_CURSOR_LEFT_ARROW );
}

/******************************************** glui_visibility_func() ********/

void GlutWindow::visibility_func (int state)
{
    GLUI *glui;

    debug::Instance ()->print (__FILE__, __LINE__, "IN GLUI VISIBILITY()\n");
    /*  fflush( stdout );          */

    glui = MasterObject::Instance()->find_glui_by_window_id (glutGetWindow ());

    if (glui)
    {
        glui->visibility (state);
    }
}


/********************************************** glui_idle_func() ********/
/* Send idle event to each glui, then to the main window            */

void GlutWindow::idle_func (void)
{
    GlutWindow* win = MasterObject::Instance()->FindWindow(glutGetWindow());
    while (glui)
    {
        debug::Instance()->print( __FILE__, __LINE__,
                "IDLE \t" );

        if ( active_control != NULL ) {
            /* First we check if the control actually needs the idle right now.
               Otherwise, let's avoid wasting cycles and OpenGL context switching */

            if ( active_control->needs_idle() ) {
                /*** Set the current glut window to the glui window */
                /*** But don't change the window if we're already at that window ***/

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
        /*** We set the current glut window before calling the user's
          idle function, even though glut explicitly says the window id is
          undefined in an idle callback.  ***/

        /** Check what the current window is first ***/

        /*** Arbitrarily set the window id to the main gfx window of the
          first glui window ***/
        /*   int current_window, new_window;          */
        /*   current_window = glutGetWindow();          */
        /*   if (MasterObject::Instance()->gluis.first_child() != NULL ) {          */
        /*      new_window = ((GLUI_Main*)MasterObject::Instance()->gluis.first_child())-> */
        /*   main_gfx_window_id;          */
        /*   if ( new_window > 0 && new_window != old_window ) {          */
        /*   --- Window is changed only if its not already the current window --- */
        /*  glutSetWindow( new_window );          */
        /* }          */
        /*}          */

        MasterObject::Instance()->glut_idle_CB ();
    }
}
/****************************** GLUI_Main::idle() **************/

void    GLUI_Main::idle(void)
{
    /*** Pass the idle event onto the active control, if any ***/

}

int  GLUI_Main::needs_idle( void )
{
    return active_control != NULL && active_control->needs_idle();
}

