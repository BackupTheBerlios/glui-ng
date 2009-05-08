/*
 * freeglut_main.c
 *
 * The windows message processing methods.
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Fri Dec 3 1999
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <GL/freeglut.h>
#include "freeglut_internal.h"
#include <errno.h>
#include <stdarg.h>
#if  HAVE_VPRINTF
#    define VFPRINTF(s,f,a) vfprintf((s),(f),(a))
#elif HAVE_DOPRNT
#    define VFPRINTF(s,f,a) _doprnt((f),(a),(s))
#else
#    define VFPRINTF(s,f,a)
#endif

#ifdef _WIN32_WCE

typedef struct GXDisplayProperties GXDisplayProperties;
typedef struct GXKeyList GXKeyList;
#include <gx.h>

typedef struct GXKeyList (*GXGETDEFAULTKEYS)(int);
typedef int (*GXOPENINPUT)();

GXGETDEFAULTKEYS GXGetDefaultKeys_ = NULL;
GXOPENINPUT GXOpenInput_ = NULL;

struct GXKeyList gxKeyList;

#endif /* _WIN32_WCE */

/*
 * Try to get the maximum value allowed for ints, falling back to the minimum
 * guaranteed by ISO C99 if there is no suitable header.
 */
#if HAVE_LIMITS_H
#    include <limits.h>
#endif
#ifndef INT_MAX
#    define INT_MAX 32767
#endif

#ifndef MIN
#    define MIN(a,b) (((a)<(b)) ? (a) : (b))
#endif


/*
 * TODO BEFORE THE STABLE RELEASE:
 *
 * There are some issues concerning window redrawing under X11, and maybe
 * some events are not handled. The Win32 version lacks some more features,
 * but seems acceptable for not demanding purposes.
 *
 * Need to investigate why the X11 version breaks out with an error when
 * closing a window (using the window manager, not glutDestroyWindow)...
 */

/* -- PRIVATE FUNCTIONS ---------------------------------------------------- */

/*
 * Handle a window configuration change. When no reshape
 * callback is hooked, the viewport size is updated to
 * match the new window size.
 */
static void fghReshapeWindow ( SFG_Window *window, int width, int height )
{
    SFG_Window *current_window = fgStructure.CurrentWindow;

    freeglut_return_if_fail( window != NULL );


#if TARGET_HOST_POSIX_X11

    XResizeWindow( fgDisplay.Display, window->Window.Handle,
                   width, height );
    XFlush( fgDisplay.Display ); /* XXX Shouldn't need this */

#elif TARGET_HOST_MS_WINDOWS && !defined(_WIN32_WCE)
    {
        RECT winRect;
        int x, y, w, h;

        /*
         * For windowed mode, get the current position of the
         * window and resize taking the size of the frame
         * decorations into account.
         */

        /* "GetWindowRect" returns the pixel coordinates of the outside of the window */
        GetWindowRect( window->Window.Handle, &winRect );
        x = winRect.left;
        y = winRect.top;
        w = width;
        h = height;

        if ( window->Parent == NULL )
        {
            if ( ! window->IsMenu && (window != fgStructure.GameModeWindow) )
            {
                w += GetSystemMetrics( SM_CXSIZEFRAME ) * 2;
                h += GetSystemMetrics( SM_CYSIZEFRAME ) * 2 +
                     GetSystemMetrics( SM_CYCAPTION );
            }
        }
        else
        {
            RECT parentRect;
            GetWindowRect( window->Parent->Window.Handle, &parentRect );
            x -= parentRect.left + GetSystemMetrics( SM_CXSIZEFRAME ) * 2;
            y -= parentRect.top  + GetSystemMetrics( SM_CYSIZEFRAME ) * 2 +
                                   GetSystemMetrics( SM_CYCAPTION );
        }

        /*
         * SWP_NOACTIVATE      Do not activate the window
         * SWP_NOOWNERZORDER   Do not change position in z-order
         * SWP_NOSENDCHANGING  Supress WM_WINDOWPOSCHANGING message
         * SWP_NOZORDER        Retains the current Z order (ignore 2nd param)
         */

        SetWindowPos( window->Window.Handle,
                      HWND_TOP,
                      x, y, w, h,
                      SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING |
                      SWP_NOZORDER
        );
    }
#endif

    /*
     * XXX Should update {window->State.OldWidth, window->State.OldHeight}
     * XXX to keep in lockstep with POSIX_X11 code.
     */
    if( FETCH_WCB( *window, Reshape ) )
        INVOKE_WCB( *window, Reshape, ( width, height ) );
    else
    {
        fgSetWindow( window );
        glViewport( 0, 0, width, height );
    }

    /*
     * Force a window redraw.  In Windows at least this is only a partial
     * solution:  if the window is increasing in size in either dimension,
     * the already-drawn part does not get drawn again and things look funny.
     * But without this we get this bad behaviour whenever we resize the
     * window.
     */
    window->State.Redisplay = GL_TRUE;

    if( window->IsMenu )
        fgSetWindow( current_window );
}

