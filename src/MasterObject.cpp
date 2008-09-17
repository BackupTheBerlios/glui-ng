/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui.cpp

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
#include <GL/glui/MasterObject.h>
using namespace GLUI;

#warning "GLUI class is a duplicate of GLUI_Main, remove!"






///////////////////////////////////////////////////////////////////////////
MasterObject* MasterObject::Instance()
{
    static MasterObject object;
    return &object;
}

//////////////////////////////////////////////////////////////////////////
GLUIWindow*      MasterObject::FindWindow( WindowId window_id )
{
  Node *node;

  node = this->first_child();
  Window* win = dynamic_cast<Window*>(node);

  while( win ) {
    if ( win->GetWindowId() == window_id )
      return win;

    win = dynamic_cast<Window*>(win->next());
  }
  return NULL;
}

////////////////////////////////////////////////////////////////////////
int  MasterObject::add_control( Node *window )
{
    // only allow first childs of this to be of Window type
    if ( NULL == dynamic_cast<Window*>(window)) return EINVAL;
    return Node::add_control(window);
}


///////////////////////////////////////////////////////////////////////

GLUI *GLUI_Master_Object::create_glui_subwindow( int parent_window,
						   long flags )
{
  std::string new_name;
  glui_format_str( new_name, "subwin_%p", this );

  GLUI *new_glui = new GLUI( new_name.c_str(), flags | GLUI_SUBWINDOW, 0,0,
		    parent_window );
  new_glui->main_panel->set_int_val( GLUI_PANEL_EMBOSSED );
  new_glui->link_this_to_parent_last( &this->gluis );
  return new_glui;
}





#error "continue from here"


/****************************** glui_parent_window_reshape_func() **********/
/* This is the reshape callback for a window that contains subwindows      */

void glui_parent_window_reshape_func( int w, int h )
{
  int   current_window;
  GLUI  *glui;
  int   first = true;

  GLUI_debug::Instance()->print( __FILE__, __LINE__,
			"glui_parent_window_reshape_func: %d\n", glutGetWindow() );

  current_window = glutGetWindow();

  glui = (GLUI*) GLUI_Master.gluis.first_child();
  while( glui ) {
    if ( TEST_AND( glui->flags, GLUI_SUBWINDOW) AND
	 glui->parent_window == current_window ) {
      glutSetWindow( glui->get_glut_window_id());
      glui->check_subwindow_position();
      glutSetWindow( current_window );

      if ( first ) {
        if (glui->glut_reshape_CB) glui->glut_reshape_CB( w, h );

        first = false;
      }
    }

    glui = (GLUI*) glui->next();
  }
}


/****************************** glui_parent_window_keyboard_func() **********/

void glui_parent_window_keyboard_func(unsigned char key, int x, int y)
{
  GLUI_debug::Instance()->print( __FILE__, __LINE__,
         "glui_parent_window_keyboard_func: %d\n", glutGetWindow() );

  int   current_window;
  GLUI  *glui;

  current_window = glutGetWindow();

  if ( GLUI_Master.active_control_glui AND GLUI_Master.active_control ) {
    glutSetWindow( GLUI_Master.active_control_glui->get_glut_window_id() );

    GLUI_Master.active_control_glui->keyboard(key,x,y);

    glutSetWindow( current_window );
  }
  else {
    glui = (GLUI*) GLUI_Master.gluis.first_child();
    while( glui ) {
      if ( TEST_AND( glui->flags, GLUI_SUBWINDOW) AND
           glui->parent_window == current_window AND
           glui->glut_keyboard_CB )
      {
        glui->glut_keyboard_CB( key, x, y );
        break;
      }

      glui = (GLUI*) glui->next();
    }
  }
}


/****************************** glui_parent_window_special_func() **********/

