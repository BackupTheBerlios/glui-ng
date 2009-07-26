#ifndef __GLUI_WINDOW_H
#define __GLUI_WINDOW_H
/*

  glui_window.cpp : the top level widget

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

#include <GL/glui/container.h>
#include <GL/glui/Exception.h>
#include <GL/glui/DefaultTheme.h>
#include <X11/Xlib.h>
#include <GL/gl.h>

#undef RootWindow
#undef DefaultScreen
#undef DefaultVisual


#define  GLUI_BOTTOM_VIEWPORT  -1000
// allow a stack of 500 objects
#define  GLUI_TOP_VIEWPORT     GLUI_BOTTOM_VIEWPORT + 500 * GLUI_CONTROL_MAX_THICKNESS

/*** Flags for GLUI class constructor ***/
#define  GLUI_SUBWINDOW          ((long)(1<<1))
#define  GLUI_SUBWINDOW_TOP      ((long)(1<<2))
#define  GLUI_SUBWINDOW_BOTTOM   ((long)(1<<3))
#define  GLUI_SUBWINDOW_LEFT     ((long)(1<<4))
#define  GLUI_SUBWINDOW_RIGHT    ((long)(1<<5))


namespace GLUI
{
        class _Window;

        typedef long unsigned int WindowId;
        enum ViewPort
        {
                BOTTOM_VIEWPORT=-1000,
                TOP_VIEWPORT= BOTTOM_VIEWPORT + 500 * GLUI_CONTROL_MAX_THICKNESS
        };


        class _Screen
        {
                public :
                        virtual int Depth()               =0;
                        virtual WindowId RootWindow()     =0;
        };

        class _Display
        {
                public :
                        virtual _Screen* DefaultScreen()  =0;
                        int DefaultVisual();
                protected :
                        _Display();
        };


        class _Window : public Container
        {
                public : //types
                        enum buffer_mode_t
                        {
                                buffer_front=1, ///< Draw updated controls directly to screen.
                                buffer_back=2   ///< Double buffering: postpone updates until next redraw.
                        };



                public :
                        _Window(const char *name,
                                        Container::orientation orient=Container::TopDown);
                        virtual ~_Window();
                        int Wait();
                        static buffer_mode_t get_buffer_mode();
                public :  //operators
                public : //XMethods
                        virtual void XMapWindow()=0;
                        virtual void XMapRaised()=0;
                        virtual void XMapSubwindows()=0;
                        virtual void XUnmapWindow()=0;
                        virtual void XUnmapSubwindows()=0;
                        virtual KeySym XLookupKeysym(::XKeyEvent *key_event, int index)=0; //a KeySym is a 32bit not unicode char
                        static  uint32_t KeySymToUcs4(KeySym keysym);
                public: //event handlers
                        virtual int AddEvent(::XEvent *event);
                        virtual int AddEvent(::XResizeRequestEvent* event);
                        virtual int AddEvent(::XExposeEvent* event);
                        virtual int AddEvent(::XDestroyWindowEvent* event);
                        virtual int AddEvent(::XKeyEvent* event);
                        virtual int AddEvent(::XButtonEvent* event);
                        virtual int AddEvent(::XMotionEvent* event);
                        virtual int AddEvent(::XCrossingEvent* event);
                        virtual int AddEvent(::XMapEvent* event);
                        virtual int AddEvent(::XUnmapEvent* event);
                        //virtual int         set_size( Size sz, Size min=Size(0u,0u) ); //replace with a XResizeRequestEvent                        

                protected : //types
                        class DefaultTheme : public _DefaultTheme
                        {
                                public : //methods
                                        DefaultTheme(_Window& owner);
                                        ~DefaultTheme();
                                        virtual int draw();
                                        virtual int update();
                                protected: //variable
                                        _Window& Owner;
                                protected: //methods
                                        void  SetOrthoProjection( void );
                                        void SetViewport(void);
                        };
                        struct ThreadArgs
                        {
                                _Window* TheWindow;
                                void* args;
                        };
                protected :
                        _Window();
                        void Start(void* args); //start event handler, shall be started in child constructor;
                        static void* _Start(void* args);
                        virtual int start_routine(void* args)=0; //< the thead main routine;

                        long flags;
                        int  SetCurrentDrawBuffer( void );
                protected:
                        pthread_t main_thread;
                        bool mapped;

        };



}


int GLUIInit(int* argc, char** argv); //optional

//now select automatically the window class according to the
//window manager we use
#ifdef __USE_XLIB
#include <GL/glui/x11_window.h>
#elif  __USE_WIN32
#include <GL/glui/win32_window.h>
#else
#include <GL/glui/glut_window.h>
#endif


#endif //__GLUI_WINDOW_H

