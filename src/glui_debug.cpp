/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_debug.cpp - Glui trace facility


          --------------------------------------------------

  Copyright (c) 2007 Jean-Luc MALET

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

#include "glui_debug.h"


#ifdef _MSC_VER
#define vsnprintf _vsnprintf
#endif


GLUI_debug::GLUI_debug()
{
  use_debug = getenv("GLUI_ENABLE_DEBUG");
  if (use_debug != NULL)
  {
      buf = new char[ISIZE];
  }
}

GLUI_debug::~GLUI_debug()
{
  if ( use_debug != NULL ) delete buf;
}

int GLUI_debug::print(const char* file, int line, const char* format,...)
{

    if (use_debug != NULL )
    {
        va_list arg;
        va_start(arg, format);
        int ret = vsnprintf(buf, ISIZE-1, format, arg);
        va_end(arg);
        if (ret<=0) {
            cerr << "debug string too long, error :" << ret << '\n';
            return -1;
        }
        cerr << buf;
        return 0;
    }
}

GLUI_debug* GLUI_debug::Instance()
{
    static GLUI_debug instance;
    return &instance;
}