/*
 * Calls a window's redraw method. This is used when
 * a redraw is forced by the incoming window messages.
 */
static void fghRedrawWindow ( SFG_Window *window )
{
    SFG_Window *current_window = fgStructure.CurrentWindow;

    freeglut_return_if_fail( window );
    freeglut_return_if_fail( FETCH_WCB ( *window, Display ) );

    window->State.Redisplay = GL_FALSE;

    freeglut_return_if_fail( window->State.Visible );

    fgSetWindow( window );

    if( window->State.NeedToResize )
    {
        fghReshapeWindow(
            window,
            window->State.Width,
            window->State.Height
        );

        window->State.NeedToResize = GL_FALSE;
    }

    INVOKE_WCB( *window, Display, ( ) );

    fgSetWindow( current_window );
}

/*
 * A static helper function to execute display callback for a window
 */
static void fghcbDisplayWindow( SFG_Window *window,
                                SFG_Enumerator *enumerator )
{
    if( window->State.Redisplay &&
        window->State.Visible )
    {
        window->State.Redisplay = GL_FALSE;

#if TARGET_HOST_POSIX_X11
        fghRedrawWindow ( window ) ;
#elif TARGET_HOST_MS_WINDOWS
        RedrawWindow(
            window->Window.Handle, NULL, NULL,
            RDW_NOERASE | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW
        );
#endif
    }

    fgEnumSubWindows( window, fghcbDisplayWindow, enumerator );
}

/*
 * Make all windows perform a display call
 */
static void fghDisplayAll( void )
{
    SFG_Enumerator enumerator;

    enumerator.found = GL_FALSE;
    enumerator.data  =  NULL;

    fgEnumWindows( fghcbDisplayWindow, &enumerator );
}

/*
 * Window enumerator callback to check for the joystick polling code
 */
static void fghcbCheckJoystickPolls( SFG_Window *window,
                                     SFG_Enumerator *enumerator )
{
    long int checkTime = fgElapsedTime( );

    if( window->State.JoystickLastPoll + window->State.JoystickPollRate <=
        checkTime )
    {
#if !defined(_WIN32_WCE)
        fgJoystickPollWindow( window );
#endif /* !defined(_WIN32_WCE) */
        window->State.JoystickLastPoll = checkTime;
    }

    fgEnumSubWindows( window, fghcbCheckJoystickPolls, enumerator );
}

/*
 * Check all windows for joystick polling
 */
static void fghCheckJoystickPolls( void )
{
    SFG_Enumerator enumerator;

    enumerator.found = GL_FALSE;
    enumerator.data  =  NULL;

    fgEnumWindows( fghcbCheckJoystickPolls, &enumerator );
}

/*
 * Check the global timers
 */
