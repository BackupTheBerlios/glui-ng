/****************************************************************************
  
  GLUI User Interface Toolkit
  ---------------------------

     glui_statictext.cpp - StaticText Control


          --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher

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

*****************************************************************************/

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
	CurrentSize.size.w = dynamic_cast<Text*>(ThemeData)->Width();
	CurrentSize.size.h = dynamic_cast<Text*>(ThemeData)->Height();
}

//////////////////////////////////////////////////////////////////////////////
theme* StaticText::GetDefaultTheme()
{
        return new StaticText::DefaultTheme(*this);
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
