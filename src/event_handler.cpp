/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

  glui_event_handling.cpp

  --------------------------------------------------

  Copyright (c) 2008 MALET Jean-Luc

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

#include <GL/glui/event_handler.h>
using namespace GLUI;


EventInterpreter::EventInterpreter (int eventCount)
{
    event *firstevent;
    event *lastevent;
    eventQueue = NULL;
#warning "todo : assert on eventCount<0"
    for (int i = 0; i < eventCount; i++)
    {
        lastevent = eventQueue;
        eventQueue = new event;
        eventQueue->Xevent.type=0;
        if (i == 0)
            firstevent = eventQueue;	//save first event of the loop
        eventQueue->next = lastevent;

    }
    firstevent->next = eventQueue;
}


int EventInterpreter::AddEvent(::XEvent *event)
{
#warning "TODO NOW! create test first!"
/*    eventQueue = eventQueue->next;
    eventQueue->Xevent = event;
    switch (event->type)
    {
        case KeyPress:
        case KeyRelease :
        case ButtonPress :
        case ButtonRelease :
        case MotionNotify :
        case EnterNotify :
        case LeaveNotify :
        case FocusIn :
        case FocusOut :
        case KeymapNotify :
        case Expose :
        case GraphicsExpose :
        case NoExpose :
        case VisibilityNotify :
        case CreateNotify :
        case DestroyNotify :
        case UnmapNotify :
        case MapNotify :
        case MapRequest :
        case ReparentNotify :
        case ConfigureNotify :
        case ConfigureRequest :
        case GravityNotify :
        case ResizeRequest :
        case CirculateNotify :
        case CirculateRequest :
        case PropertyNotify :
        case SelectionClear :
        case SelectionRequest :
        case SelectionNotify :
        case ColormapNotify :
        case ClientMessage :
        case MappingNotify :
        default: ;
    }
    */
}

int  EventInterpreter::GetStatus()
{
    return status;
}

#warning "move this to GLUI::Controls"
/*
   void EventHandler::keyboard (::XKeyEvent event)
   {
   GLUI_Control *new_control;

   if (event.type == KeyPress &&	//on keypress only, don't mind about release
   (event.state & ~ShiftMask) == 0 &&	//just shift modifier
   event.keycode == '\t')	//and it's a tab
   {



   if (curr_modifiers & GLUT_ACTIVE_SHIFT)
   {
   new_control = find_prev_control (active_control);
   }
   else
   {
   new_control = find_next_control (active_control);
   }

   if (new_control)
   {
   GLUI_debug::Instance ()->print (__FILE__, __LINE__, "new_control: %s\n", new_control->NodeName);
   }

   deactivate_current_control ();
   activate_control (new_control, GLUI_ACTIVATE_TAB);
   }
   else if (key == ' ' AND active_control AND active_control->spacebar_mouse_click)
   {
// If the user presses the spacebar, and a non-edittext control
//  is active, we send it a mouse down event followed by a mouse up
//  event (simulated mouse-click)

mouse (0, GLUT_DOWN, x, y);
mouse (0, GLUT_UP, x, y);
}
else
{
// Pass the keystroke onto the active control, if any
if (active_control != NULL)
active_control->key_handler (key, curr_modifiers);
}
}



#warning "use opengl selection function to distribute events"
#warning "this imply that each widget has to pass back event to parent"
#warning "if required"
#warning "make an event interpreter class"
void mouse (int button, int state, int x, int y)
{
int callthrough;
GLUI_Control *control;

GLUI_debug::Instance ()->print (__FILE__, __LINE__, "MOUSE: %d %d\n", button, state);

callthrough = true;

curr_modifiers = glutGetModifiers ();

if (button == GLUT_LEFT)
{
    control = find_control (x, y);

    if (control)
    {
        GLUI_debug::Instance ()->print (__FILE__, __LINE__, "control: %s\n", control->NodeName);
    }

    if (mouse_button_down AND active_control != NULL AND state == GLUT_UP)
    {
        // We just released the mouse, which was depressed at some control

        callthrough = active_control->mouse_up_handler (x, y, control == active_control);
        glutSetCursor (GLUT_CURSOR_LEFT_ARROW);

        if (active_control AND active_control->active_type == GLUI_CONTROL_ACTIVE_MOUSEDOWN AND 0)
        {
            // This is a control that needs to be deactivated when the
            mouse button is released
                deactivate_current_control ();
        }
    }
    else
    {
        if (control)
        {
            if (NOT mouse_button_down AND state == GLUT_DOWN)
            {
                // We just pressed the mouse down at some control

                if (active_control != control)
                {
                    if (active_control != NULL)
                    {
                        // There is an active control still - deactivate it
                        deactivate_current_control ();
                    }
                }

                if (control->enabled)
                {
                    activate_control (control, GLUI_ACTIVATE_MOUSE);
                    callthrough = control->mouse_down_handler (x, y);
                }
            }
        }
    }

    if (state == GLUT_DOWN)
        mouse_button_down = true;
    else if (state == GLUT_UP)
        mouse_button_down = false;
}

//
//  NO CALLTHROUGH NEEDED FOR MOUSE EVENTS
//  if ( callthrough AND glut_mouse_CB )
//  glut_mouse_CB( button, state, x, y );
//

callthrough = callthrough;	// To get rid of compiler warnings
}


void motion (int x, int y)
{
    int callthrough;
    GLUI_Control *control;

    GLUI_debug::Instance ()->print (__FILE__, __LINE__, "MOTION: %d %d\n", x, y);

    callthrough = true;

    control = find_control (x, y);

    if (mouse_button_down AND active_control != NULL)
    {
        callthrough = active_control->mouse_held_down_handler (x, y, control == active_control);
    }

    //
    //  NO CALLTHROUGH NEEDED FOR MOUSE EVENTS
    //
    //  if ( callthrough AND glut_motion_CB )
    //  glut_motion_CB(x,y);
    //

    callthrough = callthrough;	// To get rid of compiler warnings
}


void passive_motion (int x, int y)
{
    GLUI_Control *control;

    control = find_control (x, y);

    GLUI_debug::Instance ()->print (__FILE__, __LINE__, "%p %p\n", control, mouse_over_control);

    if (control != mouse_over_control)
    {
        if (mouse_over_control)
        {
            mouse_over_control->mouse_over (false, x, y);
        }

        if (control)
        {
            control->mouse_over (true, x, y);
            mouse_over_control = control;
        }
    }

    //
    //   if ( curr_cursor != GLUT_CURSOR_INHERIT ) {
    //   curr_cursor = GLUT_CURSOR_INHERIT;
    //   glutSetCursor( GLUT_CURSOR_INHERIT );
    //   }

}
*/

