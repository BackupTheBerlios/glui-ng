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
#if defined(GLUI_FREEGLUT)

// FreeGLUT does not yet work perfectly with GLUI
//  - use at your own risk.

#include <GL/freeglut.h>

#elif defined(GLUI_OPENGLUT)

// OpenGLUT does not yet work properly with GLUI
//  - use at your own risk.

#include <GL/openglut.h>

#else

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#endif
#include <GL/glui/glut_window.h>
#include <GL/glui/MasterObject.h>
#include <GL/glui/debug.h>
#include <GL/glui/themes.h>
#include <GL/glui/drawinghelpers.h>

#define XK_MISCELLANY
#define XK_LATIN1
#include <X11/keysymdef.h>
using namespace GLUI;

#define MODULE_KEY  "GLUI_DEBUG_GLUTWINDOW"

///////////////////////////////////////////////////////////////////////
GlutDisplay::GlutDisplay(char* name)
{
}
///////////////////////////////////////////////////////////////////////
void GlutWindow::draw()
{
    //    Draw GLUI window
    glLoadIdentity();
    this->SetOrthoProjection();
    glTranslatef(x, y, BOTTOM_VIEWPORT + 1);
    drawinghelpers::draw_box( this->Width(),
            this->Height());
}
///////////////////////////////////////////////////////////////////////
WindowId GlutWindow::GetWindowId()
{
    return GlutWindowId;
}


///////////////////////////////////////////////////////////////////////
int GlutScreen::Depth()
{
#warning "implement real Depth check"
    return 24;
}

//////////////////////////////////////////////////////////////////////
WindowId GlutScreen::RootWindow()
{
     return 0;
}

///////////////////////////////////////////////////////////////////////
_Screen* GlutDisplay::DefaultScreen()
{
    return     &defaultscreen;
}

///////////////////////////////////////////////////////////////////////
//

bool GlutWindow::glutinitialized = false;

///////////////////////////////////////////////////////////////////////
void  GlutWindow::XMapWindow()
{
  glutSetWindow(GlutWindowId);
  MasterObject::Instance()->pack(0, 0); //repack all master windows
  glutShowWindow();
  mapped = true;
  drawinghelpers::PostRedisplay(this);
}

void GlutWindow::XMapRaised()
{
#warning "TODO"
}

void GlutWindow::XMapSubwindows()
{
#warning "TODO"
}

///////////////////////////////////////////////////////////////////////
void GlutWindow::XUnmapWindow( void )
{
  this->focussed = NULL;
  glutSetWindow(GlutWindowId);
  glutHideWindow();
}

void GlutWindow::XUnmapSubwindows()
{
#warning "TODO"
}



//////////////////////////////////////////////////////////////////////
GlutWindow::GlutWindow(Display* display, WindowId parent,
        int x, int y,
        unsigned int width, unsigned int height,
        unsigned int border_width,
        int depth,
        class_type _class,
        Visual *visual,
        unsigned long valuemask,
        XSetWindowAttributes *attributes )
{
    _GlutWindow(display, parent, x, y,
        width, height, border_width, depth,
        _class, visual, valuemask,
        attributes );
}

GlutWindow::GlutWindow(Display *display, WindowId parent,
        int x, int y,
        unsigned int width, unsigned int height,
        unsigned int border_width,
        unsigned long border,
        unsigned long background )
{
    _GlutWindow(display, parent,
        x, y,
        width, height,
        border_width,
        24, //int depth,
        InputOutputWin, //class_type _class,
        NULL, //Visual *visual,
        0, //unsigned long valuemask,
        NULL); // XSetWindowAttributes *attributes )
}

#warning "TODO: copy constructor using WindowId, throw EINVAL if already registered"

