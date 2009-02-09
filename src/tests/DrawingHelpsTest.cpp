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
       virtual void draw(void);
       virtual void idle(void);
};


void myGluiWin::draw(void)
{
    uint8_t color_array[4][3]= { {255, 000, 000},
                                  {000, 255, 000},
                                  {000, 000, 255},
                                  {128, 128, 128}};
    int32_t color[4][3];
    drawinghelpers::ConvertglColorPointer(3, GL_UNSIGNED_BYTE, color_array, GL_INT, color);

    glLoadIdentity();
    glTranslatef(10.0,10.0,-20.0);
    drawinghelpers::draw_box(180, 180, NULL);
    glTranslatef(0.0,0.0,1.0);
    drawinghelpers::draw_box(170, 170, (GLint*)color);
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

