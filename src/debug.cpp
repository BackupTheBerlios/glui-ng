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
#include <GL/gl.h>
#include <GL/glui/debug.h>
#include <GL/glui/window.h>
#include <string.h>


#ifdef _MSC_VER
#define vsnprintf _vsnprintf
#endif

using namespace GLUI;

debug::debug()
{
        use_debug = getenv("GLUI_ENABLE_DEBUG");
        glui_enable_fileandline = getenv("GLUI_ENABLE_FILEANDLINE");
        glui_enable_indent_traces = getenv("GLUI_ENABLE_INDENT_TRACES");
        shift = 0;
}

debug::~debug()
{
}




void debug::Printxx(const char* key,
                const char* file,
                int line,
                const char* func,
                int level,
                ostringstream& str)
{

        if (use_debug != NULL && NULL != getenv(key))
        {
                if ( level == -1)
                {
                        if (shift >=1)  shift--;
                        cerr << "<";
                }
                else if ( level == 0)
                {
                        cerr << ".";
                }
                else 
                {
                        cerr << ">";
                }
                if ( glui_enable_indent_traces != NULL )
                {
                        for (uint32_t i=0; i<shift; i++)
                        {
                                cerr << "    ";
                        }
                }
                if ( NULL != glui_enable_fileandline && file != NULL && line != 0)
                {
                        cerr << file << ":" << line << "  ";
                }


                cerr << func << ":" <<str.str();

                if (level == 1) shift++;
        }
}

void debug::FlushGL(void)
{
        if (NULL != getenv("GLUI_SYNC") &&
                        _Window::get_buffer_mode() == _Window::buffer_front)
        {
                glFlush();
        }
}


debug* debug::Instance()
{
        static debug instance;
        return &instance;
}


const char* debug::EventTypeToString( int type )
{
        switch( type ) {
                case KeyPress: return "KeyPress";
                case KeyRelease: return "KeyRelease";
                case ButtonPress: return "ButtonPress";
                case ButtonRelease: return "ButtonRelease";
                case MotionNotify: return "MotionNotify";
                case EnterNotify: return "EnterNotify";
                case LeaveNotify: return "LeaveNotify";
                case FocusIn: return "FocusIn";
                case FocusOut: return "FocusOut";
                case KeymapNotify: return "KeymapNotify";
                case Expose: return "Expose";
                case GraphicsExpose: return "GraphicsExpose";
                case NoExpose: return "NoExpose";
                case VisibilityNotify: return "VisibilityNotify";
                case CreateNotify: return "CreateNotify";
                case DestroyNotify: return "DestroyNotify";
                case UnmapNotify: return "UnmapNotify";
                case MapNotify: return "MapNotify";
                case MapRequest: return "MapRequest";
                case ReparentNotify: return "ReparentNotify";
                case ConfigureNotify: return "ConfigureNotify";
                case ConfigureRequest: return "ConfigureRequest";
                case GravityNotify: return "GravityNotify";
                case ResizeRequest: return "ResizeRequest";
                case CirculateNotify: return "CirculateNotify";
                case CirculateRequest: return "CirculateRequest";
                case PropertyNotify: return "PropertyNotify";
                case SelectionClear: return "SelectionClear";
                case SelectionRequest: return "SelectionRequest";
                case SelectionNotify: return "SelectionNotify";
                case ColormapNotify: return "ColormapNotify";
                case ClientMessage: return "ClientMessage";
                case MappingNotify: return "MappingNotify";
                default: return "UNKNOWN";
        }
}

const char* debug::EventBoolToString( Bool b )
{
        return b == False ? "False" : "True";
}

const char* debug::EventNotifyHintToString( char is_hint )
{
        switch( is_hint ) {
                case NotifyNormal: return "NotifyNormal";
                case NotifyHint: return "NotifyHint";
                default: return "UNKNOWN";
        }
}

const char* debug::EventNotifyModeToString( int mode )
{
        switch( mode ) {
                case NotifyNormal: return "NotifyNormal";
                case NotifyGrab: return "NotifyGrab";
                case NotifyUngrab: return "NotifyUngrab";
                case NotifyWhileGrabbed: return "NotifyWhileGrabbed";
                default: return "UNKNOWN";
        }
}

