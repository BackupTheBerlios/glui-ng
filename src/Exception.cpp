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
#include <iostream>
#include <sstream>
#include <GL/glui/Exception.h>
#include <string.h>
using namespace GLUI;
///////////////////////////////////////////////////////////////////

Exception::Exception(int errnb, const std::string& file, int line, const std::string& str)
{
        std::stringstream format;
        char* buff = new char[30];
        format << file << ":" << line << " error "<< errnb << "(";
        if (strerror_r(errnb, buff, 30))
        {
                format << "UNKNOWN";
        }
        else
        {
                format << buff;
        }
        format << ")  " << str;

        this->err = errnb;
        this->str = format.str();
        delete[] buff;
}

///////////////////////////////////////////////////////////////////
const char * Exception::what () const throw ()
{
    return this->str.c_str();
}

