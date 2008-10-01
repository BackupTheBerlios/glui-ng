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
#include <GL/glui/container.h>
#include <GL/glui/panel.h>
#include <GL/glui/separator.h>


/************************************************************/
/*                                                          */
/*               Splitter class                             */
/*                                                          */
/************************************************************/

/**
 A Splitter object devide the drawing area into 2 container
 separated by an optional bar.
 The Layout can be either vertical or horizontal (default)
*/
namespace GLUI
{
    class GLUIAPI Splitter : public Container
    {
        public:
            Splitter( Node *parent, const char* name, bool draw_bar = true );
            Panel *GetFirstPanel() {return &first_panel;}
            Panel *GetSecondPanel() {return &second_panel;}
            void draw() {} //<nothing done here, all is done by translate_and_draw

        protected: //variables
            Panel first_panel;
            Panel second_panel;
            Separator separator;
            bool draw_separator;

        protected: //methods
            void common_init();
    };

    //////////inlines
    void Splitter::common_init()
    {
        set_orientation(horizontal);
        CurrentSize.size.w     = 0;
        CurrentSize.size.h     = 0;
    }

}
#endif //__SPLITTER_H
