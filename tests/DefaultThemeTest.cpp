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


class myGluiWinDefaultThemeData: public DefaultThemeData
{
        public
                myGluiWinDefaultThemeData(Control& owner) : DefaultThemeData(owner) {}
                virtual int draw();
                virtual int update();
};


class myGluiWin : public GLUIWindow
{
    public :
        myGluiWin(Display* glutDisplay) : GLUIWindow(glutDisplay,
                                                        glutDisplay->DefaultScreen()->RootWindow(),
                                                        -1, -1,
                                                        200, 200,
                                                        1,
                                                        1,
                                                        0),
                                         data(*this)
    {
        set_resize_policy(FixedSize);
        SetThemeData(&data);
    }
       virtual void idle(void);

       myGluiWinDefaultThemeData data;
};



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

int myGluiWinDefaultThemeData::update()
{
}

int myGluiWinDefaultThemeData::draw(void)
{
    uint8_t color_array[4][3]= { {255, 000, 000},
                                  {000, 255, 000},
                                  {000, 000, 255},
                                  {128, 128, 128}};

    glLoadIdentity();
    glTranslatef(10.0,10.0,-20.0);
    drawinghelpers::draw_box(180, 180);
    glTranslatef(0.0,0.0,1.0);
    drawinghelpers::draw_box(170, 170, 3, GL_UNSIGNED_BYTE, color_array);
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
        TestTheme* theme = new TestTheme;
        GLUIWindow::init(&argc, argv);  //optional
        Display*    glutDisplay = new Display("glut display");
        GLUIWindow* glutWindow = new myGluiWin(glutDisplay);
        glutWindow->XMapWindow();
        glutMainLoop ();

}
#endif

