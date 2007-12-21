/****************************************************************************
  
  GLUI User Interface Toolkit
  ---------------------------

     glui_control.cpp - top-level GLUI_Control class


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

int _glui_draw_border_only = 0;

/*************************** Drawing Utility routines *********************/

/* Redraw this control. */
void	      GLUI_Control::redraw(void) {
    if (glui==NULL || hidden) return;
    if (glui->should_redraw_now(this))
      translate_and_draw_front();
}

/** Redraw everybody in our window. */
void	     GLUI_Control::redraw_window(void) {
  if (glui==NULL || hidden) return;
  if ( glui->get_glut_window_id() == -1 ) return;
  int orig = set_to_glut_window();
  glutPostRedisplay();
  restore_window(orig);
}



/* GLUI_Control::translate_and_draw_front() ********/
#warning "remove"
void GLUI_Control::translate_and_draw_front()
{
  GLUI_DRAWINGSENTINAL_IDIOM

  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  draw();
  glPopMatrix();
}


/********** GLUI_Control::set_to_bkgd_color() ********/

void GLUI_Control::set_to_bkgd_color( void )
{
  if ( NOT glui )
    return;

  glColor3ubv( glui->bkgd_color );
}

/******** GLUI_Control::draw_box_inwards_outline() ********/

void GLUI_Control::draw_box_inwards_outline( int x_min, int x_max, int y_min, int y_max )
{
  glBegin( GL_LINES );
  glColor3f( .5, .5, .5 );
  glVertex2i( x_min, y_min );     glVertex2i( x_max, y_min );
  glVertex2i( x_min, y_min );     glVertex2i( x_min, y_max );     

  glColor3f( 1., 1., 1. );
  glVertex2i( x_min, y_max );     glVertex2i( x_max, y_max );
  glVertex2i( x_max, y_max );     glVertex2i( x_max, y_min );

  if ( enabled )
    glColor3f( 0., 0., 0. );
  else
    glColor3f( .25, .25, .25 );

  glVertex2i( x_min+1, y_min+1 );     glVertex2i( x_max-1, y_min+1 );
  glVertex2i( x_min+1, y_min+1 );     glVertex2i( x_min+1, y_max-1 );

  glColor3f( .75, .75, .75 );
  glVertex2i( x_min+1, y_max-1 );     glVertex2i( x_max-1, y_max-1 );
  glVertex2i( x_max-1, y_max-1 );     glVertex2i( x_max-1, y_min+1 );
  glEnd();  
}


/******* GLUI_Control::draw_box() **********/

void GLUI_Control::draw_box( int x_min, int x_max, int y_min, int y_max, float r, float g, float b)
{
  if ( r == 1.0 AND g == 1.0 AND b == 1.0 AND NOT enabled AND glui ) {
    draw_bkgd_box( x_min, x_max, y_min, y_max );
    return;
  }

  glColor3f( r, g, b );
  glBegin( GL_QUADS );
  glVertex2i( x_min, y_min );       glVertex2i( x_max, y_min );
  glVertex2i( x_max, y_max );       glVertex2i( x_min, y_max );
  glEnd();
}


/******* GLUI_Control::draw_bkgd_box() **********/

void GLUI_Control::draw_bkgd_box( int x_min, int x_max, int y_min, int y_max )
{
  set_to_bkgd_color();

  glBegin( GL_QUADS );
  glVertex2i( x_min, y_min );       glVertex2i( x_max, y_min );
  glVertex2i( x_max, y_max );       glVertex2i( x_min, y_max );
  glEnd();
}


/**** GLUI_Control::draw_active_area() ********/

void GLUI_Control::draw_active_box( int x_min, int x_max, int y_min, int y_max )
{
  GLUI_DRAWINGSENTINAL_IDIOM

  if ( active ) {
    glEnable( GL_LINE_STIPPLE );
    glLineStipple( 1, 0x5555 );
    glColor3f( 0., 0., 0. );
  } else {
    set_to_bkgd_color();
  }

  glBegin( GL_LINE_LOOP );
  glVertex2i(x_min, y_min);      glVertex2i( x_max, y_min );
  glVertex2i(x_max, y_max);      glVertex2i( x_min, y_max );
  glEnd();
  
  glDisable( GL_LINE_STIPPLE );
}


