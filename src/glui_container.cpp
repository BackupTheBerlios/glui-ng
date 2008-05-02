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
#include <GL/glui/glui_container.h>
#include <GL/glui/glui_glui.h>
#include <GL/glui/glui_debug.h>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;
#include <algorithm>

GLUI_Container::GLUI_Container(const char *name ,
                   GLUI_orientation orient):
    GLUI_Control(name)

{
    orientation = orient;
    x_off          = GLUI_XOFF;
    y_off          = GLUI_YOFF;
    y_off_top      = GLUI_YOFF;
    y_off_bot      = GLUI_YOFF;
    x_off_left     = GLUI_XOFF;
    x_off_right    = GLUI_XOFF;
}


inline void GLUI_Container::check_size_constency( void )
{
    GLUI_Node* node;
    GLUI_Control* child;
    int width(0);
    int height(0);

    node = this->first_child();
    while (NULL != node)
    {
        child = dynamic_cast<GLUI_Control*>(node);
        if (NULL != child)
        {
          if (orientation == GLUI_horizontal )
                {
                    width += child->Width() + x_off;
                    height = max<int> (this->Height(), child->Height());
                }
                else
                {
                    width = max<int> (this->Width(), child->Width());
                    height += child->Height() + y_off;
                }
        }
        node = node->next();
    }
    if (width > w) w = width;
    if(height > h) h = height;



}

#warning "split this in inline functions"
void GLUI_Container::update_size( void )
{
    GLUI_Node* node;
    GLUI_Control* child;
    if ( this->resizeable == PercentOfParent || //fixed size computed from parent
         this->resizeable == FixedSize //we have a fixed size
       )
    {
#warning "this has to be tested and improved"
        int FillSpaceCount=0;
        int width = x_off_left + x_off_right;
        int height = y_off_top  + y_off_bot;

        GLUI_Control::update_size();
        node = this->first_child();
        while (NULL != node)
        {
            child = dynamic_cast<GLUI_Control*>(node);
            if ( (NULL != child) &&
                 (child->get_resize_policy() != FillSpace)
               )
            {
                child->update_size();

                if (orientation == GLUI_horizontal )
                {
                    width += child->Width();
                    height = max<int> (height, child->Height() + y_off_top  + y_off_bot);
                }
                else
                {
                    width = max<int> (width, child->Width() + x_off_left + x_off_right);
                    height += child->Height();
                }

            }
            node = node->next();
			if (node != NULL)
			{
                if (orientation == GLUI_horizontal )
                {
                    width += x_off;
                }
                else
                {
                    height += y_off;
                }
			}
        }
        if (FillSpaceCount)
        {
            // now change type of auto fill space childs to have them
            // use percent size of parent instead of autofill feature
            node = this->first_child();
            Size newsize;

            if (orientation == GLUI_horizontal )
            {
                newsize.size.w = (this->w - width) / FillSpaceCount;
                newsize.size.h = this->h;
            }
            else
            {
                newsize.size.w = this->w;
                newsize.size.h = (this->h - width) / FillSpaceCount;
            }


            while (NULL != node)
            {
                child = dynamic_cast<GLUI_Control*>(node);
                if ( (NULL != child) &&
                     (child->get_resize_policy() != FillSpace)
                   )
                {
                    child->set_size(newsize);
                }
                node = node->next();
            }
        }

    }
    else if (this->resizeable == AdaptThisToFitChilds)
    {

        node = this->first_child();
        //this is to ensure that scalable childs will go to min size
        this->w = 0;
        this->h = 0;
        int width = x_off_left + x_off_right;
        int height = y_off_top  + y_off_bot;

        //parse all childs updating their size firt
        while (NULL != node)
        {
            child = dynamic_cast<GLUI_Control*>(node);
            if ( NULL != child)
            {
                child->update_size();

                if (orientation == GLUI_horizontal )
                {
                    width += child->Width();
                    height = max<int> (height, child->Height() + y_off_top  + y_off_bot);
                }
                else
                {
                    width = max<int> (width, child->Width() + x_off_left + x_off_right);
                    height += child->Height() ;
                }
            }
            node = node->next();
			if (node != NULL)
			{
                if (orientation == GLUI_horizontal )
                {
                    width += x_off;
                }
                else
                {
                    height += y_off;
                }
			}
        }
        this->w = width;
        this->h = height;
    }
    check_size_constency();
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

    while (NULL != node)
    {
        child = dynamic_cast<GLUI_Control*>(node);
        if ( NULL != child)
        {
            child->pack(this->x_abs + x_offset, this->y_abs + y_offset);
            if (orientation == GLUI_horizontal )
            {
                x_offset += child->Width() + x_off;
            }
            else
            {
               y_offset += child->Height() + y_off;
            }
        }
        node = node->next();
    }


}

