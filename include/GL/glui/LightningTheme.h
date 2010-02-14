#ifndef __LIGHTNINGTHEME_H
#define __LIGHTNINGTHEME_H
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

#include <GL/glui/themes.h>

namespace GLUI
{
        class VertexObject;
        class LigthningTheme : public theme
        {
                public :

                        void DoLightning();
                        uint8_t* Get_bkgd_color();
                protected:
                        virtual VertexObject* raised_box( uint32_t w,
                                                          uint32_t h,
                                                          uint32_t thickness = 0,
                                                          uint8_t size = 3,
                                                          GLenum intype = GL_BYTE,
                                                          void *color_array = NULL );
                        virtual VertexObject* lowered_box( uint32_t w,
                                                           uint32_t h,
                                                           uint32_t thickness = 0,
                                                           uint8_t size = 3,
                                                           GLenum intype = GL_BYTE,
                                                           void *color_array = NULL );
                protected :
                        uint8_t    bkgd_color[4];

        };

        class LigthningWindowTheme : public LigthningTheme
        {
                public :
                        virtual int draw();
                        virtual int update();
        };


}
#endif

