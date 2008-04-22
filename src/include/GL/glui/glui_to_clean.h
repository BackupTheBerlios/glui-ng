#ifndef __GLUI_TO_CLEAN_H
#define __GLUI_TO_CLEAN_H
/********* Constants for window placement **********/

#define GLUI_XOFF                       6
#define GLUI_YOFF                       6
#define GLUI_ITEMSPACING                3
#define GLUI_CHECKBOX_SIZE             13
#define GLUI_RADIOBUTTON_SIZE          13
#define GLUI_BUTTON_SIZE               20
#define GLUI_STATICTEXT_SIZE           13
#define GLUI_SEPARATOR_HEIGHT           8
#define GLUI_DEFAULT_CONTROL_WIDTH    100
#define GLUI_DEFAULT_CONTROL_HEIGHT    13
#define GLUI_EDITTEXT_BOXINNERMARGINX   3
#define GLUI_EDITTEXT_HEIGHT           20
#define GLUI_EDITTEXT_WIDTH           130
#define GLUI_EDITTEXT_MIN_INT_WIDTH    35
#define GLUI_EDITTEXT_MIN_TEXT_WIDTH   50
#define GLUI_PANEL_NAME_DROP            8
#define GLUI_PANEL_EMBOSS_TOP           4
/* #define GLUI_ROTATION_WIDTH         60 */
/* #define GLUI_ROTATION_HEIGHT        78 */
#define GLUI_ROTATION_WIDTH            50
#define GLUI_ROTATION_HEIGHT           (GLUI_ROTATION_WIDTH+18)
#define GLUI_MOUSE_INTERACTION_WIDTH   50
#define GLUI_MOUSE_INTERACTION_HEIGHT  (GLUI_MOUSE_INTERACTION_WIDTH)+18

/** Different panel control types **/
#define GLUI_PANEL_NONE      0
#define GLUI_PANEL_EMBOSSED  1
#define GLUI_PANEL_RAISED    2

/**  Max # of els in control's float_array  **/
#define GLUI_DEF_MAX_ARRAY  30

/********* The control's 'active' behavior *********/
#define GLUI_CONTROL_ACTIVE_MOUSEDOWN       1
#define GLUI_CONTROL_ACTIVE_PERMANENT       2

/********* Control alignment types **********/
#define GLUI_ALIGN_CENTER   1
#define GLUI_ALIGN_RIGHT    2
#define GLUI_ALIGN_LEFT     3

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

/********** What type of live variable does a control have? **********/
#define GLUI_LIVE_NONE          0
#define GLUI_LIVE_INT           1
#define GLUI_LIVE_FLOAT         2
#define GLUI_LIVE_TEXT          3
#define GLUI_LIVE_STRING        6
#define GLUI_LIVE_DOUBLE        4
#define GLUI_LIVE_FLOAT_ARRAY   5

/************* Textbox and List Defaults - JVK ******************/
#define GLUI_TEXTBOX_HEIGHT          130
#define GLUI_TEXTBOX_WIDTH           130
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

/******************* GLUI Scrollbar Defaults - JVK ***************************/
#define  GLUI_SCROLL_ARROW_WIDTH     16
#define  GLUI_SCROLL_ARROW_HEIGHT    16
#define  GLUI_SCROLL_BOX_MIN_HEIGHT   5
#define  GLUI_SCROLL_BOX_STD_HEIGHT  16
#define  GLUI_SCROLL_STATE_NONE       0
#define  GLUI_SCROLL_STATE_UP         1
#define  GLUI_SCROLL_STATE_DOWN       2
#define  GLUI_SCROLL_STATE_BOTH       3
#define  GLUI_SCROLL_STATE_SCROLL     4
#define  GLUI_SCROLL_DEFAULT_GROWTH_EXP   1.05f
#define  GLUI_SCROLL_VERTICAL         0
#define  GLUI_SCROLL_HORIZONTAL       1


/** Size of the character width hash table for faster lookups.
  Make sure to keep this a power of two to avoid the slow divide.
  This is also a speed/memory tradeoff; 128 is enough for low ASCII.
*/
#define CHAR_WIDTH_HASH_SIZE 128


#endif //__GLUI_TO_CLEAN_H
