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

#warning "GLUI class is a duplicate of GLUI_Main, remove!"






///////////////////////////////////////////////////////////////////////////
MasterObject* MasterObject::Instance()
{
    static MasterObject object("MasterObject");
    return &object;
}

MasterObject::MasterObject(const char *name) : Node (name)
{
}


//////////////////////////////////////////////////////////////////////////
GLUIWindow*      MasterObject::FindWindow( WindowId window_id )
{

  GLUIWindow* win = dynamic_cast<GLUIWindow*>( this->first_child());

  while( win ) {
    if ( win->GetWindowId() == window_id )
      return win;

    win = dynamic_cast<GLUIWindow*>(win->next());
  }
  return NULL;
}

////////////////////////////////////////////////////////////////////////
int  MasterObject::add_control( Node *window )
{
    // only allow first childs of this to be of GLUIWindow type
    if ( NULL == dynamic_cast<GLUIWindow*>(window)) return EINVAL;
    return Node::add_control(window);
}


void MasterObject::pack( int x, int y)
{
    GLUIWindow* win = dynamic_cast<GLUIWindow*>( this->first_child());

    while( win ) {
        win->pack(0, 0);
        win = dynamic_cast<GLUIWindow*>(win->next());
    }

}



