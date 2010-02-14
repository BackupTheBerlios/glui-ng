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

#ifndef __GLUI_CONTROL_H
#define __GLUI_CONTROL_H

/************************************************************/
/*                                                          */
/*       Control: base class for all controls          */
/*                                                          */
/************************************************************/

/**
 All the GUI objects inherit from Control: buttons,
 checkboxes, labels, edit boxes, scrollbars, etc.
 Most of the work of this class is in routing events,
 like keystrokes, mouseclicks, redraws, and sizing events.

 Yes, this is a huge and hideous class.  It needs to be
 split up into simpler subobjects.  None of the data members
 should be directly accessed by users (they should be protected,
 not public); only subclasses.
*/

#include <errno.h>
#include <GL/glui/commondefs.h>
#include <GL/glui/to_clean.h>

#include <GL/glui/Node.h>
#include <GL/glui/callback.h>
#include <GL/glui/xwrapper.h>
#include <GL/glui/event_handler.h>

#define GLUI_CONTROL_MAX_THICKNESS 4

namespace GLUI
{
    class LiveVariables;
    class Container;
    class theme;

    class GLUIAPI Control : public Node
    {
        public : //types
            enum SizePolicy {
                FixedSize,
                PercentOfParent,
                FillSpace,
                AdaptThisToFitChilds
            };

            struct Size {
                struct {
                    int w;
                    int h;
                } size;
                struct {
                    char w;
                    char h;
                } percent;
                Size(unsigned int w, unsigned int h)
                    {this->size.w=w; this->size.h=h;
                     percent.w = 0; percent.h = 0; }
                Size(float percent_w, float percent_h)
                    {   percent.w = (char) (percent_w * 100);
                        percent.h = (char) (percent_h * 100);
                        this->size.w=0; this->size.h=0; }
                Size()
                    {this->size.w=0; this->size.h=0;
                     percent.w = 0; percent.h = 0; }
                bool operator!=(const Size &other) const
                { return (this->size.w != other.size.w) ||
                    (this->size.h != other.size.h);
                }
                bool operator>(const Size &other) const
                {return (this->size.w > other.size.w) &&
                    (this->size.h > other.size.h);
                }
            };

            enum Alignement {
                CENTER,
                RIGHT,
                LEFT
            };



        public:
             virtual int    Width() const;
             virtual int    Height() const;
             int  YOffTop() const;
             int  YOffBot() const;
             int  XOffLeft() const;
             int  XOffRight() const;
             int  X() const;
             int  Y() const;

             int SetMargins(int top, int bottom, int left, int right);


             virtual int Activate(); //< activate the current control return 0 if activated, !=0 on error (can't activate)


        public:

            virtual void pack (int x, int y);
            virtual void update_size( void );
            virtual int  UpdateTheme( void );
            virtual void idle( void )            { }
            virtual int  mouse_over( int state, int x, int y ) { return false; }

            virtual void PostRedisplay();

            virtual void enable( void );
            virtual void disable( void );
            virtual void activate( int how )     { active = true; }
            virtual void deactivate( void )     { active = false; }

            //event interfaces
            virtual int AddEvent (::XEvent* event);
            virtual int AddEvent (::XKeyEvent* event);
            virtual int AddEvent (::XButtonEvent* event) { return 0; };
            virtual int AddEvent (::XMotionEvent* event) { return 0; };
            virtual int AddEvent (::XCrossingEvent* event) { return 0; };
            virtual int AddEvent (::XFocusChangeEvent* event) { return 0; };
            virtual int AddEvent (::XKeymapEvent* event) { return 0; };
            virtual int AddEvent (::XExposeEvent* event);
            virtual int AddEvent (::XGraphicsExposeEvent* event) { return 0; };
            virtual int AddEvent (::XNoExposeEvent* event) { return 0; };
            virtual int AddEvent (::XVisibilityEvent* event) { return 0; };
            virtual int AddEvent (::XCreateWindowEvent* event) { return 0; };
            virtual int AddEvent (::XDestroyWindowEvent* event) { return 0; };
            virtual int AddEvent (::XUnmapEvent* event) { return 0; };
            virtual int AddEvent (::XMapEvent* event) { return 0; };
            virtual int AddEvent (::XMapRequestEvent* event) { return 0; };
            virtual int AddEvent (::XReparentEvent* event) { return 0; };
            virtual int AddEvent (::XConfigureEvent* event) { return 0; };
            virtual int AddEvent (::XGravityEvent* event) { return 0; };
            virtual int AddEvent (::XResizeRequestEvent* event) { return 0; };
            virtual int AddEvent (::XConfigureRequestEvent* event) { return 0; };
            virtual int AddEvent (::XCirculateEvent* event) { return 0; };
            virtual int AddEvent (::XCirculateRequestEvent* event) { return 0; };
            virtual int AddEvent (::XPropertyEvent* event) { return 0; };
            virtual int AddEvent (::XSelectionClearEvent* event) { return 0; };
            virtual int AddEvent (::XSelectionRequestEvent* event) { return 0; };
            virtual int AddEvent (::XSelectionEvent* event) { return 0; };
            virtual int AddEvent (::XColormapEvent* event) { return 0; };
            virtual int AddEvent (::XClientMessageEvent* event) { return 0; };
            virtual int AddEvent (::XMappingEvent* event) { return 0; };
            virtual int AddEvent (::XErrorEvent* event) { return 0; };

            //this function can't be called into a constructor!
            virtual int         set_size( Size sz, Size min=Size(0u,0u) ); //replace with a XResizeRequestEvent

            void         set_alignment( Alignement align );
            void         set_resize_policy( SizePolicy policy) { resizeable = policy; }
            SizePolicy   get_resize_policy( void ) { return resizeable;}
            int SetTheme(NCRC_AutoPtr<theme> data);

            int  add_control( NCRC_AutoPtr<Node> control ); //<prevent adding subsequent controls

            virtual ~Control();

        protected: //methods
            Control(const char* name);
            Control();
            virtual NCRC_AutoPtr<theme> GetDefaultTheme();
        public: //variables
            int             alignment;
            bool            enabled;    //< Is this control grayed out?
            unsigned long   EventMask;  //<mask used to inform containers about what type of event is wanted

        protected: //variables
            NCRC_AutoPtr<theme> TheDefaultTheme;
            NCRC_AutoPtr<theme> ThemeData;
            static NCRC_AutoPtr<Control> focussed;
            SizePolicy resizeable;
            Size Min;
            Size CurrentSize;
            NCRC_AutoPtr<EventHandler> handler;
            bool active;       ///< If true, we've got the focus
                        /** relative coordinates Y axis up as in OGL */
            int             x, y;         //relative position from parent
            int  y_off_top, y_off_bot;    // top and bottom margin inside the control
            int  x_off_left, x_off_right; // right and left inner margin
    };





}
#endif
