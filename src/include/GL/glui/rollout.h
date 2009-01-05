#ifndef __GLUI_ROLLOUT_H
#define __GLUI_ROLLOUT_H
/************************************************************/
/*                                                          */
/*               Rollout class (container)                  */
/*                                                          */
/************************************************************/
/**
 A rollout contains a set of controls,
 like a panel, but can be collapsed to just the name.
*/
#include <GL/glui/glui_button.h>
#include <GL/glui/glui_panel.h>
#include <GL/glui/glui_collapsible.h>
class GLUIAPI GLUI_Rollout : public GLUI_Collapsible
{
public:

/**
 Create a new rollout.  A rollout contains a set of controls,
 like a panel, but can be collapsed to just the name.

  @param parent The panel our object is inside; or the main GLUI object.
  @param name String to show at the top of the rollout.
  @param open Optional boolean.  If true (the default), the rollout's controls are displayed.
    If false, the rollout is closed to display only the name.
  @param type Optional style to display the panel with--GLUI_PANEL_EMBOSSED by default.
      GLUI_PANEL_RAISED causes the panel to appear higher than the surroundings.
      GLUI_PANEL_NONE causes the panel's outline to be invisible.
*/
    GLUI_Rollout( GLUI_Node *parent, const char *name, int open=true,
                  int type=GLUI_PANEL_EMBOSSED );


    bool        currently_inside, initially_inside;

    void draw( void );
    void translate_and_draw( void );
    void draw_pressed( void );
    int mouse_down_handler( int local_x, int local_y );
    int mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );

    void update_size( void );

protected:
    GLUI_Panel panel;
    GLUI_TextButton button;
    void common_init() {
        currently_inside = false;
        initially_inside = false;
        can_activate     = true;
        h                = GLUI_DEFAULT_CONTROL_HEIGHT + 7;
        w                = GLUI_DEFAULT_CONTROL_WIDTH;
        y_off_top        = 21;
    }
};


#endif
