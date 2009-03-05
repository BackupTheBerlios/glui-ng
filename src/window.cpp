/*

  glui_window.cpp : the top level widget

  GLUI User Interface Toolkit 
  Copyright (c) 2008 MALET Jean-Luc

  WWW:    http://sourceforge.net/projects/glui/
  Forums: http://sourceforge.net/forum/?group_id=92496

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

*/

#include <GL/glui/window.h>
#include <GL/glui/drawinghelpers.h>
#include <GL/glui/debug.h>
#include <GL/gl.h>
using namespace GLUI;
#define MODULE_KEY  "GLUI_DEBUG_WINDOW"

/*_Display::operator ::Display*()
{
    return disp;
}*/

_Window::_Window() :
    Container("window")
{
}


void _Window::SetViewport()
{
    glViewport( 0, 0, this->Width(), this->Height() );
}

_Display::_Display()
{
}

int _Window::SetCurrentDrawBuffer( void )
{
    /* Save old buffer */
    GLint state;
    glGetIntegerv( GL_DRAW_BUFFER, &state );
    /* Switch to new buffer */
    switch (drawinghelpers::get_buffer_mode()) {
        case drawinghelpers::buffer_front: glDrawBuffer(GL_FRONT); break;
        case drawinghelpers::buffer_back:  glDrawBuffer(GL_BACK);  break; /* might not be needed... */
    }
    return (int)state;
}


/******************************* GLUI_Main::set_ortho_projection() **********/

void  _Window::SetOrthoProjection( void )
{


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    /*  gluOrtho2D( 0.0, (float) win_w, 0.0, (float) win_h );          */
    glOrtho( 0.0, (float)this->Width(), 0.0, (float)this->Height(), GLUI_BOTTOM_VIEWPORT, GLUI_TOP_VIEWPORT );
    glMatrixMode( GL_MODELVIEW );


}

///////////////////////////////////////////////////////////////////////////////
int _Window::AddEvent (::XEvent *event)
{
    switch (event->type)
    {
        case Expose : return AddEvent((::XExposeEvent*) event);
        case DestroyNotify :  return AddEvent((::XDestroyWindowEvent*) event);
        case ResizeRequest: return AddEvent((::XResizeRequestEvent*) event);
    }

    return EINVAL;
}

int _Window::AddEvent(::XResizeRequestEvent *event)
{
    IN("");

    if ( event->width  != this->CurrentSize.size.w ||
            event->height != this->CurrentSize.size.h ) {
        this->CurrentSize.size.h = event->height;
        this->CurrentSize.size.w = event->width;
        this->pack(x, y);
        glViewport( 0, 0, this->CurrentSize.size.w, this->CurrentSize.size.h);
    }
    OUT("");
    return 0;
}



int _Window::AddEvent(::XExposeEvent *event)
{
    IN("");
    if (mapped)
    {
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

        Container::AddEvent (event);

        switch (drawinghelpers::get_buffer_mode()) {
            case drawinghelpers::buffer_front: // Make sure drawing gets to screen
                glFlush();
                break;
            case drawinghelpers::buffer_back: // Bring back buffer to front
#warning "check how other *GL are doing swapbuffer"
                //glutSwapBuffers();
                break;
        }
    }
    OUT("");
    return 0;
}



int _Window::AddEvent(::XDestroyWindowEvent *event)
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


int _Window::AddEvent(::XKeyEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int _Window::AddEvent(::XButtonEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int _Window::AddEvent(::XMotionEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int _Window::AddEvent(::XCrossingEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int _Window::AddEvent(::XMapEvent* event)
{
    ::XExposeEvent expose;
    expose.type = Expose;
    Container::AddEvent((::XEvent*) event);
    this->AddEvent(&expose);
}


int _Window::AddEvent(::XUnmapEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}





