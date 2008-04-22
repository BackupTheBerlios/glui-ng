
/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_checkbox - GLUI_Checkbox control class


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

/****************************** GLUI_Checkbox::GLUI_Checkbox() **********/

GLUI_Checkbox::GLUI_Checkbox( GLUI_Node *parent,
                              const char *name, int *value_ptr,
                              int id,
                              GLUI_CB cb ): GLUI_Container(name)
{
  common_init();

  set_ptr_val( value_ptr );
  user_id    = id;
  callback   = cb;

  parent->add_control( this );
  this->resizeable = AdaptThisToFitChilds;
  this->orientation = GLUI_horizontal;

  this->x_off_left = 40;
  this->y_off_top  = 9;
  text = new GLUI_StaticText(this, "text" );
  text->set_text(name);
  init_live();
}

GLUI_Checkbox::~GLUI_Checkbox()
{
	delete text;
}

/****************************** GLUI_Checkbox::mouse_down_handler() **********/

int    GLUI_Checkbox::mouse_down_handler( int local_x, int local_y )
{
  orig_value = int_val;
  int_val = !int_val;

  currently_inside = true;
  glutPostRedisplay();

  return false;
}


/****************************** GLUI_Checkbox::mouse_up_handler() **********/

int    GLUI_Checkbox::mouse_up_handler( int local_x, int local_y, bool inside )
{
  if ( NOT inside ) { /* undo effect on value */
    int_val = orig_value;
  }
  else {
    set_int_val( int_val );

    /*** Invoke the callback ***/
    execute_callback();
  }

  return false;
}


/****************************** GLUI_Checkbox::mouse_held_down_handler() ******/

int    GLUI_Checkbox::mouse_held_down_handler( int local_x, int local_y,
					       bool inside)
{
  /********** Toggle checked and unchecked bitmap if we're entering or
    leaving the checkbox area **********/
  if ( inside != currently_inside ) {
     int_val = !int_val;
     currently_inside = inside;
     glutPostRedisplay();
  }

  return false;
}


/****************************** GLUI_Checkbox::key_handler() **********/

int    GLUI_Checkbox::key_handler( unsigned char key,int modifiers )
{
  return false;
}


/****************************** GLUI_Checkbox::draw() **********/
void    GLUI_Checkbox::draw()
{
    GLUI_DRAWINGSENTINAL_IDIOM

        if ( int_val != 0 ) {
            if ( enabled )
                glui->std_bitmaps.draw( GLUI_STDBITMAP_CHECKBOX_ON, 0, 0 );
            else
                glui->std_bitmaps.draw( GLUI_STDBITMAP_CHECKBOX_ON_DIS, 0, 0 );
        }
        else {
            if ( enabled )
                glui->std_bitmaps.draw( GLUI_STDBITMAP_CHECKBOX_OFF, 0, 0 );
            else
                glui->std_bitmaps.draw( GLUI_STDBITMAP_CHECKBOX_OFF_DIS, 0, 0 );
        }
	GLUI_debug::Instance()->FlushGL();
}

/**************************** GLUI_Checkbox::draw_active_area() **************/
/*
void    GLUI_Checkbox::draw_active_area( void )
{
  GLUI_DRAWINGSENTINAL_IDIOM
  int text_width, left, right;

  text_width = _glutBitmapWidthString( glui->font, name.c_str() );
  left       = text_x_offset-3;
  right      = left + 7 + text_width;

//  if ( active ) {
    glEnable( GL_LINE_STIPPLE );
    glLineStipple( 1, 0x5555 );
    glColor3f( 0., 0., 0. );
//  } else {
//    glColor3ubv( glui->bkgd_color );
//  }

  glBegin( GL_LINE_LOOP );
  glVertex2i(left,0);     glVertex2i( right,0);
  glVertex2i(right,h+1);   glVertex2i( left,h+1);
  glEnd();

  glDisable( GL_LINE_STIPPLE );
}*/


/************************************ GLUI_Checkbox::update_size() **********/

void   GLUI_Checkbox::update_size( void )
{
	GLUI_Container::update_size();
	this->w += 13;
	this->h = max<int>(13, this->h);
}


/********************************* GLUI_Checkbox::set_int_val() **************/

void    GLUI_Checkbox::set_int_val( int new_val )
{
  int_val = new_val;

  /*** Update the variable we're (possibly) pointing to ***/
  output_live(true);
  glutPostRedisplay();
}
