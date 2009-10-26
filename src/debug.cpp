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
        if (use_debug != NULL)
        {
                buf = new char[ISIZE];
        }
}

debug::~debug()
{
        if ( use_debug != NULL ) delete buf;
}

void debug::createString(const char* format,...)
{

        va_list arg;
        va_start(arg, format);
        int ret = vsnprintf(buf, ISIZE-1, format, arg);
        va_end(arg);
        if (ret < 0) {
                cerr << "debug string too long, error :" << ret << '\n';
                buf[0]='\0';
                return ;
        }
}


void debug::rawprint(const char* key, const char* format,...)
{

        if (use_debug != NULL && NULL != getenv(key))
        {
                va_list arg;
                va_start(arg, format);
                int ret = vsnprintf(buf, ISIZE-1, format, arg);
                va_end(arg);
                if (ret < 0) {
                        cerr << "debug string too long, error :" << ret << '\n';
                        return ;
                }
                cerr << buf;
        }
}


void debug::print(const char* func, const char* file,int line)
{
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


        cerr << func << ":" << buf;
        if ( 0 == strlen(buf) ) cerr << endl;
}

void debug::print(const char* key,
                const char* file,
                int line,
                const char* func,
                int level,
                const char* format,...)
{

        if (use_debug != NULL && NULL != getenv(key))
        {
                if ( level == -1) shift--;
                va_list arg;
                va_start(arg, format);
                int ret = vsnprintf(buf, ISIZE-1, format, arg);
                va_end(arg);
                if (ret < 0) {
                        cerr << "debug string too long, error :" << ret << '\n';
                        return ;
                }
                print(func);
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
                                createString( "%s: window=0x%x, root=0x%x, subwindow=0x%x, time=%lu, "
                                                "(x,y)=(%d,%d), (x_root,y_root)=(%d,%d), state=0x%x, "
                                                "keycode=%u, same_screen=%s\ń", EventTypeToString( e.type ),
                                                e.window, e.root, e.subwindow, (unsigned long)e.time,
                                                e.x, e.y, e.x_root, e.y_root, e.state, e.keycode,
                                                EventBoolToString( e.same_screen ) );
                                break;
                        }

                case ButtonPress:
                case ButtonRelease: 
                        {
                                ::XButtonEvent &e = (::XButtonEvent&)event;
                                createString( "%s: window=0x%x, root=0x%x, subwindow=0x%x, time=%lu, "
                                                "(x,y)=(%d,%d), (x_root,y_root)=(%d,%d), state=0x%x, "
                                                "button=%u, same_screen=%d\n", EventTypeToString( e.type ),
                                                e.window, e.root, e.subwindow, (unsigned long)e.time,
                                                e.x, e.y, e.x_root, e.y_root, e.state, e.button,
                                                EventBoolToString( e.same_screen ) );
                                break;
                        }

                case MotionNotify:
                        {
                                ::XMotionEvent &e = (::XMotionEvent&)event;
                                createString( "%s: window=0x%x, root=0x%x, subwindow=0x%x, time=%lu, "
                                                "(x,y)=(%d,%d), (x_root,y_root)=(%d,%d), state=0x%x, "
                                                "is_hint=%s, same_screen=%d\n", EventTypeToString( e.type ),
                                                e.window, e.root, e.subwindow, (unsigned long)e.time,
                                                e.x, e.y, e.x_root, e.y_root, e.state,
                                                EventNotifyHintToString( e.is_hint ),
                                                EventBoolToString( e.same_screen ) );
                                break;
                        }

                case EnterNotify:
                case LeaveNotify: 
                        {
                                ::XCrossingEvent &e = (::XCrossingEvent&)event;
                                createString( "%s: window=0x%x, root=0x%x, subwindow=0x%x, time=%lu, "
                                                "(x,y)=(%d,%d), mode=%s, detail=%s, same_screen=%d, "
                                                "focus=%d, state=0x%x\n", EventTypeToString( e.type ),
                                                e.window, e.root, e.subwindow, (unsigned long)e.time,
                                                e.x, e.y, EventNotifyModeToString( e.mode ),
                                                EventNotifyDetailToString( e.detail ), (int)e.same_screen,
                                                (int)e.focus, e.state );
                                break;
                        }

                case FocusIn:
                case FocusOut:
                        {
                                ::XFocusChangeEvent &e = (::XFocusChangeEvent&)event;
                                createString( "%s: window=0x%x, mode=%s, detail=%s\n",
                                                EventTypeToString( e.type ), e.window,
                                                EventNotifyModeToString( e.mode ),
                                                EventNotifyDetailToString( e.detail ) );
                                break;
                        }

                case KeymapNotify:
                        {
                                ::XKeymapEvent &e = (::XKeymapEvent&)event;
                                char buf[32 * 2 + 1];
                                int i;
                                for ( i = 0; i < 32; i++ ) {
                                        snprintf( &buf[ i * 2 ], sizeof( buf ) - i * 2,
                                                        "%02x", e.key_vector[ i ] );
                                }
                                buf[ i ] = '\0';
                                createString( "%s: window=0x%x, %s\n", EventTypeToString( e.type ), e.window,
                                                buf );
                                break;
                        }

                case Expose:
                        {
                                ::XExposeEvent &e = (::XExposeEvent&)event;
                                createString( "%s: window=0x%x, (x,y)=(%d,%d), (width,height)=(%d,%d), "
                                                "count=%d\n", EventTypeToString( e.type ), e.window, e.x,
                                                e.y, e.width, e.height, e.count );
                                break;
                        }

                case GraphicsExpose:
                        {
                                ::XGraphicsExposeEvent &e = (::XGraphicsExposeEvent&)event;
                                createString( "%s: drawable=0x%x, (x,y)=(%d,%d), (width,height)=(%d,%d), "
                                                "count=%d, (major_code,minor_code)=(%d,%d)\n",
                                                EventTypeToString( e.type ), e.drawable, e.x, e.y,
                                                e.width, e.height, e.count, e.major_code,
                                                e.minor_code );
                                break;
                        }

                case NoExpose:
                        {
                                ::XNoExposeEvent &e = (::XNoExposeEvent&)event;
                                createString( "%s: drawable=0x%x, (major_code,minor_code)=(%d,%d)\n",
                                                EventTypeToString( e.type ), e.drawable, e.major_code,
                                                e.minor_code );
                                break;
                        }

                case VisibilityNotify:
                        {
                                ::XVisibilityEvent &e = (::XVisibilityEvent&)event;
                                createString( "%s: window=0x%x, state=%s\n", EventTypeToString( e.type ),
                                                e.window, EventVisibilityToString( e.state) );
                                break;
                        }

                case CreateNotify:
                        {
                                ::XCreateWindowEvent &e = (::XCreateWindowEvent&)event;
                                createString( "%s: (x,y)=(%d,%d), (width,height)=(%d,%d), border_width=%d, "
                                                "window=0x%x, override_redirect=%s\n",
                                                EventTypeToString( e.type ), e.x, e.y, e.width, e.height,
                                                e.border_width, e.window,
                                                EventBoolToString( e.override_redirect ) );
                                break;
                        }

                case DestroyNotify:
                        {
                                ::XDestroyWindowEvent &e = (::XDestroyWindowEvent&)event;
                                createString( "%s: event=0x%x, window=0x%x\n",
                                                EventTypeToString( e.type ), e.event, e.window );
                                break;
                        }

                case UnmapNotify:
                        {
                                ::XUnmapEvent &e = (::XUnmapEvent&)event;
                                createString( "%s: event=0x%x, window=0x%x, from_configure=%s\n",
                                                EventTypeToString( e.type ), e.event, e.window,
                                                EventBoolToString( e.from_configure ) );
                                break;
                        }

                case MapNotify:
                        {
                                ::XMapEvent &e = (::XMapEvent&)event;
                                createString( "%s: event=0x%x, window=0x%x, override_redirect=%s\n",
                                                EventTypeToString( e.type ), e.event, e.window,
                                                EventBoolToString( e.override_redirect ) );
                                break;
                        }

                case MapRequest:
                        {
                                ::XMapRequestEvent &e = (::XMapRequestEvent&)event;
                                createString( "%s: parent=0x%x, window=0x%x\n",
                                                EventTypeToString( e.type ), e.parent, e.window );
                                break;
                        }

                case ReparentNotify:
                        {
                                ::XReparentEvent &e = (::XReparentEvent&)event;
                                createString( "%s: event=0x%x, window=0x%x, parent=0x%x, (x,y)=(%d,%d), "
                                                "override_redirect=%s\n", EventTypeToString( e.type ),
                                                e.event, e.window, e.parent, e.x, e.y,
                                                EventBoolToString( e.override_redirect ) );
                                break;
                        }

                case ConfigureNotify:
                        {
                                ::XConfigureEvent &e = (::XConfigureEvent&)event;
                                createString( "%s: event=0x%x, window=0x%x, (x,y)=(%d,%d), "
                                                "(width,height)=(%d,%d), border_width=%d, above=0x%x, "
                                                "override_redirect=%s\n", EventTypeToString( e.type ), e.event,
                                                e.window, e.x, e.y, e.width, e.height, e.border_width,
                                                e.above, EventBoolToString( e.override_redirect ) );
                                break;
                        }

                case ConfigureRequest:
                        {
                                ::XConfigureRequestEvent &e = (::XConfigureRequestEvent&)event;
                                createString( "%s: parent=0x%x, window=0x%x, (x,y)=(%d,%d), "
                                                "(width,height)=(%d,%d), border_width=%d, above=0x%x, "
                                                "detail=%s, value_mask=%lx\n", EventTypeToString( e.type ),
                                                e.parent, e.window, e.x, e.y, e.width, e.height,
                                                e.border_width, e.above,
                                                EventConfigureDetailToString( e.detail ), e.value_mask );
                                break;
                        }

                case GravityNotify:
                        {
                                ::XGravityEvent &e = (::XGravityEvent&)event;
                                createString( "%s: event=0x%x, window=0x%x, (x,y)=(%d,%d)\n",
                                                EventTypeToString( e.type ), e.event, e.window, e.x, e.y );
                                break;
                        }

                case ResizeRequest:
                        {
                                ::XResizeRequestEvent &e = (::XResizeRequestEvent&)event;
                                createString( "%s: window=0x%x, (width,height)=(%d,%d)\n",
                                                EventTypeToString( e.type ), e.window, e.width, e.height );
                                break;
                        }

                case CirculateNotify:
                        {
                                ::XCirculateEvent &e = (::XCirculateEvent&)event;
                                createString( "%s: event=0x%x, window=0x%x, place=%s\n",
                                                EventTypeToString( e.type ), e.event, e.window,
                                                EventPlaceToString( e.place ) );
                                break;
                        }

                case CirculateRequest:
                        {
                                ::XCirculateRequestEvent &e = (::XCirculateRequestEvent&)event;
                                createString( "%s: parent=0x%x, window=0x%x, place=%s\n",
                                                EventTypeToString( e.type ), e.parent, e.window,
                                                EventPlaceToString( e.place ) );
                                break;
                        }

                case PropertyNotify:
                        {
                                ::XPropertyEvent &e = (::XPropertyEvent&)event;
                                createString( "%s: window=0x%x, atom=%lu, time=%lu, state=%s\n",
                                                EventTypeToString( e.type ), e.window,
                                                (unsigned long)e.atom, (unsigned long)e.time,
                                                EventPropertyStateToString( e.state ) );
                                break;
                        }

                case SelectionClear:
                        {
                                ::XSelectionClearEvent &e = (::XSelectionClearEvent&)event;
                                createString( "%s: window=0x%x, selection=%lu, time=%lu\n",
                                                EventTypeToString( e.type ), e.window,
                                                (unsigned long)e.selection, (unsigned long)e.time );
                                break;
                        }

                case SelectionRequest:
                        {
                                ::XSelectionRequestEvent &e = (::XSelectionRequestEvent&)event;
                                createString( "%s: owner=0x%x, requestor=0x%x, selection=0x%x, "
                                                "target=0x%x, property=%lu, time=%lu\n",
                                                EventTypeToString( e.type ), e.owner, e.requestor,
                                                (unsigned long)e.selection, (unsigned long)e.target,
                                                (unsigned long)e.property, (unsigned long)e.time );
                                break;
                        }

                case SelectionNotify:
                        {
                                ::XSelectionEvent &e = (::XSelectionEvent&)event;
                                createString( "%s: requestor=0x%x, selection=0x%x, target=0x%x, "
                                                "property=%lu, time=%lu\n", EventTypeToString( e.type ),
                                                e.requestor, (unsigned long)e.selection,
                                                (unsigned long)e.target, (unsigned long)e.property,
                                                (unsigned long)e.time );
                                break;
                        }

                case ColormapNotify:
                        {
                                ::XColormapEvent &e = (::XColormapEvent&)event;
                                createString( "%s: window=0x%x, colormap=%lu, new=%s, state=%s\n",
                                                EventTypeToString( e.type ), e.window,
                                                (unsigned long)e.colormap, EventBoolToString( e.c_new ),
                                                EventColormapStateToString( e.state ) );
                                break;
                        }

                case ClientMessage:
                        {
                                ::XClientMessageEvent &e = (::XClientMessageEvent&)event;
                                char buf[ 61 ];
                                char* p = buf;
                                char* end = buf + sizeof( buf );
                                int i;
                                switch( e.format ) {
                                        case 8:
                                                for ( i = 0; i < 20; i++, p += 3 ) {
                                                        snprintf( p, end - p, " %02x", e.data.b[ i ] );
                                                }
                                                break;
                                        case 16:
                                                for ( i = 0; i < 10; i++, p += 5 ) {
                                                        snprintf( p, end - p, " %04x", e.data.s[ i ] );
                                                }
                                                break;
                                        case 32:
                                                for ( i = 0; i < 5; i++, p += 9 ) {
                                                        snprintf( p, end - p, " %08lx", e.data.l[ i ] );
                                                }
                                                break;
                                }
                                *p = '\0';
                                createString( "%s: window=0x%x, message_type=%lu, format=%d, data=(%s )\n",
                                                EventTypeToString( e.type ), e.window,
                                                (unsigned long)e.message_type, e.format, buf );
                                break;
                        }

                case MappingNotify:
                        {
                                ::XMappingEvent &e = (::XMappingEvent&)event;
                                createString( "%s: window=0x%x, request=%s, first_keycode=%d, count=%d\n",
                                                EventTypeToString( e.type ), e.window,
                                                EventMappingRequestToString( e.request ), e.first_keycode,
                                                e.count );
                                break;
                        }

                default:
                        {
                                createString( "%s\n", EventTypeToString( event.type ) );
                                break;
                        }
        }

        print(func);
}


void debug::EventTypeToString(const char* key, int type, const char* func)
{
        if (use_debug == NULL || NULL == getenv(key)) return;

        createString("%s\n",EventTypeToString(type));
        print(func);
}