/**** GLUI_Control::draw_emboss_box() ********/

void   GLUI_Control::draw_emboss_box(int x_min,int x_max,int y_min,int y_max)
{
  glLineWidth( 1.0 );
  glColor3f( 1.0, 1.0, 1.0 );

  glBegin( GL_LINE_LOOP );
  glVertex2i( x_min, y_min );    glVertex2i( x_max, y_min );
  glVertex2i( x_max, y_max );    glVertex2i( x_min, y_max );
  glEnd();
 
  glBegin( GL_LINE_LOOP );
  glVertex2i( x_min+1, y_min+1 );    glVertex2i( x_max-1, y_min+1 );
  glVertex2i( x_max-1, y_max-1 );    glVertex2i( x_min+1, y_max-1 );
  glEnd();
  
  glColor3f( .5, .5, .5 );
  glBegin( GL_LINE_LOOP );
  glVertex2i( x_min, y_min );
  glVertex2i( x_max-1, y_min );
  glVertex2i( x_max-1, y_max-1 );
  glVertex2i( x_min, y_max-1 );
  glEnd();
}




/****** GLUI_Control::set_to_glut_window() *********/
/*  Sets the current window to the glut window associated with this control  */

int GLUI_Control::set_to_glut_window()
{
  int orig_window;

  if ( NOT glui) 
    return 1;

  orig_window = glutGetWindow();

  glutSetWindow( glui->get_glut_window_id());

  return orig_window;
}


/********** GLUI_Control::restore_window() *********/

void GLUI_Control::restore_window(int orig)
{
  if ( orig > 0 )
    glutSetWindow( orig );
}



/****************************** Text ***************************/

/*************** GLUI_Control::set_font() **********/

void GLUI_Control::set_font(void *new_font)
{
  font = new_font;
  redraw();
}


/********** GLUI_Control::draw_string() ************/

void GLUI_Control::draw_string( const char *text )
{
  _glutBitmapString( get_font(), text );
}


/**************** GLUI_Control::draw_char() ********/

void GLUI_Control::draw_char(char c)
{
  glutBitmapCharacter( get_font(), c );
}


/*********** GLUI_Control::string_width() **********/

int GLUI_Control::string_width(const char *text)
{
  return _glutBitmapWidthString( get_font(), text );
}


/************* GLUI_Control::char_width() **********/

int GLUI_Control::char_width(char c)
{ /* Hash table for faster character width lookups - JVK 
       Speeds up the textbox a little bit.
  */
  int hash_index = c % CHAR_WIDTH_HASH_SIZE;
  if (char_widths[hash_index][0] != c) {
    char_widths[hash_index][0] = c;
    char_widths[hash_index][1] = glutBitmapWidth( get_font(), c );
  }
  return char_widths[hash_index][1];
}


/*************** GLUI_Control::get_font() **********/

void *GLUI_Control::get_font( void )
{
  /*** Does this control have its own font? ***/
  if ( this->font != NULL )
    return this->font;
  
  /*** Does the parent glui have a font? ***/
  if ( glui )
    return glui->font;

  /*** Return the default font ***/
  return GLUT_BITMAP_HELVETICA_12;
}


/************* GLUI_Control::draw_name() ***********/
/* This draws the name of the control as either black (if enabled), or       */
/* embossed if disabled.                                                     */

void GLUI_Control::draw_name(int x, int y)
{
  if ( NOT can_draw() )
    return;

  if ( enabled )
  {
    set_to_bkgd_color();
    glRasterPos2i(x+1, y+1);
    draw_string(name);
    glColor3b( 0, 0, 0 );
    glRasterPos2i(x, y);
    draw_string(name);
  }
  else
  {   /* Control is disabled - emboss the string */
    glColor3f( 1.0f, 1.0f, 1.0f );
    glRasterPos2i(x+1, y+1);
    draw_string(name);
    glColor3f( .4f, .4f, .4f );
    glRasterPos2i(x, y);
    draw_string(name);
  }
}


/**************************** Layout and Packing *********************/

/****** GLUI_Control::align() **************/