static void fghCheckTimers( void )
{
    long checkTime = fgElapsedTime( );

    while( fgState.Timers.First )
    {
        SFG_Timer *timer = fgState.Timers.First;

        if( timer->TriggerTime > checkTime )
            break;

        fgListRemove( &fgState.Timers, &timer->Node );
        fgListAppend( &fgState.FreeTimers, &timer->Node );

        timer->Callback( timer->ID );
    }
}

 
/* Platform-dependent time in milliseconds, as an unsigned 32-bit integer.
 * This value wraps every 49.7 days, but integer overflows cancel
 * when subtracting an initial start time, unless the total time exceeds
 * 32-bit, where the GLUT API return value is also overflowed.
 */  
unsigned long fgSystemTime(void) {
#if TARGET_HOST_SOLARIS || HAVE_GETTIMEOFDAY
    struct timeval now;
    gettimeofday( &now, NULL );
    return now.tv_usec/1000 + now.tv_sec*1000;
#elif TARGET_HOST_MS_WINDOWS
#    if defined(_WIN32_WCE)
    return GetTickCount();
#    else
    return timeGetTime();
#    endif
#endif
}
  
/*
 * Elapsed Time
 */
long fgElapsedTime( void )
{
    return (long) (fgSystemTime() - fgState.Time);
}

/*
 * Error Messages.
 */
void fgError( const char *fmt, ... )
{
    va_list ap;

    va_start( ap, fmt );

    fprintf( stderr, "freeglut ");
    if( fgState.ProgramName )
        fprintf( stderr, "(%s): ", fgState.ProgramName );
    VFPRINTF( stderr, fmt, ap );
    fprintf( stderr, "\n" );

    va_end( ap );

    if ( fgState.Initialised )
        fgDeinitialize ();

    exit( 1 );
}

void fgWarning( const char *fmt, ... )
{
    va_list ap;

    va_start( ap, fmt );

    fprintf( stderr, "freeglut ");
    if( fgState.ProgramName )
        fprintf( stderr, "(%s): ", fgState.ProgramName );
    VFPRINTF( stderr, fmt, ap );
    fprintf( stderr, "\n" );

    va_end( ap );
}

/*
 * Indicates whether Joystick events are being used by ANY window.
 *
 * The current mechanism is to walk all of the windows and ask if
 * there is a joystick callback.  We have a short-circuit early
 * return if we find any joystick handler registered.
 *
 * The real way to do this is to make use of the glutTimer() API
 * to more cleanly re-implement the joystick API.  Then, this code
 * and all other "joystick timer" code can be yanked.
 *
 */
static void fghCheckJoystickCallback( SFG_Window* w, SFG_Enumerator* e)
{
    if( FETCH_WCB( *w, Joystick ) )
    {
        e->found = GL_TRUE;
        e->data = w;
    }
    fgEnumSubWindows( w, fghCheckJoystickCallback, e );
}
static int fghHaveJoystick( void )
{
    SFG_Enumerator enumerator;

    enumerator.found = GL_FALSE;
    enumerator.data = NULL;
    fgEnumWindows( fghCheckJoystickCallback, &enumerator );
    return !!enumerator.data;
}
static void fghHavePendingRedisplaysCallback( SFG_Window* w, SFG_Enumerator* e)
{
    if( w->State.Redisplay && w->State.Visible )
    {
        e->found = GL_TRUE;
        e->data = w;
    }
    fgEnumSubWindows( w, fghHavePendingRedisplaysCallback, e );
}
static int fghHavePendingRedisplays (void)
{
    SFG_Enumerator enumerator;

    enumerator.found = GL_FALSE;
    enumerator.data = NULL;
    fgEnumWindows( fghHavePendingRedisplaysCallback, &enumerator );
    return !!enumerator.data;
}
/*
 * Returns the number of GLUT ticks (milliseconds) till the next timer event.
 */
