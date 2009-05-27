#ifndef __GLUI_MOUSE_INTERACTION_H
#define __GLUI_MOUSE_INTERACTION_H

#include <GL/glui/glui_control.h>

/************************************************************/
/*                                                          */
/*              Mouse_Interaction class                     */
/*                                                          */
/************************************************************/

/**
  This is the superclass of translation and rotation widgets.
*/
class GLUIAPI GLUI_Mouse_Interaction : public GLUI_Control
{
public:
    /*int  get_main_area_size( void ) { return MIN( h-18,  */
    int            draw_active_area_only;

    int  mouse_down_handler( int local_x, int local_y );
    int  mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );
    int  special_handler( int key, int modifiers );
    void update_size( void );
    void draw( void );
    void draw_active_area( void );

    /***  The following methods (starting with "iaction_") need to
          be overloaded  ***/
    virtual int  iaction_mouse_down_handler( int local_x, int local_y ) = 0;
    virtual int  iaction_mouse_up_handler( int local_x, int local_y, bool inside )=0;
    virtual int  iaction_mouse_held_down_handler( int local_x, int local_y, bool inside )=0;
    virtual int  iaction_special_handler( int key, int modifiers )=0;
    virtual void iaction_draw_active_area_persp( void )=0;
    virtual void iaction_draw_active_area_ortho( void )=0;
    virtual void iaction_dump( FILE *output )=0;
    virtual void iaction_init( void ) = 0;

    GLUI_Mouse_Interaction( const char* name ) : GLUI_Control(name) {
        w              = GLUI_MOUSE_INTERACTION_WIDTH;
        h              = GLUI_MOUSE_INTERACTION_HEIGHT;
        can_activate   = true;
        live_type      = GLUI_LIVE_NONE;
        alignment      = GLUI_ALIGN_CENTER;
        draw_active_area_only = false;
    }
};



#endif //__GLUI_MOUSE_INTERACTION_H
