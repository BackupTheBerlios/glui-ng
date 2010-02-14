#ifndef __GLUI_TREE_H
#define __GLUI_TREE_H
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

#include <GL/glui/glui_glui.h>

/**
  One collapsible entry in a GLUI_TreePanel.
*/
class GLUIAPI GLUI_Tree : public GLUI_Collapsible
{
public:
    GLUI_Tree(GLUI_Node *parent, const char *name,
              int open=false, int inset=0);

private:
    int level;   // how deep is this node
    float red;   //Color coding of column line
    float green;
    float blue;
    float lred;   //Color coding of level name
    float lgreen;
    float lblue;
    int id;
    GLUI_Splitter *column;
    int is_current;          // Whether this tree is the
    // current root in a treePanel
    int child_number;
    int format;

public:
    bool        currently_inside, initially_inside;
    GLUI_Button  button;
    GLUI_Text  level_name; // level name, eg: 1.1.2, III, or 3
	GLUI_Text  entry;

    void draw( void );
    void draw_pressed( void );
    int mouse_down_handler( int local_x, int local_y );
    int mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );

    /*   void set_name( char *text )   { panel.set_name( text ); }; */
    void update_size( void );
    void set_id(int i) { id = i; }
    void set_level(int l) { level = l; }
    void set_format(int f) { format = f; }
    void set_current(int c) { is_current = c; }
    int get_id() { return id; }
    int get_level() { return level; }
    int get_child_number() { return child_number; }
    void enable_bar() { if (column) { column->int_val = 1;  set_color(red, green, blue); } }
    void disable_bar() { if (column) { column->int_val = 0;  } }
    void set_child_number(int c) { child_number = c; }
    void set_level_color(float r, float g, float b) {
        lred = r;
        lgreen = g;
        lblue  = b;
    }
    void set_color(float r, float g, float b) {
        red = r;
        green = g;
        blue  = b;
    }
protected:
    GLUI_Splitter splitter;
    void common_init()
    {
        currently_inside = false;
        initially_inside = false;
        can_activate     = true;
        h                = GLUI_DEFAULT_CONTROL_HEIGHT + 7;
        w                = GLUI_DEFAULT_CONTROL_WIDTH;
        y_off_top        = 21;
        red              = .5;
        green            = .5;
        blue             = .5;
        lred             = 0;
        lgreen           = 0;
        lblue            = 0;
        column           = NULL;
        is_current       = 0;
        child_number     = 0;
        format           = 0;
        level            = 0;
    };
};



#endif
