/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_splitter.h - header for Splitter class
        GLUI User Interface Toolkit

          --------------------------------------------------

  Copyright (c) 2007 MALET Jean-Luc

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
#ifndef __GLUI_CONTAINER_H
#define __GLUI_CONTAINER_H
;

/************************************************************/
/*                                                          */
/*               Container class (container)                   */
/*                                                          */
/************************************************************/
/**
  Special control that contain other child (compared to Control leafs)
  */
#include <GL/glui/control.h>
namespace GLUI
{
    class GLUIAPI Container : public Control
    {
        public : //enums
            enum orientation{ horizontal, vertical, useparent};
            enum alignement{ left, center, right };

        public : //methods
            Container(const char *name,
                    orientation orient=vertical);
            virtual ~Container();

            virtual void update_size( void ); //<recursively update all control sizes
            virtual void pack ( int x, int y); //<recursively update positions
            void set_orientation( orientation new_orientation);
            virtual void align( void );
            int  add_control( Node *control );

            virtual int AddEvent (::XEvent* event);
            virtual int AddEvent (::XKeyEvent* event);
            virtual int AddEvent (::XButtonEvent* event);
            virtual int AddEvent (::XMotionEvent* event);
            virtual int AddEvent (::XCrossingEvent* event);
            virtual int AddEvent (::XFocusChangeEvent* event);
            virtual int AddEvent (::XKeymapEvent* event);
            virtual int AddEvent (::XExposeEvent* event);
            virtual int AddEvent (::XGraphicsExposeEvent* event);
            virtual int AddEvent (::XNoExposeEvent* event);
            virtual int AddEvent (::XVisibilityEvent* event);
            virtual int AddEvent (::XCreateWindowEvent* event);
            virtual int AddEvent (::XDestroyWindowEvent* event);
            virtual int AddEvent (::XUnmapEvent* event);
            virtual int AddEvent (::XMapEvent* event);
            virtual int AddEvent (::XMapRequestEvent* event);
            virtual int AddEvent (::XReparentEvent* event);
            virtual int AddEvent (::XConfigureEvent* event);
            virtual int AddEvent (::XGravityEvent* event);
            virtual int AddEvent (::XResizeRequestEvent* event);
            virtual int AddEvent (::XConfigureRequestEvent* event);
            virtual int AddEvent (::XCirculateEvent* event);
            virtual int AddEvent (::XCirculateRequestEvent* event);
            virtual int AddEvent (::XPropertyEvent* event);
            virtual int AddEvent (::XSelectionClearEvent* event);
            virtual int AddEvent (::XSelectionRequestEvent* event);
            virtual int AddEvent (::XSelectionEvent* event);
            virtual int AddEvent (::XColormapEvent* event);
            virtual int AddEvent (::XClientMessageEvent* event);
            virtual int AddEvent (::XMappingEvent* event);
            virtual int AddEvent (::XErrorEvent* event);





            virtual int Activate(); //< activate the current control

        protected : //internal API
            void check_size_constency( void );
            Control* FindChildWidget(int x, int y);

         protected : //variables
            orientation CurrOrientation;
            int              total_child_w;


            int             contain_x, contain_y;
            int             contain_w, contain_h;
            long            DoNotPropagateMask;
            /* if this is a container control (e.g.,
               radiogroup or panel) this indicated dimensions
               of inner area in which controls reside */

    };


    inline void Container::set_orientation( orientation new_orientation)
    {
        CurrOrientation = new_orientation;
    }

    inline Control* Container::FindChildWidget(int x, int y)
    {
        Node* current_node = first_child();
        while (current_node)
        {
            Control* current_control = dynamic_cast<Control*>(current_node);
            if (current_control)
            {
                if (x > current_control->x &&
                        x < (current_control->x + current_control->Width()) &&
                        y > current_control->y &&
                        y < (current_control->y + current_control->Height())
                   )
                    return current_control;
            }
            current_node = current_node->next();
        }
        return NULL;
    }

};
#endif //__GLUI_CONTAINER_H

