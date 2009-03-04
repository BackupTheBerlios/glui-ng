/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

  glui_glut_window.cpp : a wrapper class to use glut as an event generator

  --------------------------------------------------

  Copyright (c) 2008 MALET Jean-Luc

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


/////////////////////////////////////////////////////////////////////
X11Display::X11Display(char* name)
	{
		disp = XOpenDisplay(name);
		if (! disp) throw exception(__func__,EINVAL);
	}
/////////////////////////////////////////////////////////////////////
GLUI_Glut_Window::GLUI_Glut_Window()
:   GLUI_Node(),

	glut_window_id(0),
	glut_keyboard_CB(NULL),
	glut_special_CB(NULL),
	glut_reshape_CB(NULL),
	glut_passive_motion_CB(NULL),
	glut_mouse_CB(NULL),
	glut_visibility_CB(NULL),
	glut_motion_CB(NULL),
	glut_display_CB(NULL),
	glut_entry_CB(NULL)
{
}


/***************************** GLUI_Main::CreateGluiWindow() **********/

void GLUI_Main::CreateGluiWindow( const char *text, long flags, int x, int y, int parent_window )
{
  int old_glut_window;

  this->flags = flags;

  window_name = text;

  /*** We copy over the current window callthroughs ***/
  /*** (I think this might actually only be needed for subwindows) ***/
  /*  glut_keyboard_CB = GLUI_Master.glut_keyboard_CB;
      glut_reshape_CB  = GLUI_Master.glut_reshape_CB;
      glut_special_CB  = GLUI_Master.glut_special_CB;
      glut_mouse_CB    = GLUI_Master.glut_mouse_CB;*/


  if ( (flags & GLUI_SUBWINDOW) != GLUI_SUBWINDOW ) {  /* not a subwindow, creating a new top-level window */
    old_glut_window = glutGetWindow();

    create_standalone_window( window_name.c_str(), x, y );
    setup_default_glut_callbacks();

    if ( old_glut_window > 0 )
      glutSetWindow( old_glut_window );
    else
        glutSetWindow(glut_window_id);

    top_level_glut_window_id = glut_window_id;
  }
  else /* *is* a subwindow */
  {
    old_glut_window = glutGetWindow();

    create_subwindow( parent_window, flags );
    setup_default_glut_callbacks();

    if ( old_glut_window > 0 )
      glutSetWindow( old_glut_window );

    top_level_glut_window_id = parent_window;

    /*
      glutReshapeFunc( glui_parent_window_reshape_func );
      glutSpecialFunc( glui_parent_window_special_func );
      glutKeyboardFunc( glui_parent_window_keyboard_func );
      glutMouseFunc( glui_parent_window_mouse_func );
      */

  }
#warning "throw an exception on error here"

}

/**************************** GLUI_Main::create_standalone_window() ********/

void GLUI_Main::create_standalone_window( const char *name, int x, int y )
{
  glutInitWindowSize( 100, 100 );
  if ( x >= 0 OR y >= 0 )
    glutInitWindowPosition( x, y );
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
  glut_window_id = glutCreateWindow( name );
}


/******************************** GLUI_Main::create_subwindow() **********/

void GLUI_Main::create_subwindow( int parent_window, int window_alignment )
{
  glut_window_id = glutCreateSubWindow(parent_window, 0,0, 100, 100);
  this->parent_window = parent_window;
}



/**************************** GLUI_Main::setup_default_glut_callbacks() *****/
#error here are the glut event registration
	void
GLUI_Main::setup_default_glut_callbacks (void)
{
	glutDisplayFunc (glui_display_func);
	glutReshapeFunc (glui_reshape_func);
	glutKeyboardFunc (glui_keyboard_func);
	glutSpecialFunc (glui_special_func);
	glutMouseFunc (glui_mouse_func);
	glutMotionFunc (glui_motion_func);
	glutPassiveMotionFunc (glui_passive_motion_func);
	glutEntryFunc (glui_entry_func);
	glutVisibilityFunc (glui_visibility_func);
	glutIdleFunc (glui_idle_func);	// FIXME!  100% CPU usage!
}


/********************************************** glui_display_func() ********/

	void
