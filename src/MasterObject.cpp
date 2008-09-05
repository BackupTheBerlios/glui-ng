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

#warning "GLUI class is a duplicate of GLUI_Main, remove!"




/************************************ GLUI_Node::add_control() **************/

int GLUI_Node::add_control( GLUI_Node *child )
{
	child->link_this_to_parent_last( this );
	return true;
}

/************************************ GLUI_Main::add_control() **************/

int GLUI_Main::add_control( GLUI_Node *parent, GLUI_Node *control )
{
	control->link_this_to_parent_last( parent );
	return true;
}



/*** This object must be used to create a GLUI ***/

GLUI_Master_Object GLUI_Master;

/************************************ finish_drawing() ***********
  Probably a silly routine.  Called after all event handling callbacks.
*/

static void finish_drawing(void)
{
	glFinish();
}

/************************************ GLUI_CB::operator()() ************/
void GLUI_CB::operator()(GLUI_Control*ctrl) const
{
  if (idCB)  idCB(ctrl->user_id);
  if (objCB) objCB(ctrl);
}


/*********************************** GLUI_Master_Object::GLUI_Master_Object() ******/
GLUI_Master_Object::TheInstance = NULL;
GLUI_Master_Object::ClientCount = 0;

GLUI_Master_Object* GLUI_Master_Object::Register()
{
	if (TheInstance == NULL)
		TheInstance = new GLUI_Master_Object;
	ClientCount++;
	return TheInstance;
}

void GLUI_Master_Object::DeRegister()
{
	ClientCount--;
	if (ClientCount == 0)
	{
		delete TheInstance;
	}
}


GLUI_Master_Object::GLUI_Master_Object()
    :   gluis("gluis")
	,   glui_id_counter(1)
    ,   glut_windows("glut_windows")
    ,   glut_idle_CB(NULL)

{
}

GLUI_Master_Object::~GLUI_Master_Object()
{

}


/************************** GLUI_Master_Object::create_glui_subwindow() ******/

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


/********************** GLUI_Master_Object::find_glui_by_window_id() ********/

GLUI  *GLUI_Master_Object::find_glui_by_window_id( int window_id )
{
  GLUI_Node *node;

  node = gluis.first_child();
  while( node ) {
    if ( ((GLUI*)node)->get_glut_window_id() == window_id )
      return (GLUI*) node;

    node = node->next();
  }
  return NULL;
}




/****************************** GLUI_Main::visibility() **************/

void    GLUI_Main::visibility(int state)
{
}




/******************************************* GLUI_Main::find_control() ******/
GLUI_Control  *GLUI_Main::find_control( int x, int y, GLUI_Control * parent )
{
    GLUI_Control *node, *found, *child;

    found = NULL;

    if( parent == NULL ) {
        node = main_panel;
    }
    else
    {
        node = parent;
    }
    if ( PT_IN_BOX( x, y,
                    node->x_abs, node->x_abs + node->w,
                    node->y_abs, node->y_abs + node->h ) )
    {
        //debug ( "ctrl fits: '%s'\n", node->NodeName );
        child = dynamic_cast<GLUI_Control *>(node->first_child());
        if ( child != NULL )
        {
            //debug ( "ctrl '%s' has childs\n", node->NodeName );
            do
            {
                found = find_control ( x, y, child);
                if (NULL == found) child =  dynamic_cast<GLUI_Control *>(child->next());
            }
            while ( found == NULL && child != NULL );
        }
        if ( found == NULL ) found = node;

        // SPECIAL CASE: for edittext boxes, we make sure click is
        //  in box, and not on name string.  This should be generalized
        //  for all controls later...
        if ( dynamic_cast<GLUI_EditText*>(node) )
        {
            if ( x < node->x_abs + ((GLUI_EditText*)node)->text_x_offset )
            {
                return (GLUI_Control*) node->parent();
            }
        }
        if( parent == NULL ) {
			GLUI_debug::Instance()->print( __FILE__, __LINE__,
                   "found ctrl: '%s'\n",
                    dynamic_cast<GLUI_Node*>(found)->whole_tree() );
        }
        return found;
    }
    else
    {
	  GLUI_debug::Instance()->print( __FILE__, __LINE__,
              " not in %s.... skipping the whole tree \n", node->NodeName);
        return NULL;
    }

}

/************************************* GLUI_Main::pack_controls() ***********/

