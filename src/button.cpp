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
#include <GL/glui/EventInterpreter.h>
#include <GL/glui/debug.h>
#define MODULE_KEY  "GLUI_DEBUG_BUTTON"

using namespace GLUI;
/****************************** Button::Button() **********/
Button::Button( const char *name,
        int id, CB cb ):
    Container(name)
    //,value(NULL, id, cb)

{
        IN("\n");
        common_init();
        this->resizeable = FixedSize;
        TheDefaultTheme = new Button::DefaultTheme(*this);
        SetTheme(TheDefaultTheme);
        handler = new EventInterpreter;
        this->value = 0;
#warning "register on KeyPress, KeyRelease, ButtonPress, ButtonRelease, EnterNotify, LeaveNotify, MotionNotify"
        OUT("\n");
}

/////////////////////////////////////////////////////////////////
int Button::AddEvent(::XButtonEvent* event)
{
        IN("\n");
        handler->AddEvent((::XEvent*) event,this);
        NCRC_AutoPtr<EventInterpreter> hdl = handler;
        if (hdl->GetStatus() & EventInterpreter::click )
        {
                //value.SetVal(true);
                value = true;
                ThemeData->update();
        }
        PostRedisplay();
        OUT("\n");
}


void Button::common_init(void) 
{
        IN("\n");
        CurrentSize.size.h            = GLUI_BUTTON_SIZE;
        CurrentSize.size.w            = 100;
        alignment    = Control::CENTER;
        OUT("\n");
}

int Button::GetValue()
{
        IN("\n");
        ROUT(handler->GetStatus(),hex << handler->GetStatus() << "\n");
}

////////////////////////////////////////////////////////////
int Button::DefaultTheme::draw()
{
        IN("\n");
        MSG("GetValue : " << hex << ((Button&)Owner).GetValue() 
                        << " waited flags : " << EventInterpreter::buttonpressed << dec <<"\n");
        if (((Button&)Owner).GetValue()  & EventInterpreter::buttonpressed)
        {
                this->Pressed->draw();
        }
        else
        {
                this->UnPressed->draw();
        }
        OUT("\n");
}

int Button::DefaultTheme::update()
{
        IN("\n");
        this->Pressed = raised_box(Owner.Width(), Owner.Height(),1,16,_DefaultTheme::none);
        this->Pressed->AddTexture(TexturePressed);
        //this->UnPressed =  lowered_box(Owner.Width(), Owner.Height());
        this->UnPressed =  raised_box(Owner.Width(), Owner.Height(),1,16,_DefaultTheme::none);
        this->UnPressed->AddTexture(TextureUnpressed);
        OUT("\n");
}

Button::DefaultTheme::DefaultTheme(Button& owner) : Owner(owner)
{
        IN("\n");
        float TexCoord[8][2] = 
        {
                {0.0,  0.0},
                {1.0,  0.0},
                {1.0,  1.0},
                {0.0,  1.0},
                {0.22, 0.22},
                {0.78, 0.22},
                {0.78, 0.78},
                {0.22, 0.78}
        };
        NCRC_AutoPtr<DataArray> texcoord(new DataArray(8, 2, DataArray::FLOAT, TexCoord));

        std::string texture_unpressed_name(getenv("GLUI_THEME_DATA_DIR"));
        texture_unpressed_name += "/button unpressed.pnm";
        NCRC_AutoPtr<TextureData> texture_unpressed(new PPMTexture(texture_unpressed_name));
        this->TextureUnpressed = new Texture(texcoord, texture_unpressed);

        std::string texture_pressed_name(getenv("GLUI_THEME_DATA_DIR"));
        texture_pressed_name += "/button pressed.pnm";
        NCRC_AutoPtr<TextureData> texture_pressed(new PPMTexture(texture_pressed_name));
        this->TexturePressed = new Texture(texcoord, texture_pressed);
        OUT("\n");
}

Button::DefaultTheme::~DefaultTheme()
{
        IN("\n");
        //nothing to be done here since the NCRC_AutoPtr will delete the allocated data
        OUT("\n");
}
/*////////////////////////////////////////////////////////////
int DefaultToggleButtonTheme::draw()
{
        IN("\n");
        OUT("\n");
}
int DefaultToggleButtonTheme::update()
{
        IN("\n");
        OUT("\n");
}*/
////////////////////////////////////////////////////////////
int TextButton::DefaultTheme::draw()
{
        IN("\n");
        OUT("\n");
}
int TextButton::DefaultTheme::update()
{
        IN("\n");
        OUT("\n");
}



TextButton::TextButton (const char *name,
                int id, CB cb ) :
        Button(name, id, cb),
        text(this, "text")
{
        IN("\n");
        this->TheDefaultTheme = new TextButton::DefaultTheme(*this);
        this->resizeable == AdaptThisToFitChilds;
        OUT("\n");
}

void TextButton::SetText(char* newtext)
{
        IN("\n");
        text.set_text(newtext);
        OUT("\n");

}


