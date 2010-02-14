#ifndef __GLUI_MOUSE_INTERACTION_H
#define __GLUI_MOUSE_INTERACTION_H
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
