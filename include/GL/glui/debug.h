#ifndef __GLUI_DEBUG_H
#define __GLUI_DEBUG_H
/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_debug.h - Glui trace facility


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
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <X11/Xlib.h>
using namespace std;

const size_t ISIZE = 500;
namespace GLUI
{
        class debug
        {
                public :
                        static debug* Instance();

                        ~debug();
                        void Printxx(
                                        const char* key,    //< the key in the env to enable this trace
                                        const char* file,   //< the file where the trace is located
                                        int line,           //< the line of the debug string
                                        const char* func,   //< the function that call debug::print
                                        int levelshift,     //< relative indent (-1 unindent, 1 indent, 0 keep same indent)
                                        ostringstream& str);               //< additional args

                        void FlushGL(void);
                        void PrintEvent(const char* key,const ::XEvent& event, const char* func);
                        static const char* EventTypeToString( int type );
                        static const char* EventBoolToString( Bool b );
                        static const char* EventNotifyHintToString( char is_hint );
                        static const char* EventNotifyModeToString( int mode );
                        static const char* EventNotifyDetailToString( int detail );
                        static const char* EventVisibilityToString( int state );
                        static const char* EventConfigureDetailToString( int detail );
                        static const char* EventPlaceToString( int place );
                        static const char* EventMappingRequestToString( int request );
                        static const char* EventPropertyStateToString( int state );
                        static const char* EventColormapStateToString( int state );
                private:
                        debug();
                        char* use_debug;
                        char* glui_enable_fileandline;
                        char* glui_enable_indent_traces;
                        int shift;

                private : //methods

        };
#define IN(str)  { ostringstream string(""); string << str; debug::Instance()->Printxx(MODULE_KEY,__FILE__,__LINE__,__func__,1, string); }
#define OUT(str)  { ostringstream string(""); string << str; debug::Instance()->Printxx(MODULE_KEY,__FILE__,__LINE__,__func__,-1, string); }
#define MSG(str)  { ostringstream string(""); string << str; debug::Instance()->Printxx(MODULE_KEY,__FILE__,__LINE__,__func__,0, string); }
#define RAWMSG(str) MSG(str)
#define EVTMSG(evt) debug::Instance()->PrintEvent(MODULE_KEY, evt, __func__)
#define ROUT(ret, str) { ostringstream string(""); string << "(" << ret << ")" << str; debug::Instance()->Printxx(MODULE_KEY,__FILE__,__LINE__,__func__,-1, string); return ret; }

}

#endif //__GLUI_DEBUG_H
