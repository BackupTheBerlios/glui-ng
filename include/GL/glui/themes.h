#ifndef __GLUI_THEMES_H
#define __GLUI_THEMES_H

/*

  themes.h : themes for glui

  GLUI User Interface Toolkit 
  Copyright (c) 2008 MALET Jean-Luc

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

*/
#include <GL/gl.h>

namespace GLUI
{
        class Control;
        class Container;


        class theme
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
                        virtual void PostRedisplay(Control* ctrl);
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
