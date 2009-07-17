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
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>
using namespace GLUI;
/////////////////////////////////////////////////////////////////////////////
_Display::_Display()
{
}
/////////////////////////////////////////////////////////////////////////////
/*_Display::operator ::Display*()
{
    return disp;
}*/
/////////////////////////////////////////////////////////////////////////////
_Window::_Window() :
    Container("window")
{
}
/////////////////////////////////////////////////////////////////////////////
void _Window::DefaultTheme::SetViewport()
{
    glViewport( 0, 0, Owner.Width(), Owner.Height() );
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
_Window::DefaultTheme::DefaultTheme(_Window& owner) : Owner(owner) 
{
}
/////////////////////////////////////////////////////////////////////////////
_Window::DefaultTheme::~DefaultTheme()
{
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
}

