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
#include <GL/glui/Exception.h>
#include <GL/glui/debug.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
using namespace GLUI;
#define MODULE_KEY "time"
Time GLUI::get_time(void)
{       
     int  tint; 
     struct timeval  tv;
     struct timezone tz; /* is not used since ages */
     gettimeofday(&tv, &tz);
     tint = (int)tv.tv_sec * 1000;
     tint = tint/1000 * 1000;
     tint = tint + tv.tv_usec/1000;
     return((Time)tint);
}

#undef MODULE_KEY
#define MODULE_KEY "_Display"
/////////////////////////////////////////////////////////////////////////////
_Display::_Display()
{
}

/////////////////////////////////////////////////////////////////////////////
#undef MODULE_KEY
#define MODULE_KEY "_Window"

/////////////////////////////////////////////////////////////////////////////
_Window::_Window() :
    Container("window")
{
        args = NULL;
        mapped = false;
        thread_enabled = false;
        flags = 0;
        SetTheme(new _Window::DefaultTheme(*this));
}
_Window::~_Window()
{
        Wait();
}
///////////////////////////////////////////////////////////////////////////////
int _Window::Wait()
{
        int res;
        int err;
        if (this->thread_enabled)
        {
                err = pthread_join(main_thread, (void**)&res);
                if (err)
                {
                        return err;
                }
                return res;
        }
        else
        {
                return 0;
        }
}
/////////////////////////////////////////////////////////////////////////////
int _Window::SetCurrentDrawBuffer( void )
{
    /* Save old buffer */
    GLint state;
    glGetIntegerv( GL_DRAW_BUFFER, &state );
    /* Switch to new buffer */
    switch (get_buffer_mode()) {
        case buffer_front: glDrawBuffer(GL_FRONT); break;
        case buffer_back:  glDrawBuffer(GL_BACK);  break; /* might not be needed... */
    }
    return (int)state;
}
/////////////////////////////////////////////////////////////////////////////
_Window::buffer_mode_t _Window::get_buffer_mode() {
    char* bufferModeEnv = getenv("GLUI_BUFFER_MODE");
    if ( bufferModeEnv != NULL &&
            0 ==  strcmp(bufferModeEnv, "buffer_front") ) return buffer_front;
    else return buffer_back;
}
/////////////////////////////////////////////////////////////////////////////
::Window _Window::GetWindowId()
{
        return window;
}
/////////////////////////////////////////////////////////////////////////////
void  _Window::Start()
{
    int err = pthread_create(&main_thread,NULL,_Start, (void*)this);
    if (err)
    {
            GLUI_THROW(err, "window thread creation error");
    }
}
void* _Window::_Start(void* arg)
{
        int res;
        _Window* win = (_Window*) arg;
        win->thread_enabled = true;
        res = win->start_routine();
        pthread_exit((void*)res);
}

int _Window::_Stop()
{
        int res = pthread_kill(main_thread, SIGTERM);
        if (res) 
        {
                GLUI_THROW(res,"pthread_kill\n");
        }
        return Wait();
}


/////////////////////////////////////////////////////////////////////////////
_Window::DefaultTheme::DefaultTheme(_Window& owner) : Owner(owner) 
{
}
/////////////////////////////////////////////////////////////////////////////
_Window::DefaultTheme::~DefaultTheme()
{
}
/////////////////////////////////////////////////////////////////////////////
void _Window::DefaultTheme::SetViewport()
{
    glViewport( 0, 0, Owner.Width(), Owner.Height() );
}

/////////////////////////////////////////////////////////////////////////////
void  _Window::DefaultTheme::SetOrthoProjection( void )
{


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    /*  gluOrtho2D( 0.0, (float) win_w, 0.0, (float) win_h );          */
    glOrtho( 0.0, (float)Owner.Width(), 0.0, (float)Owner.Height(), GLUI_BOTTOM_VIEWPORT, GLUI_TOP_VIEWPORT );
    glMatrixMode( GL_MODELVIEW );


}
///////////////////////////////////////////////////////////////////////
int _Window::DefaultTheme::draw()
{
    //    Draw GLUI window
    glLoadIdentity();
    this->SetOrthoProjection();
    glTranslatef(Owner.X(), Owner.Y(), BOTTOM_VIEWPORT + 1);
}
///////////////////////////////////////////////////////////////////////
int _Window::DefaultTheme::update()
{
        return 0;
}

///////////////////////////////////////////////////////////////////////////////
int _Window::AddEvent(::XResizeRequestEvent *event)
{
    IN("");

    if ( event->width  != this->CurrentSize.size.w ||
            event->height != this->CurrentSize.size.h ) {
        this->CurrentSize.size.h = event->height;
        this->CurrentSize.size.w = event->width;
        this->pack(x, y);
        PostRedisplay();
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

            glViewport( 0, 0, this->CurrentSize.size.w, this->CurrentSize.size.h);

            this->SetCurrentDrawBuffer();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

            //update sizes and positions
            this->update_size();



            Container::AddEvent (event);

            switch (get_buffer_mode()) {
                    case buffer_front: // Make sure drawing gets to screen
                            glFlush();
                            break;
                    case buffer_back: // Bring back buffer to front
#warning "check how other *GL are doing swapbuffer"
                            //                                        glutSwapBuffers();
                            break;
            }

    }
    OUT("");
    return 0;
}



int _Window::AddEvent(::XDestroyWindowEvent *event)
{
    return 0;
}



int _Window::AddEvent(::XMapEvent* event)
{

    ::XExposeEvent expose;
    expose.type = Expose;
    this->AddEvent(&expose);



}




