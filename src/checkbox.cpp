
/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

  glui_checkbox - Checkbox control class


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

#include <GL/glui/internal_control.h>
#include <GL/glui/main.h>
#include <GL/glui/checkbox.h>
#include <GL/glui/statictext.h>
#include <GL/glui/bitmaps.h>
#include <GL/glui/masterobject.h>
#include <GL/glui/debug.h>
#include <GL/glui/internal_control.h>
#include <GL/glui/window.h>

using namespace GLUI;
#warning "there is missize computation in this"
/****************************** Checkbox::Checkbox() **********/

Checkbox::Checkbox( Node *parent,
        const char *name, int *value_ptr,
        int id,
        CB cb ):
    Container(name),
    value(value_ptr, id,cb)
                           //	button(this, "button")
{
    common_init();

    parent->add_control( this );
    this->resizeable = AdaptThisToFitChilds;
    this->CurrOrientation = Container::horizontal;
#warning "fix this : hardcoded value, replace this code with real opengl call"
#warning "and create a toogle button class for checkbox"
    this->x_off_left = 15;
    this->y_off_bot  = 2;
    text = new StaticText(this, "text" );
    text->set_text(name);
}

Checkbox::~Checkbox()
{
    delete text;
}

int Checkbox::AddEvent (::XEvent *event)
{
    EventInterpreter::AddEvent(event);
    ::XEvent EventToForward;
    EventToForward.xexpose.type=Expose;
    EventToForward.xexpose.send_event=true;
    EventToForward.xexpose.x = x_abs;
    EventToForward.xexpose.y = y_abs;
    EventToForward.xexpose.width = this->Width();
    EventToForward.xexpose.height = this->Height();

    if (GetStatus() & EventInterpreter::click )
    {
        value.SetVal(!value.GetVal());
        Control::AddEvent(&EventToForward);
    }
    //ask for redisplay of window


}



/****************************** Checkbox::draw() **********/
void    Checkbox::draw()
{
    //glui->draw_raised_box( 0, 0, 19, 19 );
    if ( value.GetVal() != 0 || (GetStatus() & EventInterpreter::buttonpressed) ) {
        if ( enabled )
            StdBitmaps::Instance()->draw( StdBitmaps::CHECKBOX_ON, 0, 0 );
        else
            StdBitmaps::Instance()->draw( StdBitmaps::CHECKBOX_ON_DIS, 0, 0 );
    }
    else {
        if ( enabled )
            StdBitmaps::Instance()->draw( StdBitmaps::CHECKBOX_OFF, 0, 0 );
        else
            StdBitmaps::Instance()->draw( StdBitmaps::CHECKBOX_OFF_DIS, 0, 0 );
    }

    debug::Instance()->FlushGL();
}

/**************************** Checkbox::draw_active_area() **************/
/*
   void    Checkbox::draw_active_area( void )
   {
   int text_width, left, right;

   text_width = _glutBitmapWidthString( glui->font, name.c_str() );
   left       = text_x_offset-3;
   right      = left + 7 + text_width;

//  if ( active ) {
glEnable( GL_LINE_STIPPLE );
glLineStipple( 1, 0x5555 );
glColor3f( 0., 0., 0. );
//  } else {
//    glColor3ubv( glui->bkgd_color );
//  }

glBegin( GL_LINE_LOOP );
glVertex2i(left,0);     glVertex2i( right,0);
glVertex2i(right,h+1);   glVertex2i( left,h+1);
glEnd();

glDisable( GL_LINE_STIPPLE );
}*/


/************************************ Checkbox::update_size() **********/

void   Checkbox::update_size( void )
{
    Container::update_size();
    this->CurrentSize.size.w += 13;
    this->CurrentSize.size.h = max<int>(13, this->CurrentSize.size.h);
}

