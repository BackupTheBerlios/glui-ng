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
#include <GL/gl.h>
using namespace std;
#include <algorithm>
using namespace GLUI;

///////////////////////////////////////////////////////////////////////////////////////
Container::Container(const char *name ,
                   orientation orient):
    Control(name)

{
    CurrOrientation = orient;

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
inline void Container::check_size_constency( void )
{
    Node* node;
    Control* child;
    int width(0);
    int height(0);

    node = this->first_child();
    while (NULL != node)
    {
        child = dynamic_cast<Control*>(node);
        if (NULL != child)
        {
          if (CurrOrientation == horizontal )
                {
                    width += child->Width() ;
                    height = max<int> (this->Height(), child->Height());
                }
                else
                {
                    width = max<int> (this->Width(), child->Width());
                    height += child->Height();
                }
        }
        node = node->next();
    }
    if (width > this->CurrentSize.size.w) this->CurrentSize.size.w = width;
    if(height > this->CurrentSize.size.h) this->CurrentSize.size.h = height;



}


///////////////////////////////////////////////////////////////////////////////////////
#warning "split this in inline functions"
void Container::update_size( void )
{
    Node* node;
    Control* child;
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

                if (CurrOrientation == horizontal )
                {
                    width += child->Width();
                    height = max<int> (height, child->Height());
                }
                else
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

            if (CurrOrientation == horizontal )
            {
                newsize.size.w = (this->CurrentSize.size.w - width) / FillSpaceCount;
                newsize.size.h = this->CurrentSize.size.h;
            }
            else
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

                if (CurrOrientation == horizontal )
                {
                    width += child->Width();
                    height = max<int> (height, child->Height() );
                }
                else
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
    check_size_constency();
}

////////////////////////////////////////////////////////////////////////////////////////
void Container::pack (int x, int y)
{
    Node* node;
    Control* child;
    node = this->first_child();

    this->x = x;
    this->y = y;

    int x_offset = 0;
    int y_offset = 0;

    while (NULL != node)
    {
        child = dynamic_cast<Control*>(node);
        if ( NULL != child)
        {
            child->pack(x_offset, y_offset);
            if (CurrOrientation == horizontal )
            {
                x_offset += child->Width();
            }
            else
            {
               y_offset += child->Height();
            }
        }
        node = node->next();
    }


}




///////////////////////////////////////////////////////////////////////////////////////
#warning "remove alignement code and create spacer control instead"
void Container::align()
{
    int  orig_x_abs;
    int  orig_y_abs;
    Container* par;

    GetAbsPosition( &orig_x_abs, &orig_y_abs);

    /* Fix alignment bug relating to columns              */
    /*return;              */

    if ( NULL == parent() )
        return;  /* Clearly this shouldn't happen, though */

    par = dynamic_cast<Container*>(parent());
    if ( NULL == par )
        return;

    if ( alignment == Control::LEFT ) {
        x = 0 ;
    }
    else if ( alignment == Control::RIGHT ) {
        x = par->Width() - this->CurrentSize.size.w;
    }
    else if ( alignment == Control::CENTER ) {
        x = (par->Width() - this->CurrentSize.size.w) / 2;
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
#warning "TODO : move to control class"
int Container::AddEvent (::XEvent* event)
{
    #warning "update this using tree list creation"
// purpose : when an event is created, use the opengl selection mechanism to know what object shall handle the event
// then create a list containing all parent (parent can have multiple childrens but only one parent is allowed per child)
// then use this list to propagate the event rather than the following algorithm

    switch ( event->type )
    {
        case KeyPress : return AddEvent((::XKeyEvent*) event);
        case KeyRelease: return AddEvent((::XKeyEvent*) event);
        case ButtonPress: return AddEvent((::XButtonEvent*) event);
        case ButtonRelease: return AddEvent((::XButtonEvent*) event);
        case MotionNotify: return AddEvent((::XMotionEvent*) event);
        case EnterNotify: return AddEvent((::XCrossingEvent*) event);
        case LeaveNotify: return AddEvent((::XCrossingEvent*) event);
        case FocusIn: return AddEvent((::XFocusChangeEvent*) event);
        case FocusOut: return AddEvent((::XFocusChangeEvent*) event);
        case KeymapNotify: return AddEvent((::XKeymapEvent*) event);
        case Expose: return AddEvent((::XExposeEvent*) event);
        case GraphicsExpose: return AddEvent((::XGraphicsExposeEvent*) event);
        case NoExpose: return AddEvent((::XNoExposeEvent*) event);
        case VisibilityNotify: return AddEvent((::XVisibilityEvent*) event);
        case CreateNotify: return AddEvent((::XCreateWindowEvent*) event);
        case DestroyNotify: return AddEvent((::XDestroyWindowEvent*) event);
        case UnmapNotify: return AddEvent((::XUnmapEvent*) event);
        case MapNotify: return AddEvent((::XMapEvent*) event);
        case MapRequest: return AddEvent((::XMapRequestEvent*) event);
        case ReparentNotify: return AddEvent((::XReparentEvent*) event);
        case ConfigureNotify: return AddEvent((::XConfigureEvent*) event);
        case ConfigureRequest: return AddEvent((::XConfigureRequestEvent*) event);
        case GravityNotify: return AddEvent((::XGravityEvent*) event);
        case ResizeRequest: return AddEvent((::XResizeRequestEvent*) event);
        case CirculateNotify: return AddEvent((::XCirculateEvent*) event);
        case CirculateRequest: return AddEvent((::XCirculateRequestEvent*) event);
        case PropertyNotify: return AddEvent((::XPropertyEvent*) event);
        case SelectionClear: return AddEvent((::XSelectionClearEvent*) event);
        case SelectionRequest: return AddEvent((::XSelectionRequestEvent*) event);
        case SelectionNotify: return AddEvent((::XSelectionEvent*) event);
        case ColormapNotify: return AddEvent((::XColormapEvent*) event);
        case ClientMessage: return AddEvent((::XClientMessageEvent*) event);
        case MappingNotify: return AddEvent((::XMappingEvent*) event);

        default : return BroadcastEvent(event, LASTEvent, NoEventMask);
    }
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
        event->x = event->x - child->x;
        event->y = event->y - child->y;
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
    debug::Instance()->print( __FILE__, __LINE__, _level,
            "%s %s \n",__func__,
            dynamic_cast<Node*>(this)->whole_tree());

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

    draw();  //we're allready positioned to (0,0,0) of current widget, so just draw

    if (CurrOrientation == horizontal )
    {
        node = dynamic_cast<Control*>(first_child());
        while( node )
        {
            node->AddEvent(event);
            glTranslatef( (float)node->Width(), 0.0, 0.0);
            node = dynamic_cast<Control*>(node->next());
        }
    }
    else
    {
        //we display childs in reverse order to have them stacked top to bottom
        node = dynamic_cast<Control*>(last_child());
        while( node )
        {
            node->AddEvent(event);
            glTranslatef( 0.0, (float) node->Height(), 0.0);
            node = dynamic_cast<Control*>(node->prev());
        }
    }
    glPopMatrix();
    debug::Instance()->FlushGL();
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
    if (LASTEvent != type && event->type != type) return EINVAL;   //check if event is correct
    if (DoNotPropagateMask & mask_check) return 0; // check if event is masked

    //now broadcast to all childs
    Control* child = dynamic_cast<Control*>(first_child());
    int rc=0;
    while (child != NULL && rc == 0)
    {
        rc = child->AddEvent(event);
        Control* child = dynamic_cast<Control*>(child->next());
    }
    //the event is for this widget and not a child
    return rc;
}
////////////////////////////////////////////////////////////////////////////////////////////
//
int Container::ForwardEvent(::XEvent* event, int* eventX, int* eventY, int EventType, long mask_check)
{
    if (event->type != EventType) return EINVAL;
    if (DoNotPropagateMask & mask_check) return 0;

    Control* child = FindChildWidget(*eventX, *eventY);
    if (child != NULL)
    {
        eventX = eventX - child->x;
        eventY = eventY - child->y;
        return child->AddEvent(event);
    }
    //the event is for this widget and not a child
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
