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
#include "glui_debug.h"

#if defined(GLUI_FREEGLUT)

  // FreeGLUT does not yet work perfectly with GLUI
  //  - use at your own risk.

  #include <GL/freeglut.h>

#elif defined(GLUI_OPENGLUT)

  // OpenGLUT does not yet work properly with GLUI
  //  - use at your own risk.

  #include <GL/openglut.h>

#else

  #ifdef __APPLE__
  #include <GLUT/glut.h>
  #else
  #include <GL/glut.h>
  #endif

#endif

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

/* GLUI API shared library export/import declarations. */
#if defined(_WIN32)
# ifdef GLUI_BUILDING_LIB
#  ifdef GLUIDLL
#   define GLUIAPI __declspec(dllexport)
#  else
#   define GLUIAPI
#  endif
# else
#  ifdef GLUIDLL
#   define GLUIAPI __declspec(dllimport)
#  else
#   define GLUIAPI
#  endif
# endif
#else
#define GLUIAPI
#endif


#define GLUI_VERSION 2.36f    /********** Current version **********/

#if defined(_WIN32)
#  if !defined(GLUI_NO_LIB_PRAGMA) && !defined(GLUI_BUILDING_LIB)
// Link automatically with GLUI library
#    if defined GLUIDLL  // define this when using glui dynamic library
#      pragma comment(lib, "glui32dll.lib")
#    else
#      pragma comment(lib, "glui32.lib")
#    endif
#  endif
#endif


/********** List of GLUT callbacks ********/

enum GLUI_Glut_CB_Types
{
    GLUI_GLUT_RESHAPE,
    GLUI_GLUT_KEYBOARD,
    GLUI_GLUT_DISPLAY,
    GLUI_GLUT_MOUSE,
    GLUI_GLUT_MOTION,
    GLUI_GLUT_SPECIAL,
    GLUI_GLUT_PASSIVE_MOTION,
    GLUI_GLUT_ENTRY,
    GLUI_GLUT_VISIBILITY
};

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

/********* Pre-declare classes as needed *********/

class GLUI;
class GLUI_Control;
class GLUI_Listbox;
class GLUI_StaticText;
class GLUI_EditText;
class GLUI_Panel;
class GLUI_Spinner;
class GLUI_RadioButton;
class GLUI_RadioGroup;
class GLUI_Glut_Window;
class GLUI_TreePanel;
class GLUI_Scrollbar;
class GLUI_List;

class Arcball;

/*** Flags for GLUI class constructor ***/
#define  GLUI_SUBWINDOW          ((long)(1<<1))
#define  GLUI_SUBWINDOW_TOP      ((long)(1<<2))
#define  GLUI_SUBWINDOW_BOTTOM   ((long)(1<<3))
#define  GLUI_SUBWINDOW_LEFT     ((long)(1<<4))
#define  GLUI_SUBWINDOW_RIGHT    ((long)(1<<5))

/*** Codes for different type of edittext boxes and spinners ***/
#define GLUI_EDITTEXT_TEXT             1
#define GLUI_EDITTEXT_INT              2
#define GLUI_EDITTEXT_FLOAT            3
#define GLUI_SPINNER_INT               GLUI_EDITTEXT_INT
#define GLUI_SPINNER_FLOAT             GLUI_EDITTEXT_FLOAT
#define GLUI_SCROLL_INT                GLUI_EDITTEXT_INT
#define GLUI_SCROLL_FLOAT              GLUI_EDITTEXT_FLOAT
// This is only for deprecated interface
#define GLUI_EDITTEXT_STRING           4

/*** Definition of callbacks ***/
typedef void (*GLUI_Update_CB) (int id);
typedef void (*GLUI_Control_CB)(GLUI_Control *);
typedef void (*Int1_CB)        (int);
typedef void (*Int2_CB)        (int, int);
typedef void (*Int3_CB)        (int, int, int);
typedef void (*Int4_CB)        (int, int, int, int);

