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
#include <GL/glui/Font.h>
using namespace GLUI;

Glyph::orientation Glyph::Orientation()
{
        return this->orient;
}


uint32_t Glyph::Advance()
{
        return this->advance;
}

uint32_t Glyph::BearingX()
{
        return this->bearingX;
}

uint32_t Glyph::BearingY()
{
        return this->bearingY;
}

uint32_t Glyph::GlyphWidth()
{
        return this->glyphWidth;
}

uint32_t Glyph::GlyphHeight()
{
        return this->glyphHeight;
}

int Glyph::Width()
{
        if (this->orient == LeftToRight || this->orient == RightToLeft)
        {
                return this->advance;
        }
        else
        {
                return this->familly->BaselineToBaseline();
        }
}

int Glyph::Height()
{
        if (this->orient == LeftToRight || this->orient == RightToLeft)
        {
                return this->familly->BaselineToBaseline();
        }
        else
        {
                return this->advance;
        }

}

Glyph::Glyph(NCRC_AutoPtr<Font> fam,orientation orient)
{
        this->familly = fam;
        this->orient = orient;
}

Glyph::~Glyph()
{
}

#warning "todo : force glyph to have an associated color array with value NULL (ie disable the glyph color"
// it will allow the Container that use the glyph to set it's color

