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

#include <GL/glui/node.h>
#include <GL/glui/callback.h>
#include <GL/glui/xwrapper.h>
#include <GL/glui/event_handler.h>


namespace GLUI
{
    class LiveVariables;
    class _Window;

    class GLUIAPI Control : public Node, public EventHandler
    {
        public : //types
            enum SizePolicy {
                FixedSize,
                PercentOfParent,
                FillSpace,
                AdaptThisToFitChilds,
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
                Size(int w, int h) {this->size.w=w; this->size.h=h; }
                Size() {this->size.w=0; this->size.h=0;}
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
                LEFT,
            };



        public:
            int            Width() const  {return CurrentSize.size.w;}
            int            Height() const {return CurrentSize.size.h;}

            /** Onscreen coordinates Y axis up as in OGL */
            int             x_abs, y_abs;

            virtual int Activate(); //< activate the current control return 0 if activated, !=0 on error (can't activate)

            int             alignment;
            bool            enabled;    //< Is this control grayed out?
            unsigned long   EventMask;  //<mask used to inform containers about what type of event is wanted


        public:

            virtual void pack (int x, int y);
            virtual void update_size( void );
            virtual void idle( void )            { }
            virtual int  mouse_over( int state, int x, int y ) { return false; }

            virtual void enable( void );
            virtual void disable( void );
            virtual void activate( int how )     { active = true; }
            virtual void deactivate( void )     { active = false; }

            virtual void draw(void)=0;
            virtual void translate_and_draw( void );

            //event interfaces
            virtual int AddEvent (::XEvent* event);
            virtual int AddEvent (::XKeyEvent* event);


            virtual int         set_size( Size sz, Size min=Size(0,0) );
            void         set_alignment( Alignement align );
            void         set_resize_policy( SizePolicy policy) { resizeable = policy; }
            SizePolicy   get_resize_policy( void ) { return resizeable;}


            virtual bool needs_idle( void ) const;
            virtual bool wants_tabs() const      { return false; }
            int  add_control( Node *control ); //<prevent adding subsequent controls

            Control(const char* name)
                : Node(name)
            {

                x_abs          = GLUI_XOFF;
                y_abs          = GLUI_YOFF;
                active         = false;
                enabled        = true;
                Min            = Size(0, 0);
                CurrentSize    = Min;
                alignment      = LEFT;
                resizeable     = FixedSize;
                handler = NULL;
            }

            virtual ~Control();

        protected: //methods
            Control();
        protected: //variables
            static Control* focussed;
            _Window *OwnerWindow;
            SizePolicy resizeable;
            Size CurrentSize;
            Size Min;
            EventHandler* handler;
            long EventMask;
            bool            active;       ///< If true, we've got the focus
    };

}
#endif
