#ifndef __GLUI_RADIO_H
#define __GLUI_RADIO_H
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
/*              RadioGroup class (container)                */
/*                                                          */
/************************************************************/

class GLUIAPI GLUI_RadioGroup : public GLUI_Container
{
public:
    int  num_buttons;

    void draw( void );
    void set_name( char *text );
    void set_int_val( int int_val );
    void set_selected( int int_val );

    void draw_group( int translate );

    GLUI_RadioGroup( GLUI_Node *parent, const char* name, int *live_var=NULL,
                     int user_id=-1,GLUI_CB callback=GLUI_CB());
	~GLUI_RadioGroup();

protected:
    void common_init( void ) {
        x_off         = 0;
        y_off_top     = 0;
        y_off_bot     = 0;
        w             = 300;
        h             = 300;
        num_buttons   = 0;
        can_activate  = false;
        live_type     = GLUI_LIVE_INT;
    }
	GLUI_StaticText* title;
};

/************************************************************/
/*                                                          */
/*               RadioButton class (container)              */
/*                                                          */
/************************************************************/

class GLUIAPI GLUI_RadioButton : public GLUI_Container
{
public:
    int orig_value;
    bool currently_inside;
    int text_x_offset;

    int  mouse_down_handler( int local_x, int local_y );
    int  mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );

    void draw( void );

    void draw_active_area( void );
    void draw_checked( void );
    void draw_unchecked( void );
    void draw_O( void );

    GLUI_RadioButton( GLUI_RadioGroup *group, const char *name );
    GLUI_RadioGroup *group;

protected:
    void common_init()
    {
        h              = GLUI_RADIOBUTTON_SIZE;
        group          = NULL;
        orig_value     = -1;
        text_x_offset  = 18;
        can_activate   = true;
    }
};


#endif
