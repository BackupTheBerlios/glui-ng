#ifndef __DEFAULTTHEME_H
#define __DEFAULTTHEME_H
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
#include <GL/glui/VertexObject.h>
namespace GLUI
{

        class _DefaultTheme : public theme
        {
                public :
                        enum VOflags
                        {
                                none = 0,
                                enablecolor = 1<<0,
                                enablenormals = 1<<1,
                                enablenormalcomputation = 1<<2
                        };
                public : 
                        _DefaultTheme();
                        virtual int draw();
                        virtual int update();
                        virtual NCRC_AutoPtr<VertexObject> raised_box( uint32_t w,
                                                          uint32_t h,
                                                          uint32_t thickness = 1,
                                                          uint32_t BorderWidth = 1,
                                                          uint32_t flags = enablecolor);
                        virtual NCRC_AutoPtr<VertexObject> lowered_box( uint32_t w,
                                                           uint32_t h,
                                                           uint32_t thickness = 1,
                                                           uint32_t BorderWidth = 1,
                                                           uint32_t flags = enablecolor);
                        void SetBorderColor(uint8_t border_color[4]);
                        void SetBkgdColor(uint8_t bkgd_color[4]);
                        void SetActivatedColor(uint8_t activated_color[4]);
                        void SetHoverColor(uint8_t hover_color[4]);
                        void GetBorderColor(uint8_t border_color[4]);
                        void GetBkgdColor(uint8_t bkgd_color[4]);
                        void GetActivatedColor(uint8_t activated_color[4]);
                        void GetHoverColor(uint8_t hover_color[4]);


                public :
                        uint8_t    border_color[4];
                        uint8_t    bkgd_color[4];
                        uint8_t    activated_color[4];
                        uint8_t    hover_color[4];
                protected :
                        NCRC_AutoPtr<VertexObject> box( NCRC_AutoPtr<DataArray> vertices,
                                        NCRC_AutoPtr<DataArray> normals,
                                        uint32_t flags);

        };

}
#endif