/************************************************************/
/**
 Callback Adapter Class
    Allows us to support different types of callbacks;
    like a GLUI_Update_CB function pointer--which takes an int;
    and a GLUI_Control_CB function pointer--which takes a GUI_Control object.
*/
class GLUIAPI GLUI_CB
{
public:
  GLUI_CB() : idCB(0),objCB(0) {}
  GLUI_CB(GLUI_Update_CB cb) : idCB(cb),objCB(0) {}
  GLUI_CB(GLUI_Control_CB cb) : idCB(0),objCB(cb) {}
  // (Compiler generated copy constructor)

  /** This control just activated.  Fire our callback.*/
  void operator()(GLUI_Control *ctrl) const;
  bool operator!() const { return !idCB && !objCB; }
  operator bool() const { return !(!(*this)); }
private:
  GLUI_Update_CB idCB;
  GLUI_Control_CB objCB;
};

#include <GL/glui/glui_node.h>
#include <GL/glui/glui_bitmaps.h>
/************************************************************/
/*                                                          */
/*                     Master GLUI Class                    */
/*                                                          */
/************************************************************/

/**
 The master manages our interaction with GLUT.
 There's only one GLUI_Master_Object.
*/
class GLUIAPI GLUI_Master_Object
{

    friend void glui_idle_func();

public:

    GLUI_Master_Object();
    ~GLUI_Master_Object();

    GLUI_Node     gluis;
    GLUI_Control *active_control, *curr_left_button_glut_menu;
    GLUI         *active_control_glui;
    int           glui_id_counter;

    GLUI_Glut_Window   *find_glut_window( int window_id );

    void           set_glutIdleFunc(void (*f)(void));

    /**************
    void (*glut_keyboard_CB)(unsigned char, int, int);
    void (*glut_reshape_CB)(int, int);
    void (*glut_special_CB)(int, int, int);
    void (*glut_mouse_CB)(int,int,int,int);

    void (*glut_passive_motion_CB)(int,int);
    void (*glut_visibility_CB)(int);
    void (*glut_motion_CB)(int,int);
    void (*glut_display_CB)(void);
    void (*glut_entry_CB)(int);
    **********/

    void  set_left_button_glut_menu_control( GLUI_Control *control );

    /********** GLUT callthroughs **********/
    /* These are the glut callbacks that we do not handle */

    void set_glutReshapeFunc (void (*f)(int width, int height));
    void set_glutKeyboardFunc(void (*f)(unsigned char key, int x, int y));
    void set_glutSpecialFunc (void (*f)(int key, int x, int y));
    void set_glutMouseFunc   (void (*f)(int, int, int, int ));

    void set_glutDisplayFunc(void (*f)(void)) {glutDisplayFunc(f);}
    void set_glutTimerFunc(unsigned int millis, void (*f)(int value), int value)
    { ::glutTimerFunc(millis,f,value);}
    void set_glutOverlayDisplayFunc(void(*f)(void)){glutOverlayDisplayFunc(f);}
    void set_glutSpaceballMotionFunc(Int3_CB f)  {glutSpaceballMotionFunc(f);}
    void set_glutSpaceballRotateFunc(Int3_CB f)  {glutSpaceballRotateFunc(f);}
    void set_glutSpaceballButtonFunc(Int2_CB f)  {glutSpaceballButtonFunc(f);}
    void set_glutTabletMotionFunc(Int2_CB f)        {glutTabletMotionFunc(f);}
    void set_glutTabletButtonFunc(Int4_CB f)        {glutTabletButtonFunc(f);}
    /*    void set_glutWindowStatusFunc(Int1_CB f)        {glutWindowStatusFunc(f);} */
    void set_glutMenuStatusFunc(Int3_CB f)            {glutMenuStatusFunc(f);}
    void set_glutMenuStateFunc(Int1_CB f)              {glutMenuStateFunc(f);}
    void set_glutButtonBoxFunc(Int2_CB f)              {glutButtonBoxFunc(f);}
    void set_glutDialsFunc(Int2_CB f)                      {glutDialsFunc(f);}


    GLUI          *create_glui( const char *name, long flags=0, int x=-1, int y=-1 );
    GLUI          *create_glui_subwindow( int parent_window, long flags=0 );
    GLUI          *find_glui_by_window_id( int window_id );
    void           get_viewport_area( int *x, int *y, int *w, int *h );
    void           auto_set_viewport();
    void           close_all();
    void           sync_live_all();

