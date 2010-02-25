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
#include <GL/glui/RecorderPlayer.h>
#include <GL/glui/debug.h>
#include <GL/glui/Exception.h>
using namespace GLUI;


EventFile::EventFile(const char* file, std::ios_base::openmode mode)
{
        if (file != NULL)
        {
                if ( NULL == fb.open (file, mode))
                {
                        GLUI_THROW(EIO,"can't open file");
                }
        }
}


EventRecorder::EventRecorder(const char* file)
        : EventFile(file, std::ios::out)
          , os(&fb)
{
}

void EventRecorder::add(::XEvent& evt)
{
        debug::Instance()->DumpEvent(evt, os);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////   EVENT PLAYER //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
std::istream& GLUI::operator>> (std::istream& str, const char* format)
{
        std::string form(format);
        char* buff = new char[form.length()+1];
        str.read(buff, form.length());
        buff[form.length()] = '\0';
        if (form != buff)
        {
                std::string errmsg="strings aren't identical : ";
                errmsg += buff;
                delete[] buff;
                GLUI_THROW(EINVAL,errmsg);
        }
        delete[] buff;
        return str;
}


EventPlayer::EventPlayer(const char* file)
        : EventFile(file, std::ios::in)
          , os(&fb)

{
        PreviousEventTime = 0;
        PreviousTime.tv_sec = 0;
        PreviousTime.tv_nsec = 0;
}

int EventPlayer::StringToEventType(const std::string type)
{
        if(type == "KeyPress:") return KeyPress;
        if(type == "KeyRelease:") return KeyRelease;
        if(type == "ButtonPress:") return ButtonPress;
        if(type == "ButtonRelease:") return ButtonRelease;
        if(type == "MotionNotify:") return MotionNotify;
        if(type == "EnterNotify:") return EnterNotify;
        if(type == "LeaveNotify:") return LeaveNotify;
        if(type == "FocusIn:") return FocusIn;
        if(type == "FocusOut:") return FocusOut;
        if(type == "KeymapNotify:") return KeymapNotify;
        if(type == "Expose:") return Expose;
        if(type == "GraphicsExpose:") return GraphicsExpose;
        if(type == "NoExpose:") return NoExpose;
        if(type == "VisibilityNotify:") return VisibilityNotify;
        if(type == "CreateNotify:") return CreateNotify;
        if(type == "DestroyNotify:") return DestroyNotify;
        if(type == "UnmapNotify:") return UnmapNotify;
        if(type == "MapNotify:") return MapNotify;
        if(type == "MapRequest:") return MapRequest;
        if(type == "ReparentNotify:") return ReparentNotify;
        if(type == "ConfigureNotify:") return ConfigureNotify;
        if(type == "ConfigureRequest:") return ConfigureRequest;
        if(type == "GravityNotify:") return GravityNotify;
        if(type == "ResizeRequest:") return ResizeRequest;
        if(type == "CirculateNotify:") return CirculateNotify;
        if(type == "CirculateRequest:") return CirculateRequest;
        if(type == "PropertyNotify:") return PropertyNotify;
        if(type == "SelectionClear:") return SelectionClear;
        if(type == "SelectionRequest:") return SelectionRequest;
        if(type == "SelectionNotify:") return SelectionNotify;
        if(type == "ColormapNotify:") return ColormapNotify;
        if(type == "ClientMessage:") return ClientMessage;
        if(type == "MappingNotify:") return MappingNotify;
        std::string errmsg="reading an unknow event.... event file might be corruped ";
        errmsg += type;
        GLUI_THROW(EINVAL,errmsg);
}

bool EventPlayer::StringToBool(const std::string boolean )
{
        if (boolean == "False") return false;
        if (boolean == "True" ) return true;
        std::string errmsg="unknown boolean string ";
        errmsg += boolean;
        GLUI_THROW(EINVAL,errmsg);
}

char EventPlayer::StringToEventNotifyHint(const std::string is_hint )
{
        if (is_hint == "NotifyNormal") return NotifyNormal;
        if (is_hint == "NotifyHint") return NotifyHint;
        std::string errmsg="unknown NotifyHint string ";
        errmsg += is_hint;
        GLUI_THROW(EINVAL,errmsg);
}

int EventPlayer::StringToEventNotifyMode(const std::string mode )
{
        if (mode == "NotifyNormal") return NotifyNormal;
        if (mode == "NotifyGrab") return NotifyGrab;
        if (mode == "NotifyUngrab") return NotifyUngrab;
        if (mode == "NotifyWhileGrabbed") return NotifyWhileGrabbed;
        std::string errmsg="unknown NotifyMode string ";
        errmsg += mode;
        GLUI_THROW(EINVAL,errmsg);
}

int EventPlayer::StringToEventNotifyDetail(const std::string detail )
{
        if (detail == "NotifyAncestor") return NotifyAncestor;
        if (detail == "NotifyVirtual") return NotifyVirtual;
        if (detail == "NotifyInferior") return NotifyInferior;
        if (detail == "NotifyNonlinear") return NotifyNonlinear;
        if (detail == "NotifyNonlinearVirtual") return NotifyNonlinearVirtual;
        if (detail == "NotifyPointer") return NotifyPointer;
        if (detail == "NotifyPointerRoot") return NotifyPointerRoot;
        if (detail == "NotifyDetailNone") return NotifyDetailNone;
        std::string errmsg="unknown NotifyDetail string ";
        errmsg += detail;
        GLUI_THROW(EINVAL,errmsg);
}

int EventPlayer::StringToEventVisibility(const std::string state ) 
{
        if (state == "VisibilityUnobscured") return VisibilityUnobscured;
        if (state == "VisibilityPartiallyObscured") return VisibilityPartiallyObscured;
        if (state == "VisibilityFullyObscured") return VisibilityFullyObscured;
        std::string errmsg="unknown Visibility string ";
        errmsg += state;
        GLUI_THROW(EINVAL,errmsg);
}

int EventPlayer::StringToEventConfigureDetail(const std::string detail )
{
        if (detail == "Above") return Above;
        if (detail == "Below") return Below;
        if (detail == "TopIf") return TopIf;
        if (detail == "BottomIf") return BottomIf;
        if (detail == "Opposite") return Opposite;
        std::string errmsg="unknown ConfigureDetail string ";
        errmsg += detail;
        GLUI_THROW(EINVAL,errmsg);
}

int EventPlayer::StringToEventPlace(const std::string place )
{
        if (place == "PlaceOnTop") return PlaceOnTop;
        if (place == "PlaceOnBottom") return PlaceOnBottom;
        std::string errmsg="unknown EventPlace string ";
        errmsg += place;
        GLUI_THROW(EINVAL,errmsg);
}

int EventPlayer::StringToEventMappingRequest(const std::string request )
{
        if (request == "MappingModifier") return MappingModifier;
        if (request == "MappingKeyboard") return MappingKeyboard;
        if (request == "MappingPointer") return MappingPointer;
        std::string errmsg="unknown MappingRequest string ";
        errmsg += request;
        GLUI_THROW(EINVAL,errmsg);
}

int EventPlayer::StringToEventPropertyState(const std::string state )
{
        if (state == "PropertyNewValue") return PropertyNewValue;
        if (state == "PropertyDelete") return PropertyDelete;
        std::string errmsg="unknown PropertyState string ";
        errmsg += state;
        GLUI_THROW(EINVAL,errmsg);
}

int EventPlayer::StringToEventColormapState(const std::string state )
{
        if (state == "ColormapUninstalled") return ColormapUninstalled;
        if (state == "ColormapInstalled") return ColormapInstalled;
        std::string errmsg="unknown ColormapState string ";
        errmsg += state;
        GLUI_THROW(EINVAL,errmsg);
}

uint64_t EventPlayer::TimespecToXms(struct timespec& ts)
{
        return ((ts.tv_sec * 1000) + (ts.tv_nsec / 1000000));
}


void EventPlayer::next(::XEvent& event)
{
        std::string buff;
        uint64_t current_event_time = 0;

        os >> buff;
        event.type = StringToEventType(buff);
        if( event.type == KeyPress || event.type == KeyRelease )
        {
                std::string SameScreen;
                ::XKeyEvent &e = (::XKeyEvent&)event;
                os      >> " window=0x" >> hex >> e.window >> dec >> " root=0x" >> hex
                        >> e.root >> dec >> " subwindow=0x" >> hex
                        >> e.subwindow >> dec >> " time=" 
                        >> e.time >> " (x,y)=("
                        >> e.x >> "," >> e.y >> ") (x_root,y_root)=("
                        >> e.x_root >>",">> e.y_root >> ") state=0x" >> hex 
                        >> e.state >> dec >> " keycode=" >> e.keycode
                        >> " same_screen=" >> SameScreen;
                e.same_screen = StringToBool(SameScreen);
                current_event_time = e.time;
        }
        else if( event.type == ButtonPress || event.type == ButtonRelease )
        {
                std::string SameScreen;
                ::XButtonEvent &e = (::XButtonEvent&)event;
                os >> " window=0x" >> hex >> e.window >> dec >> " root=0x" >> hex
                        >> e.root >> dec >> " subwindow=0x" >> hex >> e.subwindow >> dec >> " time="
                        >> e.time >> " (x,y)=(" >> e.x 
                        >> "," >> e.y >> ") (x_root,y_root)=(" 
                        >> e.x_root >> "," >> e.y_root >> ") state=0x" >> hex >> e.state
                        >> dec >> " button=" >> e.button >> " same_screen=" >> 
                        SameScreen;
                e.same_screen = StringToBool(SameScreen);
                current_event_time = e.time;
        }
        else if ( event.type == MotionNotify )
        {
                std::string is_hint;
                std::string same_screen;
                ::XMotionEvent &e = (::XMotionEvent&)event;
                os      >> " window=0x" >> hex >> e.window 
                        >> dec >> " root=0x" >> hex >> e.root 
                        >> dec >> " subwindow=0x" >> hex >> e.subwindow 
                        >> dec >> " time=" >> e.time 
                        >> " (x,y)=(" >> e.x >> "," >> e.y 
                        >> ") (x_root,y_root)=(" >> e.x_root >> "," >> e.y_root 
                        >> ") state=0x" >> hex >> e.state 
                        >> dec >> " is_hint=" >> is_hint
                        >> " same_screen=" >> same_screen;
                e.same_screen = StringToBool(same_screen);
                e.is_hint = StringToEventNotifyHint(is_hint);
                current_event_time = e.time;
        }
        else if ( event.type == EnterNotify || event.type == LeaveNotify)
        {
                std::string SameScreen;
                std::string NotifyMode;
                std::string NotifyDetail;
                ::XCrossingEvent &e = (::XCrossingEvent&)event;
                os >> " window=0x" >> hex >> e.window 
                        >> dec >> " root=0x" >> hex >> e.root >> dec >> " subwindow=0x" >> hex 
                        >> e.subwindow >> dec >> " time=" >> e.time 
                        >> " (x,y)=(" >> e.x >> "," >> e.y 
                        >> ") mode=" >> NotifyMode
                        >> " detail=" >> NotifyDetail
                        >> " same_screen=" >> SameScreen >> " focus=" 
                        >> e.focus >> " state=0x" >> hex >> e.state;
                e.same_screen = StringToBool(SameScreen);
                e.mode = StringToEventNotifyMode(NotifyMode);
                e.detail = StringToEventNotifyDetail(NotifyDetail);
                current_event_time = e.time;
        }
        else if (event.type == FocusIn || event.type == FocusOut)
        {
                std::string NotifyMode;
                std::string NotifyDetail;
                ::XFocusChangeEvent &e = (::XFocusChangeEvent&)event;
                os >> " window=0x" >> hex
                        >> e.window >> dec >> " mode="
                        >> NotifyMode >> " detail="
                        >> NotifyDetail;
                e.mode = StringToEventNotifyMode(NotifyMode);
                e.detail = StringToEventNotifyDetail(NotifyDetail);
        }
        else if (event.type == KeymapNotify)
        {
                ::XKeymapEvent &e = (::XKeymapEvent&)event;
                os >> " window=0x" >> hex >> e.window;
                for (int i = 0; i < 32; i++)
                {
                        int vect = e.key_vector[i];
                        os >> vect;
                }
        }
        else if (event.type == Expose)
        {
                ::XExposeEvent &e = (::XExposeEvent&)event;
                os >> " window=0x" >> hex 
                        >>  e.window >> dec >> " (x,y)=(" >>  e.x >> "," >> e.y 
                        >> ") (width,height)=("
                        >> e.width >> "," >> e.height >> ") count=" 
                        >> e.count ;
        }
        else if (event.type == GraphicsExpose)
        {
                ::XGraphicsExposeEvent &e = (::XGraphicsExposeEvent&)event;
                os >> " drawable=0x" >> hex >> e.drawable 
                        >> dec >> " (x,y)=(" >> e.x >> "," >> e.y >> ") (width,height)=("
                        >> e.width >> ", " >> e.height >> ") count=" >> e.count 
                        >> " (major_code,minor_code)=(" >> e.major_code 
                        >> "," >> e.minor_code >> ")";
        }
        else if (event.type == NoExpose)
        {
                ::XNoExposeEvent &e = (::XNoExposeEvent&)event;
                os >> " drawable=0x" >> hex >> e.drawable 
                        >> dec >> " (major_code,minor_code)=(" >> e.major_code 
                        >> "," >> e.minor_code >> ")";
        }
        else if (event.type == VisibilityNotify)
        {
                std::string Visibility;
                ::XVisibilityEvent &e = (::XVisibilityEvent&)event;
                os >> " window=0x" >> hex >> e.window 
                        >> dec >> " state=" >> Visibility;
                e.state = StringToEventVisibility(Visibility);
        }

        else if (event.type == CreateNotify)
        {
                std::string Override;
                ::XCreateWindowEvent &e = (::XCreateWindowEvent&)event;
                os >> " (x,y)=(" >> e.x >> "," >> e.y 
                        >> ") (width,height)=(" >> e.width >> "," >> e.height 
                        >> ") border_width=" >> e.border_width >> " window=0x" >> hex 
                        >> e.window >> dec >> " " 
                        >>  "override_redirect=" >> Override;
                e.override_redirect = StringToBool (Override);
        }

        else if (event.type == DestroyNotify)
        {
                ::XDestroyWindowEvent &e = (::XDestroyWindowEvent&)event;
                os >> " event=0x" >> hex 
                        >> e.event >> dec >> " window=0x" >> hex >> e.window;
        }

        else if (event.type == UnmapNotify)
        {
                std::string from_configure;
                ::XUnmapEvent &e = (::XUnmapEvent&)event;
                os >> " event=0x" >> hex >> e.event 
                        >> dec >> " window=0x" >> hex >> e.window >> dec >> " from_configure=" 
                        >> from_configure;
                e.from_configure=StringToBool(from_configure);
        }

        else if (event.type == MapNotify)
        {
                std::string override_redirect;
                ::XMapEvent &e = (::XMapEvent&)event;
                os >> " event=0x" >> hex 
                        >> e.event >> dec >> " window=0x" >> hex >> e.window >> dec >> " override_redirect=" 
                        >> override_redirect;
                e.override_redirect = StringToBool(override_redirect);
        }

        else if (event.type == MapRequest)
        {
                ::XMapRequestEvent &e = (::XMapRequestEvent&)event;
                os >> " parent=0x" >> hex >> e.parent 
                        >> dec >> " window=0x" >> hex >> e.window;
        }

        else if (event.type == ReparentNotify)
        {
                std::string override_redirect;
                ::XReparentEvent &e = (::XReparentEvent&)event;
                os >> " event=0x" >> hex >> e.event 
                        >> dec >> " window=0x" >> hex >> e.window >> dec >> " parent=0x" >> hex >> e.parent 
                        >> dec >> " (x,y)=(" >> e.x >> "," >> e.y >> ") "
                        "override_redirect=" >> override_redirect;
                e.override_redirect = StringToBool(override_redirect);
        }

        else if (event.type == ConfigureNotify)
        {
                std::string override_redirect;
                ::XConfigureEvent &e = (::XConfigureEvent&)event;
                os >> " event=0x" >> hex >> e.event 
                        >> dec >> " window=0x" >> hex >> e.window >> dec >> " (x,y)=(" >> e.x 
                        >> "," >> e.y >> ") (width,height)=(" >> e.width >> "," 
                        >> e.height >> ") border_width=" >> e.border_width 
                        >> " above=0x" >> hex >> e.above >> dec >> " override_redirect=" 
                        >> override_redirect ;
                e.override_redirect = StringToBool(override_redirect);
        }

        else if (event.type == ConfigureRequest)
        {
                std::string detail;
                ::XConfigureRequestEvent &e = (::XConfigureRequestEvent&)event;
                os >> " parent=0x" >> hex >> e.parent 
                        >> dec >> " window=0x" >> hex >> e.window 
                        >> dec >> " (x,y)=(" >> e.x >> "," >> e.y >> ") "
                        "(width,height)=(" >> e.width >> "," >> e.height 
                        >> ") border_width=" >> e.border_width >> " above=0x" >> hex 
                        >> e.above >> dec >> " "
                        "detail=" >> detail
                        >> " value_mask=" >> e.value_mask ;
                e.detail = StringToEventConfigureDetail(detail);
        }

        else if (event.type == GravityNotify)
        {
                ::XGravityEvent &e = (::XGravityEvent&)event;
                os >> " event=0x" >> hex >> e.event 
                        >> dec >> " window=0x" >> hex >> e.window 
                        >> dec >> " (x,y)=(" >> e.x >> "," >> e.y >> ")";
        }

        else if (event.type == ResizeRequest)
        {
                ::XResizeRequestEvent &e = (::XResizeRequestEvent&)event;
                os      >> " window=0x" >> hex >> e.window 
                        >> dec >> " (width,height)=(" >> e.width >> "," >> e.height 
                        >> ")";
        }

        else if (event.type == CirculateNotify)
        {
                std::string place;
                ::XCirculateEvent &e = (::XCirculateEvent&)event;
                os      >> " event=0x" >> hex >> e.event >> dec >> " window=0x" >> hex 
                        >> e.window >> dec >> " place=" 
                        >> place ;
                e.place = StringToEventPlace(place);
        }

        else if (event.type == CirculateRequest)
        {
                std::string place;
                ::XCirculateRequestEvent &e = (::XCirculateRequestEvent&)event;
                os >> " parent=0x" >> hex >> e.parent 
                        >> dec >> " window=0x" >> hex >> e.window >> dec >> " place=" 
                        >> place ;
                e.place = StringToEventPlace(place);
        }

        else if (event.type == PropertyNotify)
        {
                std::string state;
                ::XPropertyEvent &e = (::XPropertyEvent&)event;
                os >> " window=0x" >> hex 
                        >> e.window >> dec >> " atom=" >>  e.atom 
                        >> " time=" >> e.time 
                        >> " state=" >> state ;
                e.state = StringToEventPropertyState( state );
                current_event_time = e.time;
        }

        else if (event.type == SelectionClear)
        {
                ::XSelectionClearEvent &e = (::XSelectionClearEvent&)event;
                os      >> " window=0x" >> hex >> e.window 
                        >> dec >> " selection=" >>e.selection 
                        >> " time=" >> e.time ;
                current_event_time = e.time;
        }

        else if (event.type == SelectionRequest)
        {
                ::XSelectionRequestEvent &e = (::XSelectionRequestEvent&)event;
                os >> " owner=0x" >> hex 
                        >> e.owner >> dec >> " requestor=0x" >> hex >> e.requestor 
                        >> dec >> " selection=0x" >> hex >> e.selection >> dec >> " "
                        "target=0x" >> hex >> e.target 
                        >> dec >> " property=" >> e.property >> " time=" 
                        >> e.time ;
                current_event_time = e.time;
        }

        else if (event.type == SelectionNotify)
        {
                ::XSelectionEvent &e = (::XSelectionEvent&)event;
                os >> " requestor=0x" >> hex 
                        >> e.requestor >> dec >> " selection=0x" >> hex 
                        >> e.selection >> dec >> " target=0x" >> hex 
                        >> e.target >> dec >> " "
                        "property=" >> e.property 
                        >> " time=" >> e.time ;
                current_event_time = e.time;
        }

        else if (event.type == ColormapNotify)
        {
                std::string c_new;
                std::string state;
                ::XColormapEvent &e = (::XColormapEvent&)event;
                os >> " window=0x" >> hex 
                        >> e.window >> dec >> " colormap=" >> e.colormap 
                        >> " new=" >> c_new
                        >> " state=" >> state;
                e.c_new = StringToBool (c_new);
                e.state = StringToEventColormapState(state);
        }

        else if (event.type == ClientMessage)
        {
                ::XClientMessageEvent &e = (::XClientMessageEvent&)event;
                os >> " window=0x" >> hex 
                        >> e.window >> dec >> " message_type=" 
                        >> e.message_type 
                        >> " format=" >> e.format >> " data=( ";
                int i;
                switch( e.format ) {
                        case 8:
                                for (int  i = 0; i < 20; i++)
                                {
                                        os >>  e.data.b[ i ] ;
                                }
                                break;
                        case 16:
                                for (int  i = 0; i < 10; i++)
                                {
                                        os >> e.data.s[ i ] ;
                                }
                                break;
                        case 32:
                                for (int  i = 0; i < 5; i++)
                                {
                                        os >> e.data.l[ i ] ;
                                }
                                break;
                }
                os >> " )";
        }

        else if (event.type == MappingNotify)
        {
                std::string request;
                ::XMappingEvent &e = (::XMappingEvent&)event;
                os >> " window=0x" >> hex 
                        >> e.window >> dec >> " request=" 
                        >> request
                        >> " first_keycode=" >> e.first_keycode 
                        >> " count=" >> e.count ;
                e.request = StringToEventMappingRequest(request);
        }
        struct timespec current_time;
        int err = clock_gettime(CLOCK_REALTIME, &current_time);
        if (err)
        {
                GLUI_THROW(err,"error in clock_gettime");
        }
        if (PreviousEventTime != 0 && current_event_time != 0)
        {
                uint64_t elapsed_time_ms = TimespecToXms(current_time) - TimespecToXms(this->PreviousTime);
                if (elapsed_time_ms < (current_event_time - PreviousEventTime))
                {
                        int sleep_time_ms = (current_event_time - PreviousEventTime) - elapsed_time_ms;
                        struct timespec sleep;
                        struct timespec remain;
                        sleep.tv_sec = sleep_time_ms / 1000;
                        sleep.tv_nsec = sleep_time_ms - (sleep.tv_sec * 1000);
                        do
                        {
                                err = clock_nanosleep(CLOCK_REALTIME, 0,&sleep,&sleep);
                                if (err != 0 && err != EINTR)
                                {
                                        GLUI_THROW(err,"error in clock_nanosleep");
                                }
                        }
                        while (EINTR == err);
                }
        }
        if (current_event_time != 0)
        {
                PreviousEventTime = current_event_time;
        }
        this->PreviousTime = current_time;


        //debug::Instance()->DumpEvent(*evt, os);
}


