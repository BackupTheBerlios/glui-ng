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
#include <X11/Xlib.h>

#undef RootWindow
#undef DefaultScreen
#undef DefaultVisual



/*** Flags for GLUI class constructor ***/
#define  GLUI_SUBWINDOW          ((long)(1<<1))
#define  GLUI_SUBWINDOW_TOP      ((long)(1<<2))
#define  GLUI_SUBWINDOW_BOTTOM   ((long)(1<<3))
#define  GLUI_SUBWINDOW_LEFT     ((long)(1<<4))
#define  GLUI_SUBWINDOW_RIGHT    ((long)(1<<5))


namespace GLUI
{
    class _Window;



    class _Screen
    {
        public :
            virtual int Depth()               =0;
            virtual _Window* RootWindow()     =0;
    };

    class _Display
    {
        public :
            operator ::Display*();
            virtual _Screen* DefaultScreen()  =0;
            int DefaultVisual();
        protected :
            _Display();
            ::Display* disp;
    };


    class _Window : public Container
    {
        public :
            _Window(const char *name,
                    Container::orientation orient=Container::vertical);
            virtual int AddEvent (::XEvent *event);
        public :  //operators
            bool operator== (::Window window);
            void  set_ortho_projection( void );
            void  set_viewport( void );
            virtual void XMapWindow()=0;
            virtual void XMapRaised()=0;
            virtual void XMapSubwindows()=0;
            virtual void XUnmapWindow()=0;
            virtual void XUnmapSubwindows()=0;


            void SetViewport(void);

        protected :
            _Window();

            long flags;
            int  SetCurrentDrawBuffer( void );
    };

    inline void _Window::SetViewport()
    {
        glViewport( 0, 0, this->Width(), this->Height() );
    }


}
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

