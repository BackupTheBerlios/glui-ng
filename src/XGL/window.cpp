/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

  glui_glut_window.cpp : a wrapper class to use glut as an event generator

  --------------------------------------------------

  Copyright (c) 2008 MALET Jean-Luc

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
#include <GL/glui/debug.h>
#include <GL/glui/x11_window.h>
#undef Display
#define MODULE_KEY "GLUI_DEBUG_XGL"
using namespace GLUI;
/////////////////////////////////////////////////////////////////////
X11Screen::X11Screen(::Screen* screen) : TheScreen(screen)
{
}
int X11Screen::XDefaultDepthOfScreen()
{
        return ::XDefaultDepthOfScreen(TheScreen);
}
::Window X11Screen::XRootWindowOfScreen()
{
        return ::XRootWindowOfScreen(TheScreen);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

X11Display::X11Display()
{
        _X11Display(getenv("DISPLAY"));
}

X11Display::X11Display(char* name)
{
        _X11Display(name);
}

void X11Display::_X11Display(char* name)
{
        disp = XOpenDisplay(name);
        if (! disp) throw Exception(EINVAL,__func__);
}


X11Display::operator ::Display*()
{
        return disp;
}

_Screen* X11Display::XDefaultScreenOfDisplay()
{
        return new X11Screen(::XDefaultScreenOfDisplay(disp));
}
_Window* X11Display::XDefaultRootWindow()
{
        return new ROWindow(::XDefaultRootWindow(disp));
}
_Window* X11Display::XRootWindow(int screen_number)
{
        return new ROWindow(::XRootWindow(disp,screen_number));
}
/////////////////////////////////////////////////////////////////////
int X11Window::XMapWindow()
{
        return ::XMapWindow(*disp,window);
}

int X11Window::XMapRaised()
{
        return ::XMapRaised(*disp,window);
}

int X11Window::XMapSubwindows() 
{
        return ::XMapSubwindows(*disp,window);
}

int X11Window::XUnmapWindow()
{
        return ::XUnmapWindow(*disp,window);
}

int X11Window::XUnmapSubwindows()
{
        return ::XUnmapSubwindows(*disp,window);
}

KeySym  X11Window::XLookupKeysym(::XKeyEvent *key_event, int index)
{
        return ::XLookupKeysym(key_event, index);
}


::Window X11Window::GetWindowId()
{
        return window;
}


int X11Window::AddEvent(::XClientMessageEvent *event)
{
        /* Destroy the window when the WM_DELETE_WINDOW message arrives */
        if( (Atom) event->data.l[ 0 ] == XInternAtom(*disp, "WM_DELETE_WINDOW", False))
        {
                int res = XDestroyWindow(*disp, window);
                if ( res ) return res;
                window = -1;
                return 0;
        }

}


int X11Window::AddEvent(::XMappingEvent *event)
{
        // man XRefreshKeyboardMapping
        //       The XRefreshKeyboardMapping function refreshes the stored modifier and keymap information.  You usually call this
        //       function when a MappingNotify event with a request member of MappingKeyboard or MappingModifier occurs.  The result
        //       is to update Xlib’s knowledge of the keyboard.

        XRefreshKeyboardMapping( (XMappingEvent *) &event );
}

int X11Window::AddEvent(::XCreateWindowEvent *event)
{
        set_size( Size((unsigned int)event->width,(unsigned int)event->height) );
}

int X11Window::AddEvent(::XConfigureEvent *event)
{
        set_size( Size((unsigned int)event->width,(unsigned int)event->height) );
}


int X11Window::start_routine()
{
        ::XEvent event;

        while( XWindowEvent(*disp, window, EventMask, &event) )
        {
                debug::Instance()->PrintEvent(MODULE_KEY, event );
                Container::AddEvent(&event);
        }


}
