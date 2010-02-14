#ifndef __GLUI_TO_CLEAN_H
#define __GLUI_TO_CLEAN_H
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

/********* Constants for window placement **********/

#define GLUI_XOFF                       6
#define GLUI_YOFF                       6
#define GLUI_ITEMSPACING                3
#define GLUI_RADIOBUTTON_SIZE          13
#define GLUI_BUTTON_SIZE               20
#define GLUI_STATICTEXT_SIZE           13

#define GLUI_DEFAULT_CONTROL_WIDTH    100
#define GLUI_DEFAULT_CONTROL_HEIGHT    13

/* #define GLUI_ROTATION_WIDTH         60 */
/* #define GLUI_ROTATION_HEIGHT        78 */
#define GLUI_ROTATION_WIDTH            50
#define GLUI_ROTATION_HEIGHT           (GLUI_ROTATION_WIDTH+18)
#define GLUI_MOUSE_INTERACTION_WIDTH   50
#define GLUI_MOUSE_INTERACTION_HEIGHT  (GLUI_MOUSE_INTERACTION_WIDTH)+18


/**  Max # of els in control's float_array  **/
#define GLUI_DEF_MAX_ARRAY  30

/********* The control's 'active' behavior *********/
#define GLUI_CONTROL_ACTIVE_MOUSEDOWN       1
#define GLUI_CONTROL_ACTIVE_PERMANENT       2

/********** Limit types - how to limit spinner values *********/
#define GLUI_LIMIT_NONE    0
#define GLUI_LIMIT_CLAMP   1
#define GLUI_LIMIT_WRAP    2

/********** Translation control types ********************/
#define GLUI_TRANSLATION_XY 0
#define GLUI_TRANSLATION_Z  1
#define GLUI_TRANSLATION_X  2
#define GLUI_TRANSLATION_Y  3

#define GLUI_TRANSLATION_LOCK_NONE 0
#define GLUI_TRANSLATION_LOCK_X    1
#define GLUI_TRANSLATION_LOCK_Y    2

/********** How was a control activated? *****************/
#define GLUI_ACTIVATE_MOUSE 1
#define GLUI_ACTIVATE_TAB   2


/************* Textbox and List Defaults - JVK ******************/

#define GLUI_LIST_HEIGHT             130
#define GLUI_LIST_WIDTH              130
#define GLUI_DOUBLE_CLICK              1
#define GLUI_SINGLE_CLICK              0
#define GLUI_TAB_WIDTH                50 /* In pixels */
#define GLUI_TEXTBOX_BOXINNERMARGINX   3
#define GLUI_TEXTBOX_MIN_TEXT_WIDTH   50
#define GLUI_LIST_BOXINNERMARGINX      3
#define GLUI_LIST_MIN_TEXT_WIDTH      50

/*********************** TreePanel Defaults - JVK *****************************/
#define GLUI_TREEPANEL_DEFAULTS               0 // bar, standard bar color
#define GLUI_TREEPANEL_ALTERNATE_COLOR        1 // Alternate between 8 different bar colors
#define GLUI_TREEPANEL_ENABLE_BAR             2 // enable the bar
#define GLUI_TREEPANEL_DISABLE_BAR            4 // disable the bar
#define GLUI_TREEPANEL_DISABLE_DEEPEST_BAR    8 // disable only the deepest bar
#define GLUI_TREEPANEL_CONNECT_CHILDREN_ONLY 16 // disable only the bar of the last child of each root
#define GLUI_TREEPANEL_DISPLAY_HIERARCHY     32 // display some sort of hierachy in the tree node title
#define GLUI_TREEPANEL_HIERARCHY_NUMERICDOT  64 // display hierarchy in 1.3.2 (etc... ) format
#define GLUI_TREEPANEL_HIERARCHY_LEVEL_ONLY 128 // display hierarchy as only the level depth






#endif //__GLUI_TO_CLEAN_H
