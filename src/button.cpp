/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

  glui_button.cpp - Button control class


  --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher

WWW:    http://sourceforge.net/projects/glui/
Forums: http://sourceforge.net/forum/?group_id=92496

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 *****************************************************************************/
#include <GL/glui/internal_control.h>
#include <GL/glui/button.h>
#include <GL/glui/MasterObject.h>
#include <GL/glui/drawinghelpers.h>
#include <GL/glui/window.h>

using namespace GLUI;
/****************************** Button::Button() **********/
Button::Button( Node *parent, const char *name,
        int id, CB cb ):
    Container(name),
    value(NULL, id, cb)

{
    common_init();
    this->resizeable = AdaptThisToFitChilds;
    parent->add_control( this );
#warning "register on KeyPress, KeyRelease, ButtonPress, ButtonRelease, EnterNotify, LeaveNotify, MotionNotify"
}

int Button::AddEvent (::XEvent event)
{
    EventInterpreter::AddEvent(event);
    ::XEvent EventToForward;
    //ask for redisplay of window
    EventToForward.xexpose.type=Expose;
    EventToForward.xexpose.send_event=true;
    EventToForward.xexpose.x = x_abs;
    EventToForward.xexpose.y = y_abs;
    EventToForward.xexpose.width = this->Width();
    EventToForward.xexpose.height = this->Height();


    if (GetStatus() & EventInterpreter::click )
    {
        value.SetVal(true);
        OwnerWindow->AddEvent(EventToForward);
    }


}

/********************************************** Button::draw() **********/

void   Button::draw()
{
    if (GetStatus() & EventInterpreter::buttonpressed)
    {
        drawinghelpers::draw_lowered_box( 0, 0, CurrentSize.size.w, CurrentSize.size.h );
    }
    else
    {
        drawinghelpers::draw_raised_box( 0, 0, CurrentSize.size.w, CurrentSize.size.h );
    }
    glTranslatef( 0.0, 0.0, 1.1);
}



