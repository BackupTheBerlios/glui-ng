#include <GL/glui/window.h>
#include <GL/glui/DefaultTheme.h>
#include <GL/glui/VertexObject.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

using namespace GLUI;
class myControl;

/////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
class myControl : public Control
{
        public:
                class myControltheme : public _DefaultTheme
                {
                        public :
                                myControltheme(myControl& owner);
                                ~myControltheme();
                                int draw();
                                int update();
                        protected :
                                VertexObject* drawing;
                                myControl& Owner;
                };
        public :
                myControl(const char* name);
                virtual int AddEvent(::XKeyEvent* event);
};
///////////////////////////////////////////////////////////////////////
myControl::myControltheme::myControltheme(myControl& owner) : Owner(owner)
{
        drawing = NULL;
        update();
}

///////////////////////////////////////////////////////////////////////
myControl::myControltheme::~myControltheme()
{
        if (drawing != NULL) delete drawing;
}

///////////////////////////////////////////////////////////////////////
int myControl::myControltheme::update()
{
        if (drawing != NULL) delete drawing;
        drawing = raised_box(Owner.Width(), Owner.Height());
        return 0;
}

///////////////////////////////////////////////////////////////////////
int myControl::myControltheme::draw()
{
        return drawing->draw();
}




///////////////////////////////////////////////////////////////////////
myControl::myControl(const char* name) :
    Control(name)
{
    this->SetTheme(new myControl::myControltheme(*this));
    ((myControltheme*)&*this->ThemeData)->bkgd_color[0] = 255;
    ((myControltheme*)&*this->ThemeData)->bkgd_color[1] = 0;
    ((myControltheme*)&*this->ThemeData)->bkgd_color[2] = 0;
    this->CurrentSize = Size(200u,10u);
}

///////////////////////////////////////////////////////////////////////
int myControl::AddEvent(::XKeyEvent* event)
{
    uint8_t previous_red = ((myControltheme*)&*this->ThemeData)->bkgd_color[0];
    ((myControltheme*)&*this->ThemeData)->bkgd_color[0] = ((myControltheme*)&*this->ThemeData)->bkgd_color[2];
    ((myControltheme*)&*this->ThemeData)->bkgd_color[2] = previous_red;
    return ThemeData->update();
}




////////////////////////////////////////////////////////////////////
class myGluiWin : public GLUI::Window
{
        public :
                class myDefaulttheme : public _Window::DefaultTheme
                { 
                        public :
                                myDefaulttheme(myGluiWin& owner): _Window::DefaultTheme(owner) {};
                                int draw();
                };
        public :
                myGluiWin(NCRC_AutoPtr<GLUI::Display> TheDisplay) : GLUI::Window(TheDisplay,
                                TheDisplay->XDefaultScreenOfDisplay()->XRootWindowOfScreen(),
                                0, 0,
                                200, 200,
                                1,
                                1,
                                0)
                {
                        Angle = 0;
                        set_resize_policy(FixedSize);
                        ctrl = new myControl("top box");
                        add_control(ctrl.getPointee());
                        TheDefaultTheme = new myDefaulttheme(*this);
                        SetTheme(TheDefaultTheme);
                        Start();
                }
                ~myGluiWin()
                {
                }
                virtual int AddEvent(::XKeyEvent* event);
                void simulatekey();


        public : //variables
                float Angle;
                NCRC_AutoPtr<myControl> ctrl;
};

int myGluiWin::AddEvent(::XKeyEvent* event)
{
        int err = 0;
        Angle += 5.0f;
        if (event->type == KeyPress)
        {
                err = Container::AddEvent(event);
                if (err) return err;
                err = ThemeData->update();
                if (err) return err;
                PostRedisplay();
        }
        return err;
}
#ifdef __USE_XLIB
#include <GL/glui/x11_window.h>
#include <sys/time.h>


void myGluiWin::simulatekey(void)
{
        static int count = 0;
        ::XKeyEvent evt;

        evt.type = KeyPress;
        evt.time = get_time();
        evt.x = 100;
        evt.y = 100;
        evt.x_root = 1;
        evt.y_root = 1;
        evt.same_screen = True;
        evt.keycode = XKeysymToKeycode(disp->Disp(),XK_Up);

        count ++;
        XSendEvent ((XEvent &) evt); 
        if (count % 10 == 0)
        {
                evt.x = ctrl->X() + ctrl->Width()/2;
                evt.y = this->Height() -  ctrl->Y() - ctrl->Height()/2 ;
                evt.time = CurrentTime;
                XSendEvent ((XEvent &) evt);
        }
}
#elif  __USE_WIN32
#include <GL/glui/win32_window.h>
#else
#include <GL/glui/glut_window.h>
void myGluiWin::simulatekey(void)
{
    static int count = 0;

    count ++;
    keyboard_func (GLUT_KEY_UP, 100, 100);
    if (count % 10 == 0)
      {
        keyboard_func (GLUT_KEY_UP, ctrl->X() + ctrl->Width()/2, this->Height() -  ctrl->Y() - ctrl->Height()/2 );
      }
}
#endif

