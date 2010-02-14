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
#ifndef __GLUI_CONTAINER_H
#define __GLUI_CONTAINER_H

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
            enum orientation{ useparent, TopDown, BottomUp, LeftToRight, RightToLeft};
            enum alignement{ left, center, right };

        public : //methods
            Container(const char *name,
                    orientation orient=TopDown);
            virtual ~Container();

            virtual void update_size( void ); //<recursively update all control sizes
            virtual int  UpdateTheme( void );
            virtual void pack ( int x, int y); //<recursively update positions
            void set_orientation( orientation new_orientation);
            virtual void align( void );
            virtual int  add_control( NCRC_AutoPtr<Node> control );

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
            orientation GetParentOrientation();

        protected : //internal API
            NCRC_AutoPtr<Control> FindChildWidget(int x, int y);
            int BroadcastEvent(::XEvent* event, int EventType, long mask_check);
            int ForwardEvent(::XEvent* event, int* eventX, int* eventY, int EventType, long mask_check);

         protected : //variables
            orientation CurrOrientation;
            long        DoNotPropagateMask;

    };






}
#endif //__GLUI_CONTAINER_H

