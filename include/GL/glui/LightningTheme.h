#ifndef __LIGHTNINGTHEME_H
#define __LIGHTNINGTHEME_H
#include <GL/glui/themes.h>

namespace GLUI
{
        class VertexObject;
        class LigthningTheme : public theme
        {
                public :

                        void DoLightning();
                        uint8_t* Get_bkgd_color();
                protected:
                        virtual VertexObject* raised_box( uint32_t w,
                                                          uint32_t h,
                                                          uint32_t thickness = 0,
                                                          uint8_t size = 3,
                                                          GLenum intype = GL_BYTE,
                                                          void *color_array = NULL );
                        virtual VertexObject* lowered_box( uint32_t w,
                                                           uint32_t h,
                                                           uint32_t thickness = 0,
                                                           uint8_t size = 3,
                                                           GLenum intype = GL_BYTE,
                                                           void *color_array = NULL );
                protected :
                        uint8_t    bkgd_color[4];

        };

        class LigthningWindowTheme : public LigthningTheme
        {
                public :
                        virtual int draw();
                        virtual int update();
        };


}
#endif

