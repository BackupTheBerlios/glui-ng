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
using namespace GLUI;

class Drag : public Control
{
        public :
                Drag() : Control("drag") {};
};

class Drop : public Control
{
        public :
                Drop() : Control("drop") {};
};

int main(int argc, char** argv)
{
        NCRC_AutoPtr<EventInterpreter> interpreter(new EventInterpreter);
        NCRC_AutoPtr<Control> drag(new Drag());
        NCRC_AutoPtr<Control> drop(new Drop());
        ::XEvent evt;

        if (interpreter->GetStatus() != 0)
        {
                GLUI_THROW(-1,"bad initialised state : " << interpreter->GetStatus());
        }

        //pressed test
        evt.type = ButtonPress;
        interpreter->AddEvent(&evt, drag);
        if ((interpreter->GetStatus() & EventInterpreter::buttonpressed) == 0)
        {
                GLUI_THROW(-1,"not in buttonpressed state");
        }
        if (interpreter->GetFocused() != drag)
        {
                GLUI_THROW(-1,"not Containing the right focused Control");
        }
        evt.type = MotionNotify;
        evt.xmotion.state = Button1Mask;
        interpreter->AddEvent(&evt, drag);
        if ((interpreter->GetStatus() & EventInterpreter::buttonpressed) == 0)
        {
                GLUI_THROW(-1,"not in buttonpressed state");
        }
        if ((interpreter->GetStatus() & EventInterpreter::drag) == 0)
        {
                GLUI_THROW(-1,"not in drag state");
        }
        if (interpreter->GetFocused() != drag)
        {
                GLUI_THROW(-1,"not Containing the right focused Control");
        }
        interpreter->AddEvent(&evt, drop);
        if ((interpreter->GetStatus() & EventInterpreter::buttonpressed) == 0)
        {
                GLUI_THROW(-1,"not in buttonpressed state");
        }
        if (interpreter->GetFocused() != drag)
        {
                GLUI_THROW(-1,"not Containing the right focused Control");
        }
#warning "add a test with a full featured DnD"

        //click test
        evt.type = ButtonRelease;
        interpreter->AddEvent(&evt, drag);
        if ((interpreter->GetStatus() & EventInterpreter::click) == 0)
        {
                GLUI_THROW(-1,"not in click state");
        }
        if (interpreter->GetFocused() != drag)
        {
                GLUI_THROW(-1,"not Containing the right focused Control");
        }
        //drag and drop test
        //double click test (previous state is a click and 
        //we got again a click in a short amount of time
        //triple click test (previous state is a doubleclick and 
        //we got again a click in a short amount of time
        return 0;
}



