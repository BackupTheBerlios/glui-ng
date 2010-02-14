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

