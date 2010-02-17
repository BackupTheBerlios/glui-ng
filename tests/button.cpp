/*
   GLUI-ng, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

   This library is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the 
   Free Software Foundation; either version 2.1 of the License, 
   or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License along with this library;
   if not, write to the 
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

   based on the work of Paul Rademacher (orignal software http://glui.sourceforge.net/)
*/

#include <string.h>
#include <GL/glui.h>



/**************************************** main() ********************/

int main(int argc, char* argv[])
{
    struct timespec sleeptime = { 1, 100000000 };
    int count = 0;
    int err = 0;


    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    NCRC_AutoPtr<GLUI::Display> disp  = new GLUI::Display( NULL );
    NCRC_AutoPtr<GLUI::Window> window = new GLUI::Window( disp, disp->DefaultScreen()->RootWindow(),
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
    window->add_control(new Button("Button"));
    Window->XMapWindow();
    nanosleep(&sleeptime, &sleeptime);
    while (EINTR == err )
    {
            err =  nanosleep(&sleeptime, &sleeptime);
    }
    while (count < 50)
    {
            struct timespec sleeptime = { 0, 100000000 };
            struct timespec rem = { 0, 0};
            Window->simulatekey();
            err = nanosleep(&sleeptime, &rem);
            while (EINTR == err )
            {
                err =  nanosleep(&rem, &rem);
            }
            count++;
    }
    Window->XUnmapWindow();
    exit(0);
    return EXIT_SUCCESS;
}