glui_display_func (void)
{
	GLUI *glui;

	GLUI_debug::Instance ()->print (__FILE__, __LINE__, "display func\n");

	glui = GLUI_Master.find_glui_by_window_id (glutGetWindow ());

	if (glui)
	{
#warning "send an event to glui->Get_main_panel()->AddEvent(Expose)"
		glui->display ();
		/*
		   Do not do anything after the above line, b/c the GLUI
		   window might have just closed itself
		   */
	}
}


/********************************************** glui_reshape_func() ********/

	void
glui_reshape_func (int w, int h)
{
	GLUI *glui;
	GLUI_Glut_Window *glut_window;
	int current_window;
#warning "send an event to glui->Get_main_panel()->AddEvent(ResizeRequest)"
//	XResizeRequestEvent event = {
//		.type   = ResizeRequest,
//		.width  = w,
//		.height = h
//	};
//	glui->Get_main_panel()->AddEvent((XEvent) event);


	GLUI_debug::Instance ()->print (__FILE__, __LINE__, "glui_reshape_func(): %d  w/h: %d/%d\n", glutGetWindow (), w, h);

	current_window = glutGetWindow ();

	/***  First check if this is main glut window ***/
	glut_window = GLUI_Master.find_glut_window (current_window);
	if (glut_window)
	{
		if (glut_window->glut_reshape_CB)
			glut_window->glut_reshape_CB (w, h);

		/***  Now send reshape events to all subwindows  ***/
		glui = (GLUI *) GLUI_Master.gluis.first_child ();
		while (glui)
		{
			if (TEST_AND (glui->flags, GLUI_SUBWINDOW) AND glui->parent_window == current_window)
			{
				glutSetWindow (glui->get_glut_window_id ());
				glui->reshape (w, h);
				/*      glui->check_subwindow_position();          */
			}
			glui = (GLUI *) glui->next ();
		}
	}
	else
	{
		/***  A standalone GLUI window  ***/

		glui = GLUI_Master.find_glui_by_window_id (current_window);

		if (glui)
		{
			glui->reshape (w, h);
		}
	}
}

/********************************************** glui_keyboard_func() ********/

	void
glui_keyboard_func (unsigned char key, int x, int y)
{

	GLUI *glui;
	int current_window;
	GLUI_Glut_Window *glut_window;
	int win_w = glutGet (GLUT_WINDOW_WIDTH);
	int win_h = glutGet (GLUT_WINDOW_HEIGHT);
	y = win_h - y;

	current_window = glutGetWindow ();
	glut_window = GLUI_Master.find_glut_window (current_window);

	GLUI_debug::Instance ()->print (__FILE__, __LINE__, "key: %d\n", current_window);

	if (glut_window)
	{		       /**  Was event in a GLUT window?  **/
		if (GLUI_Master.active_control_glui AND GLUI_Master.active_control)
		{
			glutSetWindow (GLUI_Master.active_control_glui->get_glut_window_id ());

			GLUI_Master.active_control_glui->keyboard (key, x, y);
			finish_drawing ();

			glutSetWindow (current_window);
		}
		else
		{
			if (glut_window->glut_keyboard_CB)
				glut_window->glut_keyboard_CB (key, x, y);
		}
	}
	else
	{	   /***  Nope, event was in a standalone GLUI window  **/
		glui = GLUI_Master.find_glui_by_window_id (glutGetWindow ());

		if (glui)
		{
			glui->keyboard (key, x, y);
			finish_drawing ();
		}
	}
}


/************************************************ glui_special_func() ********/

	void
glui_special_func (int key, int x, int y)
{

	GLUI *glui;
	int current_window;
	GLUI_Glut_Window *glut_window;
	int win_w = glutGet (GLUT_WINDOW_WIDTH);
	int win_h = glutGet (GLUT_WINDOW_HEIGHT);
	y = win_h - y;

	current_window = glutGetWindow ();
	glut_window = GLUI_Master.find_glut_window (current_window);

	if (glut_window) /**  Was event in a GLUT window?  **/
	{
		if (GLUI_Master.active_control_glui AND GLUI_Master.active_control)
		{
			glutSetWindow (GLUI_Master.active_control_glui->get_glut_window_id ());

			GLUI_Master.active_control_glui->special (key, x, y);
			finish_drawing ();

			glutSetWindow (current_window);
		}
		else
		{
			if (glut_window->glut_special_CB)
				glut_window->glut_special_CB (key, x, y);
		}
	}
	else		   /***  Nope, event was in a standalone GLUI window  **/
	{
		glui = GLUI_Master.find_glui_by_window_id (glutGetWindow ());

		if (glui)
		{
			glui->special (key, x, y);
			finish_drawing ();
		}
	}
}