void glui_parent_window_special_func(int key, int x, int y)
{
  GLUI_debug::Instance()->print( __FILE__, __LINE__,
         "glui_parent_window_special_func: %d\n", glutGetWindow() );

  int   current_window;
  GLUI  *glui;

  /**  If clicking in the main area of a window w/subwindows,
    deactivate any current control  **/
  if ( GLUI_Master.active_control_glui != NULL )
    GLUI_Master.active_control_glui->deactivate_current_control();

  /***   Now pass on the mouse event   ***/

  current_window = glutGetWindow();

  glui = (GLUI*) GLUI_Master.gluis.first_child();
  while( glui ) {
    if ( TEST_AND( glui->flags, GLUI_SUBWINDOW) AND
         glui->parent_window == current_window )
    {
      glutSetWindow( glui->get_glut_window_id());
      if (glui->glut_special_CB) glui->glut_special_CB( key, x, y );
      break;
    }

    glui = (GLUI*) glui->next();
  }
}


/****************************** glui_parent_window_mouse_func() **********/

void glui_parent_window_mouse_func(int button, int state, int x, int y)
{
  int   current_window;
  GLUI  *glui;

  /**  If clicking in the main area of a window w/subwindows,
    deactivate any current control  **/
  if ( GLUI_Master.active_control_glui != NULL )
    GLUI_Master.active_control_glui->deactivate_current_control();


  /***   Now pass on the mouse event   ***/

  current_window = glutGetWindow();

  glui = (GLUI*) GLUI_Master.gluis.first_child();
  while( glui ) {
    if ( TEST_AND( glui->flags, GLUI_SUBWINDOW) AND
         glui->parent_window == current_window AND
         glui->glut_mouse_CB)
    {
      glutSetWindow( glui->get_glut_window_id());
      glui->glut_mouse_CB( button, state, x, y );
      break;
    }

    glui = (GLUI*) glui->next();
  }
}


/************************** GLUI_Master_Object::find_glut_window() **********/

GLUI_Glut_Window  *GLUI_Master_Object::find_glut_window( int window_id )
{
  GLUI_Glut_Window *window;

  window = (GLUI_Glut_Window*) glut_windows.first_child();
  while( window ) {
    if ( window->glut_window_id == window_id )
      return window;

    window = (GLUI_Glut_Window*) window->next();
  }

  /***  Window not found - return NULL ***/
  return NULL;
}


/******************** GLUI_Master_Object::add_cb_to_glut_window() **********/

void     GLUI_Master_Object::add_cb_to_glut_window(int window_id,
						   int cb_type,void *cb)
{
  GLUI_Glut_Window *window;

  window = find_glut_window( window_id );
  if ( NOT window ) {
    /***  Allocate new window structure  ***/

    window                 = new GLUI_Glut_Window;
    window->glut_window_id = window_id;
    window->link_this_to_parent_last( (GLUI_Node*) &this->glut_windows );
  }

  switch( cb_type ) {
  case GLUI_GLUT_RESHAPE:
    window->glut_reshape_CB   = (void(*)(int,int)) cb;
    break;
  case GLUI_GLUT_DISPLAY:
    window->glut_display_CB   = (void(*)()) cb;
    break;
  case GLUI_GLUT_KEYBOARD:
    window->glut_keyboard_CB  = (void(*)(unsigned char,int,int)) cb;
    break;
  case GLUI_GLUT_SPECIAL:
    window->glut_special_CB   = (void(*)(int,int,int)) cb;
    break;
  case GLUI_GLUT_MOUSE:
    window->glut_mouse_CB     = (void(*)(int,int,int,int)) cb;
    break;
  case GLUI_GLUT_MOTION:
    window->glut_motion_CB    = (void(*)(int,int)) cb;
    break;
  case GLUI_GLUT_PASSIVE_MOTION:
    window->glut_passive_motion_CB = (void(*)(int,int)) cb;
    break;
  case GLUI_GLUT_ENTRY:
    window->glut_entry_CB     = (void(*)(int)) cb;
    break;
  case GLUI_GLUT_VISIBILITY:
    window->glut_visibility_CB= (void(*)(int)) cb;
    break;
  }
}


/************* GLUI_Master_Object::set_left_button_glut_menu_control() *****/

