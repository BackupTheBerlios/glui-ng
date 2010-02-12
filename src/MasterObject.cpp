/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui.cpp

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



