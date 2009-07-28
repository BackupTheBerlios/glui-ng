/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

  glui_glut_window.cpp : a wrapper class to use glut as an event generator

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
#define MODULE_KEY "GLUI_DEBUG_XGL"

/////////////////////////////////////////////////////////////////////
X11Display::X11Display()
{
        _X11Display(getenv("DISPLAY"));
}
void X11Display::X11Display(char* name)
{
        _X11Display(name);
}

void X11Display::_X11Display(char* name)
{
        disp = XOpenDisplay(name);
        if (! disp) throw exception(__func__,EINVAL);
}




void X11Window::start_routine(void* args)
{
        ::XEvent event;

int XWindowEvent(Display *display, window, EventMask, XEvent *event_return);
        while(  XWindowEvent(Display *display, window, EventMask, XEvent *event_return) )
        {
                XNextEvent( fgDisplay.Display, &event );
                debug::Instance()->PrintEvent(MODULE_KEY, event );

                switch( event.type )
                {
                        case ClientMessage:
                                /* Destroy the window when the WM_DELETE_WINDOW message arrives */
                                if( (Atom) event.xclient.data.l[ 0 ] == fgDisplay.DeleteWindow )
                                {
                                        GETWINDOW( xclient );

                                        fgDestroyWindow ( window );

                                        if( fgState.ActionOnWindowClose == GLUT_ACTION_EXIT )
                                        {
                                                fgDeinitialize( );
                                                exit( 0 );
                                        }
                                        else if( fgState.ActionOnWindowClose == GLUT_ACTION_GLUTMAINLOOP_RETURNS )
                                                fgState.ExecState = GLUT_EXEC_STATE_STOP;

                                        return;
                                }
                                break;

                                /*
                                 * CreateNotify causes a configure-event so that sub-windows are
                                 * handled compatibly with GLUT.  Otherwise, your sub-windows
                                 * (in freeglut only) will not get an initial reshape event,
                                 * which can break things.
                                 *
                                 * GLUT presumably does this because it generally tries to treat
                                 * sub-windows the same as windows.
                                 */
                        case CreateNotify:
                        case ConfigureNotify:
                                {
                                        int width, height;
                                        if( event.type == CreateNotify ) {
                                                GETWINDOW( xcreatewindow );
                                                width = event.xcreatewindow.width;
                                                height = event.xcreatewindow.height;
                                        } else {
                                                GETWINDOW( xconfigure );
                                                width = event.xconfigure.width;
                                                height = event.xconfigure.height;
                                        }

                                        if( ( width != window->State.OldWidth ) ||
                                                        ( height != window->State.OldHeight ) )
                                        {
                                                SFG_Window *current_window = fgStructure.CurrentWindow;

                                                window->State.OldWidth = width;
                                                window->State.OldHeight = height;
                                                if( FETCH_WCB( *window, Reshape ) )
                                                        INVOKE_WCB( *window, Reshape, ( width, height ) );
                                                else
                                                {
                                                        fgSetWindow( window );
                                                        glViewport( 0, 0, width, height );
                                                }
                                                glutPostRedisplay( );
                                                if( window->IsMenu )
                                                        fgSetWindow( current_window );
                                        }
                                }
                                break;

                        case DestroyNotify:
                                /*
                                 * This is sent to confirm the XDestroyWindow call.
                                 *
                                 * XXX WHY is this commented out?  Should we re-enable it?
                                 */
                                /* fgAddToWindowDestroyList ( window ); */
                                break;

                        case Expose:
                                /*
                                 * We are too dumb to process partial exposes...
                                 *
                                 * XXX Well, we could do it.  However, it seems to only
                                 * XXX be potentially useful for single-buffered (since
                                 * XXX double-buffered does not respect viewport when we
                                 * XXX do a buffer-swap).
                                 *
                                 */
                                if( event.xexpose.count == 0 )
                                {
                                        GETWINDOW( xexpose );
                                        window->State.Redisplay = GL_TRUE;
                                }
                                break;

                        case MapNotify:
                                break;

                        case UnmapNotify:
                                /* We get this when iconifying a window. */
                                GETWINDOW( xunmap );
                                INVOKE_WCB( *window, WindowStatus, ( GLUT_HIDDEN ) );
                                window->State.Visible = GL_FALSE;
                                break;

                        case MappingNotify:
                                /*
                                 * Have the client's keyboard knowledge updated (xlib.ps,
                                 * page 206, says that's a good thing to do)
                                 */
                                XRefreshKeyboardMapping( (XMappingEvent *) &event );
                                break;

                        case VisibilityNotify:
                                {
                                        /*
                                         * Sending this event, the X server can notify us that the window
                                         * has just acquired one of the three possible visibility states:
                                         * VisibilityUnobscured, VisibilityPartiallyObscured or
                                         * VisibilityFullyObscured. Note that we DO NOT receive a
                                         * VisibilityNotify event when iconifying a window, we only get an
                                         * UnmapNotify then.
                                         */
                                        GETWINDOW( xvisibility );
                                        switch( event.xvisibility.state )
                                        {
                                                case VisibilityUnobscured:
                                                        INVOKE_WCB( *window, WindowStatus, ( GLUT_FULLY_RETAINED ) );
                                                        window->State.Visible = GL_TRUE;
                                                        break;

                                                case VisibilityPartiallyObscured:
                                                        INVOKE_WCB( *window, WindowStatus,
                                                                        ( GLUT_PARTIALLY_RETAINED ) );
                                                        window->State.Visible = GL_TRUE;
                                                        break;

                                                case VisibilityFullyObscured:
                                                        INVOKE_WCB( *window, WindowStatus, ( GLUT_FULLY_COVERED ) );
                                                        window->State.Visible = GL_FALSE;
                                                        break;

                                                default:
                                                        fgWarning( "Unknown X visibility state: %d",
                                                                        event.xvisibility.state );
                                                        break;
                                        }
                                }
                                break;

                        case EnterNotify:
                        case LeaveNotify:
                                GETWINDOW( xcrossing );
                                GETMOUSE( xcrossing );
                                if( ( event.type == LeaveNotify ) && window->IsMenu &&
                                                window->ActiveMenu && window->ActiveMenu->IsActive )
                                        fgUpdateMenuHighlight( window->ActiveMenu );

                                INVOKE_WCB( *window, Entry, ( ( EnterNotify == event.type ) ?
                                                        GLUT_ENTERED :
                                                        GLUT_LEFT ) );
                                break;

                        case MotionNotify:
                                {
                                        GETWINDOW( xmotion );
                                        GETMOUSE( xmotion );

                                        if( window->ActiveMenu )
                                        {
                                                if( window == window->ActiveMenu->ParentWindow )
                                                {
                                                        window->ActiveMenu->Window->State.MouseX =
                                                                event.xmotion.x_root - window->ActiveMenu->X;
                                                        window->ActiveMenu->Window->State.MouseY =
                                                                event.xmotion.y_root - window->ActiveMenu->Y;
                                                }

                                                fgUpdateMenuHighlight( window->ActiveMenu );

                                                break;
                                        }

                                        /*
                                         * XXX For more than 5 buttons, just check {event.xmotion.state},
                                         * XXX rather than a host of bit-masks?  Or maybe we need to
                                         * XXX track ButtonPress/ButtonRelease events in our own
                                         * XXX bit-mask?
                                         */
                                        fgState.Modifiers = fghGetXModifiers( event.xmotion.state );
                                        if ( event.xmotion.state & ( Button1Mask | Button2Mask | Button3Mask | Button4Mask | Button5Mask ) ) {
                                                INVOKE_WCB( *window, Motion, ( event.xmotion.x,
                                                                        event.xmotion.y ) );
                                        } else {
                                                INVOKE_WCB( *window, Passive, ( event.xmotion.x,
                                                                        event.xmotion.y ) );
                                        }
                                        fgState.Modifiers = INVALID_MODIFIERS;
                                }
                                break;

                        case ButtonRelease:
                        case ButtonPress:
                                {
                                        GLboolean pressed = GL_TRUE;
                                        int button;

                                        if( event.type == ButtonRelease )
                                                pressed = GL_FALSE ;

                                        /*
                                         * A mouse button has been pressed or released. Traditionally,
                                         * break if the window was found within the freeglut structures.
                                         */
                                        GETWINDOW( xbutton );
                                        GETMOUSE( xbutton );

                                        /*
                                         * An X button (at least in XFree86) is numbered from 1.
                                         * A GLUT button is numbered from 0.
                                         * Old GLUT passed through buttons other than just the first
                                         * three, though it only gave symbolic names and official
                                         * support to the first three.
                                         */
                                        button = event.xbutton.button - 1;

                                        /*
                                         * Do not execute the application's mouse callback if a menu
                                         * is hooked to this button.  In that case an appropriate
                                         * private call should be generated.
                                         */
                                        if( fgCheckActiveMenu( window, button, pressed,
                                                                event.xbutton.x_root, event.xbutton.y_root ) )
                                                break;

                                        /*
                                         * Check if there is a mouse or mouse wheel callback hooked to the
                                         * window
                                         */
                                        if( ! FETCH_WCB( *window, Mouse ) &&
                                                        ! FETCH_WCB( *window, MouseWheel ) )
                                                break;

                                        fgState.Modifiers = fghGetXModifiers( event.xbutton.state );

                                        /* Finally execute the mouse or mouse wheel callback */
                                        if( ( button < glutDeviceGet ( GLUT_NUM_MOUSE_BUTTONS ) ) || ( ! FETCH_WCB( *window, MouseWheel ) ) )
                                                INVOKE_WCB( *window, Mouse, ( button,
                                                                        pressed ? GLUT_DOWN : GLUT_UP,
                                                                        event.xbutton.x,
                                                                        event.xbutton.y )
                                                          );
                                        else
                                        {
                                                /*
                                                 * Map 4 and 5 to wheel zero; EVEN to +1, ODD to -1
                                                 *  "  6 and 7 "    "   one; ...
                                                 *
                                                 * XXX This *should* be behind some variables/macros,
                                                 * XXX since the order and numbering isn't certain
                                                 * XXX See XFree86 configuration docs (even back in the
                                                 * XXX 3.x days, and especially with 4.x).
                                                 *
                                                 * XXX Note that {button} has already been decremeted
                                                 * XXX in mapping from X button numbering to GLUT.
                                                 */
                                                int wheel_number = (button - glutDeviceGet ( GLUT_NUM_MOUSE_BUTTONS )) / 2;
                                                int direction = -1;
                                                if( button % 2 )
                                                        direction = 1;

                                                if( pressed )
                                                        INVOKE_WCB( *window, MouseWheel, ( wheel_number,
                                                                                direction,
                                                                                event.xbutton.x,
                                                                                event.xbutton.y )
                                                                  );
                                        }
                                        fgState.Modifiers = INVALID_MODIFIERS;
                                }
                                break;

                        case KeyRelease:
                        case KeyPress:
                                {
                                        FGCBKeyboard keyboard_cb;
                                        FGCBSpecial special_cb;

                                        GETWINDOW( xkey );
                                        GETMOUSE( xkey );

                                        /* Detect auto repeated keys, if configured globally or per-window */

                                        if ( fgState.KeyRepeat==GLUT_KEY_REPEAT_OFF || window->State.IgnoreKeyRepeat==GL_TRUE )
                                        {
                                                if (event.type==KeyRelease)
                                                {
                                                        /*
                                                         * Look at X11 keystate to detect repeat mode.
                                                         * While X11 says the key is actually held down, we'll ignore KeyRelease/KeyPress pairs.
                                                         */

                                                        char keys[32];
                                                        XQueryKeymap( fgDisplay.Display, keys ); /* Look at X11 keystate to detect repeat mode */

                                                        if ( event.xkey.keycode<256 )            /* XQueryKeymap is limited to 256 keycodes    */
                                                        {
                                                                if ( keys[event.xkey.keycode>>3] & (1<<(event.xkey.keycode%8)) )
                                                                        window->State.KeyRepeating = GL_TRUE;
                                                                else
                                                                        window->State.KeyRepeating = GL_FALSE;
                                                        }
                                                }
                                        }
                                        else
                                                window->State.KeyRepeating = GL_FALSE;

                                        /* Cease processing this event if it is auto repeated */

                                        if (window->State.KeyRepeating)
                                        {
                                                if (event.type == KeyPress) window->State.KeyRepeating = GL_FALSE;
                                                break;
                                        }

                                        if( event.type == KeyPress )
                                        {
                                                keyboard_cb = (FGCBKeyboard)( FETCH_WCB( *window, Keyboard ));
                                                special_cb  = (FGCBSpecial) ( FETCH_WCB( *window, Special  ));
                                        }
                                        else
                                        {
                                                keyboard_cb = (FGCBKeyboard)( FETCH_WCB( *window, KeyboardUp ));
                                                special_cb  = (FGCBSpecial) ( FETCH_WCB( *window, SpecialUp  ));
                                        }

                                        /* Is there a keyboard/special callback hooked for this window? */
                                        if( keyboard_cb || special_cb )
                                        {
                                                XComposeStatus composeStatus;
                                                char asciiCode[ 32 ];
                                                KeySym keySym;
                                                int len;

                                                /* Check for the ASCII/KeySym codes associated with the event: */
                                                len = XLookupString( &event.xkey, asciiCode, sizeof(asciiCode),
                                                                &keySym, &composeStatus
                                                                );

                                                /* GLUT API tells us to have two separate callbacks... */
                                                if( len > 0 )
                                                {
                                                        /* ...one for the ASCII translateable keypresses... */
                                                        if( keyboard_cb )
                                                        {
                                                                fgSetWindow( window );
                                                                fgState.Modifiers = fghGetXModifiers( event.xkey.state );
                                                                keyboard_cb( asciiCode[ 0 ],
                                                                                event.xkey.x, event.xkey.y
                                                                           );
                                                                fgState.Modifiers = INVALID_MODIFIERS;
                                                        }
                                                }
                                                else
                                                {
                                                        int special = -1;

                                                        /*
                                                         * ...and one for all the others, which need to be
                                                         * translated to GLUT_KEY_Xs...
                                                         */
                                                        switch( keySym )
                                                        {
                                                                case XK_F1:     special = GLUT_KEY_F1;     break;
                                                                case XK_F2:     special = GLUT_KEY_F2;     break;
                                                                case XK_F3:     special = GLUT_KEY_F3;     break;
                                                                case XK_F4:     special = GLUT_KEY_F4;     break;
                                                                case XK_F5:     special = GLUT_KEY_F5;     break;
                                                                case XK_F6:     special = GLUT_KEY_F6;     break;
                                                                case XK_F7:     special = GLUT_KEY_F7;     break;
                                                                case XK_F8:     special = GLUT_KEY_F8;     break;
                                                                case XK_F9:     special = GLUT_KEY_F9;     break;
                                                                case XK_F10:    special = GLUT_KEY_F10;    break;
                                                                case XK_F11:    special = GLUT_KEY_F11;    break;
                                                                case XK_F12:    special = GLUT_KEY_F12;    break;

                                                                case XK_KP_Left:
                                                                case XK_Left:   special = GLUT_KEY_LEFT;   break;
                                                                case XK_KP_Right:
                                                                case XK_Right:  special = GLUT_KEY_RIGHT;  break;
                                                                case XK_KP_Up:
                                                                case XK_Up:     special = GLUT_KEY_UP;     break;
                                                                case XK_KP_Down:
                                                                case XK_Down:   special = GLUT_KEY_DOWN;   break;

                                                                case XK_KP_Prior:
                                                                case XK_Prior:  special = GLUT_KEY_PAGE_UP; break;
                                                                case XK_KP_Next:
                                                                case XK_Next:   special = GLUT_KEY_PAGE_DOWN; break;
                                                                case XK_KP_Home:
                                                                case XK_Home:   special = GLUT_KEY_HOME;   break;
                                                                case XK_KP_End:
                                                                case XK_End:    special = GLUT_KEY_END;    break;
                                                                case XK_KP_Insert:
                                                                case XK_Insert: special = GLUT_KEY_INSERT; break;

                                                                case XK_Num_Lock :  special = GLUT_KEY_NUM_LOCK;  break;
                                                                case XK_KP_Begin :  special = GLUT_KEY_BEGIN;     break;
                                                                case XK_KP_Delete:  special = GLUT_KEY_DELETE;    break;
                                                        }

                                                        /*
                                                         * Execute the callback (if one has been specified),
                                                         * given that the special code seems to be valid...
                                                         */
                                                        if( special_cb && (special != -1) )
                                                        {
                                                                fgSetWindow( window );
                                                                fgState.Modifiers = fghGetXModifiers( event.xkey.state );
                                                                special_cb( special, event.xkey.x, event.xkey.y );
                                                                fgState.Modifiers = INVALID_MODIFIERS;
                                                        }
                                                }
                                        }
                                }
                                break;

                        case ReparentNotify:
                                break; /* XXX Should disable this event */

                                /* Not handled */
                        case GravityNotify:
                                break;

                        default:
                                fgWarning ("Unknown X event type: %d\n", event.type);
                                break;
                }
        }


}