static long fghNextTimer( void )
{
    long ret = INT_MAX;
    SFG_Timer *timer = fgState.Timers.First;

    if( timer )
        ret = timer->TriggerTime - fgElapsedTime();
    if( ret < 0 )
        ret = 0;

    return ret;
}
/*
 * Does the magic required to relinquish the CPU until something interesting
 * happens.
 */
static void fghSleepForEvents( void )
{
    long msec;

    if( fgState.IdleCallback || fghHavePendingRedisplays( ) )
        return;

    msec = fghNextTimer( );
    /* XXX Use GLUT timers for joysticks... */
    /* XXX Dumb; forces granularity to .01sec */
    if( fghHaveJoystick( ) && ( msec > 10 ) )     
        msec = 10;

#if TARGET_HOST_POSIX_X11
    /*
     * Possibly due to aggressive use of XFlush() and friends,
     * it is possible to have our socket drained but still have
     * unprocessed events.  (Or, this may just be normal with
     * X, anyway?)  We do non-trivial processing of X events
     * after the event-reading loop, in any case, so we
     * need to allow that we may have an empty socket but non-
     * empty event queue.
     */
    if( ! XPending( fgDisplay.Display ) )
    {
        fd_set fdset;
        int err;
        int socket;
        struct timeval wait;

        socket = ConnectionNumber( fgDisplay.Display );
        FD_ZERO( &fdset );
        FD_SET( socket, &fdset );
        wait.tv_sec = msec / 1000;
        wait.tv_usec = (msec % 1000) * 1000;
        err = select( socket+1, &fdset, NULL, NULL, &wait );

        if( ( -1 == err ) && ( errno != EINTR ) )
            fgWarning ( "freeglut select() error: %d", errno );
    }
#elif TARGET_HOST_MS_WINDOWS
    MsgWaitForMultipleObjects( 0, NULL, FALSE, msec, QS_ALLINPUT );
#endif
}




#if TARGET_HOST_POSIX_X11 && _DEBUG

static const char* fghTypeToString( int type )
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

static const char* fghBoolToString( Bool b )
{
    return b == False ? "False" : "True";
}

static const char* fghNotifyHintToString( char is_hint )
{
    switch( is_hint ) {
    case NotifyNormal: return "NotifyNormal";
    case NotifyHint: return "NotifyHint";
    default: return "UNKNOWN";
    }
}

static const char* fghNotifyModeToString( int mode )
{
    switch( mode ) {
    case NotifyNormal: return "NotifyNormal";
    case NotifyGrab: return "NotifyGrab";
    case NotifyUngrab: return "NotifyUngrab";
    case NotifyWhileGrabbed: return "NotifyWhileGrabbed";
    default: return "UNKNOWN";
    }
}

static const char* fghNotifyDetailToString( int detail )
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

static const char* fghVisibilityToString( int state ) {
    switch( state ) {
    case VisibilityUnobscured: return "VisibilityUnobscured";
    case VisibilityPartiallyObscured: return "VisibilityPartiallyObscured";
    case VisibilityFullyObscured: return "VisibilityFullyObscured";
    default: return "UNKNOWN";
    }
}

static const char* fghConfigureDetailToString( int detail )
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

static const char* fghPlaceToString( int place )
{
    switch( place ) {
    case PlaceOnTop: return "PlaceOnTop";
    case PlaceOnBottom: return "PlaceOnBottom";
    default: return "UNKNOWN";
    }
}

static const char* fghMappingRequestToString( int request )
{
    switch( request ) {
    case MappingModifier: return "MappingModifier";
    case MappingKeyboard: return "MappingKeyboard";
    case MappingPointer: return "MappingPointer";
    default: return "UNKNOWN";
    }
}

static const char* fghPropertyStateToString( int state )
{
    switch( state ) {
    case PropertyNewValue: return "PropertyNewValue";
    case PropertyDelete: return "PropertyDelete";
    default: return "UNKNOWN";
    }
}

