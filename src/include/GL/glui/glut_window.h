#ifndef __GLUI_GLUT_WINDOW_H
#define __GLUI_GLUT_WINDOW_H

/*

  glui_glut_window.h : the top level widget, in glut

  GLUI User Interface Toolkit
  Copyright (c) 2008 MALET Jean-Luc

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

*/

/************************************************************/
/*                                                          */
/*              Classes for managing a GLUT window            */
/*                                                          */
/************************************************************/

/**
  A top-level window.  The GLUI_Master GLUT callback can route events
  to the callbacks in this class, for arbitrary use by external users.
  (see GLUI_Master_Object::set_glutKeyboardFunc).

  This entire approach seems to be superceded by the "subwindow" flavor
  of GLUI.
  */

#include <GL/glui/window.h>
namespace GLUI
{
    class GlutDisplay;
    class GlutWindow;

    typedef GlutWindow GLUIWindow;
    typedef GlutDisplay Display;
    typedef long unsigned int WindowId;



    class GlutDisplay: public _Display
    {
        public :
            GlutDisplay(char* name);
        private:
            GlutDisplay();
    };

    class GlutWindow : public _Window
    {
        public:
            enum class_type {
                InputOutputWin = InputOutput,
                InputWin = InputOnly
            };
        public:
            GlutWindow(Display* display, WindowId parent,
                    int x, int y,
                    unsigned int width, unsigned int height,
                    unsigned int border_width,
                    int depth,
                    class_type _class,
                    Visual *visual,
                    unsigned long valuemask,
                    XSetWindowAttributes *attributes );
            GlutWindow(Display *display, WindowId parent,
                    int x, int y,
                    unsigned int width, unsigned int height,
                    unsigned int border_width,
                    unsigned long border,
                    unsigned long background );
            virtual ~GlutWindow();
            virtual int AddEvent (::XEvent* event);
            WindowId GetWindowId();

        public: //XMethods
            virtual void XMapWindow();
            virtual void XMapRaised();
            virtual void XMapSubwindows();
            virtual void XUnmapWindow();
            virtual void XUnmapSubwindows();


        public: //event handlers
            int AddEvent(::XResizeRequestEvent* event);
            int AddEvent(::XExposeEvent* event);
            int AddEvent(::XDestroyWindowEvent* event);
            int AddEvent(::XKeyEvent* event);
            int AddEvent(::XButtonEvent* event);
            int AddEvent(::XMotionEvent* event);
            int AddEvent(::XCrossingEvent* event);
            int AddEvent(::XMapEvent* event);
            int AddEvent(::XUnmapEvent* event);

        protected: //methods

            GlutWindow();
            int _GlutWindow(Display* display, Window parent,
                    int x, int y,
                    unsigned int width, unsigned int height,
                    unsigned int border_width,
                    int depth,
                    class_type _class,
                    Visual *visual,
                    unsigned long valuemask,
                    XSetWindowAttributes *attributes );
            /*********** Pointers to GLUT callthrough functions *****/
            static void keyboard_func(unsigned char, int, int);
            static void special_func(int, int, int);
            static void reshape_func(int, int);
            static void passive_motion_func(int,int);
            static void mouse_func(int,int,int,int);
            static void visibility_func(int);
            static void motion_func(int,int);
            static void display_func(void);
            static void entry_func(int);

        protected: //variables
            unsigned int KeyModifierState;
            long unsigned int GlutWindowId;
        protected: //defines
            enum _KeyModifierShift { KeyModifierShift=8 }; //256 first chars are already used in keyboard functions of glut
    };


    inline GlutDisplay::GlutDisplay(char* name)
    {
        disp = NULL;
    }
}
#endif //__GLUI_GLUT_WINDOW_H