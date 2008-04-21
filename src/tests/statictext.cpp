/****************************************************************************

  A simple GLUT program using the GLUI User Interface Library

  This program sets up a checkbox and a spinner, both with live variables.
  No callbacks are used.

  -----------------------------------------------------------------------

  9/9/98 Paul Rademacher (rademach@cs.unc.edu)

****************************************************************************/

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



