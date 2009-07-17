#include <GL/glui/window.h>
#include <GL/glui/DefaultTheme.h>
#include <GL/glui/VertexObject.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

using namespace GLUI;
class myControl;

#if (__USE_XLIB == 1 || __USE_WIN32 == 1 )
int main(int argc, char* argv[])
{
    return 0;
}
#else
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
    drawing = raised_box(Owner.Width(), Owner.Height());
}

///////////////////////////////////////////////////////////////////////
int myControl::myControltheme::draw()
{
        drawing->draw();
}




///////////////////////////////////////////////////////////////////////
myControl::myControl(const char* name) :
    Control(name)
{
    ((myControltheme*)this->ThemeData)->bkgd_color[0] = 255;
    ((myControltheme*)this->ThemeData)->bkgd_color[2] = 0;
    set_size(Size(200u,10u));
    this->SetTheme(new myControl::myControltheme(*this));
}

///////////////////////////////////////////////////////////////////////
int myControl::AddEvent(::XKeyEvent* event)
{
    uint8_t previous_red = ((myControltheme*)this->ThemeData)->bkgd_color[0];
    ((myControltheme*)this->ThemeData)->bkgd_color[0] = ((myControltheme*)this->ThemeData)->bkgd_color[2];
    ((myControltheme*)this->ThemeData)->bkgd_color[2] = previous_red;
    ThemeData->update();
}




////////////////////////////////////////////////////////////////////
class myGluiWin : public GLUIWindow
{
        public :
                class theme : public _Window::DefaultTheme
                { 
                        public :
                                theme(myGluiWin& owner): _Window::DefaultTheme(owner) {};
                                int draw();
                };
        public :
                myGluiWin(Display* glutDisplay) : GLUIWindow(glutDisplay,
                                glutDisplay->DefaultScreen()->RootWindow(),
                                0, 0,
                                200, 200,
                                1,
                                1,
                                0),
                ctrl("top box")
                {
                        Angle = 0;
                        add_control(&ctrl);
                }
                virtual int AddEvent(::XKeyEvent* event);
                void simulatekey();
                virtual void idle(void);


        public : //variables
                float Angle;
                myControl ctrl;
};

int myGluiWin::AddEvent(::XKeyEvent* event)
{
    Angle += 5.0f;
    Container::AddEvent((::XEvent*) event);
    ThemeData->update();
}

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


void myGluiWin::simulatekey(void)
{
    static int count = 0;

    count ++;
    keyboard_func (GLUT_KEY_UP, 100, 100);
    if (count % 10 == 0)
      {
        keyboard_func (GLUT_KEY_UP, ctrl.X() + ctrl.Width()/2, this->Height() -  ctrl.Y() - ctrl.Height()/2 );
      }
}

int myGluiWin::theme::draw(void)
{
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
    return _Window::DefaultTheme::draw();


}



void myGluiWin::idle(void)
{
    struct timespec sleeptime = { 0, 100000000 };
    static int count = 0;

    if (count < 500)
      {
        struct timespec sleeptime = { 0, 100000000 };
        nanosleep(&sleeptime, NULL);
        count++;
      }
    else
      {
        this->XUnmapWindow();
        delete(this);
        exit(0);
      }

}

//////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    //glutWindow->init(&argc, argv);  //optional
    Display*    glutDisplay = new Display("glut display");
    myGluiWin* glutWindow = new myGluiWin(glutDisplay);
    glutWindow->XMapWindow();
    glutMainLoop ();

}
#endif