void  GLUI_Master_Object::set_left_button_glut_menu_control(
							    GLUI_Control *control )
{
  curr_left_button_glut_menu = control;
}





/***************** GLUI_Master_Object::get_main_gfx_viewport() ***********/

void     GLUI_Master_Object::get_viewport_area( int *x, int *y,
						int *w, int *h )
{
  GLUI *curr_glui;
  int   curr_x, curr_y, curr_w, curr_h;
  int   curr_window;

  curr_window = glutGetWindow();
  curr_x = 0;
  curr_y = 0;
  curr_w = glutGet( GLUT_WINDOW_WIDTH );
  curr_h = glutGet( GLUT_WINDOW_HEIGHT );

  curr_glui = (GLUI*) gluis.first_child();
  while( curr_glui ) {
    if ( TEST_AND( curr_glui->flags, GLUI_SUBWINDOW) AND
	 curr_glui->parent_window == curr_window ) {

// this debug line cause obscure segfaulting.... the NodeName seems to be corrupted
//      debug( "%s -> %d   %d %d\n", curr_glui->NodeName, curr_glui->flags,
//				curr_glui->w, curr_glui->h );

      if ( TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_LEFT ) ) {
	curr_x += curr_glui->w;
	curr_w -= curr_glui->w;
      }
      else if ( TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_BOTTOM ) ) {
	curr_y += curr_glui->h;
	curr_h -= curr_glui->h;
      }
      else if ( TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_RIGHT ) ) {
	curr_w -= curr_glui->w;
      }
      else if ( TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_TOP ) ) {
	curr_h -= curr_glui->h;
      }
    }

    curr_glui = (GLUI*) curr_glui->next();
  }

  curr_x = MAX( 0, curr_x );
  curr_y = MAX( 0, curr_y );
  curr_w = MAX( 0, curr_w );
  curr_h = MAX( 0, curr_h );

  *x = curr_x;
  *y = curr_y;
  *w = curr_w;
  *h = curr_h;
}


/*****************GLUI_Master_Object::auto_set_main_gfx_viewport() **********/

void           GLUI_Master_Object::auto_set_viewport( void )
{
  int x, y, w, h;

  get_viewport_area( &x, &y, &w, &h );
  glViewport( MAX(x,0), MAX(y,0), MAX(w,0), MAX(h,0) );
}



/***************************************** GLUI::show() **********************/
#error "move this to glut window class, define MAP and UNMAP API"

void            GLUI::show( void )
{
  int orig_window;

  orig_window = main_panel->set_to_glut_window();

  glutShowWindow();

  main_panel->restore_window(orig_window);
}



/***************************************** GLUI::hide() **********************/
#error "move this to glut window class, define MAP and UNMAP API"
void            GLUI::hide( void )
{
  int orig_window;

  this->deactivate_current_control();

  orig_window = main_panel->set_to_glut_window();

  glutHideWindow();

  main_panel->restore_window(orig_window);
}


/**************** GLUI_DrawingSentinal **************/
GLUI_DrawingSentinal::GLUI_DrawingSentinal(GLUI_Control *c_)
	:c(c_)
{
	orig_win = c->set_to_glut_window();
	orig_buf = c->glui->set_current_draw_buffer();
}
GLUI_DrawingSentinal::~GLUI_DrawingSentinal() {
	c->glui->restore_draw_buffer(orig_buf);
	c->restore_window(orig_win);
}


void GLUI_Master_Object::glui_setIdleFuncIfNecessary( void )
{
    GLUI *glui;

    glui = (GLUI*) GLUI_Master.gluis.first_child();
    int necessary;
    if (this->glut_idle_CB)
        necessary = true;
    else {
        necessary = false;
        while( glui ) {
            if( glui->needs_idle() ) {
                necessary = true;
                break;
            }
            glui = (GLUI*) glui->next();
        }
    }
    if( necessary )
        glutIdleFunc( glui_idle_func );
    else
        glutIdleFunc( NULL );
}