void GLUI_Control::align()
{
    int  parent_x, par_y, col_w, col_h, col_x_off, col_y_off;
    int  orig_x_abs;
    GLUI_Control* par;

    orig_x_abs = x_abs;

    /* Fix alignment bug relating to columns              */
    /*return;              */

    if ( NULL == parent() )
        return;  /* Clearly this shouldn't happen, though */

    par = dynamic_cast<GLUI_Control*>(parent());
    if ( NULL == par )
        return;

    if ( alignment == GLUI_ALIGN_LEFT ) {
        x_abs = par->x_abs + par->x_off;
    }
    else if ( alignment == GLUI_ALIGN_RIGHT ) {
        x_abs = par->x_abs + par->w - par->x_off - this->w;
    }
    else if ( alignment == GLUI_ALIGN_CENTER ) {
        x_abs = par->x_abs + (par->w - this->w) / 2;
    }


}


/************** GLUI_Control::pack() ************/
/* Recalculate positions and offsets  */

void    GLUI_Control::pack( int x, int y )
{
    return;
}



/******************************** Live Variables **************************/
/*********** GLUI_Control::sync_live() ************/
/* Reads live variable and sets control to its current value                */
/* This function is recursive, and operates on control's children           */

void GLUI_Control::sync_live(int recurse, int draw_it)
{
  GLUI_Node *node;
  int        sync_it=true;
  int        i;
  float      *fp;
  bool       changed = false;

  /*** If this is currently active control, and mouse button is down,
    don't sync ***/
  if ( glui )
  {
    if ( this == glui->active_control AND glui->mouse_button_down )
      sync_it = false;

    /*** Actually, just disable syncing if button is down ***/
    /*** Nope, go ahead and sync if mouse is down - this allows syncing in
      callbacks ***/
    if ( 0 ) { /* THIS CODE BELOW SHOULD NOT BE EXECUTED */
      if ( glui->mouse_button_down ) {
	debug( "Can't sync\n" );
	return;
      }
    }
  }

  /***  If this control has a live variable, we check its current value
    against the stored value in the control  ***/

  if ( ptr_val != NULL ) {
    if ( live_type == GLUI_LIVE_NONE OR NOT sync_it ) {
    }
    else if ( live_type == GLUI_LIVE_INT ) {
      if ( *((int*)ptr_val) != last_live_int ) {
        set_int_val( *((int*)ptr_val) );
        last_live_int = *((int*)ptr_val);
        changed = true;
      }
    }   
    else if ( live_type == GLUI_LIVE_FLOAT ) {
      if ( *((float*)ptr_val) != last_live_float ) {
        set_float_val( *((float*)ptr_val) );
        last_live_float = *((float*)ptr_val);
        changed = true;
      }
    } 
    else if ( live_type == GLUI_LIVE_TEXT ) {
      if ( last_live_text.compare((const char*)ptr_val) != 0 ) {
        set_text( (char*) ptr_val );
        last_live_text = (const char*)ptr_val;
        changed = true;
      }
    } 
    else if ( live_type == GLUI_LIVE_STRING ) {
      if ( last_live_text.compare(((std::string*) ptr_val)->c_str()) != 0 ) {
        set_text( ((std::string*) ptr_val)->c_str());
        last_live_text = *((std::string*) ptr_val);
        changed = true;
      }
    } 
    else if ( live_type == GLUI_LIVE_FLOAT_ARRAY ) { 
      /***  Step through the arrays, and see if they're the same  ***/
      
      fp = (float*) ptr_val;
      for ( i=0; i<float_array_size; i++ ) {
        if ( *fp != last_live_float_array[i] ) {
          changed = true;
          break;
        }
		
        fp++;
      }
      
      if ( changed == true) {
        fp = (float*) ptr_val;
        set_float_array_val( fp );
        for ( i=0; i<float_array_size; i++ ) {
          last_live_float_array[i] = *fp;
          fp++;
        }
      }
    }
    else if ( live_type == GLUI_LIVE_DOUBLE ) {
    }
  }

  /***  If this control is changed and we're supposed to be drawing, then
    draw it now    ***/
  if ( changed == true AND draw_it ) {
    redraw();
  }

  if ( recurse ) {
    /*** Now recursively output live vars for all children ***/
    node = this->first_child();
    while( node ) {
      ((GLUI_Control*) node)->sync_live(true, true);
      node = node->next();
    }

    if ( collapsible == true AND is_open == false ) {
      /** Here we have a collapsed control (e.g., a rollout that is closed **/
      /** We need to go in and sync all the collapsed controls inside      **/
       
      node = this->collapsed_node.first_child();
      while( node ) {
	((GLUI_Control*) node)->sync_live(true, false);
	node = node->next();
      }
    }
  }
}


