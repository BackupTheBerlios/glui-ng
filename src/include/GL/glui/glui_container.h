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
    GLUI_Container();
    virtual void update_size( void );
    virtual void pack ( int x, int y);
    void set_orientation( GLUI_orientation new_orientation);
    virtual int min_w();
    virtual int min_h();


    private :
    GLUI_orientation orientation;

};
#endif //__GLUI_SPLITTER_H

