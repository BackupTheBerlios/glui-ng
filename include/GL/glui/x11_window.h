#ifndef __GLUI_X11_WINDOW_H
#define __GLUI_X11_WINDOW_H

/*

  glui_X11_window.h : the top level widget, in X11

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
/*              Class for managing a X11 window             */
/*                                                          */
/************************************************************/

/**
 A top-level window.  The GLUcallback can route events
 to the callbacks in this class, for arbitrary use by external users.
 (see GLUI_Master_Object::set_glutKeyboardFunc).

 This entire approach seems to be superceded by the "subwindow" flavor
 of GLUI.
*/
#include <GL/glui/Exception.h>
#include <GL/glui/window.h>
#define GL_GLEXT_PROTOTYPES 1
#define GLX_GLXEXT_PROTOTYPES 1
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <errno.h>
#include <GL/gl.h>
#include <GL/glx.h>
namespace GLUI
{

        class X11Screen : public _Screen
        {
                public :
                        X11Screen(::Screen* ScreenNumber);
                        virtual int XDefaultDepthOfScreen();
                        virtual NCRC_AutoPtr<_Window> XRootWindowOfScreen();
                        ::Screen* Screen();
                protected:
                        ::Screen* TheScreen;
                private:
                        X11Screen();
        };

        class X11Display : public _Display
        {
                public :
                        X11Display();
                        ~X11Display();
                        X11Display(char* name);
                        virtual NCRC_AutoPtr<_Screen> XDefaultScreenOfDisplay();
                        virtual NCRC_AutoPtr<_Window> XDefaultRootWindow();
                        virtual NCRC_AutoPtr<_Window> XRootWindow(int screen_number);
                        ::Display* Disp();

                private:
                        void _X11Display(char* name);
                        ::Display* disp;
        };


        class X11Window : public _Window
        {
                public:
                        X11Window(      NCRC_AutoPtr<X11Display> display,
                                        NCRC_AutoPtr<_Window> parent_window,
                                        int x, int y,
                                        unsigned int width, unsigned int height,
                                        unsigned int border_width,
                                        int depth,
                                        unsigned int _class,
                                        Visual *visual,
                                        unsigned long valuemask,
                                        XSetWindowAttributes *attributes );

                        X11Window(      NCRC_AutoPtr<X11Display> display,
                                        NCRC_AutoPtr<_Window> parent_window,
                                        int x, int y,
                                        unsigned int width, unsigned int height,
                                        unsigned int border_width,
                                        unsigned long border,
                                        unsigned long background );
                        ~X11Window();
                        virtual int start_routine();
                        static int init(int* argc, char** argv) { return 0;} //optional
                        virtual void PostRedisplay();
                public : //XMethods
                        virtual int XMapWindow();
                        virtual int XMapRaised();
                        virtual int XMapSubwindows();
                        virtual int XUnmapWindow();
                        virtual int XUnmapSubwindows();
                        virtual int XSendEvent(::XEvent &evt);
                        virtual KeySym XLookupKeysym(::XKeyEvent *key_event, int index);
                public: //event handlers
                        virtual int AddEvent(::XClientMessageEvent* event);
                        virtual int AddEvent(::XMappingEvent* event);
                        virtual int AddEvent(::XCreateWindowEvent* event);
                        virtual int AddEvent(::XUnmapEvent *event);
                        virtual int AddEvent(::XMapEvent *event);
                        virtual int AddEvent(::XConfigureEvent* event);
                        virtual int AddEvent(::XExposeEvent* event);
                        virtual int AddEvent(::XResizeRequestEvent* event);


                public : //operators
                        bool operator== (::Window target);
                protected: //methods
                        void _X11Window(NCRC_AutoPtr<_Window> parent_window,
                                        int x, int y,
                                        unsigned int width, unsigned int height,
                                        unsigned int border_width,
                                        int depth,
                                        unsigned int _class,
                                        Visual *visual,
                                        unsigned long valuemask,
                                        XSetWindowAttributes *attributes );
                        X11Window();
                        int CreateGLContext();
                        void EventCoordToGLCoord(::XEvent& evt);
                protected: //variables
                        NCRC_AutoPtr<X11Display> disp;
                        XVisualInfo *vi;
                        GLXFBConfig *fbc;
                        int fbc_id;
                        GLXContext ctx;
                        bool hasContext;
                        bool dirty;

        };
        typedef X11Window Window ;
        typedef X11Display Display;
        typedef X11Screen Screen;
}


#endif //__GLUI_X11_WINDOW_H
