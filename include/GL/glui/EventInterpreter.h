#ifndef __GLUI_EVENTINTERPRETER_H
#define __GLUI_EVENTINTERPRETER_H

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
#include <GL/glui/event_handler.h>
#include <string>
namespace GLUI
{
        class EventInterpreter : public EventHandler
        {
                public : //types
                        enum eventtype
                        {
                                click = 0x0001,
                                doubleClick = 0x0002,
                                tripleClick = 0x0004,
                                drag        = 0x0008,
                                drop        = 0x0010,
                                keypressed  = 0x0020, //pressed then released key
                                buttonpressed= 0x0080
                        };
                public:
                        EventInterpreter (int eventCount=10);
                        virtual int AddEvent(::XEvent *event, NCRC_AutoPtr<Control> focused);
                        int GetStatus();
                        void SetFlags(int flags);
                        void ClearFlags(int flags);
                        NCRC_AutoPtr<Control> GetFocused();
                private:
                        NCRC_AutoPtr<Control> focused;
                        int status;
                        struct event 
                        {
                                ::XEvent Xevent;
                                event* next;
                        };
                        event* eventQueue;
                protected :
                        std::string EventTypeToString(int flags);

        };
}
#endif //__GLUI_EVENTINTERPRETER_H
