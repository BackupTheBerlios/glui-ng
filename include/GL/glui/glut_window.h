#ifndef __GLUI_GLUT_WINDOW_H
#define __GLUI_GLUT_WINDOW_H
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

/************************************************************/
/*                                                          */
/*              Classes for managing a GLUT window            */
/*                                                          */
/************************************************************/

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
namespace GLUI
{
    class GlutDisplay;
    class GlutWindow;

    typedef GlutWindow Window;
    typedef GlutDisplay Display;

    class GlutScreen: public _Screen
    {
        public :
            virtual int Depth();
            virtual ::Window RootWindow();
    };


    class GlutDisplay: public _Display
    {
        public :
             GlutDisplay(char* name);
            virtual _Screen* DefaultScreen();
        private:
            GlutDisplay();
        private: //datas
            GlutScreen defaultscreen;
    };

    class GlutWindow : public _Window
    {
        public:
            enum class_type {
                InputOutputWin = InputOutput,
                InputWin = InputOnly
            };
        public:
            GlutWindow(Display* display,::Window parent,
                    int x, int y,
                    unsigned int width, unsigned int height,
                    unsigned int border_width,
                    int depth,
                    class_type _class,
                    Visual *visual,
                    unsigned long valuemask,
                    XSetWindowAttributes *attributes );
            GlutWindow(Display *display, ::Window parent,
                    int x, int y,
                    unsigned int width, unsigned int height,
                    unsigned int border_width,
                    unsigned long border,
                    unsigned long background );
            static int init(int* argc, char** argv); //optional
            virtual ~GlutWindow();
            ::Window GetWindowId();
            virtual void idle(); //< shall not rely on that, it binds you to GLUT

        public: //XMethods
            virtual void XMapWindow();
            virtual void XMapRaised();
            virtual void XMapSubwindows();
            virtual void XUnmapWindow();
            virtual void XUnmapSubwindows();
            virtual KeySym XLookupKeysym(::XKeyEvent *key_event, int index);


             virtual int AddEvent(::XExposeEvent* event);
             virtual int AddEvent(::XResizeRequestEvent* event);
             virtual int         set_size( Size sz, Size min=Size(0u,0u) ); //replace with a XResizeRequestEvent

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
            int start_routine(void* args);
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
            static void idle_func();

        protected: //variables
            unsigned int KeyModifierState;
            long unsigned int GlutWindowId;
            static bool glutinitialized;
            static pthread_mutex_t glut_mutex;
        protected: //defines
            enum _KeyModifierShift { KeyModifierShift=8 }; //256 first chars are already used in keyboard functions of glut
    };

}
#endif //__GLUI_GLUT_WINDOW_H
