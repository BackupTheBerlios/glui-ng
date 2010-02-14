#ifndef __GLUI_THEMES_H
#define __GLUI_THEMES_H
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
#include <GL/gl.h>
#include <GL/glui/NonCopyableClass.h>

namespace GLUI
{
        class Control;
        class Container;


        class theme : public NonCopyableReferenceCountedClass
        {
                public:
                        virtual int draw()=0;
                        virtual int update()=0;
                        virtual ~theme();
               protected :
                        theme( void );
                        void FillglColorPointer(
                                        uint8_t *inColor, //< array of 4 uint8_t color elements
                                        GLint size,       //< numbers of elements per colors (3=RGB 4=RGBA)
                                        GLenum type,                      //< type of the array to fill
                                        GLsizei stride,                   //< if the array is interlaved with vectors
                                        const GLvoid *pointer,            //< pointer to the array
                                        uint32_t count );                 //< numbers of colors entries
                        static void ConvertglColorPointer(
                                        GLint size, //<  how many components 3 (RGB) or 4(RGBA)
                                        GLenum intype,  //< type of the input
                                        const GLvoid *inpointer, //< pointer of the datas
                                        GLenum outype,  //< type of the output
                                        const GLvoid *outpointer  //<pointer to the outputdata
                                        );
                        static void ConvertglColorArray(
                                        GLint size, //<  how many components 3 (RGB) or 4(RGBA)
                                        GLenum intype,  //< type of the input
                                        const GLvoid *inpointer, //< pointer of the datas
                                        GLenum outype,  //< type of the output
                                        const GLvoid *outpointer,  //<pointer to the outputdata
                                        uint32_t count //< count of the numbers of elements in the array (an element in 3 or 4 components)
                                        );
                private:
        };


 
        theme* GetTheme(const Control& ctrl);


}

//IDEA :
//theme shall be singleton patern, the constructor shall use GLUI_THEME environment variable
//
//HOWTO write a theme :
//a theme is a set of widgets that derivate from the base widgets of this library, like this you're
//allowed to override your custom methods like drawing methods... the theme interface is only a set
//of C functions that call your constructor and return a pointer to the object or NULL on error.

#endif //__GLUI_THEMES_H
