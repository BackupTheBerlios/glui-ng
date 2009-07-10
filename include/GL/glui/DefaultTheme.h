#ifndef __DEFAULTTHEME_H
#define __DEFAULTTHEME_H
#include <GL/glui/themes.h>
namespace GLUI
{
        class  VertexObject;

        class DefaultTheme : public theme
        {
                public : 
                        DefaultTheme();
                        virtual VertexObject* raised_box( uint32_t w,
                                                          uint32_t h,
                                                          uint32_t thickness = 1);
                        virtual VertexObject* lowered_box( uint32_t w,
                                                           uint32_t h,
                                                           uint32_t thickness = 1);

                protected :
                        static uint8_t    border_color[4];
                        static uint8_t    bkgd_color[4];
                        static uint8_t    activated_color[4];
                        static uint8_t    hover_color[4];
        };

        class DefaultThemeData : public themeData
        {
                public:
                        DefaultThemeData();
                protected:
                        DefaultTheme TheDefaultTheme;
        };




        int SetDefaultTheme(Control& ctrl);
}
#endif
