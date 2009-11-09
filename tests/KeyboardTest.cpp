#include "KeyboardTest_common.cpp"
//////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    struct timespec sleeptime = { 0, 100000000 };
    int count = 0;
    int err = 0;

    //Window->init(&argc, argv);  //optional
    GLUI::Display*    TheDisplay = new GLUI::Display();
    myGluiWin* Window = new myGluiWin(*TheDisplay);
    Window->XMapWindow();
    nanosleep(&sleeptime, NULL);

    while (count < 50)
    {
            struct timespec sleeptime = { 0, 200000000 };
            struct timespec rem = { 0, 0};
            Window->simulatekey();
            err = nanosleep(&sleeptime, &sleeptime);
            while (EINTR == err )
            {
                err =  nanosleep(&sleeptime, &sleeptime);
            }
            count++;
    }
    Window->XUnmapWindow();
    delete(Window);
    delete(TheDisplay);
    exit(0);
}

