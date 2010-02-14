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

#include <GL/glui/container.h>
#include <GL/glui/debug.h>
#include <GL/glui/themes.h>
#include <GL/gl.h>
using namespace std;
#include <algorithm>
using namespace GLUI;

#define MODULE_KEY  "GLUI_DEBUG_CONTAINER"

///////////////////////////////////////////////////////////////////////////////////////
Container::Container(const char *name ,
                   orientation orient):
    Control(name)

{
    CurrOrientation = orient;
    resizeable = AdaptThisToFitChilds;
    DoNotPropagateMask = 0;
}

///////////////////////////////////////////////////////////////////////////////////////
Container::~Container()
{
}



///////////////////////////////////////////////////////////////////////////////////////
#warning "split this in inline functions"
void Container::update_size( void )
{
    NCRC_AutoPtr<Node> node;
    NCRC_AutoPtr<Control> child;

    orientation theOrient = CurrOrientation;
    if( theOrient == useparent ) theOrient = GetParentOrientation();

    if ( this->resizeable == PercentOfParent || //fixed size computed from parent
         this->resizeable == FixedSize //we have a fixed size
       )
    {
#warning "this has to be tested and improved"
        int FillSpaceCount=0;
        int width = 0;
        int height = 0;

        Control::update_size();
        node = this->first_child();
        while (node != NULL)
        {
            child = dynamic_cast<Control*>(node.getPointee());
            if ( (child != NULL) &&
                 (child->get_resize_policy() != FillSpace)
               )
            {
                child->update_size();

                if (theOrient == LeftToRight || theOrient == RightToLeft )
                {
                    width += child->Width();
                    height = max<int> (height, child->Height());
                }
                else if (theOrient == TopDown || theOrient == BottomUp )
                {
                    width = max<int> (width, child->Width());
                    height += child->Height();
                }

            }
            node = node->next();
        }
        if (FillSpaceCount)
        {
            // now change type of auto fill space childs to have them
            // use percent size of parent instead of autofill feature
            node = this->first_child();
            Size newsize;

            if (theOrient == LeftToRight || theOrient == RightToLeft)
            {
                newsize.size.w = (this->CurrentSize.size.w - width) / FillSpaceCount;
                newsize.size.h = this->CurrentSize.size.h;
            }
            else if (theOrient == TopDown || theOrient == BottomUp )
            {
                newsize.size.w = this->CurrentSize.size.w;
                newsize.size.h = (this->CurrentSize.size.h - width) / FillSpaceCount;
            }


            while (node != NULL )
            {
                child = dynamic_cast<Control*>(node.getPointee());
                if ( (child != NULL) &&
                     (child->get_resize_policy() != FillSpace)
                   )
                {
                    child->set_size(newsize);
                }
                node = node->next();
            }
        }

    }
    else if (this->resizeable == AdaptThisToFitChilds)
    {

        node = this->first_child();
        //this is to ensure that scalable childs will go to min size
        this->CurrentSize.size.w = 0;
        this->CurrentSize.size.h = 0;
        int width = 0;
        int height = 0;

        //parse all childs updating their size firt
        while (node != NULL)
        {
            child = dynamic_cast<Control*>(node.getPointee());
            if (child != NULL)
            {
                child->update_size();

                if (theOrient == LeftToRight || theOrient == RightToLeft)
                {
                    width += child->Width();
                    height = max<int> (height, child->Height() );
                }
                else if (theOrient == TopDown || theOrient == BottomUp )
                {
                    width = max<int> (width, child->Width());
                    height += child->Height() ;
                }
            }
            node = node->next();
        }
        this->CurrentSize.size.w = width;
        this->CurrentSize.size.h = height;
    }
}
///////////////////////////////////////////////////////////////////////////////////////
int Container::UpdateTheme( void )
{
        Control::UpdateTheme();
        NCRC_AutoPtr<Control> child = dynamic_cast<Control*>(first_child().getPointee());
        while (child != NULL)
        {
                int  rc;
                rc = child->UpdateTheme();
                if(rc) return rc;
                NCRC_AutoPtr<Node> sibling = child->next();
                child = dynamic_cast<Control*>(sibling.getPointee());
        }
        return 0;

}
////////////////////////////////////////////////////////////////////////////////////////
void Container::pack (int x, int y)
{
    NCRC_AutoPtr<Control> child;
    NCRC_AutoPtr<Node> node = this->first_child();
    orientation theOrient = CurrOrientation;
    if( theOrient == useparent ) theOrient = GetParentOrientation();

    this->x = x;
    this->y = y;
    int ChildTotalWidth = 0;
    int ChildTotalHeight = 0;


    while (node != NULL)
    {
        child = dynamic_cast<Control*>(node.getPointee());
        if ( child != NULL)
        {
            if (theOrient == TopDown || theOrient == BottomUp )
            {
                if (theOrient == TopDown)
                {
                    ChildTotalHeight += child->Height();  //increment before setting
                    child->pack(x + x_off_left , y + this->Height() - y_off_top - ChildTotalHeight);
                }
                else
                {
                    child->pack(x + x_off_left , y + y_off_bot + ChildTotalHeight);
                    ChildTotalHeight += child->Height();
                }
            }
            else if (theOrient == LeftToRight || theOrient == RightToLeft)
            {
                if (theOrient == LeftToRight)
                {
                    child->pack(x + ChildTotalWidth + x_off_left, y + y_off_bot);
                    ChildTotalWidth += child->Width();
                }
                else
                {
                    ChildTotalWidth += child->Width();  //increment before setting
                    child->pack(x + this->Width() - x_off_right - ChildTotalWidth, y + y_off_bot);
                }
            }
        }
        node = node->next();
    }


}