const char* debug::EventNotifyDetailToString( int detail )
{
        switch( detail ) {
                case NotifyAncestor: return "NotifyAncestor";
                case NotifyVirtual: return "NotifyVirtual";
                case NotifyInferior: return "NotifyInferior";
                case NotifyNonlinear: return "NotifyNonlinear";
                case NotifyNonlinearVirtual: return "NotifyNonlinearVirtual";
                case NotifyPointer: return "NotifyPointer";
                case NotifyPointerRoot: return "NotifyPointerRoot";
                case NotifyDetailNone: return "NotifyDetailNone";
                default: return "UNKNOWN";
        }
}

const char* debug::EventVisibilityToString( int state ) {
        switch( state ) {
                case VisibilityUnobscured: return "VisibilityUnobscured";
                case VisibilityPartiallyObscured: return "VisibilityPartiallyObscured";
                case VisibilityFullyObscured: return "VisibilityFullyObscured";
                default: return "UNKNOWN";
        }
}

const char* debug::EventConfigureDetailToString( int detail )
{
        switch( detail ) {
                case Above: return "Above";
                case Below: return "Below";
                case TopIf: return "TopIf";
                case BottomIf: return "BottomIf";
                case Opposite: return "Opposite";
                default: return "UNKNOWN";
        }
}

const char* debug::EventPlaceToString( int place )
{
        switch( place ) {
                case PlaceOnTop: return "PlaceOnTop";
                case PlaceOnBottom: return "PlaceOnBottom";
                default: return "UNKNOWN";
        }
}

const char* debug::EventMappingRequestToString( int request )
{
        switch( request ) {
                case MappingModifier: return "MappingModifier";
                case MappingKeyboard: return "MappingKeyboard";
                case MappingPointer: return "MappingPointer";
                default: return "UNKNOWN";
        }
}

const char* debug::EventPropertyStateToString( int state )
{
        switch( state ) {
                case PropertyNewValue: return "PropertyNewValue";
                case PropertyDelete: return "PropertyDelete";
                default: return "UNKNOWN";
        }
}

const char* debug::EventColormapStateToString( int state )
{
        switch( state ) {
                case ColormapUninstalled: return "ColormapUninstalled";
                case ColormapInstalled: return "ColormapInstalled";
                default: return "UNKNOWN";
        }
}

void debug::PrintEvent(const char* key,const ::XEvent& event, const char* func)
{
        if (use_debug == NULL || NULL == getenv(key)) return;
        DumpEvent(event, cerr);
}

