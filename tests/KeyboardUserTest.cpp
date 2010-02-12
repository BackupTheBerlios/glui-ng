#include "KeyboardTest_common.cpp"

//////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
        //Window->init(&argc, argv);  //optional
        NCRC_AutoPtr<GLUI::Display>    TheDisplay = new GLUI::Display();
        NCRC_AutoPtr<myGluiWin> Window = new myGluiWin(TheDisplay);
        Window->XMapWindow();
        int res = Window->Wait();
        exit(res);

}

