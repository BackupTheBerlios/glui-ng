/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_debug.cpp - Glui trace facility


          --------------------------------------------------

  Copyright (c) 2007 Jean-Luc MALET

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
        switch( event.type )
        {

                case KeyPress:
                case KeyRelease:
                        {
                                ::XKeyEvent &e = (::XKeyEvent&)event;
                                cerr << EventTypeToString( e.type )
                                     << "window=0x" << hex << e.window << dec << ", root=0x" << hex
                                     << e.root << dec << ", subwindow=0x" << hex
                                     <<  e.subwindow << dec << ", time=" 
                                     <<  (unsigned long)e.time << ", (x,y)=("
                                     << e.x << "," << e.y << "), (x_root,y_root)=("
                                     << e.x_root <<","<< e.y_root << "), state=0x" << hex 
                                     << e.state << dec << "keycode=" << e.keycode
                                     << "same_screen=" << EventBoolToString( e.same_screen ) <<endl;
                                return;
                        }

                case ButtonPress:
                case ButtonRelease: 
                        {
                                ::XButtonEvent &e = (::XButtonEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": window=0x" << hex << e.window << dec << ", root=0x" << hex
                                        << e.root << dec << ", subwindow=0x" << hex << e.subwindow << dec << ", time="
                                        << (unsigned long)e.time << ", (x,y)=(" << e.x 
                                        << "," << e.y << "), (x_root,y_root)=(" 
                                        << e.x_root << "," << e.y_root << "), state=0x" << hex << e.state
                                        << dec << ", button=" << e.button << ", same_screen=" << EventBoolToString( e.same_screen )<< endl;
                                return;
                        }

                case MotionNotify:
                        {
                                ::XMotionEvent &e = (::XMotionEvent&)event;
                                cerr << EventTypeToString( e.type ) 
                                        << ": window=0x" << hex << e.window 
                                        << dec << ", root=0x" << hex << e.root 
                                        << dec << ", subwindow=0x" << hex << e.subwindow 
                                        << dec << ", time=" << (unsigned long)e.time 
                                        << "u, (x,y)=(" << e.x << "," << e.y 
                                        << "), (x_root,y_root)=(" << e.x_root << "," << e.y_root 
                                        << "), state=0x" << hex << e.state 
                                        << dec << ", is_hint=" << EventNotifyHintToString( e.is_hint ) 
                                        << ", same_screen=" << EventBoolToString( e.same_screen ) 
                                        << "\n";
                                return;
                        }

                case EnterNotify:
                case LeaveNotify: 
                        {
                                ::XCrossingEvent &e = (::XCrossingEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": window=0x" << hex << e.window 
                                        << dec << ", root=0x" << hex << e.root << dec << ", subwindow=0x" << hex 
                                        << e.subwindow << dec << ", time=" << (unsigned long)e.time 
                                        << "u, (x,y)=(" << e.x << "," << e.y 
                                        << "), mode=" << EventNotifyModeToString( e.mode ) 
                                        << ", detail=" << EventNotifyDetailToString( e.detail ) 
                                        << ", same_screen=" << (int)e.same_screen << ", focus=" 
                                        << (int)e.focus << ", state=0x" << hex << e.state << dec << "\n";
                                return;
                        }

                case FocusIn:
                case FocusOut:
                        {
                                ::XFocusChangeEvent &e = (::XFocusChangeEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": window=0x" << hex
                                        << e.window << dec << ", mode="
                                        << EventNotifyModeToString( e.mode ) << ", detail="
                                        << EventNotifyDetailToString( e.detail ) << endl;
                                return;
                        }

                case KeymapNotify:
                        {
                                ::XKeymapEvent &e = (::XKeymapEvent&)event;
                                cerr << EventTypeToString( e.type )
                                       << ": window=0x" << hex << e.window << dec << ", ";
                                for (int i = 0; i < 32; i++)
                                {
                                        cerr << e.key_vector[i];
                                }
                                cerr << endl;
                                return;
                        }

                case Expose:
                        {
                                ::XExposeEvent &e = (::XExposeEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": window=0x" << hex 
                                        <<  e.window << dec << ", (x,y)=(" <<  e.x << "," << e.y 
                                        << "), (width,height)=("
                                        << e.width << "," << e.height << "), count=" 
                                        << e.count << endl;
                                return;
                        }

                case GraphicsExpose:
                        {
                                ::XGraphicsExposeEvent &e = (::XGraphicsExposeEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": drawable=0x" << hex << e.drawable 
                                        << dec << ", (x,y)=(" << e.x << "," << e.y << "), (width,height)=("
                                        << e.width << ", " << e.height << "), count=" << e.count 
                                        << ", (major_code,minor_code)=(" << e.major_code 
                                        << "," << e.minor_code << ")\n";
                                return;
                        }

                case NoExpose:
                        {
                                ::XNoExposeEvent &e = (::XNoExposeEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": drawable=0x" << hex << e.drawable 
                                        << dec << ", (major_code,minor_code)=(" << e.major_code 
                                        << "," << e.minor_code << ")\n";
                                return;
                        }

                case VisibilityNotify:
                        {
                                ::XVisibilityEvent &e = (::XVisibilityEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": window=0x" << hex << e.window 
                                        << dec << ", state=" << EventVisibilityToString( e.state) << "\n";
                                return;
                        }

                case CreateNotify:
                        {
                                ::XCreateWindowEvent &e = (::XCreateWindowEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": (x,y)=(" << e.x << "," << e.y 
                                        << "), (width,height)=(" << e.width << "," << e.height 
                                        << "), border_width=" << e.border_width << ", window=0x" << hex 
                                        << e.window << dec << "," 
                                        <<  "override_redirect=" <<EventBoolToString( e.override_redirect ) << "\n";
                                return;
                        }

                case DestroyNotify:
                        {
                                ::XDestroyWindowEvent &e = (::XDestroyWindowEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": event=0x" << hex 
                                        << e.event << dec << ", window=0x" << hex << e.window << dec << "\n";
                                return;
                        }

                case UnmapNotify:
                        {
                                ::XUnmapEvent &e = (::XUnmapEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": event=0x" << hex << e.event 
                                        << dec << ", window=0x" << hex << e.window << dec << ", from_configure=" 
                                        << EventBoolToString( e.from_configure )  << "\n";
                                return;
                        }

                case MapNotify:
                        {
                                ::XMapEvent &e = (::XMapEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": event=0x" << hex 
                                        << e.event << dec << ", window=0x" << hex << e.window << dec << ", override_redirect=" 
                                        << EventBoolToString( e.override_redirect ) << "\n";
                                return;
                        }

                case MapRequest:
                        {
                                ::XMapRequestEvent &e = (::XMapRequestEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": parent=0x" << hex << e.parent 
                                        << dec << ", window=0x" << hex << e.window << dec << "\n";
                                return;
                        }

                case ReparentNotify:
                        {
                                ::XReparentEvent &e = (::XReparentEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": event=0x" << hex << e.event 
                                        << dec << ", window=0x" << hex << e.window << dec << ", parent=0x" << hex << e.parent 
                                        << dec << ", (x,y)=(" << e.x << "," << e.y << "), "
                                        "override_redirect=" << EventBoolToString( e.override_redirect ) << "\n";
                                return;
                        }

                case ConfigureNotify:
                        {
                                ::XConfigureEvent &e = (::XConfigureEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": event=0x" << hex << e.event 
                                        << dec << ", window=0x" << hex << e.window << dec << ", (x,y)=(" << e.x 
                                        << "," << e.y << "), (width,height)=(" << e.width << "," 
                                        << e.height << "), border_width=" << e.border_width 
                                        << ", above=0x" << hex << e.above << dec << ", override_redirect=" 
                                        << EventBoolToString( e.override_redirect ) << "\n";
                                return;
                        }

                case ConfigureRequest:
                        {
                                ::XConfigureRequestEvent &e = (::XConfigureRequestEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": parent=0x" << hex << e.parent 
                                        << dec << ", window=0x" << hex << e.window 
                                        << dec << ", (x,y)=(" << e.x << "," << e.y << "), "
                                        "(width,height)=(" << e.width << "," << e.height 
                                        << "), border_width=" << e.border_width << ", above=0x" << hex 
                                        << e.above << dec << ", "
                                        "detail=" << EventConfigureDetailToString( e.detail ) 
                                        << ", value_mask=" << e.value_mask << "\n";
                                return;
                        }

                case GravityNotify:
                        {
                                ::XGravityEvent &e = (::XGravityEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": event=0x" << hex << e.event 
                                        << dec << ", window=0x" << hex << e.window 
                                        << dec << ", (x,y)=(" << e.x << "," << e.y << ")\n";
                                return;
                        }

                case ResizeRequest:
                        {
                                ::XResizeRequestEvent &e = (::XResizeRequestEvent&)event;
                                cerr << EventTypeToString( e.type ) 
                                        << ": window=0x" << hex << e.window 
                                        << dec << ", (width,height)=(" << e.width << "," << e.height 
                                        << ")\n";
                                return;
                        }

                case CirculateNotify:
                        {
                                ::XCirculateEvent &e = (::XCirculateEvent&)event;
                                cerr << EventTypeToString( e.type ) 
                                        << ": event=0x" << hex << e.event << dec << ", window=0x" << hex 
                                        << e.window << dec << ", place=" 
                                        << EventPlaceToString( e.place ) << "\n";
                                return;
                        }

                case CirculateRequest:
                        {
                                ::XCirculateRequestEvent &e = (::XCirculateRequestEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": parent=0x" << hex << e.parent 
                                        << dec << ", window=0x" << hex << e.window << dec << ", place=" 
                                        << EventPlaceToString( e.place ) << "\n";
                                return;
                        }

                case PropertyNotify:
                        {
                                ::XPropertyEvent &e = (::XPropertyEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": window=0x" << hex 
                                        << e.window << dec << ", atom=" << (unsigned long) e.atom 
                                        << "u, time=" << (unsigned long)e.time 
                                        << "u, state=" << EventPropertyStateToString( e.state ) << "\n";
                                return;
                        }

                case SelectionClear:
                        {
                                ::XSelectionClearEvent &e = (::XSelectionClearEvent&)event;
                                cerr << EventTypeToString( e.type ) 
                                        << ": window=0x" << hex << e.window 
                                        << dec << ", selection=" << (unsigned long)e.selection 
                                        << "u, time=" << (unsigned long)e.time << "u\n";
                                return;
                        }

                case SelectionRequest:
                        {
                                ::XSelectionRequestEvent &e = (::XSelectionRequestEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": owner=0x" << hex 
                                        << e.owner << dec << ", requestor=0x" << hex << e.requestor 
                                        << dec << ", selection=0x" << hex << (unsigned long)e.selection << dec << ", "
                                        "target=0x" << hex << (unsigned long)e.target 
                                        << dec << ", property=" << (unsigned long)e.property << "u, time=" 
                                        << (unsigned long)e.time << "u\n";
                                return;
                        }

                case SelectionNotify:
                        {
                                ::XSelectionEvent &e = (::XSelectionEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": requestor=0x" << hex 
                                        << e.requestor << dec << ", selection=0x" << hex 
                                        << (unsigned long)e.selection << dec << ", target=0x" << hex 
                                        << (unsigned long)e.target << dec << ", "
                                        "property=" << (unsigned long)e.property 
                                        << "u, time=" << (unsigned long)e.time << "u\n";
                                return;
                        }

                case ColormapNotify:
                        {
                                ::XColormapEvent &e = (::XColormapEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": window=0x" << hex 
                                        << e.window << dec << ", colormap=" << (unsigned long)e.colormap 
                                        << "u, new=" << EventBoolToString( e.c_new ) 
                                        << ", state=" << EventColormapStateToString( e.state )
                                        << "\n";
                                return;
                        }

                case ClientMessage:
                        {
                                ::XClientMessageEvent &e = (::XClientMessageEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": window=0x" << hex 
                                        << e.window << dec << ", message_type=" 
                                        << (unsigned long)e.message_type 
                                        << "u, format=" << e.format << ", data=(";
                                int i;
#warning "todo"
                                /*switch( e.format ) {
                                        case 8:
                                                for (int  i = 0; i < 20; i++, p += 3 ) {
                                                        cerr << " %02x" <<  e.data.b[ i ];
                                                }
                                                break;
                                        case 16:
                                                for (int  i = 0; i < 10; i++, p += 5 ) {
                                                        cerr << " %04x" << e.data.s[ i ];
                                                }
                                                break;
                                        case 32:
                                                for (int  i = 0; i < 5; i++, p += 9 ) {
                                                        cerr << " %08lx" << e.data.l[ i ] ;
                                                }
                                                break;
                                }*/
                                cerr << ")\n";
                                return;
                        }

                case MappingNotify:
                        {
                                ::XMappingEvent &e = (::XMappingEvent&)event;
                                cerr << EventTypeToString( e.type ) << ": window=0x" << hex 
                                        << e.window << dec << ", request=" 
                                        << EventMappingRequestToString( e.request ) 
                                        << ", first_keycode=" << e.first_keycode 
                                        << ", count=" << e.count << "\n";
                                return;
                        }

                default:
                        {
                                cerr << EventTypeToString( event.type ) << "\n";
                                return;
                        }
        }
}


