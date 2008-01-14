#ifndef __GLUI_SCROLLBAR_H
#define __GLUI_SCROLLBAR_H

#include <GL/glui/glui_control.h>

/************************************************************/
/*                                                          */
/*               Scrollbar class - JVK                      */
/*                                                          */
/************************************************************/

class GLUIAPI GLUI_Scrollbar : public GLUI_Control
{
public:
    // Constructor, no live var
    GLUI_Scrollbar( GLUI_Node *parent,
                    const char *name,
                    int horz_vert=GLUI_SCROLL_HORIZONTAL,
                    int data_type=GLUI_SCROLL_INT,
                    int id=-1, GLUI_CB callback=GLUI_CB()
                    /*,GLUI_Control *object = NULL*/
                    /*,GLUI_InterObject_CB obj_cb = NULL*/
                    );

    // Constructor, int live var
    GLUI_Scrollbar( GLUI_Node *parent, const char *name, int horz_vert,
                    int *live_var,
                    int id=-1, GLUI_CB callback=GLUI_CB()
                    /*,GLUI_Control *object = NULL*/
                    /*,GLUI_InterObject_CB obj_cb = NULL*/
                    );

    // Constructor, float live var
    GLUI_Scrollbar( GLUI_Node *parent, const char *name, int horz_vert,
                    float *live_var,
                    int id=-1, GLUI_CB callback=GLUI_CB()
                    /*,GLUI_Control *object = NULL*/
                    /*,GLUI_InterObject_CB obj_cb = NULL*/
                    );

    bool          currently_inside;
    int           state;
    float         growth, growth_exp;
    int           last_x, last_y;
    int           data_type;
    int           callback_count;
    int           last_int_val;  ///< Used to prevent repeated callbacks.
    float         last_float_val;
    int           first_callback;
    float         user_speed;
    float         float_min, float_max;
    int           int_min, int_max;
    int           horizontal;
    double     last_update_time; ///< GLUI_Time() we last advanced scrollbar.
    double     velocity_limit; ///< Maximum distance to advance per second.
    int box_length;
    int box_start_position;
    int box_end_position;
    int track_length;


    /* Rather than directly access an Editbox or Textbox for
       changing variables, a pointer to some object is defined
       along with a static callback in the form func(void *, int) -
       the int is the new value, the void * must be cast to that
       particular object type before use.
    */
    void *        associated_object; /* Lets the Spinner manage it's own callbacks */
    GLUI_CB       object_cb; /* function pointer to object call_back */

    int  mouse_down_handler( int local_x, int local_y );
    int  mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );
    int  key_handler( unsigned char key,int modifiers );
    int  special_handler( int key,int modifiers );

    void draw( void );
    void draw_pressed( void );
    void draw_unpressed( void );
    void draw_text( int sunken );

    void update_size( void );

    void set_int_limits( int low, int high,int limit_type=GLUI_LIMIT_CLAMP);
    void set_float_limits( float low,float high,int limit_type=GLUI_LIMIT_CLAMP);
    int  find_arrow( int local_x, int local_y );
    void do_drag( int x, int y );
    void do_callbacks( void );
    void draw_scroll( void );
    void do_click( void );
    void idle( void );
    bool needs_idle( void ) const;
    void set_int_val( int new_val );
    void set_float_val( float new_val );
    void increase_growth( void );
    void reset_growth( void );

    void set_speed( float speed ) { user_speed = speed; };
    void update_scroll_parameters();
    void set_object_callback(GLUI_CB cb=GLUI_CB(), GLUI_Control*obj=NULL)
    { object_cb=cb; associated_object=obj; }

protected:
    void common_init ( void );
    void common_construct(
        GLUI_Node *parent,
        const char *name,
        int horz_vert,
        int data_type, void* live_var,
        int id, GLUI_CB callback
        /*,GLUI_Control *object
        ,GLUI_InterObject_CB obj_cb*/
        );

    virtual void draw_scroll_arrow(int arrowtype, int x, int y);
    virtual void draw_scroll_box(int x, int y, int w, int h);
};



#endif //__GLUI_SCROLLBAR_H
