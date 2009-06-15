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
        class Arcball;
        class Button;
        class ToggleButton;
        class TextButton;

        class theme
        {
                public : //methods
                        static theme* Instance();
                        void FillglColorPointer(GLint size,       //< numbers of elements per colors (3=RGB 4=RGBA)
                                        GLenum type,                      //< type of the array to fill
                                        GLsizei stride,                   //< if the array is interlaved with vectors
                                        const GLvoid *pointer,            //< pointer to the array
                                        uint32_t count );                 //< numbers of colors entries
                        void DoLightning();
                        uint8_t* Get_bkgd_color();
                        int SetTheme(Control* ctrl);
                        int SetTheme(Container* cont);

                protected : //variables
                        uint8_t    bkgd_color[4];
                        int ThemeMajor;
                        int ThemeMinor;
                        int ThemeRevision;
                private : //methods
                        theme( void );
        };

        class themeData
        {
                public: //methods
                        themeData(theme& TheTheme, Control* owner);
                        virtual int draw() = 0;
                        virtual int update() = 0;
                protected:
                        Control* owner;
                private:
                        themeData() {};
        };

        class DefaultButtonTheme : public themeData
        {
                public : //methods
                        DefaultButtonTheme(theme& TheTheme, Control* owner);
                        virtual int draw();
                        virtual int update();
                protected: //variable
                        VertexObject* background;
                        VertexObject* forground_no_pressed;
                        VertexObject* forground_pressed;
                        Button* owner;

        };

        class DefaultToggleButtonTheme : public themeData
        {
                public : //methods
                        DefaultToggleButtonTheme(theme& TheTheme, Control* owner);
                        virtual int draw();
                        virtual int update();
                protected: //variable

        };


        class DefaultTextButtonTheme : public themeData
        {
                public : //methods
                        DefaultTextButtonTheme(theme& TheTheme, Control* owner);
                        virtual int draw();
                        virtual int update();
                protected: //variable
        };


        class DefaultArcballTheme : public themeData
        {
                public : //methods
                        DefaultArcballTheme(theme& TheTheme, Control* owner);
                        virtual int draw();
                        virtual int update();
                protected: //variable
        };

        class DefaultTheme : public theme
        {
                public : 
                        DefaultTheme();
        };



}

//IDEA :
//theme shall be singleton patern, the constructor shall use GLUI_THEME environment variable
//
//HOWTO write a theme :
//a theme is a set of widgets that derivate from the base widgets of this library, like this you're
//allowed to override your custom methods like drawing methods... the theme interface is only a set
//of C functions that call your constructor and return a pointer to the object or NULL on error.

#endif //__GLUI_THEMES_H
