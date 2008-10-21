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
    this->x_abs = x;
    this->y_abs = y;
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
    ::XEvent EventToForward;
    EventToForward.xexpose.type=Expose;
    EventToForward.xexpose.send_event=true;
    EventToForward.xexpose.x = x_abs;
    EventToForward.xexpose.y = y_abs;
    EventToForward.xexpose.width = this->Width();
    EventToForward.xexpose.height = this->Height();
    Container* cont  = dynamic_cast<Container*>(GetRootNode());
    if ( cont != NULL)
    {
        cont->AddEvent(&EventToForward);
    }

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

    //ask for redisplay of window
    ::XEvent EventToForward;
    EventToForward.xexpose.type=Expose;
    EventToForward.xexpose.send_event=true;
    EventToForward.xexpose.x = x_abs;
    EventToForward.xexpose.y = y_abs;
    EventToForward.xexpose.width = this->Width();
    EventToForward.xexpose.height = this->Height();
    Container* cont  = dynamic_cast<Container*>(GetRootNode());
    if ( cont != NULL)
    {
        cont->AddEvent(&EventToForward);
    }


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
    draw();
    glPopMatrix();
    debug::Instance()->FlushGL();
}


int Control::AddEvent(::XEvent *event)
{
    if (event->xany.type == Expose)
    {
        return AddEvent((::XExposeEvent*) event);
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
    Size dontchange(0, 0);
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
    update_size();
    ::XEvent EventToForward;
    EventToForward.xexpose.type=Expose;
    EventToForward.xexpose.send_event=true;
    EventToForward.xexpose.x = x_abs;
    EventToForward.xexpose.y = y_abs;
    EventToForward.xexpose.width = this->Width();
    EventToForward.xexpose.height = this->Height();
    Container* cont  = dynamic_cast<Container*>(GetRootNode());
    if ( cont != NULL)
    {
        cont->AddEvent(&EventToForward);
    }
}



/***** Control::set_alignment() ******/

void Control::set_alignment(Alignement new_align)
{
    alignment = new_align;

    ::XEvent EventToForward;
    EventToForward.xexpose.type=Expose;
    EventToForward.xexpose.send_event=true;
    EventToForward.xexpose.x = x_abs;
    EventToForward.xexpose.y = y_abs;
    EventToForward.xexpose.width = this->Width();
    EventToForward.xexpose.height = this->Height();
    Container* cont  = dynamic_cast<Container*>(GetRootNode());
    if ( cont != NULL)
    {
        cont->AddEvent(&EventToForward);
    }
}


/********* Control::~Control() **********/

Control::~Control()
{
    if (focussed == this) focussed = NULL;
}

Control::Control(const char* name) : Node(name)
{

    x_abs          = GLUI_XOFF;
    y_abs          = GLUI_YOFF;
    active         = false;
    enabled        = true;
    Min            = Size(0, 0);
    CurrentSize    = Min;
    alignment      = LEFT;
    resizeable     = FixedSize;
    handler        = NULL;
}