static const char* fghColormapStateToString( int state )
{
    switch( state ) {
    case ColormapUninstalled: return "ColormapUninstalled";
    case ColormapInstalled: return "ColormapInstalled";
    default: return "UNKNOWN";
    }
}

static void fghPrintEvent( XEvent *event )
{
    switch( event->type ) {

    case KeyPress:
    case KeyRelease: {
        XKeyEvent *e = &event->xkey;
        fgWarning( "%s: window=0x%x, root=0x%x, subwindow=0x%x, time=%lu, "
                   "(x,y)=(%d,%d), (x_root,y_root)=(%d,%d), state=0x%x, "
                   "keycode=%u, same_screen=%s", fghTypeToString( e->type ),
                   e->window, e->root, e->subwindow, (unsigned long)e->time,
                   e->x, e->y, e->x_root, e->y_root, e->state, e->keycode,
                   fghBoolToString( e->same_screen ) );
        break;
    }

    case ButtonPress:
    case ButtonRelease: {
        XButtonEvent *e = &event->xbutton;
        fgWarning( "%s: window=0x%x, root=0x%x, subwindow=0x%x, time=%lu, "
                   "(x,y)=(%d,%d), (x_root,y_root)=(%d,%d), state=0x%x, "
                   "button=%u, same_screen=%d", fghTypeToString( e->type ),
                   e->window, e->root, e->subwindow, (unsigned long)e->time,
                   e->x, e->y, e->x_root, e->y_root, e->state, e->button,
                   fghBoolToString( e->same_screen ) );
        break;
    }

    case MotionNotify: {
        XMotionEvent *e = &event->xmotion;
        fgWarning( "%s: window=0x%x, root=0x%x, subwindow=0x%x, time=%lu, "
                   "(x,y)=(%d,%d), (x_root,y_root)=(%d,%d), state=0x%x, "
                   "is_hint=%s, same_screen=%d", fghTypeToString( e->type ),
                   e->window, e->root, e->subwindow, (unsigned long)e->time,
                   e->x, e->y, e->x_root, e->y_root, e->state,
                   fghNotifyHintToString( e->is_hint ),
                   fghBoolToString( e->same_screen ) );
        break;
    }

    case EnterNotify:
    case LeaveNotify: {
        XCrossingEvent *e = &event->xcrossing;
        fgWarning( "%s: window=0x%x, root=0x%x, subwindow=0x%x, time=%lu, "
                   "(x,y)=(%d,%d), mode=%s, detail=%s, same_screen=%d, "
                   "focus=%d, state=0x%x", fghTypeToString( e->type ),
                   e->window, e->root, e->subwindow, (unsigned long)e->time,
                   e->x, e->y, fghNotifyModeToString( e->mode ),
                   fghNotifyDetailToString( e->detail ), (int)e->same_screen,
                   (int)e->focus, e->state );
        break;
    }

    case FocusIn:
    case FocusOut: {
        XFocusChangeEvent *e = &event->xfocus;
        fgWarning( "%s: window=0x%x, mode=%s, detail=%s",
                   fghTypeToString( e->type ), e->window,
                   fghNotifyModeToString( e->mode ),
                   fghNotifyDetailToString( e->detail ) );
        break;
    }

    case KeymapNotify: {
        XKeymapEvent *e = &event->xkeymap;
        char buf[32 * 2 + 1];
        int i;
        for ( i = 0; i < 32; i++ ) {
            snprintf( &buf[ i * 2 ], sizeof( buf ) - i * 2,
                      "%02x", e->key_vector[ i ] );
        }
        buf[ i ] = '\0';
        fgWarning( "%s: window=0x%x, %s", fghTypeToString( e->type ), e->window,
                   buf );
        break;
    }

    case Expose: {
        XExposeEvent *e = &event->xexpose;
        fgWarning( "%s: window=0x%x, (x,y)=(%d,%d), (width,height)=(%d,%d), "
                   "count=%d", fghTypeToString( e->type ), e->window, e->x,
                   e->y, e->width, e->height, e->count );
        break;
    }

    case GraphicsExpose: {
        XGraphicsExposeEvent *e = &event->xgraphicsexpose;
        fgWarning( "%s: drawable=0x%x, (x,y)=(%d,%d), (width,height)=(%d,%d), "
                   "count=%d, (major_code,minor_code)=(%d,%d)",
                   fghTypeToString( e->type ), e->drawable, e->x, e->y,
                   e->width, e->height, e->count, e->major_code,
                   e->minor_code );
        break;
    }

    case NoExpose: {
        XNoExposeEvent *e = &event->xnoexpose;
        fgWarning( "%s: drawable=0x%x, (major_code,minor_code)=(%d,%d)",
                   fghTypeToString( e->type ), e->drawable, e->major_code,
                   e->minor_code );
        break;
    }

    case VisibilityNotify: {
        XVisibilityEvent *e = &event->xvisibility;
        fgWarning( "%s: window=0x%x, state=%s", fghTypeToString( e->type ),
                   e->window, fghVisibilityToString( e->state) );
        break;
    }

    case CreateNotify: {
        XCreateWindowEvent *e = &event->xcreatewindow;
        fgWarning( "%s: (x,y)=(%d,%d), (width,height)=(%d,%d), border_width=%d, "
                   "window=0x%x, override_redirect=%s",
                   fghTypeToString( e->type ), e->x, e->y, e->width, e->height,
                   e->border_width, e->window,
                   fghBoolToString( e->override_redirect ) );
        break;
    }

    case DestroyNotify: {
        XDestroyWindowEvent *e = &event->xdestroywindow;
        fgWarning( "%s: event=0x%x, window=0x%x",
                   fghTypeToString( e->type ), e->event, e->window );
        break;
    }

    case UnmapNotify: {
        XUnmapEvent *e = &event->xunmap;
        fgWarning( "%s: event=0x%x, window=0x%x, from_configure=%s",
                   fghTypeToString( e->type ), e->event, e->window,
                   fghBoolToString( e->from_configure ) );
        break;
    }

    case MapNotify: {
        XMapEvent *e = &event->xmap;
        fgWarning( "%s: event=0x%x, window=0x%x, override_redirect=%s",
                   fghTypeToString( e->type ), e->event, e->window,
                   fghBoolToString( e->override_redirect ) );
        break;
    }

    case MapRequest: {
        XMapRequestEvent *e = &event->xmaprequest;
        fgWarning( "%s: parent=0x%x, window=0x%x",
                   fghTypeToString( event->type ), e->parent, e->window );
        break;
    }

    case ReparentNotify: {
        XReparentEvent *e = &event->xreparent;
        fgWarning( "%s: event=0x%x, window=0x%x, parent=0x%x, (x,y)=(%d,%d), "
                   "override_redirect=%s", fghTypeToString( e->type ),
                   e->event, e->window, e->parent, e->x, e->y,
                   fghBoolToString( e->override_redirect ) );
        break;
    }

    case ConfigureNotify: {
        XConfigureEvent *e = &event->xconfigure;
        fgWarning( "%s: event=0x%x, window=0x%x, (x,y)=(%d,%d), "
                   "(width,height)=(%d,%d), border_width=%d, above=0x%x, "
                   "override_redirect=%s", fghTypeToString( e->type ), e->event,
                   e->window, e->x, e->y, e->width, e->height, e->border_width,
                   e->above, fghBoolToString( e->override_redirect ) );
        break;
    }

    case ConfigureRequest: {
        XConfigureRequestEvent *e = &event->xconfigurerequest;
        fgWarning( "%s: parent=0x%x, window=0x%x, (x,y)=(%d,%d), "
                   "(width,height)=(%d,%d), border_width=%d, above=0x%x, "
                   "detail=%s, value_mask=%lx", fghTypeToString( e->type ),
                   e->parent, e->window, e->x, e->y, e->width, e->height,
                   e->border_width, e->above,
                   fghConfigureDetailToString( e->detail ), e->value_mask );
        break;
    }

    case GravityNotify: {
        XGravityEvent *e = &event->xgravity;
        fgWarning( "%s: event=0x%x, window=0x%x, (x,y)=(%d,%d)",
                   fghTypeToString( e->type ), e->event, e->window, e->x, e->y );
        break;
    }

    case ResizeRequest: {
        XResizeRequestEvent *e = &event->xresizerequest;
        fgWarning( "%s: window=0x%x, (width,height)=(%d,%d)",
                   fghTypeToString( e->type ), e->window, e->width, e->height );
        break;
    }

    case CirculateNotify: {
        XCirculateEvent *e = &event->xcirculate;
        fgWarning( "%s: event=0x%x, window=0x%x, place=%s",
                   fghTypeToString( e->type ), e->event, e->window,
                   fghPlaceToString( e->place ) );
        break;
    }

    case CirculateRequest: {
        XCirculateRequestEvent *e = &event->xcirculaterequest;
        fgWarning( "%s: parent=0x%x, window=0x%x, place=%s",
                   fghTypeToString( e->type ), e->parent, e->window,
                   fghPlaceToString( e->place ) );
        break;
    }

    case PropertyNotify: {
        XPropertyEvent *e = &event->xproperty;
        fgWarning( "%s: window=0x%x, atom=%lu, time=%lu, state=%s",
                   fghTypeToString( e->type ), e->window,
                   (unsigned long)e->atom, (unsigned long)e->time,
                   fghPropertyStateToString( e->state ) );
        break;
    }

    case SelectionClear: {
        XSelectionClearEvent *e = &event->xselectionclear;
        fgWarning( "%s: window=0x%x, selection=%lu, time=%lu",
                   fghTypeToString( e->type ), e->window,
                   (unsigned long)e->selection, (unsigned long)e->time );
        break;
    }

    case SelectionRequest: {
        XSelectionRequestEvent *e = &event->xselectionrequest;
        fgWarning( "%s: owner=0x%x, requestor=0x%x, selection=0x%x, "
                   "target=0x%x, property=%lu, time=%lu",
                   fghTypeToString( e->type ), e->owner, e->requestor,
                   (unsigned long)e->selection, (unsigned long)e->target,
                   (unsigned long)e->property, (unsigned long)e->time );
        break;
    }

    case SelectionNotify: {
        XSelectionEvent *e = &event->xselection;
        fgWarning( "%s: requestor=0x%x, selection=0x%x, target=0x%x, "
                   "property=%lu, time=%lu", fghTypeToString( e->type ),
                   e->requestor, (unsigned long)e->selection,
                   (unsigned long)e->target, (unsigned long)e->property,
                   (unsigned long)e->time );
        break;
    }

    case ColormapNotify: {
        XColormapEvent *e = &event->xcolormap;
        fgWarning( "%s: window=0x%x, colormap=%lu, new=%s, state=%s",
                   fghTypeToString( e->type ), e->window,
                   (unsigned long)e->colormap, fghBoolToString( e->new ),
                   fghColormapStateToString( e->state ) );
        break;
    }

    case ClientMessage: {
        XClientMessageEvent *e = &event->xclient;
        char buf[ 61 ];
        char* p = buf;
        char* end = buf + sizeof( buf );
        int i;
        switch( e->format ) {
        case 8:
          for ( i = 0; i < 20; i++, p += 3 ) {
                snprintf( p, end - p, " %02x", e->data.b[ i ] );
            }
            break;
        case 16:
            for ( i = 0; i < 10; i++, p += 5 ) {
                snprintf( p, end - p, " %04x", e->data.s[ i ] );
            }
            break;
        case 32:
            for ( i = 0; i < 5; i++, p += 9 ) {
                snprintf( p, end - p, " %08lx", e->data.l[ i ] );
            }
            break;
        }
        *p = '\0';
        fgWarning( "%s: window=0x%x, message_type=%lu, format=%d, data=(%s )",
                   fghTypeToString( e->type ), e->window,
                   (unsigned long)e->message_type, e->format, buf );
        break;
    }

    case MappingNotify: {
        XMappingEvent *e = &event->xmapping;
        fgWarning( "%s: window=0x%x, request=%s, first_keycode=%d, count=%d",
                   fghTypeToString( e->type ), e->window,
                   fghMappingRequestToString( e->request ), e->first_keycode,
                   e->count );
        break;
    }

    default: {
        fgWarning( "%s", fghTypeToString( event->type ) );
        break;
    }
    }
}

