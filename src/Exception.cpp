/*

  glui_window.cpp : the top level widget

  GLUI User Interface Toolkit 
  Copyright (c) 2008 MALET Jean-Luc

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

*/

#include <GL/glui/Exception.h>
using namespace GLUI;
///////////////////////////////////////////////////////////////////
Exception::Exception(int errnb, const std::string* str)
{
    this->err = errnb;
    this->str   = str;
    this->c_str = NULL;
}

///////////////////////////////////////////////////////////////////
Exception::Exception(int errnb, const char* str)
{
    this->err = errnb;
    this->str   = NULL;
    this->c_str = str;
}

///////////////////////////////////////////////////////////////////
const char * Exception::what () const throw ()
{
    if (this->str != NULL) return this->str->c_str();
    else if (this->c_str != NULL) return this->c_str;
}

