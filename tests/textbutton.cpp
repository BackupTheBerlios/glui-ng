/****************************************************************************

  A simple GLUT program using the GLUI User Interface Library

  This program sets up a checkbox and a spinner, both with live variables.
  No callbacks are used.

  -----------------------------------------------------------------------

  9/9/98 Paul Rademacher (rademach@cs.unc.edu)

****************************************************************************/

#include <string.h>
#include <GL/glui.h>


/**************************************** main() ********************/

int main(int argc, char* argv[])
{
	GLUI_TextButton* button;

  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  GLUI *glui = GLUI_Master.create_glui( "GLUI" );
  glui->Get_main_panel()->set_resize_policy(GLUI_Control::AdaptThisToFitChilds);

  button=new GLUI_TextButton( glui, "Button");
  button->SetText("this is the test button");
  GLUI_Master.set_glutIdleFunc( NULL );
  glutMainLoop();

  return EXIT_SUCCESS;
}



