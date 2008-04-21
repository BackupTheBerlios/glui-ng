/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_splitter.h - header for Splitter class
        GLUI User Interface Toolkit

          --------------------------------------------------

  Copyright (c) 2007 MALET Jean-Luc

  WWW:    http://sourceforge.net/projects/glui/
  Forums: http://sourceforge.net/forum/?group_id=92496

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

*****************************************************************************/
#ifndef __GLUI_CONTAINER_H
#define __GLUI_CONTAINER_H

enum GLUI_orientation {
    GLUI_horizontal,
    GLUI_vertical,
	GLUI_parent
};

/************************************************************/
/*                                                          */
/*               Container class (container)                   */
/*                                                          */
/************************************************************/
/**
  Special control that contain other child (compared to GLUI_Control leafs)
*/

class GLUIAPI GLUI_Container : public GLUI_Control
{
    public :
    GLUI_Container(const char *name,
                   GLUI_orientation orient=GLUI_vertical);
    virtual void update_size( void ); //<recursively update all control sizes
    virtual void pack ( int x, int y); //<recursively update positions
    virtual void translate_and_draw (void);  //<draw with the right size and position
    void set_orientation( GLUI_orientation new_orientation) {orientation = new_orientation; }
    virtual void align( void );

    protected :
    GLUI_orientation orientation;
    int              total_child_w;

    protected : //internal API
    void GLUI_Container::check_size_constency( void );

    ///data :
    protected :
    int             x_off, y_off;            // offset between childs elements
    int             y_off_top, y_off_bot;    // top and bottom margin inside the control
    int             x_off_left, x_off_right; // right and left inner margin
    int             contain_x, contain_y;
    int             contain_w, contain_h;
    /* if this is a container control (e.g.,
       radiogroup or panel) this indicated dimensions
       of inner area in which controls reside */

};
#endif //__GLUI_SPLITTER_H

