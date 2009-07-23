#include "GlutKeyboardTest_common.cpp"
//////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    struct timespec sleeptime = { 0, 100000000 };
    int count = 0;

    //Window->init(&argc, argv);  //optional
    Display*    TheDisplay = new Display("display");
    myGluiWin* Window = new myGluiWin(TheDisplay);
    Window->XMapWindow();

    while (count < 50)
    {
            struct timespec sleeptime = { 0, 100000000 };
            Window->simulatekey();
            nanosleep(&sleeptime, NULL);
            count++;
    }
    Window->XUnmapWindow();
    delete(Window);
    delete(TheDisplay);
    exit(0);
}

