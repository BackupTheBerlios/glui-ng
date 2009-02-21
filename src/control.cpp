/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

  control.cpp - top-level Control class


  --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher

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

#include <GL/glui/internal_control.h>
#include <GL/glui/event_handler.h>
#include <GL/glui/drawinghelpers.h>
#include <GL/glui/debug.h>
#include <GL/glui/control.h>
#include <GL/gl.h>
#include <GL/glui/window.h>
using namespace GLUI;


Control*  Control::focussed = NULL;

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
#warning "use ::XResizeRequestEvent instead for the api"
void Control::update_size( void )
{

    if (this->resizeable == PercentOfParent)
    {
        Control* par= dynamic_cast<Control*>(this->parent());
        if (par)
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
/*************************** Drawing Utility routines *********************/





int  Control::add_control( Node *control )
{
    //prevent adding subsequent controls
    return -1;
}

/**************************** Little Utility Routines ********************/

/**** Control::enable() ****************/

void Control::enable()
{
    Control *node;

    enabled = true;
    drawinghelpers::PostRedisplay(this);

#warning "this has nothing todo here, move to container class"
    /*** Now recursively enable all buttons below it ***/
    node = (Control*) first_child();
    while(node)
    {
        node->enable();
        node = (Control*) node->next();
    }
}


/***** Control::disable() ****************/

void Control::disable()
{
    Control *node;

    enabled = false;

    drawinghelpers::PostRedisplay(this);

#warning "this has nothing todo here, move to container class"
    /*** Now recursively disable all buttons below it ***/
    node = (Control*) first_child();
    while(node) {
        node->disable();
        node = (Control*) node->next();
    }
}

int Control::AddEvent(::XExposeEvent *event)
{
    //we have been exposed, redraw ourself
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x + x_off_left, y + y_off_bot, BOTTOM_VIEWPORT + GLUI_CONTROL_MAX_THICKNESS * level());
    draw();
    glPopMatrix();
    debug::Instance()->FlushGL();
}


int Control::AddEvent(::XEvent *event)
{
    switch ( event->type )
    {
        case KeyPress : return  AddEvent((::XKeyEvent*) event);
        case KeyRelease: return  AddEvent((::XKeyEvent*) event);
        case ButtonPress: return  AddEvent((::XButtonEvent*) event);
        case ButtonRelease: return  AddEvent((::XButtonEvent*) event);
        case MotionNotify: return  AddEvent((::XMotionEvent*) event);
        case EnterNotify: return  AddEvent((::XCrossingEvent*) event);
        case LeaveNotify: return  AddEvent((::XCrossingEvent*) event);
        case FocusIn: return  AddEvent((::XFocusChangeEvent*) event);
        case FocusOut: return  AddEvent((::XFocusChangeEvent*) event);
        case KeymapNotify: return  AddEvent((::XKeymapEvent*) event);
        case Expose: return  AddEvent((::XExposeEvent*) event);
        case GraphicsExpose: return  AddEvent((::XGraphicsExposeEvent*) event);
        case NoExpose: return  AddEvent((::XNoExposeEvent*) event);
        case VisibilityNotify: return  AddEvent((::XVisibilityEvent*) event);
        case CreateNotify: return  AddEvent((::XCreateWindowEvent*) event);
        case DestroyNotify: return  AddEvent((::XDestroyWindowEvent*) event);
        case UnmapNotify: return  AddEvent((::XUnmapEvent*) event);
        case MapNotify: return  AddEvent((::XMapEvent*) event);
        case MapRequest: return  AddEvent((::XMapRequestEvent*) event);
        case ReparentNotify: return  AddEvent((::XReparentEvent*) event);
        case ConfigureNotify: return  AddEvent((::XConfigureEvent*) event);
        case ConfigureRequest: return  AddEvent((::XConfigureRequestEvent*) event);
        case GravityNotify: return  AddEvent((::XGravityEvent*) event);
        case ResizeRequest: return  AddEvent((::XResizeRequestEvent*) event);
        case CirculateNotify: return  AddEvent((::XCirculateEvent*) event);
        case CirculateRequest: return  AddEvent((::XCirculateRequestEvent*) event);
        case PropertyNotify: return  AddEvent((::XPropertyEvent*) event);
        case SelectionClear: return  AddEvent((::XSelectionClearEvent*) event);
        case SelectionRequest: return  AddEvent((::XSelectionRequestEvent*) event);
        case SelectionNotify: return  AddEvent((::XSelectionEvent*) event);
        case ColormapNotify: return  AddEvent((::XColormapEvent*) event);
        case ClientMessage: return  AddEvent((::XClientMessageEvent*) event);
        case MappingNotify: return  AddEvent((::XMappingEvent*) event);

    }

}


int Control::AddEvent (::XKeyEvent* event)
{
#warning "TODO : if key is tab or backtab or this control don't support..."
    //... FocusIn through tab then send the event to the next sibling
    //    if there is no sibling return an error, if control is desactivated,
    //    do the same
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
    Control* cont  = dynamic_cast<Control*>(GetRootNode());
    if ( cont != NULL)
    {
        cont->update_size();
        cont->pack (0, 0);
    }
    drawinghelpers::PostRedisplay(this);
}



/***** Control::set_alignment() ******/

void Control::set_alignment(Alignement new_align)
{
    alignment = new_align;

    drawinghelpers::PostRedisplay(this);

}


/********* Control::~Control() **********/

Control::~Control()
{
    if (focussed == this) focussed = NULL;
}

Control::Control(const char* name) : Node(name)
{

    active         = false;
    enabled        = true;
    Min            = Size(0u, 0u);
    CurrentSize    = Min;
    alignment      = LEFT;
    resizeable     = FixedSize;
    handler        = NULL;
    y_off_top      = GLUI_YOFF;
    y_off_bot      = GLUI_YOFF;
    x_off_left     = GLUI_XOFF;
    x_off_right    = GLUI_XOFF;
    x              = 0;
    y              = 0;
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
    Control* cont  = dynamic_cast<Control*>(GetRootNode());
    if ( cont != NULL)
      {
        cont->update_size();
        cont->pack (0, 0);
      }
    return 0;

}
