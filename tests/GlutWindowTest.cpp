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


class myGluiWin : public GLUIWindow
{
        public :
                myGluiWin(Display* glutDisplay) : GLUIWindow(glutDisplay,
                                glutDisplay->DefaultScreen()->RootWindow(),
                                -1, -1,
                                200, 200,
                                1,
                                1,
                                0)
                {
                        set_resize_policy(FixedSize);
                }
                virtual void idle(void);
                class myGluiWinTheme : public _Window::DefaultTheme
                {
                        public:
                                myGluiWinTheme(myGluiWin& owner) : _Window::DefaultTheme(owner) {}
                                int draw();
                };
                theme* GetDefaultTheme() { return new myGluiWinTheme(*this); }

};

int myGluiWin::myGluiWinTheme::draw(void)
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
    glRotatef(45.0,1.0f,1.0f,0.0f);			// Rotate The Quad On The X axis
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
    return DefaultTheme::draw();
}


void myGluiWin::idle(void)
{
    struct timespec sleeptime = { 0, 100000000 };
    static int count = 0;

    if (count < 50)
      {
        count++;
        nanosleep(&sleeptime, NULL);
      }
    else
      {
        XUnmapWindow();
        delete(this); 
        exit(0);
      }

}

int main(int argc, char** argv)
{
    GLUIWindow::init(&argc, argv);  //optional
    Display*    glutDisplay = new Display("glut display");
    GLUIWindow* glutWindow = new myGluiWin(glutDisplay);
    glutWindow->XMapWindow();
    glutMainLoop ();

}
#endif