#endif

/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*
 * Executes a single iteration in the freeglut processing loop.
 */
void FGAPIENTRY glutMainLoopEvent( void )
{
#if TARGET_HOST_POSIX_X11
#elif TARGET_HOST_MS_WINDOWS
#endif

    if( fgState.Timers.First )
        fghCheckTimers( );
    fghCheckJoystickPolls( );
    fghDisplayAll( );

    fgCloseWindows( );
}

/*
 * Enters the freeglut processing loop.
 * Stays until the "ExecState" changes to "GLUT_EXEC_STATE_STOP".
 */
void FGAPIENTRY glutMainLoop( void )
{
    int action;

#if TARGET_HOST_MS_WINDOWS
    SFG_Window *window = (SFG_Window *)fgStructure.Windows.First ;
#endif

    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutMainLoop" );

#if TARGET_HOST_MS_WINDOWS
    /*
     * Processing before the main loop:  If there is a window which is open and
     * which has a visibility callback, call it.  I know this is an ugly hack,
     * but I'm not sure what else to do about it.  Ideally we should leave
     * something uninitialized in the create window code and initialize it in
     * the main loop, and have that initialization create a "WM_ACTIVATE"
     * message.  Then we would put the visibility callback code in the
     * "case WM_ACTIVATE" block below.         - John Fay -- 10/24/02
     */
    while( window )
    {
        if ( FETCH_WCB( *window, Visibility ) )
        {
            SFG_Window *current_window = fgStructure.CurrentWindow ;

            INVOKE_WCB( *window, Visibility, ( window->State.Visible ) );
            fgSetWindow( current_window );
        }

        window = (SFG_Window *)window->Node.Next ;
    }
#endif

    fgState.ExecState = GLUT_EXEC_STATE_RUNNING ;
    while( fgState.ExecState == GLUT_EXEC_STATE_RUNNING )
    {
        SFG_Window *window;

        glutMainLoopEvent( );
        /*
         * Step through the list of windows, seeing if there are any
         * that are not menus
         */
        for( window = ( SFG_Window * )fgStructure.Windows.First;
             window;
             window = ( SFG_Window * )window->Node.Next )
            if ( ! ( window->IsMenu ) )
                break;

        if( ! window )
            fgState.ExecState = GLUT_EXEC_STATE_STOP;
        else
        {
            if( fgState.IdleCallback )
            {
                if( fgStructure.CurrentWindow &&
                    fgStructure.CurrentWindow->IsMenu )
                    /* fail safe */
                    fgSetWindow( window );
                fgState.IdleCallback( );
            }

            fghSleepForEvents( );
        }
    }

    /*
     * When this loop terminates, destroy the display, state and structure
     * of a freeglut session, so that another glutInit() call can happen
     *
     * Save the "ActionOnWindowClose" because "fgDeinitialize" resets it.
     */
    action = fgState.ActionOnWindowClose;
    fgDeinitialize( );
    if( action == GLUT_ACTION_EXIT )
        exit( 0 );
}

/*
 * Leaves the freeglut processing loop.
 */
void FGAPIENTRY glutLeaveMainLoop( void )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutLeaveMainLoop" );
    fgState.ExecState = GLUT_EXEC_STATE_STOP ;
}



/*** END OF FILE ***/
