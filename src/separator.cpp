/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_separator.cpp - Separator control class


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

#include <GL/glui/separator.h>
#include <math.h>
using namespace GLUI;
/****************************** Separator::Separator() **********/

Separator::Separator( Node *parent, const char* name )
     :    Control(name)

{
  common_init();
  parent->add_control( this );
}

/****************************** Separator::draw() **********/

void    Separator::draw( )
{

        Control* par;

    int width, indent;

    par = dynamic_cast<Control*>(parent());
    if ( par != NULL ) {
        width = par->Width();
    }
    else {
        width = this->Width();
    }

    indent = (int) floor(width * .05);

    glLineWidth( 1.0 );
    glBegin( GL_LINES );
    glColor3f( .5, .5, .5 );
    glVertex2i( indent,       CurrentSize.size.h/2-1 );
    glVertex2i( width-indent, CurrentSize.size.h/2-1 );

    glColor3f( 1., 1., 1. );
    glVertex2i( indent,       CurrentSize.size.h/2 );
    glVertex2i( width-indent, CurrentSize.size.h/2 );
    glEnd();


}