int GlutWindow::_GlutWindow(Display* display, WindowId parent,
        int x, int y,
        unsigned int width, unsigned int height,
        unsigned int border_width,
        int depth,
        class_type _class,
        Visual *visual,
        unsigned long valuemask,
        XSetWindowAttributes *attributes )
{
    GlutWindow* win= MasterObject::Instance()->FindWindow(parent);
    mapped      = false;
    y_off_top   = 0;
    y_off_bot   = 0;
    x_off_left  = 0;
    x_off_right = 0;
      {
        int argc=1;
        char* argv[1] = { "glutnoname" };
        GlutWindow::init(&argc, argv);
      }
    if ( win == NULL ) {  // not a subwindow, creating a new top-level window
        int old_glut_window = glutGetWindow();

        glutInitWindowSize( width, height);
        if ( x >= 0 || y >= 0 )
            glutInitWindowPosition( x, y );
        glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        this->GlutWindowId = glutCreateWindow(" ");


        if ( old_glut_window > 0 )
            glutSetWindow( old_glut_window );
        else
            glutSetWindow(GlutWindowId);

    }
    else // *is* a subwindow
    {
        int old_glut_window = glutGetWindow();

        GlutWindowId = glutCreateSubWindow(win->GetWindowId(), x, y, width, height);
        win->add_control(this);

        if ( old_glut_window > 0 )
            glutSetWindow( old_glut_window );

    }
    int rc = MasterObject::Instance()->add_control(this);
    if (rc)
    {
        throw rc;
    }
    if (width != 0  && height != 0)
    {
        set_resize_policy(FixedSize);
        set_size(Size(width, height));
    }
    else
    {
        update_size();
        pack(x,y);
    }

    //init glut callbacks
    glutDisplayFunc (display_func);
    glutReshapeFunc (reshape_func);
    glutKeyboardFunc (keyboard_func);
    glutSpecialFunc (special_func);
    glutMouseFunc (mouse_func);
    glutMotionFunc (motion_func);
    glutPassiveMotionFunc (passive_motion_func);
    glutEntryFunc (entry_func);
    glutVisibilityFunc (visibility_func);
    glutIdleFunc (idle_func);

}

GlutWindow::~GlutWindow()
{
#warning "Todo : delete childs. close the window"
}

int GlutWindow::init(int* argc, char** argv)
{
  if(glutinitialized == false)
    {
        glutInit(argc, argv);
        glutinitialized = true;
    }

}

int GLUIInit(int* argc, char** argv)
{
   return GlutWindow::init(argc, argv);
}

///////////////////////////////////////////////////////////////////////////////
int GlutWindow::AddEvent (::XEvent *event)
{
    switch (event->type)
    {
        case Expose : return AddEvent((::XExposeEvent*) event);
        case DestroyNotify :  return AddEvent((::XDestroyWindowEvent*) event);
        case ResizeRequest: return AddEvent((::XResizeRequestEvent*) event);
    }

    return EINVAL;
}

int GlutWindow::AddEvent(::XResizeRequestEvent *event)
{
    IN("");
    this->pack(x, y);

    if ( event->width  != this->CurrentSize.size.w ||
            event->height != this->CurrentSize.size.h ) {
        this->CurrentSize.size.w = event->width;
        this->CurrentSize.size.h = event->height;
        glutSetWindow( this->GlutWindowId );
        glutReshapeWindow( this->CurrentSize.size.w, this->CurrentSize.size.h );
    }
    else {
    }

    glViewport( 0, 0, this->CurrentSize.size.w, this->CurrentSize.size.h);

    MSG("%d: %d\n", glutGetWindow(), this->flags );

    glutPostRedisplay();
    OUT("");
    return 0;
}


int GlutWindow::AddEvent(::XExposeEvent *event)
{
    IN("");
    if (mapped)
    {
        int       win_w, win_h;

        // SUBTLE: on freeGLUT, the correct window is always already set.
        // But older versions of GLUT need this call, or else subwindows
        // don't update properly when resizing or damage-painting.
        glutSetWindow( this->GlutWindowId );

        // Set up OpenGL state for widget drawing
        glEnable( GL_DEPTH_TEST );
        glDepthFunc(GL_LEQUAL);
        //glCullFace( GL_BACK );
        //glDisable( GL_CULL_FACE );
        glEnable ( GL_COLOR_MATERIAL );
        glEnable ( GL_NORMALIZE );
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glShadeModel(GL_SMOOTH);

        theme::Instance()->DoLightning();
        SetOrthoProjection();


        this->SetCurrentDrawBuffer();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

        //update sizes and positions
        this->update_size();

        // Check here if the window needs resizing
        win_w = glutGet( GLUT_WINDOW_WIDTH );
        win_h = glutGet( GLUT_WINDOW_HEIGHT );
        if ( win_w != this->Width() || win_h != this->Height() ) {
            glutReshapeWindow( this->Width(), this->Height() );
        }

        Container::AddEvent (event);

        switch (drawinghelpers::get_buffer_mode()) {
            case drawinghelpers::buffer_front: // Make sure drawing gets to screen
                glFlush();
                break;
            case drawinghelpers::buffer_back: // Bring back buffer to front
                glutSwapBuffers();
                break;
        }
        glutPostRedisplay();
    }
    OUT("");
    return 0;
}