void      GLUI_Main::pack_controls( void )
{
    main_panel->update_size();
    main_panel->align();
    main_panel->pack(0,0);

  /***  If this is a subwindow, expand panel to fit parent window  ***/
  if ( TEST_AND( this->flags, GLUI_SUBWINDOW ) ) {
    int parent_h, parent_w;
    int orig_window;

    orig_window = glutGetWindow();
    glutSetWindow( this->top_level_glut_window_id );
    parent_h = glutGet( GLUT_WINDOW_HEIGHT );
    parent_w = glutGet( GLUT_WINDOW_WIDTH );

    glutSetWindow( orig_window );

  GLUI_debug::Instance()->print( __FILE__, __LINE__,
           "%d %d\n", parent_h, parent_w );

    if ( 1 ) {
        if ( TEST_AND(this->flags,GLUI_SUBWINDOW_TOP )) {
            main_panel->w = MAX( main_panel->w, parent_w );
        }
        else if ( TEST_AND(this->flags,GLUI_SUBWINDOW_LEFT )) {
            main_panel->h = MAX( main_panel->h, parent_h );
        }
        else if ( TEST_AND(this->flags,GLUI_SUBWINDOW_BOTTOM )) {
            main_panel->w = MAX( main_panel->w, parent_w );
        }
        else if ( TEST_AND(this->flags,GLUI_SUBWINDOW_RIGHT )) {
            main_panel->h = MAX( main_panel->h, parent_h );
        }
    }
  }

  this->w = main_panel->w;
  this->h = main_panel->h;
}



/*********************************** GLUI::set_main_gfx_window() ************/

void   GLUI::set_main_gfx_window( int window_id )
{
  main_gfx_window_id = window_id;
}


/********************************* GLUI_Main::post_update_main_gfx() ********/

void   GLUI_Main::post_update_main_gfx( void )
{
  int old_window;

  if ( main_gfx_window_id > 0 ) {
    old_window = glutGetWindow();
    glutSetWindow( main_gfx_window_id );
    glutPostRedisplay();
    if( old_window > 0 )
      glutSetWindow( old_window );
  }
}

/********************************* GLUI_Main::should_redraw_now() ********/
/** Return true if this control should redraw itself immediately (front buffer);
   Or queue up a redraw and return false if it shouldn't (back buffer).

   Called from GLUI_Control::redraw.
*/
bool	     GLUI_Main::should_redraw_now(GLUI_Control *ctl)
{
  switch (get_buffer_mode()) {
  case buffer_front: return true; /* always draw in front-buffer mode */
  case buffer_back: {
    int orig = ctl->set_to_glut_window();
    glutPostRedisplay(); /* redraw soon */
    ctl->restore_window(orig);
    return false; /* don't draw now. */
   }
  }
  return false; /* never executed */
}



/********************************* GLUI_Main::restore_draw_buffer() **********/

void         GLUI_Main::restore_draw_buffer( int buffer_state )
{
  glDrawBuffer( buffer_state );
}


/******************************************** GLUI_Main::GLUI_Main() ********/

GLUI_Main::GLUI_Main( const char *text, long flags, int x, int y, int parent_window )
{
  mouse_button_down       = false;
  w                       = 0;
  h                       = 0;
  active_control          = NULL;
  mouse_over_control      = NULL;
  main_gfx_window_id      = -1;
  glut_window_id          = -1;
  curr_modifiers          = 0;
  closing                 = false;
#warning "what does this line is there? it's an arg..... one is enough!"
  parent_window           = -1;
  glui_id                 = GLUI_Master.glui_id_counter;
  GLUI_Master.glui_id_counter++;

  font                    = GLUT_BITMAP_HELVETICA_12;
  curr_cursor             = GLUT_CURSOR_LEFT_ARROW;



  CreateGluiWindow(text, flags, x, y, parent_window);
  /*** Create the main panel ***/
  main_panel              = new GLUI_Panel((GLUI*)this, NULL, "root panel");
  main_panel->set_int_val( GLUI_PANEL_NONE );
}


/************************************* GLUI_Main::activate_control() *********/

void         GLUI_Main::activate_control( GLUI_Control *control, int how )
{
  /** Are we not activating a control in the same window as the
    previous active control? */
  if ( GLUI_Master.active_control_glui AND
       this != (GLUI_Main*) GLUI_Master.active_control_glui ) {
    GLUI_Master.active_control_glui->deactivate_current_control();
  }

  /*******      Now activate it      *****/
  if ( control != NULL AND control->can_activate AND control->enabled ) {
    active_control = control;

    control->activate(how);

    glutPostRedisplay();

  }
  else {
    active_control = NULL;
  }

  GLUI_debug::Instance()->print( __FILE__, __LINE__,
         "activate: %d\n", glutGetWindow() );
  GLUI_Master.active_control      = active_control;
  GLUI_Master.active_control_glui = (GLUI*) this;
}


