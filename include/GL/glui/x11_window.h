#ifndef __GLUI_GLUT_WINDOW_H
#define __GLUI_GLUT_WINDOW_H

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
#include <errno.h>
namespace GLUI
{


    class GLUIAPI X11Display : public _Display
    {
        public :
            X11Display();
            X11Display(char* name);
        private:
            void _X11Display(char* name);
            ::Display disp;
    };


    class GLUIAPI X11Window : public _Window
    {
        public:
            X11Window(X11Display* display, int parent_window,
                    int x, int y,
                    unsigned int width, unsigned int height,
                    unsigned int border_width,
                    int depth,
                    unsigned int _class,
                    Visual *visual,
                    unsigned long valuemask,
                    XSetWindowAttributes *attributes );
            X11Window(X11Display *display, Window parent,
                    int x, int y,
                    unsigned int width, unsigned int height,
                    unsigned int border_width,
                    unsigned long border,
                    unsigned long background );
            virtual int start_routine(void* args);
        public : //operators
            bool operator== (::Window target);
        protected:
            ::Window* window;
            X11Display* disp;
            X11Window();
    };

#define GLUIWindow X11Window
#define Display X11Display
}
#endif //__GLUI_GLUT_WINDOW_H
