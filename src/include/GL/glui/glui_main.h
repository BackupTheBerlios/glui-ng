#ifndef __GLUI_MAIN_H
#define __GLUI_MAIN_H
/************************************************************/
/*                                                          */
/*       Main Window GLUI class (not user-level)            */
/*                                                          */
/************************************************************/

/**
  A GLUI_Main handles GLUT events for one window, routing them to the
  appropriate controls.  The central user-visible "GLUI" class
  inherits from this class; users should not allocate GLUT_Main objects.

  There's a separate GLUI_Main object for:
    - Each top-level window with GUI stuff in it.
    - Each "subwindow" of another top-level window.

  All the GLUI_Main objects are listed in GLUI_Master.gluis.
  A better name for this class might be "GLUI_Environment";
  this class provides the window-level context for every control.
*/
class GLUIAPI GLUI_Main : public GLUI_Node
{


    /********** Friend classes *************/

    friend class GLUI_Control;
    friend class GLUI_Rotation;
    friend class GLUI_Translation;
    friend class GLUI;
    friend class GLUI_Master_Object;

    /*********** Friend functions **********/

    friend void glui_mouse_func(int button, int state, int x, int y);
    friend void glui_keyboard_func(unsigned char key, int x, int y);
    friend void glui_special_func(int key, int x, int y);
    friend void glui_passive_motion_func(int x, int y);
    friend void glui_reshape_func( int w, int h );
    friend void glui_visibility_func(int state);
    friend void glui_motion_func(int x, int y);
    friend void glui_entry_func(int state);
    friend void glui_display_func( void );
    friend void glui_idle_func(void);

    friend void glui_parent_window_reshape_func( int w, int h );
    friend void glui_parent_window_keyboard_func( unsigned char, int, int );
    friend void glui_parent_window_special_func( int, int, int );
    friend void glui_parent_window_mouse_func( int, int, int, int );
public:
	/********** our data types *************/
	enum buffer_mode_t {
		buffer_front=1, ///< Draw updated controls directly to screen.
		buffer_back=2   ///< Double buffering: postpone updates until next redraw.
	};
	buffer_mode_t get_buffer_mode() {return buffer_mode;}

protected:
    /*** Variables ***/
    int           main_gfx_window_id;
    int           mouse_button_down;
    int           glut_window_id;
    int           top_level_glut_window_id;
    GLUI_Control *active_control;
    GLUI_Control *mouse_over_control;
    GLUI_Panel   *main_panel;
    buffer_mode_t buffer_mode; ///< Current drawing mode
    int           curr_cursor;
    int           w, h;
    long          flags;
    bool          closing;
    int           parent_window;
    int           glui_id;

    /********** Misc functions *************/

    GLUI_Control  *find_control( int x, int y, GLUI_Control * parent=NULL  );
    GLUI_Control  *find_next_control( GLUI_Control *control );
    GLUI_Control  *find_next_control_rec( GLUI_Control *control );
    GLUI_Control  *find_next_control_( GLUI_Control *control );
    GLUI_Control  *find_prev_control( GLUI_Control *control );
    void           create_standalone_window( const char *name, int x=-1, int y=-1 );
    void           create_subwindow( int parent,int window_alignment );
    void           setup_default_glut_callbacks( void );

    void           mouse(int button, int state, int x, int y);
    void           keyboard(unsigned char key, int x, int y);
    void           special(int key, int x, int y);
    void           passive_motion(int x, int y);
    void           reshape( int w, int h );
    void           visibility(int state);
    void           motion(int x, int y);
    void           entry(int state);
    void           display( void );
    void           idle(void);
    int            needs_idle(void);

    void (*glut_mouse_CB)(int, int, int, int);
    void (*glut_keyboard_CB)(unsigned char, int, int);
    void (*glut_special_CB)(int, int, int);
    void (*glut_reshape_CB)(int, int);

   /** Pack, resize the window, and redraw all the controls. */

    /*********** Controls ************/

    virtual int    add_control( GLUI_Node *parent, GLUI_Control *control );


    /********** Constructors and Destructors ***********/

    GLUI_Main( void );

public:
    GLUI_StdBitmaps  std_bitmaps;
    std::string      window_name;
    unsigned char    bkgd_color[3];
    float            bkgd_color_f[3];

    void            *font;
    int              curr_modifiers;

    void         adjust_glut_xy( int &x, int &y ) { y = h-y; }
    void         activate_control( GLUI_Control *control, int how );
    void         align_controls( GLUI_Control *control );
    void         deactivate_current_control( void );

    /** Draw a 3D-look pushed-out box around this rectangle */
    void         draw_raised_box( int x, int y, int w, int h );
    /** Draw a 3D-look pushed-in box around this rectangle */
    void         draw_lowered_box( int x, int y, int w, int h );

    /** Return true if this control should redraw itself immediately (front buffer);
       Or queue up a redraw and return false if it shouldn't (back buffer).
    */
    bool         should_redraw_now(GLUI_Control *ctl);

    /** Switch to the appropriate draw buffer now.  Returns the old draw buffer.
       This routine should probably only be called from inside the GLUI_DrawingSentinal,
       in glui_internal_control.h
    */
    int          set_current_draw_buffer();
    /** Go back to using this draw buffer.  Undoes set_current_draw_buffer. */
    void         restore_draw_buffer( int buffer_state );

    /** Redraw the main graphics window */
    void         post_update_main_gfx();

    /** Recompute the sizes and positions of all controls */
    void         pack_controls();

    void         close_internal();
    void         check_subwindow_position();
    void         set_ortho_projection();
    void         set_viewport();
    int          get_glut_window_id( void ) { return glut_window_id; } /* JVK */
};



#endif
