/****************************************************************************
  
  GLUI User Interface Toolkit
  ---------------------------

     glui_button.cpp - GLUI_Button control class


          --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher

  WWW:    http://sourceforge.net/projects/glui/
  Forums: http://sourceforge.net/forum/?group_id=92496

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/
#include "glui_internal_control.h"

/****************************** GLUI_Button::GLUI_Button() **********/

GLUI_Button::GLUI_Button( GLUI_Node *parent, const char *name,
                          int id, GLUI_CB cb ):
    GLUI_Container(name)

{
  common_init();
  user_id     = id;
  callback    = cb;
  currently_inside = false; 
  this->resizeable = AdaptThisToFitChilds;
  parent->add_control( this );
}


/****************************** GLUI_Button::mouse_down_handler() **********/

int    GLUI_Button::mouse_down_handler( int local_x, int local_y )
{
  int_val = 1;   /** A button always in unpressed before here, so
		   now we invariably set it to 'depressed' **/

  currently_inside = true;
  glutPostRedisplay();

  return false;
}


/****************************** GLUI_Button::mouse_up_handler() **********/

int    GLUI_Button::mouse_up_handler( int local_x, int local_y, bool inside )
{
  set_int_val( 0 );   /** A button always turns off after you press it **/

  currently_inside = false; 
  glutPostRedisplay();

  if ( inside ) { 
    /*** Invoke the user's callback ***/
    execute_callback();
  }

  return false;
}


/****************************** GLUI_Button::mouse_held_down_handler() ******/

int    GLUI_Button::mouse_held_down_handler( int local_x, int local_y,
					     bool new_inside)
{
  if (new_inside != currently_inside) {
    currently_inside = new_inside;
    glutPostRedisplay();
  }
  
  return false;
}


/****************************** GLUI_Button::key_handler() **********/

int    GLUI_Button::key_handler( unsigned char key,int modifiers )
{
  return false;
}

/********************************************** GLUI_Button::draw() **********/

void    GLUI_Button::draw()
{
	if (currently_inside)
	{
		glui->draw_lowered_box( 0, 0, w, h );
	}
	else
	{
		glui->draw_raised_box( 0, 0, w, h );
	}
	glTranslatef( 0.0, 0.0, 1.1);
}