    void           reshape();

    float          get_version() { return GLUI_VERSION; }

    void glui_setIdleFuncIfNecessary(void);


private:
    GLUI_Node     glut_windows;

    void (*glut_idle_CB)(void);
    void          add_cb_to_glut_window(int window,int cb_type,void *cb);
};

/**
 This is the only GLUI_Master_Object in existence.
*/
extern GLUIAPI GLUI_Master_Object GLUI_Master;

/************************************************************/
/*                                                          */
/*              Class for managing a GLUT window            */
/*                                                          */
/************************************************************/

/**
 A top-level window.  The GLUI_Master GLUT callback can route events
 to the callbacks in this class, for arbitrary use by external users.
 (see GLUI_Master_Object::set_glutKeyboardFunc).

 This entire approach seems to be superceded by the "subwindow" flavor
 of GLUI.
*/
class GLUIAPI GLUI_Glut_Window : public GLUI_Node
{
public:
    GLUI_Glut_Window();

    int    glut_window_id;

    /*********** Pointers to GLUT callthrough functions *****/
    void (*glut_keyboard_CB)(unsigned char, int, int);
    void (*glut_special_CB)(int, int, int);
    void (*glut_reshape_CB)(int, int);
    void (*glut_passive_motion_CB)(int,int);
    void (*glut_mouse_CB)(int,int,int,int);
    void (*glut_visibility_CB)(int);
    void (*glut_motion_CB)(int,int);
    void (*glut_display_CB)(void);
    void (*glut_entry_CB)(int);
};

#include <GL/glui/glui_text.h>
#include <GL/glui/glui_main.h>
#include <GL/glui/glui_control.h>
#include <GL/glui/glui_separator.h>
#include <GL/glui/glui_container.h>
#include <GL/glui/glui_button.h>
#include <GL/glui/glui_checkbox.h>
#include <GL/glui/glui_panel.h>
#include <GL/glui/glui_splitter.h>
#include <GL/glui/glui_file_browser.h>
#include <GL/glui/glui_collapsible.h>
#include <GL/glui/glui_rollout.h>
#include <GL/glui/glui_treepanel.h>
/************************************************************/
/*                                                          */
/*                     User-Level GLUI class                */
/*                                                          */
/************************************************************/

class GLUI_Rotation;
class GLUI_Translation;

#include <GL/glui/glui_glui.h>
#include <GL/glui/glui_edittext.h>
#include <GL/glui/glui_commandline.h>
#include <GL/glui/glui_radio.h>
#include <GL/glui/glui_spinner.h>
#include <GL/glui/glui_statictext.h>
#include <GL/glui/glui_textbox.h>
#include <GL/glui/glui_list.h>
#include <GL/glui/glui_scrollbar.h>
#include <GL/glui/glui_listbox.h>
#include <GL/glui/glui_mouse_interaction.h>
#include <GL/glui/glui_rotation.h>
#include <GL/glui/glui_translation.h>

/********** Misc functions *********************/
int _glutBitmapWidthString( void *font, const char *s );
void _glutBitmapString( void *font, const char *s );

/********** Our own callbacks for glut *********/
/* These are the callbacks that we pass to glut.  They take
   some action if necessary, then (possibly) call the user-level
   glut callbacks.
*/

void glui_display_func( void );
void glui_reshape_func( int w, int h );
void glui_keyboard_func(unsigned char key, int x, int y);
void glui_special_func(int key, int x, int y);
void glui_mouse_func(int button, int state, int x, int y);
void glui_motion_func(int x, int y);
void glui_passive_motion_func(int x, int y);
void glui_entry_func(int state);
void glui_visibility_func(int state);
void glui_idle_func(void);

void glui_parent_window_reshape_func( int w, int h );
void glui_parent_window_keyboard_func(unsigned char key, int x, int y);
void glui_parent_window_mouse_func(int, int, int, int );
void glui_parent_window_special_func(int key, int x, int y);

#endif
