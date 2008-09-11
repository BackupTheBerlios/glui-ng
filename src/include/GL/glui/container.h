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
        public :
            enum orientation
            {
                horizontal,
                vertical,
                useparent
            };

        public :
            Container(const char *name,
                    orientation orient=vertical);
            virtual void update_size( void ); //<recursively update all control sizes
            virtual void pack ( int x, int y); //<recursively update positions
            virtual void translate_and_draw (void);  //<draw with the right size and position
            void set_orientation( orientation new_orientation);
            virtual void align( void );
            int  add_control( Node *control );
            virtual int AddEvent (::XEvent* event);

        protected :
            orientation CurrOrientation;
            int              total_child_w;

        protected : //internal API
            void check_size_constency( void );
            int UpdateRelativePosition (int *x, int *y, int widget_x, int widget_y, int widget_w, int widget_h);
                //<update the absolute x and y of an event to provide relative to the widget, return 0 if the
                //event is inside widget, 1 if not

            ///data :
        protected :
            int             x_off, y_off;            // offset between childs elements
            int             y_off_top, y_off_bot;    // top and bottom margin inside the control
            int             x_off_left, x_off_right; // right and left inner margin
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

    inline int Container::UpdateRelativePosition(int *x, int *y, int widget_x, int widget_y, int widget_w, int widget_h)
    {
        if (*x > widget_x &&
                *x < (widget_x + widget_w) &&
                *y > widget_y &&
                *y < (widget_y + widget_h)
           )
        {
            *x = *x - widget_x;
            *y = *y - widget_y;
            return 0;
        }
        return 1; //default value
    }

};
#endif //__GLUI_CONTAINER_H

