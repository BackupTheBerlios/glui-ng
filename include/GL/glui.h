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