///////////////////////////////////////////////////////////////////////////////////////
Container::orientation Container::GetParentOrientation()
{
    NCRC_AutoPtr<Container> parent = dynamic_cast<Container*>(this->parent().getPointee());
    if (CurrOrientation == useparent && parent != NULL)
    {
        return parent->GetParentOrientation();
    }
    else if (CurrOrientation == useparent && parent == NULL)
    {
        // even the top most parent has useparent, so arbitraly choose TopDown
        return TopDown;
    }
    return CurrOrientation;
}

///////////////////////////////////////////////////////////////////////////////////////
#warning "remove alignement code and create spacer control instead"
void Container::align()
{
    NCRC_AutoPtr<Container> par;


    if ( parent() == NULL)
        return;  /* Clearly this shouldn't happen, though */

    par = dynamic_cast<Container*>(parent().getPointee());
    if ( par == NULL )
        return;

    if ( alignment == Control::LEFT ) {
        x = par->X() ;
    }
    else if ( alignment == Control::RIGHT ) {
        x = par->X() + par->Width() - this->CurrentSize.size.w;
    }
    else if ( alignment == Control::CENTER ) {
        x = par->X() + (par->Width() - this->CurrentSize.size.w) / 2;
    }

    // now align childs
    NCRC_AutoPtr<Node> child;
    NCRC_AutoPtr<Container> childc;
    child = this->first_child();

    while( child != NULL )
    {
        childc=dynamic_cast<Container*>(child.getPointee());
        if (childc != NULL) childc->align();

        child = child->next();
    }
}

////////////////////////////////////////////////////////////////////////////////////////
int Container::add_control( NCRC_AutoPtr<Node> control )
{
        NCRC_AutoPtr<Control> child;

        child = dynamic_cast<Control*>(control.getPointee());
        if ( child != NULL )
        {
                Node::add_control(control);
                child->enabled = this->enabled;
                return 0;
        }
        return EINVAL;
}


