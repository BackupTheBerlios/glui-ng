#include <GL/glui/window.h>
#include <unistd.h>
#include <assert.h>
using namespace GLUI;

#if (__USE_XLIB == 1 || __USE_WIN32 == 1 )
int main(int argc, char* argv[])
{
    return 0;
}
#else
int main(int argc, char** argv)
{
    //glutWindow->init(&argc, argv);  //optional
    Display*    glutDisplay = new Display("glut display");
    GLUIWindow* glutWindow = new GLUIWindow(glutDisplay,
                                            glutDisplay->DefaultScreen()->RootWindow(),
                                            0, 0,
                                            200, 200,
                                            1,
                                            1,
                                            0);
    glutWindow->XMapWindow();
    sleep(20);
    glutWindow->XUnmapWindow();

}
#endif

