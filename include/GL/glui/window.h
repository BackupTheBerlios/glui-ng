#ifndef __GLUI_WINDOW_H
#define __GLUI_WINDOW_H
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

#include <sys/time.h>

#include <GL/glui/container.h>
#include <GL/glui/Exception.h>
#include <GL/glui/DefaultTheme.h>
#include <GL/glui/SmartPointer.h>
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

        enum ViewPort
        {
                BOTTOM_VIEWPORT=-1000,
                TOP_VIEWPORT= BOTTOM_VIEWPORT + 500 * GLUI_CONTROL_MAX_THICKNESS
        };

        Time get_time(void);

        class _Screen : public NonCopyableReferenceCountedClass
        {
                public :
                        virtual int XDefaultDepthOfScreen()  =0;
                        virtual NCRC_AutoPtr<_Window> XRootWindowOfScreen() =0;
                        virtual ::Screen* Screen()=0;
        };

        class _Display  : public NonCopyableReferenceCountedClass
        {
                public :
                        virtual NCRC_AutoPtr<_Screen> XDefaultScreenOfDisplay()  =0;
                        //virtual _Screen* XScreenOfDisplay(int screen_number) =0;
                        virtual NCRC_AutoPtr<_Window> XDefaultRootWindow() =0;
                        virtual NCRC_AutoPtr<_Window> XRootWindow(int screen_number) =0;
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
                        ::Window GetWindowId();
                public :  //operators
                public : //XMethods
                        virtual int XMapWindow()=0;
                        virtual int XMapRaised()=0;
                        virtual int XMapSubwindows()=0;
                        virtual int XUnmapWindow()=0;
                        virtual int XUnmapSubwindows()=0;
                        virtual int XSendEvent(::XEvent &evt)=0;
                        virtual KeySym XLookupKeysym(::XKeyEvent *key_event, int index)=0; //a KeySym is a 32bit not unicode char
                        static  uint32_t KeySymToUcs4(KeySym keysym);
                public: //event handlers
                        virtual int AddEvent(::XResizeRequestEvent* event);
                        virtual int AddEvent(::XExposeEvent* event);
                        virtual int AddEvent(::XDestroyWindowEvent* event);
                        virtual int AddEvent(::XMapEvent* event);
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
                protected : //methods
                        _Window();
                        virtual void Start(); //start event handler, shall be started in child constructor;
                        static void* _Start(void* args);
                        int _Stop();
                        virtual int start_routine()=0; //< the thead main routine;
                        int  SetCurrentDrawBuffer( void );
                protected: //variables
                        ::Window window;
                        void* args; //arguments to the thread
                        pthread_t main_thread;
                        bool mapped;
                        bool thread_enabled;
                        long flags;

        };

        class ROWindow : public _Window
        {
                public : 
                        ROWindow(::Window win) { window = win; }
                public : //XMethods
                        virtual int XMapWindow() {return 0;}
                        virtual int XMapRaised() {return 0;}
                        virtual int XMapSubwindows() {return 0;}
                        virtual int XUnmapWindow() {return 0;}
                        virtual int XUnmapSubwindows() {return 0;}
                        virtual KeySym XLookupKeysym(::XKeyEvent *key_event, int index) {return 0;}
                        virtual int XSendEvent(::XEvent &evt) {return 0;};
                protected:
                        virtual void Start() {thread_enabled = false;}
                        virtual int start_routine() { return 0; }
                private:
                        ROWindow();
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
#error shallnotgothere
#include <GL/glui/glut_window.h>
#endif


#endif //__GLUI_WINDOW_H

