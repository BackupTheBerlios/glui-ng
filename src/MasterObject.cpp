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

