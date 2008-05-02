#ifndef __GLUI_CHECKBOX_H
#define __GLUI_CHECKBOX_H
/************************************************************/
/*                                                          */
/*               Checkbox class (container)                 */
/*                                                          */
/************************************************************/

/**
 A checkbox, which can be checked on or off.  Can be linked
 to an int value, which gets 1 for on and 0 for off.
*/
class GLUIAPI GLUI_Checkbox : public GLUI_Container
{
public:
    int  orig_value;
    bool currently_inside;

    int  mouse_down_handler( int local_x, int local_y );
    int  mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );
    int  key_handler( unsigned char key,int modifiers );

    void update_size( void );

    void draw( void );

    void draw_active_area( void );
    void draw_empty_box( void );
    void set_int_val( int new_val );

/**
 Create a new checkbox object.

  @param parent The panel our object is inside; or the main GLUI object.
  @param name Label next to our checkbox.
  @param value_ptr Optional integer value to attach to this checkbox.  When the
     checkbox is checked or unchecked, *value_ptr will also be changed. ("Live Vars").
  @param id Optional ID number, to pass to the optional callback function.
  @param callback Optional callback function, taking either the int ID or control.
*/
    GLUI_Checkbox(GLUI_Node *parent, const char *name, int *value_ptr=NULL,
                  int id=-1, GLUI_CB callback=GLUI_CB());

	~GLUI_Checkbox();

protected:
    void common_init(void) {
        w              = 100;
        h              = GLUI_CHECKBOX_SIZE;
        orig_value     = -1;
        can_activate   = true;
        live_type      = GLUI_LIVE_INT;   /* This control has an 'int' live var */
    }
	GLUI_StaticText* text;
//	GLUI_Button button;
};

#endif
