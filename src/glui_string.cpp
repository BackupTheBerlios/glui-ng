/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui.cpp


          --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher (this file, Bill Baxter 2005)

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

*****************************************************************************/

#include "GL/glui.h"

#ifdef _MSC_VER
#define vsnprintf _vsnprintf
#endif

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


/****************************** Text ***************************/

/*************** GLUI_Text::set_font() **********/

void GLUI_Text::set_font(void *new_font)
{
  font = new_font;
}

/*************************************** glutBitmapStringWidth **********/
int GLUI_Text::char_width( char c  )
{
  return  glutBitmapWidth( font, c );
}

int GLUI_Text::graph_Width( )
{
  const char *p = this->c_str();
  int  width = 0;

  while( *p != '\0' )  {
    width = max<int>(glutBitmapWidth( font, *p ), width);
    p++;
  }

  return width;
}

/*************************************** glutBitmapStringLength **********/

int GLUI_Text::graph_Length( )
{
    return glutBitmapLength( font, (const unsigned char*)this->c_str() );
}


/************************************ draw *********************************/
/* Displays the contents of a string using GLUT's bitmap character function */
/* Does not handle newlines                                             */

void GLUI_Text::draw()
{
  const char *p = this->c_str();
  glPushMatrix();
  glColor3ubv( Color );
  while( *p != '\0' )  {
    glutBitmapCharacter( font, *p );
#warning remove
    glFlush();
    p++;
  }
  glPopMatrix();
}


/*************** GLUI_Text::get_font() **********/

void *GLUI_Text::get_font( void ) const
{
  /*** Does this control have its own font? ***/
  if ( this->font != NULL )
    return this->font;

  /*** Return the default font ***/
  return GLUT_BITMAP_HELVETICA_12;
}


/************* GLUI_Text::draw_name() ***********/
/* This draws the name of the control as either black (if enabled), or       */
/* embossed if disabled.                                                     */
/*
void GLUI_Text::draw_name(int x, int y)
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

GLUI_Text& GLUI_Text::operator=(GLUI_Text& copy)
{
    *(dynamic_cast<std::string*>(this)) = *(dynamic_cast<std::string*>(&copy));
    this->set_font(copy.get_font());
    return *this;
}

GLUI_Text& GLUI_Text::operator=(std::string& str)
{
    *(dynamic_cast<std::string*>(this)) = str;
}

GLUI_Text& GLUI_Text::operator=(const std::string& str)
{
    *(dynamic_cast<std::string*>(this)) = str;
}
