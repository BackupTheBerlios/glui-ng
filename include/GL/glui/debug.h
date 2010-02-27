#ifndef __GLUI_DEBUG_H
#define __GLUI_DEBUG_H
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
                        void DumpEvent(const ::XEvent& event, ostream& out);
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
