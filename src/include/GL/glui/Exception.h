#ifndef __GLUI_EXCEPTION_H
#define __GLUI_EXCEPTION_H

/*

  GLUI User Interface Toolkit
  Copyright (c) 2008 MALET Jean-Luc

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

#include <exception>
#include <string>
#include <errno.h>
namespace GLUI
{
    class Exception : public std::exception
    {
        private :
            Exception();
            const char* c_str;
            const std::string* str;
            int err;
        public:
             Exception(int errnb, const std::string* str);
             Exception(int errnb, const char* str);
             virtual const char * 	what () const throw ();
    };

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define GLUI_THROW(errnb, str) throw new Exception(errnb, __FILE__ ":" TOSTRING(__LINE__) str TOSTRING(errnb))
}


#endif //__GLUI_EXCEPTION_H
