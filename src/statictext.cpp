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

#include <GL/glui/statictext.h>
#include <GL/glui/debug.h>
#include <GL/glui/window.h>
#include <GL/glui/themes.h>

using namespace GLUI;
///////////////////////////////////////////////////////////////////////////////
StaticText::StaticText( Node *parent, const char *name )
    :    Control(name)

{
  Control* ctrl;
  parent->add_control( this );
  ctrl = (Control*)this;
  this->TheDefaultTheme = new StaticText::DefaultTheme(*this);
#warning "TODO"
  //set_font(theme::Instance()->font);
}


///////////////////////////////////////////////////////////////////////////////

void    StaticText::set_text(const char *text )
{
    *(dynamic_cast<std::string*>(this)) = text;
    ThemeData->update();
}


///////////////////////////////////////////////////////////////////////////////

void   StaticText::update_size( void )
{
	CurrentSize.size.w = dynamic_cast<Text*>(&*ThemeData)->Width();
	CurrentSize.size.h = dynamic_cast<Text*>(&*ThemeData)->Height();
}

///////////////////////////////////////////////////////////////////////////////

int StaticText::DefaultTheme::draw( )
{

//    drawinghelpers::draw_box(Width(), Height()); //erase text
  glColor3ubv( Color );
  glRasterPos3f(0.0, 0.0, 0.1);
  //glRasterPos store the color and translate, since glut drawing routine use
  //y axis up, we need to translate down before drawing
  Text::draw();
}

int StaticText::DefaultTheme::update( )
{
}
