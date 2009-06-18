#ifndef __DEFAULTTHEME_H
#define __DEFAULTTHEME_H
#include <GL/glui/themes.h>
namespace GLUI
{
        class Arcball;
        class Button;
        class ToggleButton;
        class TextButton;
        class VertexObject;
        class DefaultTheme;

        class DefaultThemeData : public themeData
        {
                private :
                        DefaultThemeData();
                public:
                        DefaultThemeData(DefaultTheme& TheTheme);
                protected:
                        DefaultTheme& TheTheme;
        };

        class DefaultButtonTheme : public DefaultThemeData
        {
                public : //methods
                        DefaultButtonTheme(theme& TheTheme, Control& owner);
                        ~DefaultButtonTheme();
                        virtual int draw();
                        virtual int update();
                protected: //variable

                        VertexObject* un_pressed;
                        VertexObject* pressed;
        };

        class DefaultToggleButtonTheme : public DefaultThemeData
        {
                public : //methods
                        DefaultToggleButtonTheme(theme& TheTheme, Control& owner);
                        virtual int draw();
                        virtual int update();
                protected: //variable

        };


        class DefaultTextButtonTheme : public DefaultThemeData
        {
                public : //methods
                        DefaultTextButtonTheme(theme& TheTheme, Control& owner);
                        virtual int draw();
                        virtual int update();
                protected: //variable
        };


        class DefaultArcballTheme : public DefaultThemeData
        {
                public : //methods
                        DefaultArcballTheme(theme& TheTheme, Control& owner);
                        virtual int draw();
                        virtual int update();
                protected: //variable
        };

        class DefaultTheme : public theme
        {
                public : 
                        DefaultTheme();
                        void PostRedisplay(Control* ctrl);
                        virtual VertexObject* raised_box( uint32_t w,
                                                          uint32_t h,
                                                          uint32_t thickness = 1);
                        virtual VertexObject* lowered_box( uint32_t w,
                                                           uint32_t h,
                                                           uint32_t thickness = 1);

                protected :
                        uint8_t    border_color[4];
                        uint8_t    bkgd_color[4];
                        uint8_t    activated_color[4];
                        uint8_t    hover_color[4];
        };
}
#endif