////////////////////////////////////////////////////////////////////////////////////////
#warning "TODO : implement the DoNotPropagateMask update mechanism?"
int Container::AddEvent (::XEvent* event)
{
        IN("::XEvent");
        int err;
#warning "update this using tree list creation"
        // purpose : when an event is created, use the opengl selection mechanism to know what object shall handle the event
        // then create a list containing all parent (parent can have multiple childrens but only one parent is allowed per child)
        // then use this list to propagate the event rather than the following algorithm
        EVTMSG((::XEvent) *event);

        switch ( event->type )
        {
                case KeyPress : err = AddEvent((::XKeyEvent*) event); break;
                case KeyRelease: err = AddEvent((::XKeyEvent*) event); break;
                case ButtonPress: err = AddEvent((::XButtonEvent*) event); break;
                case ButtonRelease: err = AddEvent((::XButtonEvent*) event); break;
                case MotionNotify: err = AddEvent((::XMotionEvent*) event); break;
                case EnterNotify: err = AddEvent((::XCrossingEvent*) event); break;
                case LeaveNotify: err = AddEvent((::XCrossingEvent*) event); break;
                case FocusIn: err = AddEvent((::XFocusChangeEvent*) event); break;
                case FocusOut: err = AddEvent((::XFocusChangeEvent*) event); break;
                case KeymapNotify: err = AddEvent((::XKeymapEvent*) event); break;
                case Expose: err = AddEvent((::XExposeEvent*) event); break;
                case GraphicsExpose: err = AddEvent((::XGraphicsExposeEvent*) event); break;
                case NoExpose: err = AddEvent((::XNoExposeEvent*) event); break;
                case VisibilityNotify: err = AddEvent((::XVisibilityEvent*) event); break;
                case CreateNotify: err = AddEvent((::XCreateWindowEvent*) event); break;
                case DestroyNotify: err = AddEvent((::XDestroyWindowEvent*) event); break;
                case UnmapNotify: err = AddEvent((::XUnmapEvent*) event); break;
                case MapNotify: err = AddEvent((::XMapEvent*) event); break;
                case MapRequest: err = AddEvent((::XMapRequestEvent*) event); break;
                case ReparentNotify: err = AddEvent((::XReparentEvent*) event); break;
                case ConfigureNotify: err = AddEvent((::XConfigureEvent*) event); break;
                case ConfigureRequest: err = AddEvent((::XConfigureRequestEvent*) event); break;
                case GravityNotify: err = AddEvent((::XGravityEvent*) event); break;
                case ResizeRequest: err = AddEvent((::XResizeRequestEvent*) event); break;
                case CirculateNotify: err = AddEvent((::XCirculateEvent*) event); break;
                case CirculateRequest: err = AddEvent((::XCirculateRequestEvent*) event); break;
                case PropertyNotify: err = AddEvent((::XPropertyEvent*) event); break;
                case SelectionClear: err = AddEvent((::XSelectionClearEvent*) event); break;
                case SelectionRequest: err = AddEvent((::XSelectionRequestEvent*) event); break;
                case SelectionNotify: err = AddEvent((::XSelectionEvent*) event); break;
                case ColormapNotify: err = AddEvent((::XColormapEvent*) event); break;
                case ClientMessage: err = AddEvent((::XClientMessageEvent*) event); break;
                case MappingNotify: err = AddEvent((::XMappingEvent*) event); break;

                default : err = BroadcastEvent(event, LASTEvent, NoEventMask); break;
        }
        ROUT(err, "\n");
}

