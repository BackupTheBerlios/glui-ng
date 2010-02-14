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
#include <GL/glui/MasterObject.h>
using namespace GLUI;






///////////////////////////////////////////////////////////////////////////
MasterObject::MasterObject()
        : Node ("MasterObject")
{
}


///////////////////////////////////////////////////////////////////////////
NCRC_AutoPtr<Node> MasterObject::Instance()
{
    static NCRC_AutoPtr<Node> object;
    if ( object == NULL)
    {
            object = new  MasterObject ("MasterObject");
    }
    return object;
}

MasterObject::MasterObject(const char *name) : Node (name)
{
}


//////////////////////////////////////////////////////////////////////////
NCRC_AutoPtr<GLUI::Window>      MasterObject::FindWindow( ::Window window_id )
{
        NCRC_AutoPtr<GLUI::Window> win = dynamic_cast<GLUI::Window*>(this->first_child().getPointee());

        while( win != NULL )
        {
                if ( win->GetWindowId() == window_id )
                        return win;

                win = dynamic_cast<GLUI::Window*>(win->next().getPointee());
        }
        return NULL;
}

////////////////////////////////////////////////////////////////////////
int  MasterObject::add_control( Node *window )
{
        // only allow first childs of this to be of GLUIWindow type
        if ( NULL == dynamic_cast<GLUI::Window*>(window)) return EINVAL;
        return Node::add_control(window);
}


void MasterObject::pack( int x, int y)
{
        NCRC_AutoPtr<GLUI::Window> win = dynamic_cast<GLUI::Window*>(this->first_child().getPointee());

        while( win != NULL )
        {
                win->pack(0, 0);
                win = dynamic_cast<GLUI::Window*>(win->next().getPointee());
        }

}