/********** GLUI_Control::output_live() ************/
/* Writes current value of control to live variable.                         */

void GLUI_Control::output_live(int update_main_gfx)
{
  int    i;
  float *fp;

  if ( ptr_val == NULL )
    return;
   
  if ( NOT live_inited ) 
    return;
   
  if ( live_type == GLUI_LIVE_NONE ) {
  }
  else if ( live_type == GLUI_LIVE_INT ) {
    *((int*)ptr_val) = int_val;
    last_live_int    = int_val;
  } 
  else if ( live_type == GLUI_LIVE_FLOAT ) {
    *((float*)ptr_val) = float_val;
    last_live_float    = float_val;
  } 
  else if ( live_type == GLUI_LIVE_TEXT ) {
    strncpy( (char*) ptr_val, text.c_str(), text.length()+1);
    last_live_text =  text;
  } 
  else if ( live_type == GLUI_LIVE_STRING ) {
    (*(std::string*)ptr_val)= text.c_str();
    last_live_text =  text;
  } 
  else if ( live_type == GLUI_LIVE_FLOAT_ARRAY ) {
    fp = (float*) ptr_val;

    for( i=0; i<float_array_size; i++ ) {
      *fp                      = float_array_val[i];
      last_live_float_array[i] = float_array_val[i];
      fp++;
    }
  }
  else if ( live_type == GLUI_LIVE_DOUBLE ) {
  }

  /** Update the main gfx window? **/
  if ( update_main_gfx AND this->glui != NULL ) {
    this->glui->post_update_main_gfx();
  }
}


/****** GLUI_Control::execute_callback() **********/

void GLUI_Control::execute_callback()
{
  int old_window;
  
  old_window = glutGetWindow();

  if ( glui AND glui->main_gfx_window_id != -1 ) 
    glutSetWindow( glui->main_gfx_window_id );

  this->callback( this );
//  if ( this->callback ) 
//    this->callback( this->user_id );

  glutSetWindow( old_window );
}


/************** GLUI_Control::init_live() **********/
/* Reads in  value of a live variable.  Called once, when ctrl is created   */

void GLUI_Control::init_live()
{
  int    i;
  float *fp;

  if ( ptr_val == NULL )
    return;

  if ( live_type == GLUI_LIVE_NONE ) {
  }
  else if ( live_type == GLUI_LIVE_INT ) {
    set_int_val( *((int*)ptr_val) );
    last_live_int = *((int*)ptr_val);
  } 
  else if ( live_type == GLUI_LIVE_FLOAT ) {
    set_float_val( *((float*)ptr_val) );
    last_live_float = *((float*)ptr_val);
  } 
  else if ( live_type == GLUI_LIVE_TEXT ) {
    set_text( (const char*) ptr_val );
    last_live_text = (const char*) ptr_val;
  }
  else if ( live_type == GLUI_LIVE_STRING ) {
    set_text( ((std::string*) ptr_val)->c_str() );
    last_live_text = ((std::string*) ptr_val)->c_str();
  }
  else if ( live_type == GLUI_LIVE_FLOAT_ARRAY ) {
    set_float_array_val( (float*) ptr_val );

    fp = (float*) ptr_val;

    for( i=0; i<float_array_size; i++ ) {
      last_live_float_array[i] = *fp;
      fp++;
    }

  }
  else if ( live_type == GLUI_LIVE_DOUBLE ) {
  }

  live_inited = true;
}

/***** GLUI_Control::set_float_array_val() ********/

void  GLUI_Control::set_float_array_val( float *array_ptr )
{
  int i;

  if ( array_ptr == NULL )
    return;

  for( i=0; i<float_array_size; i++ ) {
    float_array_val[i] = array_ptr[i];
  }

  /*** Output the live var, without updating the main gfx window ***/
  output_live(false);
}


/***** GLUI_Control::get_float_array_val() ********/

void  GLUI_Control::get_float_array_val( float *array_ptr )
{
  int i;

  if ( array_ptr == NULL )
    return;

  for( i=0; i<float_array_size; i++ ) {
    array_ptr[i] = float_array_val[i];
  }
}



