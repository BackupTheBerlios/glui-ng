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
#include <GL/gl.h>
#include <GL/glui/debug.h>
#include <GL/glui/drawinghelpers.h>


#ifdef _MSC_VER
#define vsnprintf _vsnprintf
#endif

using namespace GLUI;

debug::debug()
{
    use_debug = getenv("GLUI_ENABLE_DEBUG");
    glui_enable_fileandline = getenv("GLUI_ENABLE_FILEANDLINE");
    glui_enable_indent_traces = getenv("GLUI_ENABLE_INDENT_TRACES");
    shift = 0;
    if (use_debug != NULL)
    {
        buf = new char[ISIZE];
    }
}

debug::~debug()
{
    if ( use_debug != NULL ) delete buf;
}

int debug::print(const char* key,
        const char* file,
        int line,
        const char* func,
        int level,
        const char* format,...)
{

    if (use_debug != NULL && NULL != getenv(key))
    {
        if ( level == -1) shift--;
        va_list arg;
        va_start(arg, format);
        int ret = vsnprintf(buf, ISIZE-1, format, arg);
        va_end(arg);
        if (ret < 0) {
            cerr << "debug string too long, error :" << ret << '\n';
            return -1;
        }
        if ( glui_enable_indent_traces != NULL )
          {
            for (uint32_t i=0; i<shift; i++)
              {
                cerr << "    ";
              }
          }
        if ( NULL != glui_enable_fileandline )
          {
            cerr << file << ":" << line << "  ";
          }

        cerr << func << ":" << buf;
        if (ret == 0) cerr << endl;
        if (level == 1) shift++;
        return 0;
    }
}

void debug::FlushGL(void)
{
      if (NULL != getenv("GLUI_SYNC") &&
              drawinghelpers::get_buffer_mode() == drawinghelpers::buffer_front)
      {
          glFlush();
      }
}


debug* debug::Instance()
{
    static debug instance;
    return &instance;
}
