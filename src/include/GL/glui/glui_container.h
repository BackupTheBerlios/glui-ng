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
    void set_packrule (PackPolicy pol);
    virtual void align( void );
    virtual void pack( int x, int y );    /* Recalculate positions and offsets */

    void         set_w( int new_w );
    void         set_h( int new_w );



    protected :
    GLUI_orientation orientation;
    int              total_child_w

};
#endif //__GLUI_SPLITTER_H