/**************************** Little Utility Routines ********************/

/**** GLUI_Control::set_name() ********************/

void   GLUI_Control::set_name( char *str )
{
  name.clear();
  name = str;
  redraw(); 
}

/**** GLUI_Control::enable() ****************/

void GLUI_Control::enable()
{
  GLUI_Control *node;

  enabled = true;
   
  if ( NOT glui )
    return;

  redraw();

  /*** Now recursively enable all buttons below it ***/
  node = (GLUI_Control*) first_child();
  while(node)
  {
    node->enable();
    node = (GLUI_Control*) node->next();
  }
}


/***** GLUI_Control::disable() ****************/

void GLUI_Control::disable()
{
  GLUI_Control *node;

  enabled = false;
  
  if ( NOT glui )
    return;

  if ( glui->active_control == this )
    glui->deactivate_current_control();
  redraw();

  /*** Now recursively disable all buttons below it ***/
  node = (GLUI_Control*) first_child();
  while(node) {
    node->disable();
    node = (GLUI_Control*) node->next();
  }
}

/******* GLUI_Control::set_w() **************/

void GLUI_Control::set_w(int new_w)
{
  w = new_w;
  update_size();  /* Make sure control is big enough to fit text */
  if (glui) glui->refresh();
}


/**** GLUI_Control::set_h() **************/

void GLUI_Control::set_h(int new_h)
{
  h = new_h;
  update_size();  /* Make sure control is big enough to fit text */
  if (glui) glui->refresh();
}


/***** GLUI_Control::set_alignment() ******/

void GLUI_Control::set_alignment(int new_align)
{
  alignment = new_align;

  if ( glui )
  {
    glui->align_controls(this);
    redraw_window();
  }
}


/***** GLUI_Control::needs_idle() *********/
/* This method gets overloaded by specific classes, e.g. Spinner.            */
/* It returns whether or not a control needs to receive an idle event or not */
/* For example, a spinner only needs idle events when the user is holding    */
/* the mouse down in one of the arrows.  Otherwise, don't waste cycles       */
/* and OpenGL context switching by calling its idle.                         */

bool GLUI_Control::needs_idle() const
{ 
  return false; 
}


/********* GLUI_Control::~GLUI_Control() **********/

GLUI_Control::~GLUI_Control()
{
  GLUI_Control *item = (GLUI_Control*) this->first_child();

  while (item) 
  {
    GLUI_Control *tmp = item;
    item = (GLUI_Control*) item->next();
    delete tmp;
  }
}

/********* GLUI_Control::hide_internal() ********/
/** Sets hidden==true for this  control and all its siblings.             */
/**  If recurse is true, we go to children as well                       */

void         GLUI_Control::hide_internal( int recurse )
{
  GLUI_Node *node;

  node = (GLUI_Node *) this;
  while( node != NULL ) {
    ((GLUI_Control*)node)->hidden = true;

    if ( recurse AND node->first_child() != NULL )  
      ((GLUI_Control*) node->first_child())->hide_internal(true);
      
    node = node->next();
  }

  node = this->collapsed_node.first_child();
  while( node != NULL ) {
    ((GLUI_Control*)node)->hidden = true;

    if ( recurse AND node->first_child() != NULL )  
      ((GLUI_Control*) node->first_child())->hide_internal(true);
      
    node = node->next();
  }
}


/********* GLUI_Control::unhide_internal() ********/
/** Sets hidden==false for this  control and all its siblings.             */
/**  If recurse is true, we go to children as well                       */

void         GLUI_Control::unhide_internal( int recurse )
{
  GLUI_Node *node;

  node = (GLUI_Node *) this;
  while( node != NULL ) {
    debug( "unhide: %s [%d]\n", ((GLUI_Control*)node)->name.c_str(),
	    ((GLUI_Control*)node)->hidden );
    ((GLUI_Control*)node)->hidden = false;

    if ( recurse AND node->first_child() != NULL )
      ((GLUI_Control*) node->first_child())->unhide_internal(true);

    node = node->next();
  }

  node = this->collapsed_node.first_child();
  while( node != NULL ) {
    ((GLUI_Control*)node)->hidden = false;

    if ( recurse AND node->first_child() != NULL )
      ((GLUI_Control*) node->first_child())->unhide_internal(true);

    node = node->next();
  }
}
