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

#include <GL/glui/internal_control.h>
#include <GL/glui/event_handler.h>
#include <GL/glui/debug.h>
#include <GL/glui/control.h>
#include <GL/gl.h>
#include <GL/glui/window.h>
#include <GL/glui/themes.h>
using namespace GLUI;
#define MODULE_KEY  "GLUI_DEBUG_CONTROL"


NCRC_AutoPtr<EventInterpreter> Control::handler(new EventInterpreter);
int _glui_draw_border_only = 0;


///////////////////////////////////////////////////////////////////////
int Control::Activate()
{
#warning "TODO : use FocusIn or FocusOut events for this feature"
}

///////////////////////////////////////////////////////////////////////
#warning "use ::XConfigureRequestEvent instead for the api"
void Control::pack (int x, int y)
{
    this->x = x;
    this->y = y;
}

////////////////////////////////////////////////////////////////////////
 void Control::PostRedisplay()
{
        NCRC_AutoPtr<Control> par = dynamic_cast<Control*>(parent().getPointee());
        if (par != NULL) par->PostRedisplay();
}


////////////////////////////////////////////////////////////////////////
#warning "use ::XResizeRequestEvent instead for the api"
void Control::update_size( void )
{

    if (this->resizeable == PercentOfParent)
    {
        NCRC_AutoPtr<Control> par= dynamic_cast<Control*>(this->parent().getPointee());
        if (par != NULL)
        {
            this->CurrentSize.size.w = par->Width() * this->CurrentSize.percent.w / 100;
            this->CurrentSize.size.h = par->Height() * this->CurrentSize.percent.h / 100;
            if (Min > CurrentSize)
            {
                CurrentSize = Min;
            }
        }
    }
    else if (this->resizeable == FixedSize ||
            this->resizeable == FillSpace)
    {
        return; //nothing to do since we already have a fixed size
    }
}
/******* Control::set_w() **************/
int Control::set_size( Size sz, Size min)
{
    Size dontchange(0u, 0u);
    if (dontchange != min)
    {
        this->Min = min;
    }
    if (sz > this->Min)
    {
        this->CurrentSize = sz;
    }
    else
    {
        return EINVAL;
    }
#warning "use a bottom to top approach : child shall ask parent to update size only if size did change"
    NCRC_AutoPtr<Control> cont  = dynamic_cast<Control*>(GetRootNode().getPointee());
    if ( cont != NULL)
    {
        cont->update_size();
        cont->pack (0, 0);
    }
    ThemeData->update();
}

///////////////////////////////////////////////////////////////////////////////////////
int Control::UpdateTheme( void )
{
        return Control::SetTheme(GLUI::GetTheme(*this));
}

/*************************** Drawing Utility routines *********************/





int  Control::add_control( NCRC_AutoPtr<Node> control )
{
    //prevent adding subsequent controls
    return -1;
}

/**************************** Little Utility Routines ********************/

/**** Control::enable() ****************/

void Control::enable()
{
    enabled = true;
    ThemeData->update();
}


/***** Control::disable() ****************/

void Control::disable()
{
    enabled = false;
    ThemeData->update();
}

void Control::Focus(::XEvent* event)
{
         handler->AddEvent(event, this);
}

void Control::UnFocus( void )
{
        handler->AddEvent(NULL, NULL);
}
////////////////////////////////////////////////////////////////////////////
int Control::AddEvent(::XExposeEvent *event)
{
    //we have been exposed, redraw ourself
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x + x_off_left, y + y_off_bot, BOTTOM_VIEWPORT + GLUI_CONTROL_MAX_THICKNESS * level());
    if (this->ThemeData != NULL)
    {
            this->ThemeData->draw();
    }
    glPopMatrix();
    debug::Instance()->FlushGL();
}

////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XEvent* event)
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

                default : err = EINVAL; break;
        }
        ROUT(err, "\n");
}

///////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XKeyEvent* event)
{
#warning "TODO : if key is tab or backtab or this control don't support..."
    //... FocusIn through tab then send the event to the next sibling
    //    if there is no sibling return an error, if control is desactivated,
    //    do the same
        Focus((::XEvent*) event);
}
////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XButtonEvent* event)
{
        Focus((::XEvent*) event);
}
/////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XMotionEvent* event)
{
        Focus((::XEvent*) event);
}
////////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XCrossingEvent* event)
{
        Focus((::XEvent*) event);
}

