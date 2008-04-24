/****************************************************************************
  
  GLUI User Interface Toolkit
  ---------------------------

     glui_statictext.cpp - GLUI_StaticText Control


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

#include "glui_internal_control.h"

/****************************** GLUI_StaticText::GLUI_StaticText() **********/
GLUI_StaticText::GLUI_StaticText( GLUI_Node *parent, const char *name )
    :    GLUI_Control(name), GLUI_Text(GLUT_BITMAP_HELVETICA_12)

{
  GLUI_Control* ctrl;
  common_init();
  parent->add_control( this );
  ctrl = dynamic_cast<GLUI_Control*>(this);
  if (ctrl)
	{
		set_font(ctrl->glui->font);
	}
}

/****************************** GLUI_StaticText::draw() **********/

void    GLUI_StaticText::draw( )
{

    GLUI_DRAWINGSENTINAL_IDIOM
  if ( NOT can_draw() )
    return;

  erase_text();
  glColor3ubv( Color );
  glPushMatrix();
  glRasterPos3f(0.0, (float)this->Height(), 0.0);
  //glRasterPos store the color and translate, since glut drawing routine use
  //y axis up, we need to translate down before drawing
  GLUI_Text::draw();
  glPopMatrix();
}


/****************************** GLUI_StaticText::set_text() **********/

void    GLUI_StaticText::set_text(const char *text )
{
  *(dynamic_cast<std::string*>(this)) = text;
  glutPostRedisplay();
}


/************************************ GLUI_StaticText::update_size() **********/

void   GLUI_StaticText::update_size( void )
{
	w = GLUI_Text::graph_Length( );
	h = GLUI_Text::graph_Width( );
}




/****************************** GLUI_StaticText::erase_text() **********/

void    GLUI_StaticText::erase_text( void )
{
  if ( NOT can_draw() )
    return;

  set_to_bkgd_color();
  glDisable( GL_CULL_FACE );
  glBegin( GL_TRIANGLES );
  glVertex2i( 0,0 );   glVertex2i( w, 0 );  glVertex2i( w, h );  
  glVertex2i( 0, 0 );  glVertex2i( w, h );  glVertex2i( 0, h );   
  glEnd();
}



