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
        virtual void draw(void);

        virtual void idle(void);
    private :
        VertexObject* box1;
        VertexObject* box2;
};

myGluiWin::myGluiWin(Display* glutDisplay) : GLUIWindow(glutDisplay,
        glutDisplay->DefaultScreen()->RootWindow(),
        -1, -1,
        200, 200,
        1,
        1,
        0)
{
    uint8_t color_array[8][3] = { {255, 000, 000},
                   {255, 000, 000},
                   {255, 000, 000},
                   {255, 000, 000},
/*{255, 000, 000},
{255, 000, 000},
{255, 000, 000},
{255, 000, 000}};*/

                   {000, 255, 000},
                   {000, 255, 000},
                   {000, 255, 000},
                   {000, 255, 000}};

    box1 = drawinghelpers::raised_box(180, 180);
    box2 = drawinghelpers::raised_box(160, 160, 8, 3, GL_UNSIGNED_BYTE, color_array);
    set_resize_policy(FixedSize);
}

void myGluiWin::draw(void)
{
    glLoadIdentity();
    glTranslatef(10.0,10.0,-20.0);
    box1->draw();
    glTranslatef(10.0,10.0,2.0);
    box2->draw();
    glutPostRedisplay();
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

