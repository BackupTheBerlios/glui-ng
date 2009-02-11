#include <GL/glui/window.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

using namespace GLUI;

#if (__USE_XLIB == 1 || __USE_WIN32 == 1 )
int main(int argc, char* argv[])
{
    return 0;
}
#else
/////////////////////////////////////////////////////////////////////
class myControl : public Control
{
    public :
        myControl(const char* name);
        virtual void draw();
        virtual int AddEvent(::XKeyEvent* event);
    private:
        float fColors[3];
};

myControl::myControl(const char* name) :
    Control(name)
{
    fColors[0] = 1.0;
    fColors[2] = 0.0;
    set_size(Size(200u,10u));
}

int myControl::AddEvent(::XKeyEvent* event)
{
    float previous_red = fColors[0];
    fColors[0] = fColors[2];
    fColors[2] = previous_red;
    drawinghelpers::PostRedisplay(this);
}

void myControl::draw()
{
    GLint iColorArray[4][3];
    float fColorArray[4][3] = { fColors[0], 0.0, fColors[2],
        fColors[0], 0.0, fColors[2],
        fColors[0], 0.0, fColors[2],
        fColors[0], 0.0, fColors[2] };
    for (uint8_t i=0; i<4; i++)
    {
        drawinghelpers::ConvertglColorPointer(3, GL_FLOAT, fColorArray[i], GL_INT, iColorArray[i]);
    }
    drawinghelpers::draw_box(CurrentSize.size.w, CurrentSize.size.h, &(iColorArray[0][0]));
}


////////////////////////////////////////////////////////////////////
class myGluiWin : public GLUIWindow
{
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
       virtual void draw(void);
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
    drawinghelpers::PostRedisplay(this);
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


void myGluiWin::draw(void)
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
    glRotatef(Angle,1.0f,1.0f,0.0f);			// Rotate The Quad On The X axis
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
    GLUIWindow::draw();


}

void myGluiWin::idle(void)
{
    struct timespec sleeptime = { 0, 100000000 };
    static int count = 0;

    if (count < 50)
      {
        struct timespec sleeptime = { 0, 100000000 };
        this->simulatekey();
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

