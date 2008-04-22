/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_debug.h - Glui trace facility


          --------------------------------------------------

  Copyright (c) 2007 Jean-Luc MALET

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
#ifndef __GLUI_COLLAPSIBLE_H
#define __GLUI_COLLAPSIBLE_H
#include <GL/glui/glui_commondefs.h>
#include <GL/glui/glui_container.h>

class GLUIAPI GLUI_Collapsible : public GLUI_Container
{
    public  :
        GLUI_Collapsible(const char *name,
                   GLUI_orientation orient=GLUI_vertical);
        void  open               (  bool recurse=false );
        void  close              (  bool recurse=false );

    protected :
        bool            is_open;
        GLUI_Control*   Toggle; //the toggle ie widget that is always displayed
        GLUI_Control*   Content; //the content that can or not be displayed
};
#endif //__GLUI_COLLAPSIBLE_H
