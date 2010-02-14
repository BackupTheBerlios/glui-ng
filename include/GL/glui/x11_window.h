#ifndef __GLUI_X11_WINDOW_H
#define __GLUI_X11_WINDOW_H
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
