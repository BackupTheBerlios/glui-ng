/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui.h - Main header for
        GLUI User Interface Toolkit

          --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher

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

#ifndef GLUI_GLUI_H
#define GLUI_GLUI_H



// Having stdlib here first fixes some 'exit() redefined' errors on MSVC.NET
// that come from old GLUT headers.
#include <cstdlib>
#include <GL/glui/debug.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <GL/glui/commondefs.h>
#include <GL/glui/to_clean.h>


/**********  Translation codes  **********/

enum TranslationCodes
{
    GLUI_TRANSLATION_MOUSE_NONE = 0,
    GLUI_TRANSLATION_MOUSE_UP,
    GLUI_TRANSLATION_MOUSE_DOWN,
    GLUI_TRANSLATION_MOUSE_LEFT,
    GLUI_TRANSLATION_MOUSE_RIGHT,
    GLUI_TRANSLATION_MOUSE_UP_LEFT,
    GLUI_TRANSLATION_MOUSE_UP_RIGHT,
    GLUI_TRANSLATION_MOUSE_DOWN_LEFT,
    GLUI_TRANSLATION_MOUSE_DOWN_RIGHT
};

/************ A string type for us to use **********/

GLUIAPI std::string& glui_format_str(std::string &str, const char* fmt, ...);



#include <GL/glui/callback.h>

#include <GL/glui/node.h>
#include <GL/glui/bitmaps.h>


#include <GL/glui/text.h>
#include <GL/glui/main.h>
#include <GL/glui/control.h>
#include <GL/glui/separator.h>
#include <GL/glui/container.h>
#include <GL/glui/button.h>
#include <GL/glui/checkbox.h>
#include <GL/glui/panel.h>
#include <GL/glui/splitter.h>
#include <GL/glui/file_browser.h>
#include <GL/glui/collapsible.h>
#include <GL/glui/rollout.h>
#include <GL/glui/tree.h>
/************************************************************/
/*                                                          */
/*                     User-Level GLUI class                */
/*                                                          */
/************************************************************/


#include <GL/glui/window.h>
#include <GL/glui/glui.h>
#include <GL/glui/edittext.h>
#include <GL/glui/commandline.h>
#include <GL/glui/radio.h>
#include <GL/glui/spinner.h>
#include <GL/glui/statictext.h>
#include <GL/glui/textbox.h>
#include <GL/glui/list.h>
#include <GL/glui/scrollbar.h>
#include <GL/glui/listbox.h>
#include <GL/glui/mouse_interaction.h>
#include <GL/glui/rotation.h>
#include <GL/glui/translation.h>

/********** Misc functions *********************/
int _glutBitmapWidthString( void *font, const char *s );
void _glutBitmapString( void *font, const char *s );


#endif
