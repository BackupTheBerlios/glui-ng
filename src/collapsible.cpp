/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_panel.cpp - Panel control class


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
#include <GL/glui/collapsible.h>
#include <GL/glui/drawinghelpers.h>

using namespace GLUI;

Collapsible::Collapsible(const char *name,
                   orientation orient) :
    Container (name, orient)
{
    is_open = false;
}


void    Collapsible::open( bool recurse )
{
	Collapsible*    ctrl;
	Node*           node;


	if ( is_open )
		return;
	is_open = true;

	this->CurrentSize.size.h = Toggle->Height() + Content->Height();

	if (recurse)
	{
		node = Content;
		while (node != NULL)
		{
			ctrl=static_cast<Collapsible*>(node);
			if (ctrl != NULL)
			{
				ctrl->open(recurse);
			}
			node=node->next();
		}
	}
    drawinghelpers::PostRedisplay(this);

}



void    Collapsible::close( bool recurse )
{

	if ( ! is_open )
		return;
	is_open = false;

	this->CurrentSize.size.h = Toggle->Height();

	Collapsible*    ctrl;
	Node*           node;
	is_open = false;

	if (recurse)
	{
		node = Content;
		while (node != NULL)
		{
			ctrl=static_cast<Collapsible*>(node);
			if (ctrl != NULL)
			{
				ctrl->open(recurse);
			}
			node=node->next();
		}
	}
    drawinghelpers::PostRedisplay(this);

}
