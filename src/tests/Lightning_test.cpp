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
        myGluiWin(Display* glutDisplay);
        virtual ~myGluiWin();
        virtual void draw(void);

        virtual void idle(void);
    private :
        VertexObject* box1;
        GLUquadricObj *quadric;

};

myGluiWin::myGluiWin(Display* glutDisplay) : GLUIWindow(glutDisplay,
        glutDisplay->DefaultScreen()->RootWindow(),
        -1, -1,
        200, 200,
        1,
        1,
        0)
{
    quadric = gluNewQuadric();
    box1 = drawinghelpers::raised_box(180, 180, 9);
    set_resize_policy(FixedSize);
}

myGluiWin::~myGluiWin()
{
    delete box1;
    gluDeleteQuadric(quadric);
}

void myGluiWin::draw(void)
{
    glLoadIdentity();
    glTranslatef(100.0,100.0,-100.0);

    float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
    float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float no_shininess = 0.0f;
    float low_shininess = 5.0f;
    float high_shininess = 100.0f;
    float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    gluQuadricDrawStyle(quadric, GLU_FILL );
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere( quadric , 60.5 , 36 , 18 );

    glLoadIdentity();
    glTranslatef(10.0,10.0,-100.0);
    box1->draw();


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

