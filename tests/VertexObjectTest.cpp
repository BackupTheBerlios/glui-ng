#include <GL/glui/window.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
using namespace GLUI;

class myGluiWin : public GLUI::Window
{
        public :
                class myGluiWinTheme : public _Window::DefaultTheme
                {
                        public:
                                myGluiWinTheme(myGluiWin& owner) : _Window::DefaultTheme(owner) {}
                                int draw();
                };
        public :
                myGluiWin(GLUI::Display& TheDisplay) : GLUI::Window(TheDisplay,
                                TheDisplay.XDefaultScreenOfDisplay()->XRootWindowOfScreen(),
                                -1, -1,
                                200, 200,
                                1,
                                1,
                                0)
                {
                        set_resize_policy(FixedSize);
                        SetTheme(new myGluiWinTheme(*this));
                        Start();
                }

                theme* GetDefaultTheme() { return new myGluiWinTheme(*this); }

};


int main(int argc, char** argv)
{
        struct timespec sleeptime = { 5, 0 };
        GLUI::Window::init(&argc, argv);  //optional
        GLUI::Display*    TheDisplay = new GLUI::Display();
        GLUI::Window* Window = new myGluiWin(*TheDisplay);
        Window->XMapWindow();
        nanosleep(&sleeptime, NULL);
        Window->XUnmapWindow();
        nanosleep(&sleeptime, NULL);
        delete(Window); 
        delete(TheDisplay);
        exit(0);

}