int myGluiWin::myDefaulttheme::draw(void)
{
        _Window::DefaultTheme::draw();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix
    glTranslatef(40.0f,40.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
    glBegin(GL_TRIANGLES);								// Drawing Using Triangles
        glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
        glVertex3f( 0.0f, 30.0f, 0.0f);					// Top
        glColor3f(0.0f,1.0f,0.0f);						// Set The Color To Green
        glVertex3f(-30.0f,-30.0f, 0.0f);					// Bottom Left
        glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
        glVertex3f( 30.0f,-30.0f, 0.0f);					// Bottom Right
    glEnd();											// Finished Drawing The Triangle
    glFlush();
    glTranslatef(0.0,0.0f,-1.0f);						// Move Right 3 Units
    glColor3f(0.5f,0.5f,1.0f);							// Set The Color To Blue One Time Only
    glBegin(GL_QUADS);									// Draw A Quad
        glVertex3f(-30.0f, 30.0f, 0.0f);					// Top Left
        glVertex3f( 30.0f, 30.0f, 0.0f);					// Top Right
        glVertex3f( 30.0f,-30.0f, 0.0f);					// Bottom Right
        glVertex3f(-30.0f,-30.0f, 0.0f);					// Bottom Left
    glEnd();											// Done Drawing The Quad
    glFlush();
    glTranslatef(100.0f,100.0f,-6.0f);				// Move Right 1.5 Units And Into The Screen 6.0
    glRotatef(((myGluiWin&)Owner).Angle,1.0f,1.0f,0.0f);			// Rotate The Quad On The X axis
    glColor3f(0.5f,0.5f,1.0f);							// Set The Color To Blue One Time Only
    glBegin(GL_QUADS);									// Draw A Quad
        glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue
        glVertex3f( 30.0f, 30.0f,-30.0f);			// Top Right Of The Quad (Top)
        glVertex3f(-30.0f, 30.0f,-30.0f);			// Top Left Of The Quad (Top)
        glVertex3f(-30.0f, 30.0f, 30.0f);			// Bottom Left Of The Quad (Top)
        glVertex3f( 30.0f, 30.0f, 30.0f);			// Bottom Right Of The Quad (Top)
        glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
        glVertex3f( 30.0f,-30.0f, 30.0f);			// Top Right Of The Quad (Bottom)
        glVertex3f(-30.0f,-30.0f, 30.0f);			// Top Left Of The Quad (Bottom)
        glVertex3f(-30.0f,-30.0f,-30.0f);			// Bottom Left Of The Quad (Bottom)
        glVertex3f( 30.0f,-30.0f,-30.0f);			// Bottom Right Of The Quad (Bottom)
        glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
        glVertex3f( 30.0f, 30.0f, 30.0f);			// Top Right Of The Quad (Front)
        glVertex3f(-30.0f, 30.0f, 30.0f);			// Top Left Of The Quad (Front)
        glVertex3f(-30.0f,-30.0f, 30.0f);			// Bottom Left Of The Quad (Front)
        glVertex3f( 30.0f,-30.0f, 30.0f);			// Bottom Right Of The Quad (Front)
        glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
        glVertex3f( 30.0f,-30.0f,-30.0f);			// Bottom Left Of The Quad (Back)
        glVertex3f(-30.0f,-30.0f,-30.0f);			// Bottom Right Of The Quad (Back)
        glVertex3f(-30.0f, 30.0f,-30.0f);			// Top Right Of The Quad (Back)
        glVertex3f( 30.0f, 30.0f,-30.0f);			// Top Left Of The Quad (Back)
        glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
        glVertex3f(-30.0f, 30.0f, 30.0f);			// Top Right Of The Quad (Left)
        glVertex3f(-30.0f, 30.0f,-30.0f);			// Top Left Of The Quad (Left)
        glVertex3f(-30.0f,-30.0f,-30.0f);			// Bottom Left Of The Quad (Left)
        glVertex3f(-30.0f,-30.0f, 30.0f);			// Bottom Right Of The Quad (Left)
        glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
        glVertex3f( 30.0f, 30.0f,-30.0f);			// Top Right Of The Quad (Right)
        glVertex3f( 30.0f, 30.0f, 30.0f);			// Top Left Of The Quad (Right)
        glVertex3f( 30.0f,-30.0f, 30.0f);			// Bottom Left Of The Quad (Right)
        glVertex3f( 30.0f,-30.0f,-30.0f);			// Bottom Right Of The Quad (Right)
    glEnd();						// Done Drawing The Quad
    glFlush();
    //#error "pb dans le calcul de la taille de la fenêtre"
    return 0;


}


