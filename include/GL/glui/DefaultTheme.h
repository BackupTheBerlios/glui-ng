#ifndef __DEFAULTTHEME_H
#define __DEFAULTTHEME_H
#include <GL/glui/themes.h>
namespace GLUI
{
        class  VertexObject;

        class _DefaultTheme : public theme
        {
                public : 
                        _DefaultTheme();
                        virtual int draw();
                        virtual int update();
                        virtual VertexObject* raised_box( uint32_t w,
                                        uint32_t h,
                                                          uint32_t thickness = 1);
                        virtual VertexObject* lowered_box( uint32_t w,
                                                           uint32_t h,
                                                           uint32_t thickness = 1);
                        void SetBorderColor(uint8_t border_color[4]);
                        void SetBkgdColor(uint8_t bkgd_color[4]);
                        void SetActivatedColor(uint8_t activated_color[4]);
                        void SetHoverColor(uint8_t hover_color[4]);
                        void GetBorderColor(uint8_t border_color[4]);
                        void GetBkgdColor(uint8_t bkgd_color[4]);
                        void GetActivatedColor(uint8_t activated_color[4]);
                        void GetHoverColor(uint8_t hover_color[4]);


                public :
                        uint8_t    border_color[4];
                        uint8_t    bkgd_color[4];
                        uint8_t    activated_color[4];
                        uint8_t    hover_color[4];
        };

}
#endif
