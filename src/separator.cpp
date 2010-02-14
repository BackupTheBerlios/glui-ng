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

#include <GL/glui/separator.h>
#include <GL/gl.h>
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

    NCRC_AutoPtr<Control> par;

    int width, indent;

    par = dynamic_cast<Control*>(parent().getPointee());
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