int GlutWindow::AddEvent(::XDestroyWindowEvent *event)
{
#warning "USE container destructor"
    Node* child = first_child();
    while (child)
    {
        Node* next = child->next();
        delete child;
        child = next;
    }
    delete this;
    return 0;
}


int GlutWindow::AddEvent(::XKeyEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int GlutWindow::AddEvent(::XButtonEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int GlutWindow::AddEvent(::XMotionEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int GlutWindow::AddEvent(::XCrossingEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}


int GlutWindow::AddEvent(::XMapEvent* event)
{
    ::XExposeEvent expose;
    expose.type = Expose;
    Container::AddEvent((::XEvent*) event);
    this->AddEvent(&expose);
}


int GlutWindow::AddEvent(::XUnmapEvent* event)
{
    Container::AddEvent((::XEvent*) event);
}

int GlutWindow::set_size( Size sz, Size min) //replace with a XResizeRequestEvent
{
    Control::set_size(sz,min);
    glutReshapeWindow( this->Width(), this->Height() );
}




/********************************************** glui_display_func() ********/
void GlutWindow::display_func (void)
{
    ::XExposeEvent event;
        event.type   = Expose;
    IN("");
    GlutWindow* win= MasterObject::Instance()->FindWindow(glutGetWindow ());

    if (win)
    {
        win->AddEvent(&event);
    }
    OUT("");
}



/********************************************** glui_reshape_func() ********/
void GlutWindow::reshape_func (int w, int h)
{
    ::XResizeRequestEvent event;
        event.type   = ResizeRequest;
        event.width  = w;
        event.height = h;

    IN("");

    /***  First check if this is main glut window ***/
    GlutWindow* glut_window = MasterObject::Instance()->FindWindow(glutGetWindow ());
    if (glut_window)
    {
        glut_window->AddEvent(&event);
    }
    OUT("");
}





#warning "factorise
/********************************************** glui_keyboard_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::keyboard_func (unsigned char key, int x, int y)
{

    IN("");
    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);
    y = win_h - y;
    ::XKeyEvent event;
    event.type=KeyPress;
    event.keycode=key; //first 256 char are reserved for non modifier keys
    event.x=x;
    event.y=y;

    int current_window = glutGetWindow ();
    GlutWindow* glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());


    if (glut_window)
    {
        MSG("key: %d(%d,%d) modifier %d\n", key, x, y, glutGetModifiers());
        event.state=glut_window->KeyModifierState;
        glut_window->AddEvent(&event);
    }
    OUT("");
}


/************************************************ glui_special_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::special_func (int key, int x, int y)
{

    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);
    y = win_h - y;
    ::XKeyEvent event;
    event.type = KeyPress;
    event.keycode = key << KeyModifierShift ; //first 256 char are reserved for non modifier keys
    event.x = x;
    event.y = y;


    int current_window = glutGetWindow ();
    GlutWindow* glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
            int glutModifiers = glutGetModifiers();
            glut_window->KeyModifierState &= ! ( ControlMask | ShiftMask | Mod1Mask );
            if ( glutModifiers | GLUT_ACTIVE_SHIFT ) glut_window->KeyModifierState | ShiftMask;
            if ( glutModifiers | GLUT_ACTIVE_CTRL  ) glut_window->KeyModifierState | ControlMask;
            if ( glutModifiers | GLUT_ACTIVE_ALT   ) glut_window->KeyModifierState | Mod1Mask;

            MSG("key: %d(%d,%d) modifier %d\n", key, x, y, glutModifiers/*glut_window->KeyModifierState*/);
            event.state=glut_window->KeyModifierState;
            glut_window->AddEvent(&event);

    }
}

