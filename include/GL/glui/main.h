#ifndef __GLUI_MAIN_H
#define __GLUI_MAIN_H
/************************************************************/
/*                                                          */
/*       Main Window GLUI class (not user-level)            */
/*                                                          */
/************************************************************/
#include <GL/glui/commondefs.h>
#include <GL/glui/node.h>
#include <GL/glui/bitmaps.h>
#include <cstring>
#include <string>

/**
  A Main handles GLUT events for one window, routing them to the
  appropriate controls.  The central user-visible "GLUI" class
  inherits from this class; users should not allocate GLUT_Main objects.

  There's a separate Main object for:
    - Each top-level window with GUI stuff in it.
    - Each "subwindow" of another top-level window.

  All the Main objects are listed in Master.gluis.
  A better name for this class might be "Environment";
  this class provides the window-level context for every control.
*/
/*
namespace GLUI
{
	class Panel;
	class Control;

	class GLUIAPI Main : public Node
	{


		/////////// Friend classes //////////////

		friend class Rotation;
		friend class Translation;
		friend class Master_Object;

		//////////// Friend functions ///////////

		protected:
		//// Variables ////
		int           main_gfx_window_id;
		int           mouse_button_down;
		Control *active_control;
		Control *mouse_over_control;
		Panel   *main_panel;
		int           curr_cursor;
		long          flags;
		bool          closing;
		int           parent_window;
		int           glui_id;

		/////////// Misc functions //////////////

		Control  *find_control( int x, int y, Control * parent=NULL  );
		Control  *find_next_control( Control *control );
		Control  *find_next_control_rec( Control *control );
		Control  *find_next_control_( Control *control );
		Control  *find_prev_control( Control *control );

		void           idle(void);
		int            needs_idle(void);

		/// Pack, resize the window, and redraw all the controls. //

		//////////// Controls /////////////

		virtual int    add_control( Node *parent, Node *control );


		/////////// Constructors and Destructors ////////////

		Main( void );
		void Main::CreateGluiWindow( const char *text, long flags, int x, int y, int parent_window );

		public:
		Main( const char *text, long flags, int x, int y, int parent_window );

		StdBitmaps  std_bitmaps;


		void            *font;
		int              curr_modifiers;

		void         activate_control( Control *control, int how );
		void         align_controls( Control *control );
		void         deactivate_current_control( void );

		/// Return true if this control should redraw itself immediately (front buffer);
		//Or queue up a redraw and return false if it shouldn't (back buffer).
		////
		bool         should_redraw_now(Control *ctl);

		/// Switch to the appropriate draw buffer now.  Returns the old draw buffer.
		//This routine should probably only be called from inside the DrawingSentinal,
		//in glui_internal_control.h
		////
		int          set_current_draw_buffer();
		/// Go back to using this draw buffer.  Undoes set_current_draw_buffer. //
		void         restore_draw_buffer( int buffer_state );

		/// Redraw the main graphics window //
		void         post_update_main_gfx();

		/// Recompute the sizes and positions of all controls //
		void         pack_controls();

		void         close_internal();
		void         check_subwindow_position();
		void         set_ortho_projection();
		static void  LoadIdentityYAxisDown();
		void         set_viewport();
	};
}

*/
#endif
