#ifndef __GLUI_ROTATION_H
#define __GLUI_ROTATION_H


#include <GL/glui/glui_mouse_interaction.h>


/************************************************************/
/*                                                          */
/*                   Rotation class                         */
/*                                                          */
/************************************************************/

/**
  An onscreen rotation controller--allows the user to interact with
  a 3D rotation via a spaceball-like interface.
*/
class GLUIAPI GLUI_Rotation : public GLUI_Mouse_Interaction
{
public:
    Arcball        *ball;
    GLUquadricObj *quadObj;
    bool           can_spin, spinning;
    float          damping;

    int  iaction_mouse_down_handler( int local_x, int local_y );
    int  iaction_mouse_up_handler( int local_x, int local_y, bool inside );
    int  iaction_mouse_held_down_handler( int local_x, int local_y, bool inside );
    int  iaction_special_handler( int key, int modifiers );
    void iaction_init( void ) { init_ball(); }
    void iaction_draw_active_area_persp( void );
    void iaction_draw_active_area_ortho( void );
    void iaction_dump( FILE *output );

    /*  void update_size( void ); */
    /*  void draw( int x, int y ); */
    /*  int mouse_over( int state, int x, int y ); */

    void setup_texture( void );
    void setup_lights( void );
    void draw_ball( float radius );

    void init_ball( void );

    void reset( void );

    bool needs_idle( void ) const;
    void idle( void );

    void copy_float_array_to_ball( void );
    void copy_ball_to_float_array( void );

    void set_spin( float damp_factor );

    GLUI_Rotation( GLUI_Node *parent, const char *name, float *live_var=NULL,
                   int id=-1, GLUI_CB callback=GLUI_CB() );

protected:
    void common_init();
};


#endif //__GLUI_ROTATION_H
