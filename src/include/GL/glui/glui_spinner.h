#ifndef __GLUI_SPINNER_H
#define __GLUI_SPINNER_H

#define  GLUI_SPINNER_ARROW_WIDTH   12
#define  GLUI_SPINNER_ARROW_HEIGHT   8
#define  GLUI_SPINNER_ARROW_Y        2

#define  GLUI_SPINNER_STATE_NONE     0
#define  GLUI_SPINNER_STATE_UP       1
#define  GLUI_SPINNER_STATE_DOWN     2
#define  GLUI_SPINNER_STATE_BOTH     3

#define  GLUI_SPINNER_DEFAULT_GROWTH_EXP   1.05f

/************************************************************/
/*                                                          */
/*               Spinner class                              */
/*                                                          */
/************************************************************/

class GLUIAPI GLUI_Spinner : public GLUI_Container
{
public:
    // Constructor, no live var
    GLUI_Spinner( GLUI_Node* parent, const char *name,
                  int data_type=GLUI_SPINNER_INT, int id=-1, GLUI_CB callback=GLUI_CB() );
    // Constructor, int live var
    GLUI_Spinner( GLUI_Node* parent, const char *name,
                  int *live_var, int id=-1, GLUI_CB callback=GLUI_CB() );
    // Constructor, float live var
    GLUI_Spinner( GLUI_Node* parent, const char *name,
                  float *live_var, int id=-1, GLUI_CB callback=GLUI_CB() );

    bool          currently_inside;
    int           state;
    float         growth, growth_exp;
    int           last_x, last_y;
    int           data_type;
    int           callback_count;
    int           last_int_val;
    float         last_float_val;
    int           first_callback;
    float         user_speed;

    GLUI_EditText *edittext;

    int  mouse_down_handler( int local_x, int local_y );
    int  mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );
    int  key_handler( unsigned char key,int modifiers );
    int  special_handler(   int key,int modifiers );

    void draw( void );
    void draw_pressed( void );
    void draw_unpressed( void );
    void draw_text( int sunken );

    void update_size( void );

    void set_float_limits( float low,float high,int limit_type=GLUI_LIMIT_CLAMP);
    void set_int_limits( int low, int high,int limit_type=GLUI_LIMIT_CLAMP);
    int  find_arrow( int local_x, int local_y );
    void do_drag( int x, int y );
    void do_callbacks( void );
    void do_click( void );
    void idle( void );
    bool needs_idle( void ) const;

    const char *get_text( void );

    void set_float_val( float new_val );
    void set_int_val( int new_val );
    float  get_float_val( void );
    int    get_int_val( void );
    void increase_growth( void );
    void reset_growth( void );

    void set_speed( float speed ) { user_speed = speed; }

protected:
    void common_init() {
        h            = GLUI_EDITTEXT_HEIGHT;
        w            = GLUI_EDITTEXT_WIDTH;
        x_off        = 0;
        y_off_top    = 0;
        y_off_bot    = 0;
        can_activate = true;
        state        = GLUI_SPINNER_STATE_NONE;
        edittext     = NULL;
        growth_exp   = GLUI_SPINNER_DEFAULT_GROWTH_EXP;
        callback_count = 0;
        first_callback = true;
        user_speed   = 1.0;
    }
    void common_construct( GLUI_Node* parent, const char *name,
                           int data_type, void *live_var,
                           int id, GLUI_CB callback );
};


#endif

