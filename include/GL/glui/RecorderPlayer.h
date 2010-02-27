#ifndef __GLUI_RECORDERPLAYER_H
#define __GLUI_RECORDERPLAYER_H
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
#include <iostream>
#include <fstream>
#include <X11/Xlib.h>
#include <time.h>
#include <stdint.h>

namespace GLUI
{
        class EventFile
        {
                public :
                        EventFile(const char* file, std::ios_base::openmode mode);
                protected : //variables
                        std::filebuf fb;
                private:
                        EventFile();
        };

        class EventRecorder :public EventFile
        {
                public :
                        EventRecorder(const char* file);
                        void add(::XEvent& evt);
                protected : //variables
                        std::ostream os;
                private:
                        EventRecorder();
        };

        std::istream& operator>> (std::istream& str, const char* format);

        class EventPlayer : public EventFile
        {
                public :
                        EventPlayer(const char* file);
                        void next(::XEvent& evt);
                protected : //variables
                        std::istream os;
                        struct timespec PreviousTime;
                        uint64_t PreviousEventTime;
                protected : //methods
                        int StringToEventType(const std::string type);
                        bool StringToBool(const std::string boolean );
                        char StringToEventNotifyHint(const std::string is_hint );
                        int StringToEventNotifyMode(const std::string mode );
                        int StringToEventNotifyDetail(const std::string detail );
                        int StringToEventVisibility(const std::string state );
                        int StringToEventConfigureDetail(const std::string detail );
                        int StringToEventPlace(const std::string place );
                        int StringToEventMappingRequest(const std::string request );
                        int StringToEventPropertyState(const std::string state );
                        int StringToEventColormapState(const std::string state );
                        uint64_t TimespecToXms(struct timespec& ts);

                private:
                        EventPlayer();
        };


}

#endif //__GLUI_RECORDERPLAYER_H

