/****************************************************************************
  GLUI User Interface Toolkit
  ---------------------------

     glui_splittercolumn.cpp - Splitter control class


          --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher
  Copyright (c) 2007 MALET Jean-Luc

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

#include <GL/glui/splitter.h>
using namespace GLUI;
/******************************** Splitter::Splitter() ************/

Splitter::Splitter( Node *parent, const char* name, bool draw_bar )
    : Container (name),
      first_panel (this, "first_panel"),
      second_panel (this, "second_panel"),
      separator    (this, "separator")
{
  common_init();
  draw_separator = draw_bar;

  parent->add_control( this );
}

/*
void  Splitter::draw (void)
{
  int   panel_x, panel_y, panel_w, panel_h, panel_x_off, panel_y_off;
  int   y_diff;
  Control* curr_parent = dynamic_cast<Control*>(parent());

  if ( int_val == 1 ) {  // Draw a vertical bar 
    
    if ( curr_parent != NULL ) {
      get_this_column_dims(&panel_x, &panel_y, &panel_w, &panel_h, 
			   &panel_x_off, &panel_y_off);

      y_diff = y_abs - panel_y;

      if ( 0 ) {
	glLineWidth(1.0);
	glBegin( GL_LINES );
	glColor3f( .5, .5, .5 );
	glVertex2i( -GLUI_XOFF+1, -y_diff + GLUI_SEPARATOR_HEIGHT/2 );
	glVertex2i( -GLUI_XOFF+1, -y_diff + panel_h - GLUI_SEPARATOR_HEIGHT/2);

	glColor3f( 1.0, 1.0, 1.0 );
	glVertex2i( -GLUI_XOFF+2, -y_diff + GLUI_SEPARATOR_HEIGHT/2 );
	glVertex2i( -GLUI_XOFF+2, -y_diff + panel_h - GLUI_SEPARATOR_HEIGHT/2);
	glEnd();
      }
      else {
	glLineWidth(1.0);
	glBegin( GL_LINES );
	glColor3f( .5, .5, .5 );
	glVertex2i( -2, 0 );
	glVertex2i( -2, h );
	//glVertex2i( 0, -y_diff + GLUI_SEPARATOR_HEIGHT/2 );
	//glVertex2i( 0, -y_diff + panel_h - GLUI_SEPARATOR_HEIGHT/2);

	glColor3f( 1.0, 1.0, 1.0 );
	glVertex2i( -1, 0 );
	glVertex2i( -1, h );
	//glVertex2i( 1, -y_diff + GLUI_SEPARATOR_HEIGHT/2 );
	//glVertex2i( 1, -y_diff + panel_h - GLUI_SEPARATOR_HEIGHT/2);
	glEnd();
      }		
    } 
  }
}
*/

///////////////////////////////////////////////////////////////////////
void Splitter::common_init()
{
    set_orientation(LeftToRight);
    CurrentSize.size.w     = 0;
    CurrentSize.size.h     = 0;
}



