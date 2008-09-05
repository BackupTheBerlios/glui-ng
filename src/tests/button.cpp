/****************************************************************************

  A simple GLUT program using the GLUI User Interface Library

  This program sets up a checkbox and a spinner, both with live variables.
  No callbacks are used.

  -----------------------------------------------------------------------

  9/9/98 Paul Rademacher (rademach@cs.unc.edu)

****************************************************************************/

#include <string.h>
#include <GL/glui.h>



/**************************************** main() ********************/

int main(int argc, char* argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    GLUI::Display *disp  = new GLUI::Display( NULL );
    GLUI::Window *window = new GLUI::Window( disp, disp->DefaultScreen()->RootWindow(),
            0, //winX,
            0, //winY,
            0, //winW,
            0, //winH,
            1, //border_width,
            disp->DefaultScreen()->Depth(),
            GLUI::Window::InputOutput,
            disp->DefaultVisual(disp->DefaultScreen()),
            0, //CWEventMask|CWBackPixel|CWBorderPixel,
            &xswa);
    window->set_resize_policy(GLUI_Control::AdaptThisToFitChilds);

    GLUI_Button( glui, "Button");
    GLUI_Master.set_glutIdleFunc( NULL );
    glutMainLoop();

    return EXIT_SUCCESS;
}



