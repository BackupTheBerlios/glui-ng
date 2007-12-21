/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_splitter.h - header for Splitter class
        GLUI User Interface Toolkit

          --------------------------------------------------

  Copyright (c) 2007 MALET Jean-Luc

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
#include <GL/glui.h>
using namespace std;
#include <algorithm>

GLUI_Container::GLUI_Container(const char *name ,
                   GLUI_orientation orient):
    GLUI_Control(name)

{
    orientation = orient;
}

int GLUI_Container::min_w() { return x_off_left + x_off_right;}
int GLUI_Container::min_h() { return y_off_top  + y_off_bot; }


void GLUI_Container::update_size( void )
{
    GLUI_Node* node;
    GLUI_Control* child;
    node = this->first_child();
    //default value (no child)
    this->w = x_off_left + x_off_right;
    this->h = y_off_top  + y_off_bot;

    //parse all childs updating their size firt
    while (NULL != node)
    {
        child = dynamic_cast<GLUI_Control*>(this->first_child());
        if ( NULL != child)
        {
            child->update_size();
            if (orientation == GLUI_horizontal )
            {
                this->w += child->w + x_off;
                this->h = max<int> (this->h, child->h);
            }
            else
            {
                this->w = max<int> (this->w, child->w);
                this->h += child->h + y_off;
            }
        }
        node = node->next();
    }
    this->w = max<int>(this->min_w(), this->w);
    this->h = max<int>(this->min_h(), this->h);

}

void GLUI_Container::pack (int x, int y)
{
    GLUI_Node* node;
    GLUI_Control* child;
    node = this->first_child();
    int x_offset = x_off_left;
    int y_offset = y_off_top;

    this->x_abs = x;
    this->y_abs = y;

    //parse all childs updating their size firt
    while (NULL != node)
    {
        child = dynamic_cast<GLUI_Control*>(this->first_child());
        if ( NULL != child)
        {
            child->pack(this->x_abs + x_offset, this->y_abs + y_offset);
            if (orientation == GLUI_horizontal )
            {
                x_offset += child->w + x_off;
            }
            else
            {
               y_offset += child->h + y_off;
            }
        }
        node = node->next();
    }


}

void GLUI_Container::draw (void)
{
  GLUI_Control *node;

  debug ( "%s %s hidden(%d)\n",__func__,
          dynamic_cast<GLUI_Node*>(this)->whole_tree(),
          this->hidden );
  if ( ! can_draw() )
    return;

  /*if ( 1 ) {  --  Debugging to check control width
    glColor3f( 1.0, 0.0, 0.0 );
    glBegin( GL_LINES );
    glVertex2i( x_abs, y_abs );00
    glVertex2i( x_abs+w, y_abs );

    glEnd();
    }*/

  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();

  glTranslatef( (float) this->x_abs + .5,
          (float) this->y_abs + .5,
          0.0 );

  /* The following draws the area of each control              */
  glColor3f( 1.0, 0.0, 0.0 );
  glBegin( GL_LINE_LOOP );
  glVertex2i( 0, 0 ); glVertex2i( w, 0 );
  glVertex2i( w, h ); glVertex2i( 0, h );
  glEnd();

  node = dynamic_cast<GLUI_Control*>(first_child());
  while( node ) {
    node->draw();
    node = dynamic_cast<GLUI_Control*>(node->next());
  }

  glPopMatrix();
}
