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

#include <GL/glui/EventInterpreter.h>
#include <GL/glui/control.h>
#include <GL/glui/debug.h>

using namespace GLUI;
#define MODULE_KEY  "GLUI_DEBUG_EVENTINTERPRETER"


EventInterpreter::EventInterpreter (int eventCount)
{
        IN("eventCount " << eventCount << "\n");
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
        this->status = 0;
        OUT("\n");
}

NCRC_AutoPtr<Control> EventInterpreter::GetFocused()
{
        return focused;
}

void EventInterpreter::SetFlags(int flags)
{
        IN("setting " << EventTypeToString(flags) << "\n");
        status |= flags;
        MSG("current status : " << EventTypeToString(status) << "\n");
        OUT("\n");
}

void EventInterpreter::ClearFlags(int flags)
{
        IN("clearing " << EventTypeToString(flags) << "\n");
        status &= ~flags;
        MSG("current status : " << EventTypeToString(status) << "\n");
        OUT("\n");
}


int EventInterpreter::AddEvent(::XEvent *event, NCRC_AutoPtr<Control> focused)
{
        IN("event :" << debug::Instance()->EventTypeToString(event->type) << " Node :" << focused->Name() << "\n");
        if (event == NULL || focused == NULL)
        {
                status = 0;
                focused = NULL;
                return 0;
        }
        //eventQueue = eventQueue->next;
        //eventQueue->Xevent = event;
        switch (event->type)
        {
                case KeyPress:
                        break;
                case KeyRelease :
                        break;
                case ButtonPress :
                        SetFlags(buttonpressed);
                        this->focused = focused;
                        break;
                case ButtonRelease :
                        if (this->focused != focused && 
                                        ( this->status & drag)
                           )
                        {
                                ClearFlags(drag);
                                SetFlags(drop);
                        }
                        if (this->focused == focused)
                        {
                                ClearFlags(drag|drop);
                                SetFlags(click);
                        }
                        ClearFlags(buttonpressed);
                        this->focused = focused;
                        break;
                case MotionNotify :
                        if (event->xmotion.state & (Button1Mask |
                                                Button2Mask |
                                                Button3Mask |
                                                Button4Mask |
                                                Button5Mask)
                           )
                        {
                                SetFlags(buttonpressed);
                        }
                        else
                        {
                                ClearFlags(buttonpressed|drag|drop);
                        }
                        if (this->status & buttonpressed)
                        {
                                SetFlags(drag);
                        }
                        break;
                case EnterNotify :
                        break;
                case LeaveNotify :
                        break;
                case FocusIn :
                        break;
                case FocusOut :
                        break;
                case KeymapNotify :
                        break;
                case Expose :
                        break;
                case GraphicsExpose :
                        break;
                case NoExpose :
                        break;
                case VisibilityNotify :
                        break;
                case CreateNotify :
                        break;
                case DestroyNotify :
                        break;
                case UnmapNotify :
                        break;
                case MapNotify :
                        break;
                case MapRequest :
                        break;
                case ReparentNotify :
                        break;
                case ConfigureNotify :
                        break;
                case ConfigureRequest :
                        break;
                case GravityNotify :
                        break;
                case ResizeRequest :
                        break;
                case CirculateNotify :
                        break;
                case CirculateRequest :
                        break;
                case PropertyNotify :
                        break;
                case SelectionClear :
                        break;
                case SelectionRequest :
                        break;
                case SelectionNotify :
                        break;
                case ColormapNotify :
                        break;
                case ClientMessage :
                        break;
                case MappingNotify :
                        break;
                default: ;
        }
        OUT("\n");
}

int  EventInterpreter::GetStatus()
{
        IN("\n");
        ROUT(status,hex << status << "\n");
}

std::string EventInterpreter::EventTypeToString(int flags)
{
        ostringstream str;

        if (flags & click ) str << "click,";
        if (flags & doubleClick ) str << "doubleClick,";
        if (flags & tripleClick ) str << "tripleClick,";
        if (flags & drag ) str << "drag,";
        if (flags & keypressed ) str << "keypressed,";
        if (flags & buttonpressed ) str << "buttonpressed,";
        str.flush();
        return str.str();
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

#warning "detect auto repeat"
/*
   if (event.type==KeyRelease)
   {
//
// Look at X11 keystate to detect repeat mode.
// While X11 says the key is actually held down, we'll ignore KeyRelease/KeyPress pairs.
//

char keys[32];
XQueryKeymap( fgDisplay.Display, keys ); // Look at X11 keystate to detect repeat mode 

if ( event.xkey.keycode<256 )            // XQueryKeymap is limited to 256 keycodes    
{
if ( keys[event.xkey.keycode>>3] & (1<<(event.xkey.keycode%8)) )
window->State.KeyRepeating = GL_TRUE;
else
window->State.KeyRepeating = GL_FALSE;
}
}
*/