/********************************************** glui_mouse_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::mouse_func (int button, int state, int x, int y)
{
    int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);

    y = win_h - y;
    ::XButtonEvent event;
    event.type =

    event.x=x;
    event.y=y;


    int current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
        if (state == GLUT_DOWN)
        {
            event.type = ButtonPress;
            glut_window->KeyModifierState |= (Button1Mask << ( button - Button1 ) );
        }
        else
        {
            event.type = ButtonRelease;
            glut_window->KeyModifierState &= ! (Button1Mask << ( button - Button1 ) );
        }
        int glutModifiers = glutGetModifiers();
        glut_window->KeyModifierState &= ! ( ControlMask | ShiftMask | Mod1Mask );
        if ( glutModifiers | GLUT_ACTIVE_SHIFT ) glut_window->KeyModifierState | ShiftMask;
        if ( glutModifiers | GLUT_ACTIVE_CTRL  ) glut_window->KeyModifierState | ControlMask;
        if ( glutModifiers | GLUT_ACTIVE_ALT   ) glut_window->KeyModifierState | Mod1Mask;

        event.state=glut_window->KeyModifierState;
        glut_window->AddEvent(&event);
    }
}


/********************************************** glui_motion_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::motion_func (int x, int y)
{
        int win_w = glutGet (GLUT_WINDOW_WIDTH);
    int win_h = glutGet (GLUT_WINDOW_HEIGHT);

    y = win_h - y;
    ::XMotionEvent event;
    event.type = MotionNotify;

    event.x=x;
    event.y=y;


    int current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
        event.state=glut_window->KeyModifierState;
        glut_window->AddEvent(&event);
    }
}


/**************************************** glui_passive_motion_func() ********/
//GLUI use Y axis up (0,0) is bottom left corner as in OpenGl
void GlutWindow::passive_motion_func (int x, int y)
{
    motion_func (x,y);
}


/********************************************** glui_entry_func() ********/
void GlutWindow::entry_func (int state)
{
    ::XCrossingEvent event;
    if ( state == GLUT_LEFT )
    {
        event.type = EnterNotify;
    }
    else
    {
        event.type = LeaveNotify;
    }
#warning "complete the structure with other information"


    int current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
        event.state=glut_window->KeyModifierState;
        glut_window->AddEvent(&event);
    }

}




/******************************************** glui_visibility_func() ********/
void GlutWindow::visibility_func (int state)
{
    ::XMapEvent mapevent;
    ::XUnmapEvent unmapevent;

    mapevent.type = MapNotify;
    unmapevent.type = UnmapNotify;
    #warning "complete the structure with other information"


    IN("");
    /*  fflush( stdout );          */

    int current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
        if ( state == GLUT_VISIBLE )
        {
            glut_window->AddEvent(&mapevent);
        }
        else
        {
            glut_window->AddEvent(&unmapevent);
        }
    }
    OUT("");


}


/********************************************** glui_idle_func() ********/
/* Send idle event to each glui, then to the main window            */
void GlutWindow::idle (void)
{
        struct timespec sleeptime = { 0, 100000000 };
        nanosleep(&sleeptime, NULL);
}


void GlutWindow::idle_func (void)
{
    int current_window = glutGetWindow ();
    GlutWindow *glut_window = MasterObject::Instance()->FindWindow(glutGetWindow());

    if (glut_window)
    {
        glut_window->idle();
    }

}