/************************* GLUI_Main::deactivate_current_control() **********/

void         GLUI_Main::deactivate_current_control( void )
{
  int orig;

  if ( active_control != NULL ) {
    orig = active_control->set_to_glut_window();

    active_control->deactivate();

    /** If this isn't a container control, then redraw it in its
      deactivated state.  Container controls, such as panels, look
      the same activated or not **/
    glutPostRedisplay();

    active_control->restore_window( orig );

    active_control = NULL;
  }

  GLUI_debug::Instance()->print( __FILE__, __LINE__,
         "deactivate: %d\n", glutGetWindow() );
  GLUI_Master.active_control      = NULL;
  GLUI_Master.active_control_glui = NULL;
}


/****************************** GLUI_Main::find_next_control() **************/

GLUI_Control  *GLUI_Main::find_next_control_( GLUI_Control *control )
{
  /*** THIS IS NOT find_next_control()!  This is an unused older
    version (look at the underscore at the end) ***/

  if ( control == NULL )
    return find_next_control_rec( main_panel );
  else
    return find_next_control_rec( control );
}

/****************************** GLUI_Main::find_next_control() **************/

GLUI_Control  *GLUI_Main::find_next_control_rec( GLUI_Control *control )
{
  GLUI_Control *child = NULL, *rec_control, *sibling;

  /*** Recursively investigate children ***/
  child = (GLUI_Control*) control->first_child();
  if ( child ) {
    /*** If we can activate the first child, then do so ***/
    if ( child->can_activate AND child->enabled )
      return child;
    else     /*** Recurse into first child ***/
      rec_control = find_next_control_rec( child );

    if ( rec_control )
      return rec_control;
  }

  /*** At this point, either we don't have children, or the child cannot
    be activated.  So let's try the next sibling ***/

  sibling = (GLUI_Control*) control->next();
  if ( sibling ) {
    if ( sibling->can_activate AND sibling->enabled )
      return sibling;
    else     /*** Recurse into sibling ***/
      rec_control = find_next_control_rec( sibling );

    if ( rec_control )
      return rec_control;
  }

  return NULL;
}


/****************************** GLUI_Main::find_next_control() **************/

GLUI_Control  *GLUI_Main::find_next_control( GLUI_Control *control )
{
  GLUI_Control *tmp_control = NULL;
  int           back_up;

  if ( control == NULL )
    control = main_panel;

  while( control != NULL ) {
    /** see if this control has a child **/
    tmp_control = (GLUI_Control*) control->first_child();

    if ( tmp_control != NULL ) {
      if ( tmp_control->can_activate AND tmp_control->enabled )
	return tmp_control;

      control = tmp_control;  /* Descend into child */
      continue;
    }

    /*** At this point, control has no children ***/

    /** see if this control has a next sibling **/
    tmp_control = (GLUI_Control*) control->next();

    if ( tmp_control != NULL ) {
      if ( tmp_control->can_activate AND tmp_control->enabled )
	return tmp_control;

      control = tmp_control;
      continue;
    }

    /** back up until we find a sibling of an ancestor **/
    back_up = true;
    while ( control->parent() AND back_up ) {
      control = (GLUI_Control*) control->parent();

      if ( control->next() ) {
	control = (GLUI_Control*) control->next();
	if ( control->can_activate AND control->enabled )
	  return control;
	else
	  back_up = false;

	/***	if ( control->is_container ) {
	  tmp_control = control;
	  control     = NULL;
	  break;
	  }
	  else {
	  back_up = false;
	  }
	  ***/
      }
    }

    /** Check if we've cycled back to the top... if so, return NULL **/
    if ( control == main_panel ) {
      return NULL;
    }
  }
  /*
    if ( tmp_control != NULL AND tmp_control->can_activate AND
    tmp_control->enabled ) {
    return tmp_control;
    }*/

  return NULL;
}


/****************************** GLUI_Main::find_prev_control() **************/

GLUI_Control  *GLUI_Main::find_prev_control( GLUI_Control *control )
{
  GLUI_Control *tmp_control, *next_control;

  if ( control == NULL ) {        /* here we find the last valid control */
    next_control = main_panel;

    do {
      tmp_control  = next_control;
      next_control = find_next_control( tmp_control );
    } while( next_control != NULL );

    return tmp_control;
  }
  else {                         /* here we find the actual previous control */
    next_control = main_panel;

    do {
      tmp_control  = next_control;
      next_control = find_next_control( tmp_control );
    } while( next_control != NULL AND next_control != control );

    if ( next_control == NULL OR tmp_control == main_panel )
      return NULL;
    else
      return tmp_control;
  }
}

