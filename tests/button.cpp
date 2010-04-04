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
#include <GL/glui/button.h>
#include <GL/glui/window.h>
using namespace GLUI;


/**************************************** main() ********************/

int main(int argc, char* argv[])
{
        //Window->init(&argc, argv);  //optional
        NCRC_AutoPtr<GLUI::Display>    TheDisplay = new GLUI::Display();
        NCRC_AutoPtr<GLUI::Window> window = new GLUI::Window(TheDisplay,
                                TheDisplay->XDefaultScreenOfDisplay()->XRootWindowOfScreen(),
                                0, 0,
                                200, 200,
                                1,
                                1,
                                0);
        NCRC_AutoPtr<Button> button1 = new Button("Button");
        button1->set_size(Control::Size(100u,200u));
        window->set_resize_policy(Control::AdaptThisToFitChilds);
        window->add_control(button1);
        window->Start();
        window->XMapWindow();
        int res = window->Wait();
        exit(res);
}