///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XFocusChangeEvent* event)
{ return 0; }

///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XKeymapEvent* event)
{ return 0; }

///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XExposeEvent* event);

///////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XGraphicsExposeEvent* event)
{
        Focus((::XEvent*) event);
}

///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XNoExposeEvent* event)
{ return 0; }

///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XVisibilityEvent* event)
{ return 0; }

///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XCreateWindowEvent* event)
{ return 0; }

///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XDestroyWindowEvent* event)
{ return 0; }

///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XUnmapEvent* event)
{ return 0; }

///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XMapEvent* event)
{ return 0; }

///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XMapRequestEvent* event)
{ return 0; }

//////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XReparentEvent* event)
{
        Focus((::XEvent*) event);
}
//////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XConfigureEvent* event)
{
        Focus((::XEvent*) event);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XGravityEvent* event)
{
        Focus((::XEvent*) event);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XResizeRequestEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XConfigureRequestEvent* event)
{
        Focus((::XEvent*) event);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XCirculateEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XCirculateRequestEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XPropertyEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XSelectionClearEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XSelectionRequestEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XSelectionEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XColormapEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XClientMessageEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XMappingEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////////////////////
int Control::AddEvent (::XErrorEvent* event)
{ return 0; }
///////////////////////////////////////////////////////////////////////////
void Control::set_alignment(Alignement new_align)
{
    alignment = new_align;

    ThemeData->update();
}
///////////////////////////////////////////////////////////////////////////
int Control::SetTheme(NCRC_AutoPtr<theme> data)
{
        if (data != NULL)
        {
                this->ThemeData = data;
                return 0;
        }
        return EINVAL;
}



////////////////////////////////////////////////////////////////////////
Control::~Control()
{
#warning "to fix"
//    if (focussed == this) focussed = NULL;
}

////////////////////////////////////////////////////////////////////////
Control::Control(const char* name) : Node(name)
{
    alignment      = LEFT;
    enabled        = true;
    EventMask      = 0;
    resizeable     = FixedSize;
    Min            = Size(0u, 0u);
    CurrentSize    = Min;
    x              = 0;
    y              = 0;
    y_off_top      = GLUI_YOFF;
    y_off_bot      = GLUI_YOFF;
    x_off_left     = GLUI_XOFF;
    x_off_right    = GLUI_XOFF;
    this->TheDefaultTheme = GLUI::GetTheme(*this);
    SetTheme(new _DefaultTheme);
}

////////////////////////////////////////////////////////////////////////
NCRC_AutoPtr<theme> Control::GetDefaultTheme()
{
        return TheDefaultTheme;
}

////////////////////////////////////////////////////////////////////////
int Control::Width() const
{
    return CurrentSize.size.w + x_off_left + x_off_right;
}
////////////////////////////////////////////////////////////////////////
int Control::Height() const
{
    return CurrentSize.size.h + y_off_top + y_off_bot;
}
////////////////////////////////////////////////////////////////////////
int  Control::YOffTop() const {return y_off_top;}
////////////////////////////////////////////////////////////////////////
int  Control::YOffBot() const {return y_off_bot;}
////////////////////////////////////////////////////////////////////////
int  Control::XOffLeft() const {return x_off_left;}
////////////////////////////////////////////////////////////////////////
int  Control::XOffRight() const {return x_off_right;}
////////////////////////////////////////////////////////////////////////
int  Control::X() const {return x;}
////////////////////////////////////////////////////////////////////////
int  Control::Y() const {return y;}
////////////////////////////////////////////////////////////////////////
int Control::SetMargins(int top, int bottom, int left, int right)
{
    y_off_top = top;
    y_off_bot = bottom;
    x_off_left = left;
    x_off_right = right;
    NCRC_AutoPtr<Control> cont  = dynamic_cast<Control*>(GetRootNode().getPointee());
    if ( cont != NULL)
      {
        cont->update_size();
        cont->pack (0, 0);
      }
    return 0;

}