////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XKeyEvent* event)
{
    return Container::ForwardEvent((::XEvent*) event, &event->x, &event->y, KeyPress, KeyPressMask) &&
        Container::ForwardEvent((::XEvent*) event, &event->x, &event->y, KeyRelease, KeyReleaseMask);
}
////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XButtonEvent* event)
{
    return Container::ForwardEvent((::XEvent*) event, &event->x, &event->y, ButtonPress, ButtonPressMask) &&
        Container::ForwardEvent((::XEvent*) event, &event->x, &event->y, ButtonRelease, ButtonReleaseMask);
}
/////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XMotionEvent* event)
{
    if ( ( event->type == MotionNotify  &&
                ( ( DoNotPropagateMask & PointerMotionMask )                                    ||
                  ( DoNotPropagateMask & PointerMotionHintMask  )                               ||
                  ( (event->state & Button1Mask) && ( DoNotPropagateMask & Button1MotionMask )) ||
                  ( (event->state & Button1Mask) && ( DoNotPropagateMask & Button2MotionMask )) ||
                  ( (event->state & Button1Mask) && ( DoNotPropagateMask & Button3MotionMask )) ||
                  ( (event->state & Button1Mask) && ( DoNotPropagateMask & Button4MotionMask )) ||
                  ( (event->state & Button1Mask) && ( DoNotPropagateMask & Button5MotionMask )) ||
                  ( DoNotPropagateMask & ButtonMotionMask )
                )
         )
       )
        return 0;
    NCRC_AutoPtr<Control> child = FindChildWidget(event->x, event->y);
    if (child != NULL)
    {
        event->x = event->x - child->X();
        event->y = event->y - child->Y();
        return child->AddEvent((::XEvent*) event);
    }
    //the event is for this widget and not a child
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XCrossingEvent* event)
{
   return Container::ForwardEvent((::XEvent*) event, &event->x, &event->y, EnterNotify, EnterWindowMask) &&
        Container::ForwardEvent((::XEvent*) event, &event->x, &event->y, LeaveNotify, LeaveWindowMask);

}
////////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XFocusChangeEvent* event)
{
    return BroadcastEvent((::XEvent*) event, FocusIn, FocusChangeMask) &&
        BroadcastEvent((::XEvent*) event, FocusOut, FocusChangeMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XKeymapEvent* event)
{
    return BroadcastEvent((::XEvent*) event, KeymapNotify, KeymapStateMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XExposeEvent* event)
{
    NCRC_AutoPtr<Control> node;
    IN("\n");

    pack (x, y);
    // we don't need this since it's allready done into the Control::AddEvent(XEposeEvent)
    // glMatrixMode   ( GL_MODELVIEW );  // Select The Model View Matrix
    // glPushMatrix();
    // glLoadIdentity ( );    // Reset The Model View Matrix

    Control::AddEvent (event);
    node = dynamic_cast<Control*>(first_child().getPointee());
    while( node != NULL )
    {
        node->AddEvent(event);
        node = dynamic_cast<Control*>(node->next().getPointee());
    }
    // glPopMatrix();
    debug::Instance()->FlushGL();
    OUT("\n");
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XGraphicsExposeEvent* event)
{
    return Container::ForwardEvent((::XEvent*) event, &event->x, &event->y, GraphicsExpose, ExposureMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XNoExposeEvent* event)
{
    return BroadcastEvent((::XEvent*) event, NoExpose, ExposureMask);
}
//////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XVisibilityEvent* event)
{
    return BroadcastEvent((::XEvent*) event, VisibilityNotify, VisibilityChangeMask);
}
//////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XCreateWindowEvent* event)
{
    return BroadcastEvent((::XEvent*) event, CreateNotify, SubstructureNotifyMask);
}
//////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XDestroyWindowEvent* event)
{
    return BroadcastEvent((::XEvent*) event, DestroyNotify, StructureNotifyMask|SubstructureNotifyMask);
}
//////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XUnmapEvent* event)
{
    return BroadcastEvent((::XEvent*) event, UnmapNotify, StructureNotifyMask|SubstructureNotifyMask);
}
//////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XMapEvent* event)
{
    return BroadcastEvent((::XEvent*) event, MapNotify, StructureNotifyMask|SubstructureNotifyMask);
}
//////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XMapRequestEvent* event)
{
    return BroadcastEvent((::XEvent*) event, MapRequest, SubstructureRedirectMask);
}
//////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XReparentEvent* event)
{
    return ForwardEvent((::XEvent*) event, &event->x, &event->y, ReparentNotify, StructureNotifyMask|SubstructureNotifyMask);
}
//////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XConfigureEvent* event)
{
    return ForwardEvent((::XEvent*) event, &event->x, &event->y, ConfigureNotify, StructureNotifyMask|SubstructureNotifyMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XGravityEvent* event)
{
   return Container::ForwardEvent((::XEvent*) event, &event->x, &event->y, GravityNotify, StructureNotifyMask|SubstructureNotifyMask);
}
////////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XResizeRequestEvent* event)
{
    return BroadcastEvent((::XEvent*) event, ResizeRequest, ResizeRedirectMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XConfigureRequestEvent* event)
{
   return ForwardEvent((::XEvent*) event, &event->x, &event->y, ConfigureRequest, NoEventMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XCirculateEvent* event)
{
    return BroadcastEvent((::XEvent*) event, CirculateNotify, StructureNotifyMask|SubstructureNotifyMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XCirculateRequestEvent* event)
{
    return BroadcastEvent((::XEvent*) event, CirculateRequest, SubstructureRedirectMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XPropertyEvent* event)
{
    return BroadcastEvent((::XEvent*) event, PropertyNotify, PropertyChangeMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XSelectionClearEvent* event)
{
    return BroadcastEvent((::XEvent*) event, SelectionClear, NoEventMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XSelectionRequestEvent* event)
{
    return BroadcastEvent((::XEvent*) event, SelectionRequest, NoEventMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XSelectionEvent* event)
{
    return BroadcastEvent((::XEvent*) event, SelectionNotify, NoEventMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XColormapEvent* event)
{
    return BroadcastEvent((::XEvent*) event, ColormapNotify, NoEventMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XClientMessageEvent* event)
{
    return BroadcastEvent((::XEvent*) event, ClientMessage, NoEventMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XMappingEvent* event)
{
    return BroadcastEvent((::XEvent*) event, MappingNotify, NoEventMask);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Container::AddEvent (::XErrorEvent* event)
{
    return BroadcastEvent((::XEvent*) event, 0, NoEventMask);
}
//////////////////////////////////////////////////////////////////////////////////////////
int Container::BroadcastEvent(::XEvent* event, int type, long mask_check)
{
        IN("\n");
        if (LASTEvent != type && event->type != type)
        {
               ROUT(EINVAL,"\n");   //check if event is correct
        }
        if (DoNotPropagateMask & mask_check) 
        {
                ROUT(0,"DoNotPropagateMask\n"); // check if event is masked
        }

        //now broadcast to all childs
        NCRC_AutoPtr<Control> child = dynamic_cast<Control*>(first_child().getPointee());
        int rc=0;
        while (child != NULL && rc == 0)
        {
                rc = child->AddEvent(event);
                NCRC_AutoPtr<Node> sibling = child->next();
                child = dynamic_cast<Control*>(sibling.getPointee());
        }
        //the event is for this widget and not a child
        ROUT(rc,"\n");
}
//
////////////////////////////////////////////////////////////////////////////////////////////
int Container::ForwardEvent(::XEvent* event, int* eventX, int* eventY, int EventType, long mask_check)
{
        IN("\n");
        if (event->type != EventType)
        {
                //int strerror_r(int errnum, char *buf, size_t buflen);
                ROUT(EINVAL,"\n");
        }
        if (DoNotPropagateMask & mask_check)
        {
                ROUT(0,"DoNotPropagateMask\n");
        }

        NCRC_AutoPtr<Control> child = FindChildWidget(*eventX, *eventY);
        if (child != NULL)
        {
                int rc = child->AddEvent(event);
                ROUT(rc, "\n");
        }
        //the event is for this widget and not a child
        ROUT(0,"\n");

}

int Container::Activate()
{
    #warning "TODO : use FocusIn or FocusOut events for this feature"
    #warning "TODO : store the focussed child into focussed pointer of Control"
}

#warning "TODO : if key is tab or backtab or this control don't support..."
/*
int Container::AddEvent (::XKeyEvent* event)
{
    //... FocusIn through tab then send the event to the next sibling
    //    if there is no sibling return an error
    //
}
*/



////////////////////////////////////////////////////////////////////////////////////////////
void Container::set_orientation( orientation new_orientation)
{
    CurrOrientation = new_orientation;
    NCRC_AutoPtr<Container> cont  = dynamic_cast<Container*>(GetRootNode().getPointee());
    if ( cont != NULL)
      {
        cont->update_size();
        cont->pack (0, 0);
      }

}

////////////////////////////////////////////////////////////////////////////////////////////
NCRC_AutoPtr<Control> Container::FindChildWidget(int x, int y)
{
    NCRC_AutoPtr<Node> current_node = first_child();
    while (current_node != NULL)
      {
        NCRC_AutoPtr<Control> current_control = dynamic_cast<Control*>(current_node.getPointee());
        if (current_control != NULL)
          {
            if (x > current_control->X() &&
                    x < (current_control->X() + current_control->Width()) &&
                    y > current_control->Y() &&
                    y < (current_control->Y() + current_control->Height())
               )
                return current_control;
          }
        current_node = current_node->next();
      }
    return NULL;
}
