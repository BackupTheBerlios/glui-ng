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
#include <GL/glui/glui_debug.h>

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

#include <GL/glui/glui_commondefs.h>

#include <GL/glui/glui_to_clean.h>




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

#include <GL/glui/glui_forward.h>

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

#include <GL/glui/glui_callback.h>

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
#include <GL/glui/glui_tree.h>
/************************************************************/
/*                                                          */
/*                     User-Level GLUI class                */
/*                                                          */
/************************************************************/



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
