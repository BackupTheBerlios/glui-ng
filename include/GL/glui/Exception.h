#ifndef __GLUI_EXCEPTION_H
#define __GLUI_EXCEPTION_H
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
#include <exception>
#include <string>
#include <errno.h>
namespace GLUI
{
    class Exception : public std::exception
    {
        private :
            Exception();
        private : //variables
            std::string str;
            int err;
        public:
             Exception(int errnb, const std::string& file, int line, const std::string& str);
             ~Exception() throw() { }
             virtual const char * 	what () const throw ();
    };

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define GLUI_THROW(errnb, str) throw Exception(errnb, __FILE__ , __LINE__,str )
}


#endif //__GLUI_EXCEPTION_H
