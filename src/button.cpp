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
#include <GL/glui/internal_control.h>
#include <GL/glui/button.h>
#include <GL/glui/window.h>
#include <GL/glui/themes.h>
#include <GL/glui/VertexObject.h>

using namespace GLUI;
/****************************** Button::Button() **********/
Button::Button( Node *parent, const char *name,
        int id, CB cb ):
    Container(name)
    //,value(NULL, id, cb)

{
    common_init();
    this->resizeable = AdaptThisToFitChilds;
    parent->add_control( this );
    TheDefaultTheme = new Button::DefaultTheme(*this);
#warning "register on KeyPress, KeyRelease, ButtonPress, ButtonRelease, EnterNotify, LeaveNotify, MotionNotify"
}

/////////////////////////////////////////////////////////////////
int Button::AddEvent(::XEvent *event)
{
    EventInterpreter::AddEvent(event);

    if (GetStatus() & EventInterpreter::click )
    {
        //value.SetVal(true);
        value = true;
        ThemeData->update();
    }


}


void Button::common_init(void) {
    CurrentSize.size.h            = GLUI_BUTTON_SIZE;
    CurrentSize.size.w            = 100;
    alignment    = Control::CENTER;
}

bool Button::GetValue()
{
        return value;
}

////////////////////////////////////////////////////////////
int Button::DefaultTheme::draw()
{
        if (((Button&)Owner).GetValue())
        {
                this->pressed->draw();
        }
        else
        {
                this->un_pressed->draw();
        }
}

int Button::DefaultTheme::update()
{
        if (this->un_pressed != NULL ) delete this->un_pressed;
        if (this->pressed != NULL ) delete this->pressed;

        this->un_pressed =  lowered_box(Owner.Width(), Owner.Height());
        this->pressed = raised_box(Owner.Width(), Owner.Height());

}

Button::DefaultTheme::~DefaultTheme()
{
        if (this->un_pressed != NULL ) delete this->un_pressed;
        if (this->pressed != NULL ) delete this->pressed;
}
/*////////////////////////////////////////////////////////////
int DefaultToggleButtonTheme::draw()
{
}
int DefaultToggleButtonTheme::update()
{
}*/
////////////////////////////////////////////////////////////
int TextButton::DefaultTheme::draw()
{
}
int TextButton::DefaultTheme::update()
{
}



TextButton::TextButton (Node *parent, const char *name,
        int id, CB cb ) :
    Button(parent, name, id, cb),
    text(this, "text")
{
    this->TheDefaultTheme = new TextButton::DefaultTheme(*this);
    this->resizeable == AdaptThisToFitChilds;
}

void TextButton::SetText(char* newtext)
{
    text.set_text(newtext);
}


