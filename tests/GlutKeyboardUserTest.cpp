#include "GlutKeyboardTest_common.cpp"

//////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    //Window->init(&argc, argv);  //optional
    Display*    TheDisplay = new Display("display");
    myGluiWin* Window = new myGluiWin(TheDisplay);
    Window->XMapWindow();
    int res = Window->Wait();
    delete(Window);
    delete(TheDisplay);
    exit(res);

}

