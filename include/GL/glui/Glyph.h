#ifndef __GLUI_GLYPH_H
#define __GLUI_GLYPH_H
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
#include <GL/glui/commondefs.h>
#include <GL/glui/VertexObject.h>
#include <stdint.h>
namespace GLUI
{
        class Font;
        //see http://www.freetype.org/freetype2/docs/glyphs/glyphs-3.html
        class GLUIAPI Glyph : public VertexObject
        {
                friend class Font;
                enum orientation{ TopDown, BottomUp, LeftToRight, RightToLeft};
                public :
                        orientation Orientation();
                        uint32_t Advance();
                        uint32_t BearingX();
                        uint32_t BearingY();
                        uint32_t GlyphWidth();
                        uint32_t GlyphHeight();
                        int Width();
                        int Height();
                protected:
                        Glyph(NCRC_AutoPtr<Font> fam, orientation orient=LeftToRight);
                        ~Glyph();
                        
                protected:
                        uint32_t bearingX;
                        uint32_t bearingY;
                        uint32_t glyphWidth;
                        uint32_t glyphHeight;
                        uint32_t advance;
                        orientation orient;
                        NCRC_AutoPtr<Font> familly;
                private:
                        Glyph() {};
        };

}
#endif


