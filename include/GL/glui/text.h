#ifndef __GLUI_TEXT_H
#define __GLUI_TEXT_H
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

#include <stdarg.h>
#include <cstring>
#include <string>
#include <memory>

#include <GL/glui/commondefs.h>
#include <GL/glui/DefaultTheme.h>
#include <GL/glui/VertexObject.h>
#include <GL/glui/FontServer.h>
#include <GL/gl.h>

/************************************************************/
/*                                                          */
/*               Text class                                 */
/*                                                          */
/************************************************************/
namespace GLUI
{
        /** Size of the character width hash table for faster lookups.
          Make sure to keep this a power of two to avoid the slow divide.
          This is also a speed/memory tradeoff; 128 is enough for low ASCII.
          */
#define CHAR_WIDTH_HASH_SIZE 128

        class GLUIAPI Text : public std::string, public _DefaultTheme
        {


                public:
                        void         SetFont(const std::string& fontname);
                        std::string& GetFont( void ) const;
                        void         SetColor(const GLubyte *v) {Color[0]=v[0];Color[1]=v[1];Color[2]=v[2];}
                        int          Width();
                        int          Height();
                        int          draw();
                        int          update();


                        Text (const std::string txt="", const std::string& fontname = "default");

                        //operators
                        Text& operator=( Text& copy);
                        Text& operator=(std::string& str);
                        Text& operator=(const std::string& str);

                protected:
                        NCRC_AutoPtr<Font>   font;       //< Our font
                        GLubyte Color[3];
                        int          char_widths[CHAR_WIDTH_HASH_SIZE][2]; // Character width hash table
                        int tests;

                        int flags;

        };


}
#endif
