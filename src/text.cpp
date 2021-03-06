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

#include <GL/glui/text.h>
#include <GL/glui/debug.h>


//implement X11 font API
#warning "TODO : rename this class into FONT, don't derivate from std::string..."
//               implement << operator to draw the text with the selected font
#warning "TODO : http://www.tronche.com/gui/x/xlib/graphics/font-metrics/"
#warning "TODO : http://www.tronche.com/gui/x/xlib/graphics/font-metrics/XListFonts.html"
#warning "TODO : add default font into theme class"

using namespace GLUI;

#ifdef _MSC_VER
#define vsnprintf _vsnprintf
#endif
//////////////////////////////////////////////////////////////////////////////
Text::Text (const std::string txt,const std::string& fontname) :
    std::string(txt),
    font(new Font(fontname)) //GLUT_BITMAP_HELVETICA_12;
{
    memset(char_widths, -1, sizeof(char_widths)); /* JVK */
    tests =0;
    memset(Color, 0, sizeof(Color));

    ////begin to implement rendering to texture
    //glGenTextures( 1, &render_texture );
    //glBindTexture( GL_TEXTURE_2D, render_texture );
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    //                GL_LINEAR_MIPMAP_LINEAR );
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
    //                GL_LINEAR );
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
    //                GL_CLAMP_TO_EDGE );
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
    //                GL_CLAMP_TO_EDGE );
}


//////////////////////////////////////////////////////////////////////////////
 std::string& glui_format_str( std::string& str, const char* fmt, ...)
{
  const size_t ISIZE = 128;
  char stackbuf[ISIZE];
  size_t bufsz = ISIZE;
  char *buf = stackbuf;
  str = "";
  va_list arg;
  while (1) {
    va_start(arg, fmt);
    int ret = vsnprintf(buf,bufsz-1,fmt,arg);
    va_end(arg);
    if (ret>=0) {
      break;
    }
    // else make a bigger buf, try again
    bufsz <<= 1;
    if (buf==stackbuf) buf = (char*)malloc(sizeof(char)*bufsz);
    else buf = (char*)realloc(buf, sizeof(char)*bufsz);
  }
  if (buf!=stackbuf) free(buf);
  str=buf;
  return str;
}


/////////////////////////////////////////////////////////////////////////
void Text::SetFont(const std::string& fontname )
{
  font = new Font(fontname);
}

//////////////////////////////////////////////////////////////////////////
int Text::Width( )
{
  const char *p = this->c_str();
  int  width = 0;

  while( *p != '\0' )  {
    width += font->GetGlyph(*p)->GlyphWidth();
    p++;
  }

  return width;
}

//////////////////////////////////////////////////////////////////////////
int Text::Height( )
{
    return font->BaselineToBaseline();
}


/************************************ draw *********************************/
/* Displays the contents of a string using GLUT's bitmap character function */
/* Does not handle newlines                                             */

int Text::draw()
{
  const char *p = this->c_str();
  glPushMatrix();
//  glColor3ubv( Color );
//  while( *p != '\0' )  {
//    glutBitmapCharacter( font, *p );
//    debug::Instance()->FlushGL();
//    p++;
//  }
  glPopMatrix();
}

int Text::update()
{
#warning "todo : create a linked list of Glyph"
}


/*************** Text::GetFont() **********/

std::string& Text::GetFont( void ) const
{
    return this->font->Name();
    //return GLUT_BITMAP_HELVETICA_12;
}


/************* Text::draw_name() ***********/
/* This draws the name of the control as either black (if enabled), or       */
/* embossed if disabled.                                                     */
/*
void Text::draw_name(int x, int y)
{
  if ( enabled )
  {
    set_to_bkgd_color();
    glRasterPos2i(x+1, y+1);
    draw_string();
    glColor3b( 0, 0, 0 );
    glRasterPos2i(x, y);
    draw_string();
  }
  else
  {   /// Control is disabled - emboss the string
    glColor3f( 1.0f, 1.0f, 1.0f );
    glRasterPos2i(x+1, y+1);
    draw_string();
    glColor3f( .4f, .4f, .4f );
    glRasterPos2i(x, y);
    draw_string();
  }
}
*/
#warning "add text effects api"
// something like a flag field with all the current options like embossed,
// color, bold, underline, size, stroked, double stroke, italics....

Text& Text::operator=(Text& copy)
{
    *(dynamic_cast<std::string*>(this)) = *(dynamic_cast<std::string*>(&copy));
    this->SetFont(copy.GetFont());
    return *this;
}

Text& Text::operator=(std::string& str)
{
    *(dynamic_cast<std::string*>(this)) = str;
}

Text& Text::operator=(const std::string& str)
{
    *(dynamic_cast<std::string*>(this)) = str;
}
