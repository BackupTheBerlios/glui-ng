#include "KeyboardTest_common.cpp"

//////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
        //Window->init(&argc, argv);  //optional
        GLUI::Display*    TheDisplay = new GLUI::Display();
        myGluiWin* Window = new myGluiWin(*TheDisplay);
        Window->XMapWindow();
        int res = Window->Wait();
        delete(Window);
        delete(TheDisplay);
        exit(res);

}