/************************* GLUI_Master_Object::set_glutIdleFunc() ***********/

void    GLUI_Master_Object::set_glutIdleFunc(void (*f)(void))
{
  glut_idle_CB = f;
  GLUI_Master.glui_setIdleFuncIfNecessary();
}


/**************************************** GLUI::disable() ********************/

void   GLUI::disable( void )
{
  deactivate_current_control();
  main_panel->disable();
}


/******************************************** GLUI::sync_live() **************/

void   GLUI::sync_live( void )
{
  main_panel->sync_live(true, true);
}


/********************************* GLUI_Master_Object::sync_live_all() *****/

void   GLUI_Master_Object::sync_live_all( void )
{
  GLUI *glui;

  glui = (GLUI*) GLUI_Master.gluis.first_child();
  while( glui ) {

    glui->sync_live();  /** sync it **/

    glui = (GLUI*) glui->next();
  }
}


/************************************* GLUI_Master_Object::close() **********/

void   GLUI_Master_Object::close_all( void )
{
  GLUI *glui;

  glui = (GLUI*) GLUI_Master.gluis.first_child();
  while( glui ) {

    glui->close();  /** Set flag to close **/

    glui = (GLUI*) glui->next();
  }
}


/************************************* GLUI_Main::close_internal() **********/

void   GLUI_Main::close_internal( void )
{
  glutDestroyWindow(glutGetWindow()); /** Close this window **/

  this->unlink();

  if ( GLUI_Master.active_control_glui == this ) {
    GLUI_Master.active_control      = NULL;
    GLUI_Master.active_control_glui = NULL;
  }

  if ( parent_window != -1 ) {
    glutSetWindow( parent_window );
    int win_w = glutGet( GLUT_WINDOW_WIDTH );
    int win_h = glutGet( GLUT_WINDOW_HEIGHT );
    glutReshapeWindow(win_w+1, win_h);
    glutReshapeWindow(win_w-1, win_h);
  }

  delete this->main_panel;

  delete this;
}


/************************************************** GLUI::close() **********/

void   GLUI::close( void )
{
  int   old_glut_window;

  closing = true;

  old_glut_window = glutGetWindow();
  glutSetWindow( get_glut_window_id() );
  glutPostRedisplay();

  glutSetWindow( old_glut_window );
}


/************************** GLUI_Main::check_subwindow_position() **********/

void   GLUI_Main::check_subwindow_position( void )
{
  /*** Reposition this window if subwindow ***/
  if ( TEST_AND( this->flags, GLUI_SUBWINDOW ) ) {

    int parent_w, parent_h, new_x, new_y;
    int old_window = glutGetWindow();

    glutSetWindow( glut_window_id );

    glutSetWindow( glutGet( GLUT_WINDOW_PARENT ));
    parent_w = glutGet( GLUT_WINDOW_WIDTH );
    parent_h = glutGet( GLUT_WINDOW_HEIGHT );

    glutSetWindow( glut_window_id );

    if ( TEST_AND(this->flags,GLUI_SUBWINDOW_RIGHT )) {
      new_x = parent_w - this->w;
      new_y = 0;
    }
    else if ( TEST_AND(this->flags,GLUI_SUBWINDOW_LEFT )) {
      new_x = 0;
      new_y = 0;
    }
    else if ( TEST_AND(this->flags,GLUI_SUBWINDOW_BOTTOM )) {
      new_x = 0;
      new_y = parent_h - this->h;
    }
    else {    /***   GLUI_SUBWINDOW_TOP    ***/
      new_x = 0;
      new_y = 0;
    }

    /** Now make adjustments based on presence of other subwindows **/
    GLUI *curr_glui;
    curr_glui = (GLUI*) GLUI_Master.gluis.first_child();
    while( curr_glui ) {
      if ( TEST_AND( curr_glui->flags, GLUI_SUBWINDOW) AND
	   curr_glui->parent_window == this->parent_window ) {

	if ( TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_LEFT ) ) {
	}
	else if ( TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_BOTTOM ) ) {
	}
	else if ( TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_RIGHT ) ) {
	}
	else if ( TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_TOP ) AND
		  ( TEST_AND( this->flags,GLUI_SUBWINDOW_LEFT ) OR
		    TEST_AND( this->flags,GLUI_SUBWINDOW_RIGHT ) ) ) {
	  /** If we are a RIGHT or LEFT subwindow, and there exists some
	    TOP subwindow, bump our position down  **/

	  new_y += curr_glui->h;
	}

	/** CHeck multiple subwins at same position  **/
	/** We check the glui_id's:  only the glui with the higher
	  ID number (meaning it was created later) gets bumped over **/
	if ( curr_glui != this AND this->glui_id > curr_glui->glui_id ) {
	  if ( TEST_AND( this->flags,GLUI_SUBWINDOW_LEFT ) AND
	       TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_LEFT ) ) {
	    new_x += curr_glui->w;
	  }
	  else if ( TEST_AND( this->flags,GLUI_SUBWINDOW_TOP ) AND
		    TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_TOP ) ) {
	    new_y += curr_glui->h;
	  }
	  else if ( TEST_AND( this->flags,GLUI_SUBWINDOW_BOTTOM ) AND
		    TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_BOTTOM ) ) {
	    new_y -= curr_glui->h;
	  }
	  else if ( TEST_AND( this->flags,GLUI_SUBWINDOW_RIGHT ) AND
		    TEST_AND( curr_glui->flags,GLUI_SUBWINDOW_RIGHT ) ) {
	    new_x -= curr_glui->w;
	  }

	}
      }

      curr_glui = (GLUI*) curr_glui->next();
    }



    CLAMP( new_x, 0, new_x );
    CLAMP( new_y, 0, new_y );

    glutPositionWindow( new_x, new_y );
    /*		glutPostRedisplay();          */

    glutSetWindow( old_window );
  }
}


