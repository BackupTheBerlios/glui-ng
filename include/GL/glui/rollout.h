#ifndef __GLUI_ROLLOUT_H
#define __GLUI_ROLLOUT_H
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
