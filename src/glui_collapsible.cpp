/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_panel.cpp - GLUI_Panel control class


          --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher

  WWW:    http://sourceforge.net/projects/glui/
  Forums: http://sourceforge.net/forum/?group_id=92496

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

*****************************************************************************/
#include <GL/glui/glui_collapsible.h>
#include <GL/glut.h>

GLUI_Collapsible::GLUI_Collapsible(const char *name,
                   GLUI_orientation orient) :
    GLUI_Container (name, orient)
{
    is_open = false;
}


void    GLUI_Collapsible::open( bool recurse )
{
	if ( is_open )
		return;
	is_open = true;

	glutPostRedisplay();

	this->h = Toggle->Height() + Content->Height();


	GLUI_Collapsible*    ctrl;
	GLUI_Node*           node;
	if ( is_open )
		return;
	is_open = true;

	if (recurse)
	{
		node = Content;
		while (node != NULL)
		{
			ctrl=static_cast<GLUI_Collapsible*>(node);
			if (ctrl != NULL)
			{
				ctrl->open(recurse);
			}
			node=node->next();
		}
	}
	glutPostRedisplay();

}



void    GLUI_Collapsible::close( bool recurse )
{

	if ( ! is_open )
		return;
	is_open = false;

	this->h = Toggle->Height();

	GLUI_Collapsible*    ctrl;
	GLUI_Node*           node;
	is_open = false;

	if (recurse)
	{
		node = Content;
		while (node != NULL)
		{
			ctrl=static_cast<GLUI_Collapsible*>(node);
			if (ctrl != NULL)
			{
				ctrl->open(recurse);
			}
			node=node->next();
		}
	}
	glutPostRedisplay();

}
