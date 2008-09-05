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

inline operator _Display::Display*()
{
    return disp;
}


_Window::_Window()
{
}

int _Window::AddEvent(XEvent event)
{
}

inline operator== (::Window window)
{

}

int _Window::set_current_draw_buffer( void )
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


/******************************* GLUI_Main::set_ortho_projection() **********/

void  _Window::set_ortho_projection( void )
{
  int win_h, win_w;

  win_w = glutGet( GLUT_WINDOW_WIDTH );
  win_h = glutGet( GLUT_WINDOW_HEIGHT );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  /*  gluOrtho2D( 0.0, (float) win_w, 0.0, (float) win_h );          */
  glOrtho( 0.0, (float)win_w, 0.0, (float) win_h, -1000.0, 1000.0 );
  glMatrixMode( GL_MODELVIEW );


}


/******************************* GLUI_Main::set_viewport() **********/

void  _Window::set_viewport( void )
{
  glViewport( 0, 0, main_panel->w, main_panel->h );
}
