#ifndef __GLUI_FONT_H
#define __GLUI_FONT_H
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
#include <GL/glui/Glyph.h>

namespace GLUI
{
        class GLUIAPI Font : public NonCopyableReferenceCountedClass
        {
                friend class Text;
                public : //methods
                        std::string& Name();
                        NCRC_AutoPtr<Glyph> GetGlyph(char c);
                        NCRC_AutoPtr<Glyph> GetGlyph(uint16_t utf16);
                        NCRC_AutoPtr<Glyph> GetGlyph(uint8_t* utf8);
                        uint32_t Ascent()  {return ascent;}  //maximum number of dot above the Baseline
                        uint32_t Descent() {return descent;} //maximum number of dot below the Baseline
                        uint32_t Linegap() {return linegap;} //additional space around
                        uint32_t Baseline() {return linegap + descent;} //return baseline position
                        uint32_t BaselineToBaseline() {return ascent + descent + linegap;}
                protected: //methods
                        Font(const std::string& name);
                        ~Font();
                protected: //variables
                        std::string name;
                        uint32_t ascent;
                        uint32_t descent;
                        uint32_t linegap;
                private:
                Font();
        };


}
#endif

