#ifndef __DEFAULTTHEME_H
#define __DEFAULTTHEME_H
#include <GL/glui/themes.h>
namespace GLUI
{
        class Arcball;
        class Button;
        //class ToggleButton;
        class TextButton;
        class VertexObject;
        class DefaultTheme;

        class DefaultThemeData : public themeData
        {
                private :
                        DefaultThemeData();
                public:
                        DefaultThemeData(Control& owner, theme* NewTheme);
                protected:
                        DefaultTheme* TheDefaultTheme;
        };

        class DefaultButtonTheme : public DefaultThemeData
        {
                public : //methods
                        DefaultButtonTheme(Control& owner, theme* NewTheme) : DefaultThemeData(owner,NewTheme) {};
                        ~DefaultButtonTheme();
                        virtual int draw();
                        virtual int update();
                protected: //variable

                        VertexObject* un_pressed;
                        VertexObject* pressed;
        };

/*        class DefaultToggleButtonTheme : public DefaultThemeData
        {
                public : //methods
                        DefaultToggleButtonTheme(Control& owner, theme* NewTheme) : DefaultThemeData(owner,NewTheme);
                        virtual int draw();
                        virtual int update();
                protected: //variable

        };
        */


        class DefaultTextButtonTheme : public DefaultThemeData
        {
                public : //methods
                        DefaultTextButtonTheme(Control& owner, theme* NewTheme) : DefaultThemeData(owner,NewTheme) {};
                        virtual int draw();
                        virtual int update();
                protected: //variable
        };


        class DefaultArcballTheme : public DefaultThemeData
        {
                public : //methods
                        DefaultArcballTheme(Control& owner, theme* NewTheme) : DefaultThemeData(owner,NewTheme) {};
                        virtual int draw();
                        virtual int update();
                protected: //variable
        };

        class DefaultTheme : public theme
        {
                public : 
                        DefaultTheme();
                        virtual themeData* GetData(Control& ctrl);
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
