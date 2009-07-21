#ifndef __GLUI_DRAWINGHELPERS_H
#define __GLUI_DRAWINGHELPERS_H

/*

  drawinghelpers.h : the top level widget, in glut

  GLUI User Interface Toolkit
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

*/
#include <GL/gl.h>

namespace GLUI
{
    class Control;
    class VertexObject;


    class drawinghelpers
    {
        public : //data types
            enum buffer_mode_t
            {
                buffer_front=1, ///< Draw updated controls directly to screen.
                buffer_back=2   ///< Double buffering: postpone updates until next redraw.
            };
        public :
            static void draw_box_inwards_outline(int enabled, int x_min, int x_max,
                                                 int y_min, int y_max );
            static void draw_box(uint32_t w, uint32_t h, uint8_t size = 3, GLenum intype = GL_BYTE, void *color_array = NULL);
            static void draw_emboss_box( int x_min, int x_max,int y_min,int y_max);

            static void draw_active_box(int active,  int x_min, int x_max, int y_min, int y_max );
            static void set_to_bkgd_color( void );
            static buffer_mode_t get_buffer_mode();

    };

}

#endif //__GLUI_DRAWINGHELPERS_H