void debug::DumpEvent(const ::XEvent& event, ostream& out)
{
        switch( event.type )
        {

                case KeyPress:
                case KeyRelease:
                        {
                                ::XKeyEvent &e = (::XKeyEvent&)event;
                                out << EventTypeToString( e.type )
                                     << ": window=0x" << hex << e.window << dec << " root=0x" << hex
                                     << e.root << dec << " subwindow=0x" << hex
                                     <<  e.subwindow << dec << " time=" 
                                     <<  e.time << " (x,y)=("
                                     << e.x << "," << e.y << ") (x_root,y_root)=("
                                     << e.x_root <<","<< e.y_root << ") state=0x" << hex 
                                     << e.state << dec << " keycode=" << e.keycode
                                     << " same_screen=" << EventBoolToString( e.same_screen ) <<endl;
                                return;
                        }

                case ButtonPress:
                case ButtonRelease: 
                        {
                                ::XButtonEvent &e = (::XButtonEvent&)event;
                                out << EventTypeToString( e.type ) << ": window=0x" << hex << e.window << dec << " root=0x" << hex
                                        << e.root << dec << " subwindow=0x" << hex << e.subwindow << dec << " time="
                                        << e.time << " (x,y)=(" << e.x 
                                        << "," << e.y << ") (x_root,y_root)=(" 
                                        << e.x_root << "," << e.y_root << ") state=0x" << hex << e.state
                                        << dec << " button=" << e.button << " same_screen=" << EventBoolToString( e.same_screen )<< endl;
                                return;
                        }

                case MotionNotify:
                        {
                                ::XMotionEvent &e = (::XMotionEvent&)event;
                                out << EventTypeToString( e.type ) 
                                        << ": window=0x" << hex << e.window 
                                        << dec << " root=0x" << hex << e.root 
                                        << dec << " subwindow=0x" << hex << e.subwindow 
                                        << dec << " time=" << e.time 
                                        << " (x,y)=(" << e.x << "," << e.y 
                                        << ") (x_root,y_root)=(" << e.x_root << "," << e.y_root 
                                        << ") state=0x" << hex << e.state 
                                        << dec << " is_hint=" << EventNotifyHintToString( e.is_hint ) 
                                        << " same_screen=" << EventBoolToString( e.same_screen ) 
                                        << "\n";
                                return;
                        }

                case EnterNotify:
                case LeaveNotify: 
                        {
                                ::XCrossingEvent &e = (::XCrossingEvent&)event;
                                out << EventTypeToString( e.type ) << ": window=0x" << hex << e.window 
                                        << dec << " root=0x" << hex << e.root << dec << " subwindow=0x" << hex 
                                        << e.subwindow << dec << " time=" << e.time 
                                        << " (x,y)=(" << e.x << "," << e.y 
                                        << ") mode=" << EventNotifyModeToString( e.mode ) 
                                        << " detail=" << EventNotifyDetailToString( e.detail ) 
                                        << " same_screen=" << EventBoolToString(e.same_screen) << " focus=" 
                                        << (int)e.focus << " state=0x" << hex << e.state << dec << "\n";
                                return;
                        }

                case FocusIn:
                case FocusOut:
                        {
                                ::XFocusChangeEvent &e = (::XFocusChangeEvent&)event;
                                out << EventTypeToString( e.type ) << ": window=0x" << hex
                                        << e.window << dec << " mode="
                                        << EventNotifyModeToString( e.mode ) << " detail="
                                        << EventNotifyDetailToString( e.detail ) << endl;
                                return;
                        }

                case KeymapNotify:
                        {
                                ::XKeymapEvent &e = (::XKeymapEvent&)event;
                                out << EventTypeToString( e.type )
                                       << ": window=0x" << hex << e.window << " ";
                                for (int i = 0; i < 32; i++)
                                {
                                        int vect = e.key_vector[i];
                                        out << vect << " ";
                                }
                                out << endl;
                                return;
                        }

                case Expose:
                        {
                                ::XExposeEvent &e = (::XExposeEvent&)event;
                                out << EventTypeToString( e.type ) << ": window=0x" << hex 
                                        <<  e.window << dec << " (x,y)=(" <<  e.x << "," << e.y 
                                        << ") (width,height)=("
                                        << e.width << "," << e.height << ") count=" 
                                        << e.count << endl;
                                return;
                        }

                case GraphicsExpose:
                        {
                                ::XGraphicsExposeEvent &e = (::XGraphicsExposeEvent&)event;
                                out << EventTypeToString( e.type ) << ": drawable=0x" << hex << e.drawable 
                                        << dec << " (x,y)=(" << e.x << "," << e.y << ") (width,height)=("
                                        << e.width << "," << e.height << ") count=" << e.count 
                                        << " (major_code,minor_code)=(" << e.major_code 
                                        << "," << e.minor_code << ")\n";
                                return;
                        }

                case NoExpose:
                        {
                                ::XNoExposeEvent &e = (::XNoExposeEvent&)event;
                                out << EventTypeToString( e.type ) << ": drawable=0x" << hex << e.drawable 
                                        << dec << " (major_code,minor_code)=(" << e.major_code 
                                        << "," << e.minor_code << ")\n";
                                return;
                        }

                case VisibilityNotify:
                        {
                                ::XVisibilityEvent &e = (::XVisibilityEvent&)event;
                                out << EventTypeToString( e.type ) << ": window=0x" << hex << e.window 
                                        << dec << " state=" << EventVisibilityToString( e.state) << "\n";
                                return;
                        }

                case CreateNotify:
                        {
                                ::XCreateWindowEvent &e = (::XCreateWindowEvent&)event;
                                out << EventTypeToString( e.type ) << ": (x,y)=(" << e.x << "," << e.y 
                                        << ") (width,height)=(" << e.width << "," << e.height 
                                        << ") border_width=" << e.border_width << " window=0x" << hex 
                                        << e.window << dec 
                                        <<  " override_redirect=" <<EventBoolToString( e.override_redirect ) << "\n";
                                return;
                        }

                case DestroyNotify:
                        {
                                ::XDestroyWindowEvent &e = (::XDestroyWindowEvent&)event;
                                out << EventTypeToString( e.type ) << ": event=0x" << hex 
                                        << e.event << dec << " window=0x" << hex << e.window << dec << "\n";
                                return;
                        }

                case UnmapNotify:
                        {
                                ::XUnmapEvent &e = (::XUnmapEvent&)event;
                                out << EventTypeToString( e.type ) << ": event=0x" << hex << e.event 
                                        << dec << " window=0x" << hex << e.window << dec << " from_configure=" 
                                        << EventBoolToString( e.from_configure )  << "\n";
                                return;
                        }

                case MapNotify:
                        {
                                ::XMapEvent &e = (::XMapEvent&)event;
                                out << EventTypeToString( e.type ) << ": event=0x" << hex 
                                        << e.event << dec << " window=0x" << hex << e.window << dec << " override_redirect=" 
                                        << EventBoolToString( e.override_redirect ) << "\n";
                                return;
                        }

                case MapRequest:
                        {
                                ::XMapRequestEvent &e = (::XMapRequestEvent&)event;
                                out << EventTypeToString( e.type ) << ": parent=0x" << hex << e.parent 
                                        << dec << " window=0x" << hex << e.window << dec << "\n";
                                return;
                        }

                case ReparentNotify:
                        {
                                ::XReparentEvent &e = (::XReparentEvent&)event;
                                out << EventTypeToString( e.type ) << ": event=0x" << hex << e.event 
                                        << dec << " window=0x" << hex << e.window << dec << " parent=0x" << hex << e.parent 
                                        << dec << " (x,y)=(" << e.x << "," << e.y << ") "
                                        "override_redirect=" << EventBoolToString( e.override_redirect ) << "\n";
                                return;
                        }

                case ConfigureNotify:
                        {
                                ::XConfigureEvent &e = (::XConfigureEvent&)event;
                                out << EventTypeToString( e.type ) << ": event=0x" << hex << e.event 
                                        << dec << " window=0x" << hex << e.window << dec << " (x,y)=(" << e.x 
                                        << "," << e.y << ") (width,height)=(" << e.width << "," 
                                        << e.height << ") border_width=" << e.border_width 
                                        << " above=0x" << hex << e.above << dec << " override_redirect=" 
                                        << EventBoolToString( e.override_redirect ) << "\n";
                                return;
                        }

                case ConfigureRequest:
                        {
                                ::XConfigureRequestEvent &e = (::XConfigureRequestEvent&)event;
                                out << EventTypeToString( e.type ) << ": parent=0x" << hex << e.parent 
                                        << dec << " window=0x" << hex << e.window 
                                        << dec << " (x,y)=(" << e.x << "," << e.y << ") "
                                        "(width,height)=(" << e.width << "," << e.height 
                                        << ") border_width=" << e.border_width << " above=0x" << hex 
                                        << e.above << dec << " "
                                        "detail=" << EventConfigureDetailToString( e.detail ) 
                                        << " value_mask=" << e.value_mask << "\n";
                                return;
                        }

                case GravityNotify:
                        {
                                ::XGravityEvent &e = (::XGravityEvent&)event;
                                out << EventTypeToString( e.type ) << ": event=0x" << hex << e.event 
                                        << dec << " window=0x" << hex << e.window 
                                        << dec << " (x,y)=(" << e.x << "," << e.y << ")\n";
                                return;
                        }

                case ResizeRequest:
                        {
                                ::XResizeRequestEvent &e = (::XResizeRequestEvent&)event;
                                out << EventTypeToString( e.type ) 
                                        << ": window=0x" << hex << e.window 
                                        << dec << " (width,height)=(" << e.width << "," << e.height 
                                        << ")\n";
                                return;
                        }

                case CirculateNotify:
                        {
                                ::XCirculateEvent &e = (::XCirculateEvent&)event;
                                out << EventTypeToString( e.type ) 
                                        << ": event=0x" << hex << e.event << dec << " window=0x" << hex 
                                        << e.window << dec << " place=" 
                                        << EventPlaceToString( e.place ) << "\n";
                                return;
                        }

                case CirculateRequest:
                        {
                                ::XCirculateRequestEvent &e = (::XCirculateRequestEvent&)event;
                                out << EventTypeToString( e.type ) << ": parent=0x" << hex << e.parent 
                                        << dec << " window=0x" << hex << e.window << dec << " place=" 
                                        << EventPlaceToString( e.place ) << "\n";
                                return;
                        }

                case PropertyNotify:
                        {
                                ::XPropertyEvent &e = (::XPropertyEvent&)event;
                                out << EventTypeToString( e.type ) << ": window=0x" << hex 
                                        << e.window << dec << " atom=" << e.atom 
                                        << " time=" << e.time 
                                        << " state=" << EventPropertyStateToString( e.state ) << "\n";
                                return;
                        }

                case SelectionClear:
                        {
                                ::XSelectionClearEvent &e = (::XSelectionClearEvent&)event;
                                out << EventTypeToString( e.type ) 
                                        << ": window=0x" << hex << e.window 
                                        << dec << " selection=" << e.selection 
                                        << " time=" << e.time << "\n";
                                return;
                        }

                case SelectionRequest:
                        {
                                ::XSelectionRequestEvent &e = (::XSelectionRequestEvent&)event;
                                out << EventTypeToString( e.type ) << ": owner=0x" << hex 
                                        << e.owner << dec << " requestor=0x" << hex << e.requestor 
                                        << dec << " selection=0x" << hex << e.selection << dec << " "
                                        "target=0x" << hex << e.target 
                                        << dec << " property=" << e.property << " time=" 
                                        << e.time << "\n";
                                return;
                        }

                case SelectionNotify:
                        {
                                ::XSelectionEvent &e = (::XSelectionEvent&)event;
                                out << EventTypeToString( e.type ) << ": requestor=0x" << hex 
                                        << e.requestor << dec << " selection=0x" << hex 
                                        << e.selection << dec << " target=0x" << hex 
                                        << e.target << dec << " "
                                        "property=" << e.property 
                                        << " time=" << e.time << "\n";
                                return;
                        }

                case ColormapNotify:
                        {
                                ::XColormapEvent &e = (::XColormapEvent&)event;
                                out << EventTypeToString( e.type ) << ": window=0x" << hex 
                                        << e.window << dec << " colormap=" << e.colormap 
                                        << " new=" << EventBoolToString( e.c_new ) 
                                        << " state=" << EventColormapStateToString( e.state )
                                        << "\n";
                                return;
                        }

                case ClientMessage:
                        {
                                ::XClientMessageEvent &e = (::XClientMessageEvent&)event;
                                out << EventTypeToString( e.type ) << ": window=0x" << hex 
                                        << e.window << dec << " message_type=" 
                                        << e.message_type 
                                        << " format=" << e.format << " data=( ";
                                int i;
                                switch( e.format ) {
                                        case 8:
                                                for (int  i = 0; i < 20; i++)
                                                {
                                                        out <<  e.data.b[ i ] << " ";
                                                }
                                                break;
                                        case 16:
                                                for (int  i = 0; i < 10; i++)
                                                {
                                                        out << e.data.s[ i ] << " ";
                                                }
                                                break;
                                        case 32:
                                                for (int  i = 0; i < 5; i++)
                                                {
                                                        out << e.data.l[ i ] << " " ;
                                                }
                                                break;
                                }
                                out << ")\n";
                                return;
                        }

                case MappingNotify:
                        {
                                ::XMappingEvent &e = (::XMappingEvent&)event;
                                out << EventTypeToString( e.type ) << ": window=0x" << hex 
                                        << e.window << dec << " request=" 
                                        << EventMappingRequestToString( e.request ) 
                                        << " first_keycode=" << e.first_keycode 
                                        << " count=" << e.count << "\n";
                                return;
                        }

                default:
                        {
                                out << EventTypeToString( event.type ) << "\n";
                                return;
                        }
        }
}


