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

/** These are the live variables passed into GLUI ***/
int   wireframe = 0;



/**************************************** main() ********************/

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  GLUI *glui = GLUI_Master.create_glui( "GLUI" );
  glui->Get_main_panel()->set_resize_policy(GLUI_Control::AdaptThisToFitChilds);

  GLUI_StaticText* text1 = new GLUI_StaticText( glui, "text1" );
  GLUI_StaticText* text2 = new GLUI_StaticText( glui, "text2" );
  GLUI_StaticText* text3 = new GLUI_StaticText( glui, "text3" );
  text1->set_text("text1 :  the brown dog");
  text2->set_text("text2 : jump on");
  text3->set_text("text3 : the lazy fox, qwerty");


  GLUI_Master.set_glutIdleFunc( NULL );
  glutMainLoop();

  return EXIT_SUCCESS;
}



