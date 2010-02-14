#ifndef __GLUI_TRANSLATION_H
#define __GLUI_TRANSLATION_H
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
/*                   Translation class                      */
/*                                                          */
/************************************************************/

/**
  An onscreen translation controller--allows the user to interact with
  a 3D translation.
*/
class GLUIAPI GLUI_Translation : public GLUI_Mouse_Interaction
{
public:
    int trans_type;  /* Is this an XY or a Z controller? */
    int down_x, down_y;
    float scale_factor;
    GLUquadricObj *quadObj;
    int   trans_mouse_code;
    float orig_x, orig_y, orig_z;
    int   locked;

    int  iaction_mouse_down_handler( int local_x, int local_y );
    int  iaction_mouse_up_handler( int local_x, int local_y, bool inside );
    int  iaction_mouse_held_down_handler( int local_x, int local_y, bool inside );
    int  iaction_special_handler( int key, int modifiers );
    void iaction_init( void ) { }
    void iaction_draw_active_area_persp( void );
    void iaction_draw_active_area_ortho( void );
    void iaction_dump( FILE *output );

    void set_speed( float s ) { scale_factor = s; }

    void setup_texture( void );
    void setup_lights( void );
    void draw_2d_arrow( int radius, int filled, int orientation );
    void draw_2d_x_arrows( int radius );
    void draw_2d_y_arrows( int radius );
    void draw_2d_z_arrows( int radius );
    void draw_2d_xy_arrows( int radius );

    int  get_mouse_code( int x, int y );

    /* Float array is either a single float (for single-axis controls),
       or two floats for X and Y (if an XY controller) */

    float get_z( void ) {       return float_array_val[0];  }
    float get_x( void ) {       return float_array_val[0];  }
    float get_y( void ) {
        if ( trans_type == GLUI_TRANSLATION_XY )    return float_array_val[1];
        else					return float_array_val[0];
    }

    void  set_z( float val );
    void  set_x( float val );
    void  set_y( float val );
    void  set_one_val( float val, int index );

    GLUI_Translation( GLUI_Node *parent, const char *name,
                      int trans_type, float *live_var=NULL,
                      int id=-1, GLUI_CB callback=GLUI_CB()	);

protected:
    void common_init() {
        locked              = GLUI_TRANSLATION_LOCK_NONE;
        w                   = GLUI_MOUSE_INTERACTION_WIDTH;
        h                   = GLUI_MOUSE_INTERACTION_HEIGHT;
        can_activate        = true;
        live_type           = GLUI_LIVE_FLOAT_ARRAY;
        float_array_size    = 0;
        alignment           = GLUI_ALIGN_CENTER;
        trans_type          = GLUI_TRANSLATION_XY;
        scale_factor        = 1.0;
        quadObj             = NULL;
        trans_mouse_code    = GLUI_TRANSLATION_MOUSE_NONE;
    }
};



#endif //__GLUI_TRANSLATION_H