void GLUI_Container::translate_and_draw (void)
{
  GLUI_Control *node;
  GLUI_debug::Instance()->print( __FILE__, __LINE__,
          "%s %s \n",__func__,
          dynamic_cast<GLUI_Node*>(this)->whole_tree());
  if ( ! can_draw() )
    return;

  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();

  draw();  //we're allready positioned to (0,0,0) of current widget, so just draw

  //now postion for the next child
  glTranslatef( x_off_left, y_off_bot, 0.5 );

  if (orientation == GLUI_horizontal )
  {
	  node = dynamic_cast<GLUI_Control*>(first_child());
	  while( node ) {
		  node->translate_and_draw();
		  glTranslatef( (float)node->Width(), 0.0, 0.0);
		  node = dynamic_cast<GLUI_Control*>(node->next());
		  if (node != NULL)
		  {
			  glTranslatef( (float)x_off, 0.0, 0.0);
		  }
	  }
  }
  else
  {
	  //we display childs in reverse order to have them stacked top to bottom
	  node = dynamic_cast<GLUI_Control*>(last_child());
	  while( node ) {

		  node->translate_and_draw();

		  glTranslatef( 0.0, (float) node->Height(), 0.0);
		  node = dynamic_cast<GLUI_Control*>(node->prev());
		  if (node != NULL)
		  {
			  glTranslatef( 0.0, (float)y_off, 0.0);
		  }
	  }
  }


  glPopMatrix();
  GLUI_debug::Instance()->FlushGL();

}



#warning "remove alignement code and create spacer control instead"
void GLUI_Container::align()
{
    int  orig_x_abs;
    GLUI_Container* par;

    orig_x_abs = x_abs;

    /* Fix alignment bug relating to columns              */
    /*return;              */

    if ( NULL == parent() )
        return;  /* Clearly this shouldn't happen, though */

    par = dynamic_cast<GLUI_Container*>(parent());
    if ( NULL == par )
        return;

    if ( alignment == GLUI_ALIGN_LEFT ) {
        x_abs = par->x_abs + par->x_off;
    }
    else if ( alignment == GLUI_ALIGN_RIGHT ) {
        x_abs = par->x_abs + par->w - par->x_off - this->w;
    }
    else if ( alignment == GLUI_ALIGN_CENTER ) {
        x_abs = par->x_abs + (par->w - this->w) / 2;
    }

    // now align childs
    GLUI_Node *child;
    GLUI_Container *childc;
    child = this->first_child();

    while( child != NULL )
    {
        childc=dynamic_cast<GLUI_Container*>(child);
        if (childc != NULL) childc->align();

        child = child->next();
    }


}


int GLUI_Container::add_control(GLUI_Node *control )
{
	GLUI_Control *child;

	control->link_this_to_parent_last( this );
	child = static_cast<GLUI_Control*>(control);
	if ( NULL != child)
	{
		child->glui = (GLUI*) this->glui;
		child->enabled = this->enabled;
		glutPostRedisplay();
	}

}