/********************************************** glui_mouse_func() ********/

	void
glui_mouse_func (int button, int state, int x, int y)
{
	GLUI *glui;
	int current_window;
	GLUI_Glut_Window *glut_window;
	int win_w = glutGet (GLUT_WINDOW_WIDTH);
	int win_h = glutGet (GLUT_WINDOW_HEIGHT);
	y = win_h - y;

	current_window = glutGetWindow ();
	glut_window = GLUI_Master.find_glut_window (current_window);

	if (glut_window)
	{		       /**  Was event in a GLUT window?  **/
		if (GLUI_Master.active_control_glui != NULL)
			GLUI_Master.active_control_glui->deactivate_current_control ();

		if (glut_window->glut_mouse_CB)
			glut_window->glut_mouse_CB (button, state, x, y);
		finish_drawing ();
	}
	else
	{		       /**  Nope - event was in a GLUI standalone window  **/
		glui = GLUI_Master.find_glui_by_window_id (glutGetWindow ());
		if (glui)
		{
			glui->passive_motion (0, 0);
			glui->mouse (button, state, x, y);
			finish_drawing ();
		}
	}
}


/********************************************** glui_motion_func() ********/

	void
glui_motion_func (int x, int y)
{
	GLUI *glui;
	int win_w = glutGet (GLUT_WINDOW_WIDTH);
	int win_h = glutGet (GLUT_WINDOW_HEIGHT);
	y = win_h - y;

	glui = GLUI_Master.find_glui_by_window_id (glutGetWindow ());

	if (glui)
	{
		glui->motion (x, y);
		finish_drawing ();
	}

}


/**************************************** glui_passive_motion_func() ********/

	void
glui_passive_motion_func (int x, int y)
{
	GLUI *glui;
	int win_w = glutGet (GLUT_WINDOW_WIDTH);
	int win_h = glutGet (GLUT_WINDOW_HEIGHT);
	y = win_h - y;

	glui = GLUI_Master.find_glui_by_window_id (glutGetWindow ());

	if (glui)
	{
		glui->passive_motion (x, y);
		finish_drawing ();
	}
}


/********************************************** glui_entry_func() ********/

	void
glui_entry_func (int state)
{
	GLUI *glui;

	glui = GLUI_Master.find_glui_by_window_id (glutGetWindow ());

	if (glui)
	{
		glui->entry (state);
	}
}


/******************************************** glui_visibility_func() ********/

	void
glui_visibility_func (int state)
{
	GLUI *glui;

	GLUI_debug::Instance ()->print (__FILE__, __LINE__, "IN GLUI VISIBILITY()\n");
	/*  fflush( stdout );          */

	glui = GLUI_Master.find_glui_by_window_id (glutGetWindow ());

	if (glui)
	{
		glui->visibility (state);
	}
}


/********************************************** glui_idle_func() ********/
/* Send idle event to each glui, then to the main window            */

	void
glui_idle_func (void)
{
	GLUI *glui;

	glui = (GLUI *) GLUI_Master.gluis.first_child ();
	while (glui)
	{
		glui->idle ();
		finish_drawing ();

		glui = (GLUI *) glui->next ();
	}

	if (GLUI_Master.glut_idle_CB)
	{
		/*** We set the current glut window before calling the user's
		  idle function, even though glut explicitly says the window id is
		  undefined in an idle callback.  ***/

		/** Check what the current window is first ***/

		/*** Arbitrarily set the window id to the main gfx window of the
		  first glui window ***/
		/*   int current_window, new_window;          */
		/*   current_window = glutGetWindow();          */
		/*   if (GLUI_Master.gluis.first_child() != NULL ) {          */
		/*      new_window = ((GLUI_Main*)GLUI_Master.gluis.first_child())-> */
		/*   main_gfx_window_id;          */
		/*   if ( new_window > 0 AND new_window != old_window ) {          */
		/*   --- Window is changed only if its not already the current window --- */
		/*  glutSetWindow( new_window );          */
		/* }          */
		/*}          */

		GLUI_Master.glut_idle_CB ();
	}
}
