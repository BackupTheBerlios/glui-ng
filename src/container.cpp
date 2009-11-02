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
}

///////////////////////////////////////////////////////////////////////////////////////
Container::~Container()
{
    Control *item = (Control*) this->first_child();

    while (item)
    {
        Control *tmp = item;
        item = (Control*) item->next();
        delete tmp;
    }
}



///////////////////////////////////////////////////////////////////////////////////////
#warning "split this in inline functions"
void Container::update_size( void )
{
    Node* node;
    Control* child;

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
        while (NULL != node)
        {
            child = dynamic_cast<Control*>(node);
            if ( (NULL != child) &&
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


            while (NULL != node)
            {
                child = dynamic_cast<Control*>(node);
                if ( (NULL != child) &&
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
        while (NULL != node)
        {
            child = dynamic_cast<Control*>(node);
            if ( NULL != child)
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
        Control* child = dynamic_cast<Control*>(first_child());
        while (child != NULL)
        {
                int  rc;
                rc = child->UpdateTheme();
                if(rc) return rc;
                Node* sibling = child->next();
                child = dynamic_cast<Control*>(sibling);
        }
        return 0;

}
////////////////////////////////////////////////////////////////////////////////////////
void Container::pack (int x, int y)
{
    Node* node;
    Control* child;
    node = this->first_child();
    orientation theOrient = CurrOrientation;
    if( theOrient == useparent ) theOrient = GetParentOrientation();

    this->x = x;
    this->y = y;
    int ChildTotalWidth = 0;
    int ChildTotalHeight = 0;


    while (NULL != node)
    {
        child = dynamic_cast<Control*>(node);
        if ( NULL != child)
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
    Container* parent = dynamic_cast<Container*>(this->parent());
    if (CurrOrientation == useparent && NULL != parent)
    {
        return parent->GetParentOrientation();
    }
    else if (CurrOrientation == useparent && NULL == parent)
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
    Container* par;


    if ( NULL == parent() )
        return;  /* Clearly this shouldn't happen, though */

    par = dynamic_cast<Container*>(parent());
    if ( NULL == par )
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
    Node *child;
    Container *childc;
    child = this->first_child();

    while( child != NULL )
    {
        childc=dynamic_cast<Container*>(child);
        if (childc != NULL) childc->align();

        child = child->next();
    }
}

////////////////////////////////////////////////////////////////////////////////////////
int Container::add_control(Node *control )
{
	Control *child;

	child = dynamic_cast<Control*>(control);
	if ( NULL != child)
	{
        Node::add_control(control);
		child->enabled = this->enabled;
        return 0;
	}
    return -1;
}


////////////////////////////////////////////////////////////////////////////////////////
#warning "TODO : implement the DoNotPropagateMask update mechanism?"
int Container::AddEvent (::XEvent* event)
{
        IN("");
        int err;
    #warning "update this using tree list creation"
// purpose : when an event is created, use the opengl selection mechanism to know what object shall handle the event
// then create a list containing all parent (parent can have multiple childrens but only one parent is allowed per child)
// then use this list to propagate the event rather than the following algorithm
        EVTMSG((::XEvent) *event);

    debug::Instance()->EventTypeToString(MODULE_KEY, event->type,__func__);
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
    OUT("%d\n", err);
    return err;
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
    Control* child = FindChildWidget(event->x, event->y);
    if (child)
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
    Control *node;
    IN("");

    pack (x, y);
    // we don't need this since it's allready done into the Control::AddEvent(XEposeEvent)
    // glMatrixMode   ( GL_MODELVIEW );  // Select The Model View Matrix
    // glPushMatrix();
    // glLoadIdentity ( );    // Reset The Model View Matrix

    Control::AddEvent (event);
    node = dynamic_cast<Control*>(first_child());
    while( node )
    {
        node->AddEvent(event);
        node = dynamic_cast<Control*>(node->next());
    }
    // glPopMatrix();
    debug::Instance()->FlushGL();
    OUT("");
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
        IN("");
        if (LASTEvent != type && event->type != type) return EINVAL;   //check if event is correct
        if (DoNotPropagateMask & mask_check) return 0; // check if event is masked

        //now broadcast to all childs
        Control* child = dynamic_cast<Control*>(first_child());
        int rc=0;
        while (child != NULL && rc == 0)
        {
                rc = child->AddEvent(event);
                Node* sibling = child->next();
                child = dynamic_cast<Control*>(sibling);
        }
        //the event is for this widget and not a child
        OUT("%d\n", rc);
        return rc;
}
//
////////////////////////////////////////////////////////////////////////////////////////////
int Container::ForwardEvent(::XEvent* event, int* eventX, int* eventY, int EventType, long mask_check)
{
        IN("");
    if (event->type != EventType) return EINVAL;
    if (DoNotPropagateMask & mask_check) return 0;

    Control* child = FindChildWidget(*eventX, *eventY);
    if (child != NULL)
    {
            int rc = child->AddEvent(event);
            OUT("%d\n", rc);
            return rc;
    }
    //the event is for this widget and not a child
    OUT("%d\n", 0);
    return 0;

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
    Container* cont  = dynamic_cast<Container*>(GetRootNode());
    if ( cont != NULL)
      {
        cont->update_size();
        cont->pack (0, 0);
      }

}

////////////////////////////////////////////////////////////////////////////////////////////
Control* Container::FindChildWidget(int x, int y)
{
    Node* current_node = first_child();
    while (current_node)
      {
        Control* current_control = dynamic_cast<Control*>(current_node);
        if (current_control)
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