////////////////////////////////////////////////////////////////////
KeySym GlutWindow::XLookupKeysym(::XKeyEvent *key_event, int index)
{
/*    switch (key_event->keycode)
    {

        case GLUT_KEY_F1 << KeyModifierShift : return XK_F1;
        case GLUT_KEY_F2 << KeyModifierShift : return XK_F2;
        case GLUT_KEY_F3 << KeyModifierShift : return XK_F3;
        case GLUT_KEY_F4 << KeyModifierShift : return XK_F4;
        case GLUT_KEY_F5 << KeyModifierShift : return XK_F5;
        case GLUT_KEY_F6 << KeyModifierShift : return XK_F6;
        case GLUT_KEY_F7 << KeyModifierShift : return XK_F7;
        case GLUT_KEY_F8 << KeyModifierShift : return XK_F8;
        case GLUT_KEY_F9 << KeyModifierShift : return XK_F9;
        case GLUT_KEY_F10 << KeyModifierShift : return XK_F10;
        case GLUT_KEY_F11 << KeyModifierShift : return XK_F11;
        case GLUT_KEY_F12 << KeyModifierShift : return XK_F12;
        case GLUT_KEY_UP << KeyModifierShift : return XK_Up;
        case GLUT_KEY_RIGHT << KeyModifierShift : return XK_Right;
        case GLUT_KEY_DOWN << KeyModifierShift : return XK_Down;
        case GLUT_KEY_PAGE_UP << KeyModifierShift : return XK_Page_Up;
        case GLUT_KEY_PAGE_DOWN << KeyModifierShift : return XK_Page_Down;
        case GLUT_KEY_HOME << KeyModifierShift : return XK_Home;
        case GLUT_KEY_END << KeyModifierShift : return XK_End;
        case GLUT_KEY_INSERT << KeyModifierShift : return XK_Insert;
        case ' ' : return XK_space;
        case '!' : return XK_exclam;
        case '"' : return XK_quotedbl;
        case '#' : return XK_numbersign;
        case '$' : return XK_dollar;
        case '%' : return XK_percent;
        case '&' : return XK_ampersand;
        case '\'': return XK_apostrophe;
        case '(' : return XK_parenleft;
        case ')' : return XK_parenright;
        case '*' : return XK_asterisk;
        case '+' : return XK_plus;
        case ',' : return XK_comma;
        case '-' : return XK_minus;
        case '.' : return XK_period;
        case '/' : return XK_slash;
        case '0' : return XK_0;
        case '1' : return XK_1;
        case '2' : return XK_2;
        case '3' : return XK_3;
        case '4' : return XK_4;
        case '5' : return XK_5;
        case '6' : return XK_6;
        case '7' : return XK_7;
        case '8' : return XK_8;
        case '9' : return XK_9;
        case ':' : return XK_colon;
        case ';' : return XK_semicolon;
        case '<' : return XK_less;
        case '=' : return XK_equal;
        case '>' : return XK_greater;
        case '?' : return XK_question;
        case '@' : return XK_at;
        case 'A' : return XK_A;
        case 'B' : return XK_B;
        case 'C' : return XK_C;
        case 'D' : return XK_D;
        case 'E' : return XK_E;
        case 'F' : return XK_F;
        case 'G' : return XK_G;
        case 'H' : return XK_H;
        case 'I' : return XK_I;
        case 'J' : return XK_J;
        case 'K' : return XK_K;
        case 'L' : return XK_L;
        case 'M' : return XK_M;
        case 'N' : return XK_N;
        case 'O' : return XK_O;
        case 'P' : return XK_P;
        case 'Q' : return XK_Q;
        case 'R' : return XK_R;
        case 'S' : return XK_S;
        case 'T' : return XK_T;
        case 'U' : return XK_U;
        case 'V' : return XK_V;
        case 'W' : return XK_W;
        case 'X' : return XK_X;
        case 'Y' : return XK_Y;
        case 'Z' : return XK_Z;
        case '[' : return XK_bracketleft;
        case '\\': return XK_backslash;
        case ']' : return XK_bracketright;
        case '^' : return XK_asciicircum;
        case '_' : return XK_underscore;
        case '`' : return XK_grave;
        case 'a' : return XK_a;
        case 'b' : return XK_b;
        case 'c' : return XK_c;
        case 'd' : return XK_d;
        case 'e' : return XK_e;
        case 'f' : return XK_f;
        case 'g' : return XK_g;
        case 'h' : return XK_h;
        case 'i' : return XK_i;
        case 'j' : return XK_j;
        case 'k' : return XK_k;
        case 'l' : return XK_l;
        case 'm' : return XK_m;
        case 'n' : return XK_n;
        case 'o' : return XK_o;
        case 'p' : return XK_p;
        case 'q' : return XK_q;
        case 'r' : return XK_r;
        case 's' : return XK_s;
        case 't' : return XK_t;
        case 'u' : return XK_u;
        case 'v' : return XK_v;
        case 'w' : return XK_w;
        case 'x' : return XK_x;
        case 'y' : return XK_y;
        case 'z' : return XK_z;
        case '{' : return XK_braceleft;
        case '|' : return XK_bar;
        case '}' : return XK_braceright;
        case '~' : return XK_asciitilde;
        default: return XK_VoidSymbol;

    }
*/
}

