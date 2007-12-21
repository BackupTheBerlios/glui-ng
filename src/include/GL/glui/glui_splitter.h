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
#ifndef __GLUI_SPLITTER_H
#define __GLUI_SPLITTER_H
#include <GL/glui.h>


/************************************************************/
/*                                                          */
/*               Splitter class                             */
/*                                                          */
/************************************************************/

/**
 A GLUI_Splitter object devide the drawing area into 2 container
 separated by an optional bar.
 The Layout can be either vertical or horizontal (default)
*/
class GLUIAPI GLUI_Splitter : public GLUI_Container
{
public:

    GLUI_Splitter( GLUI_Node *parent, const char* name, int draw_bar = true );

    GLUI_Panel *GetFirstPanel() {return &first_panel;}
    GLUI_Panel *GetSecondPanel() {return &second_panel;}

protected:
    GLUI_Panel first_panel;
    GLUI_Panel second_panel;
    GLUI_Separator separator;

    void common_init() {
        set_orientation(GLUI_horizontal);
        w            = 0;
        h            = 0;
        int_val      = 0;
        can_activate = false;
    }
};

#endif //__GLUI_SPLITTER_H
