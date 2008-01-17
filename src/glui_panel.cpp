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

#include "glui_internal_control.h"
GLUI_Panel::GLUI_Panel(GLUI* theglui, GLUI_Node *parent, const char *name,
                int type):
    GLUI_Container(name)
{
  common_init();
  user_id    = -1;
  int_val    = type;
  if (parent != NULL)
	{
	  parent->add_control( this );
	}
  glui       = theglui;
  title = new GLUI_StaticText(this, name);
}

GLUI_Panel::GLUI_Panel( GLUI_Node *parent, const char *name, int type):
    GLUI_Container(name)
{
  common_init();
  user_id    = -1;
  int_val    = type;
  if (parent != NULL)
	{
	  parent->add_control( this );
	}
  title = new GLUI_StaticText(this, name);
}

GLUI_Panel::~GLUI_Panel()
{
	delete title;
}

/****************************** GLUI_Panel::draw() **********/

void    GLUI_Panel::draw( )
{
    int top;
    GLUI_DRAWINGSENTINAL_IDIOM

        if ( int_val == GLUI_PANEL_RAISED ) {
            top = 0;
            glLineWidth( 1.0 );
            glColor3f( 1.0, 1.0, 1.0 );
            glBegin( GL_LINE_LOOP );
            glVertex2i( 0, top );    glVertex2i( w, top );
            glVertex2i( 0, top );    glVertex2i( 0, h );
            glEnd();

            glColor3f( .5, .5, .5 );
            glBegin( GL_LINE_LOOP );
            glVertex2i( w, top );
            glVertex2i( w, h );
            glVertex2i( 0, h );
            glVertex2i( w, h );
            glEnd();

            /** ORIGINAL RAISED PANEL METHOD - A LITTLE TOO HIGH **
              glLineWidth(1.0);
              glBegin( GL_LINES );
              glColor3f( 1.0, 1.0, 1.0 );
              glVertex2i( 1, 1 );    glVertex2i( w-2, 1 );
              glVertex2i( 1, 1 );    glVertex2i( 1, h-2 );

              glColor3f( .5, .5, .5 );
              glVertex2i( w-1, 1 );    glVertex2i( w-1, h-1 );
              glVertex2i( 1, h-1 );    glVertex2i( w-1, h-1 );

              glColor3f( 0.0, 0.0, 0.0 );
              glVertex2i( 0, h );    glVertex2i( w, h );
              glVertex2i( w, 0 );    glVertex2i( w, h );
              glEnd();

              -- Touch up the lines a bit (needed in some opengl implementations
              glBegin( GL_POINTS );
              glColor3f( .5, .5, .5 );
              glVertex2i( w-1, h-1 );
              glColor3f( 0.0, 0.0, 0.0 );
              glVertex2i( w, h );
              glEnd();
             **/
        }
        else if ( int_val == GLUI_PANEL_EMBOSSED ) {
            if ( parent_node == NULL || *title == "" ) {
                top = 0;
            }
            else {
                top = GLUI_PANEL_EMBOSS_TOP;
            }

            glLineWidth( 1.0 );
            glColor3f( 1.0, 1.0, 1.0 );
            glBegin( GL_LINE_LOOP );
            glVertex2i( 0, top );    glVertex2i( w, top );
            glVertex2i( w, h );    glVertex2i( 0, h );

            glVertex2i( 1, top+1 );    glVertex2i( w-1, top+1 );
            glVertex2i( w-1, h-1 );    glVertex2i( 1, h-1 );
            glEnd();

            glColor3f( .5, .5, .5 );
            glBegin( GL_LINE_LOOP );
            glVertex2i( 0, top );
            glVertex2i( w-1, top );
            glVertex2i( w-1, h-1 );
            glVertex2i( 0, h-1 );
            glEnd();

            /**** Only display text in embossed panel ****/
            if ( parent_node != NULL && *title != "" ) { /* Only  draw non-null strings */
                int left = 7, height=GLUI_PANEL_NAME_DROP+1;


                if ( glui )
                    glColor3ubv(glui->bkgd_color);
                glDisable( GL_CULL_FACE );
                glBegin( GL_QUADS );
                glVertex2i( left-3, 0 );               glVertex2i( left+title->w+3, 0 );
                glVertex2i( left+title->w+3, height );  glVertex2i( left-3, height );
                glEnd();

                title->draw();
            }
        }

    glLineWidth( 1.0 );

}

/****************************** GLUI_Panel::set_name() **********/

void    GLUI_Panel::set_name( char *new_name )
{
  *(dynamic_cast<std::string*>(title))=new_name;

  update_size();
  glutPostRedisplay();
}


/****************************** GLUI_Panel::set_type() **********/

void    GLUI_Panel::set_type( int new_type )
{
  if ( new_type != int_val ) {
    int_val = new_type;
    update_size();
    glutPostRedisplay();
  }
}


/************************************** GLUI_Panel::update_size() **********/
int GLUI_Panel::min_w()
{

#warning "assert on it"
    if ( NOT glui )
        return 0;

    return x_off_left + x_off_right + title->w;
}

int GLUI_Panel::min_h() { return y_off_top  + y_off_bot + title->h; }


void   GLUI_Panel::update_size( void )
{
  if ( *title != "" AND int_val == GLUI_PANEL_EMBOSSED ) {
    this->y_off_top = GLUI_YOFF + 8;
  }
  else {
    this->y_off_top = GLUI_YOFF;
  }
  GLUI_Container::update_size();
  w = max<int>(title->w + 16,w) ;
}
