#ifndef __GLUI_ROTATION_H
#define __GLUI_ROTATION_H
/*
   GLUI-ng, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

   This library is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the 
   Free Software Foundation; either version 2.1 of the License, 
   or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License along with this library;
   if not, write to the 
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

   based on the work of Paul Rademacher (orignal software http://glui.sourceforge.net/)
*/


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