/********************************* GLUI_Master_Object::reshape() **********/
/* This gets called by the user from a GLUT reshape callback.  So we look */
/* for subwindows that belong to the current window                   */

void  GLUI_Master_Object::reshape( void )
{
  GLUI *glui;
  int   current_window;

  current_window = glutGetWindow();

  glui = (GLUI*) GLUI_Master.gluis.first_child();
  while( glui ) {
    if ( TEST_AND( glui->flags, GLUI_SUBWINDOW) AND
	 glui->parent_window == current_window ) {
      glutSetWindow( glui->get_glut_window_id());
      glui->check_subwindow_position();
    }

    glui = (GLUI*) glui->next();
  }

  glutSetWindow(current_window);
}


/**************************** GLUI_Master_Object::set_glutReshapeFunc() *****/

void GLUI_Master_Object::set_glutReshapeFunc(void (*f)(int width, int height))
{
  glutReshapeFunc( glui_reshape_func );
  add_cb_to_glut_window( glutGetWindow(), GLUI_GLUT_RESHAPE, (void*) f);
}


/**************************** GLUI_Master_Object::set_glutKeyboardFunc() ****/

void GLUI_Master_Object::set_glutKeyboardFunc(void (*f)(unsigned char key,
							int x, int y))
{
  glutKeyboardFunc( glui_keyboard_func );
  add_cb_to_glut_window( glutGetWindow(), GLUI_GLUT_KEYBOARD, (void*) f);
}


/*********************** GLUI_Master_Object::set_glutSpecialFunc() **********/

void GLUI_Master_Object::set_glutSpecialFunc(void (*f)(int key,
						       int x, int y))
{
  glutSpecialFunc( glui_special_func );
  add_cb_to_glut_window( glutGetWindow(), GLUI_GLUT_SPECIAL, (void*) f);
}


/*********************** GLUI_Master_Object::set_glutMouseFunc() **********/

void GLUI_Master_Object::set_glutMouseFunc(void (*f)(int button, int state,
						     int x, int y))
{
  glutMouseFunc( glui_mouse_func );
  add_cb_to_glut_window( glutGetWindow(), GLUI_GLUT_MOUSE, (void*) f);
}


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


/******************************* GLUI_Main::set_ortho_projection() **********/

void  GLUI_Main::set_ortho_projection( void )
{
  int win_h, win_w;

  win_w = glutGet( GLUT_WINDOW_WIDTH );
  win_h = glutGet( GLUT_WINDOW_HEIGHT );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  /*  gluOrtho2D( 0.0, (float) win_w, 0.0, (float) win_h );          */
  glOrtho( 0.0, (float)win_w, 0.0, (float) win_h, -1000.0, 1000.0 );
  glMatrixMode( GL_MODELVIEW );


}


/******************************* GLUI_Main::set_viewport() **********/

void  GLUI_Main::set_viewport( void )
{
  glViewport( 0, 0, main_panel->w, main_panel->h );
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

void            GLUI::show( void )
{
  int orig_window;

  orig_window = main_panel->set_to_glut_window();

  glutShowWindow();

  main_panel->restore_window(orig_window);
}



/***************************************** GLUI::hide() **********************/

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

