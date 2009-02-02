/*

  glui_glut_window.h : the top level widget, in glut

  GLUI User Interface Toolkit
  Copyright (c) 2008 MALET Jean-Luc

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

#include <GL/glui/themes.h>
#include <string.h>

using namespace GLUI;


void theme::FillglColorPointer(GLint size,
        GLenum type,
        GLsizei stride,
        const GLvoid *pointer,
        uint32_t count)
{
    if (size >= 3 && size <=4)
    {
        switch (type)
        {
            case GL_BYTE :
                {
                    int8_t colorelem[4] = { bkgd_color[0] - INT8_MAX,
                        bkgd_color[1] - INT8_MAX,
                        bkgd_color[2] - INT8_MAX,
                        bkgd_color[3] - INT8_MAX };
                    for (uint32_t i=0; i<count; i++)
                    {
                        memcpy((int8_t*)pointer + size * i ,colorelem, size * sizeof(int8_t));
                    }
                    return;
                }
            case GL_UNSIGNED_BYTE :
                {
                    uint8_t colorelem[4] = { bkgd_color[0],
                        bkgd_color[1],
                        bkgd_color[2],
                        bkgd_color[3] };
                    for (uint32_t i=0; i<count; i++)
                    {
                        memcpy((uint8_t*)pointer + size * i ,colorelem, size * sizeof(uint8_t));
                    }
                    return;
                }
            case GL_SHORT:
                {
                    int16_t colorelem[4] = { bkgd_color[0] * INT16_MAX / UINT8_MAX,
                        bkgd_color[1] * INT16_MAX / UINT8_MAX,
                        bkgd_color[2] * INT16_MAX / UINT8_MAX,
                        bkgd_color[3] * INT16_MAX / UINT8_MAX };
                    for (uint32_t i=0; i<count; i++)
                    {
                        memcpy((int16_t*)pointer + size * i ,colorelem, size * sizeof(int16_t));
                    }
                    return;
                }
            case GL_UNSIGNED_SHORT:
                {
                    uint16_t colorelem[4] = { bkgd_color[0] * UINT16_MAX / UINT8_MAX,
                        bkgd_color[1] * UINT16_MAX / UINT8_MAX,
                        bkgd_color[2] * UINT16_MAX / UINT8_MAX,
                        bkgd_color[3] * UINT16_MAX / UINT8_MAX };
                    for (uint32_t i=0; i<count; i++)
                    {
                        memcpy((uint16_t*)pointer + size * i ,colorelem, size * sizeof(uint16_t));
                    }
                    return;
                }
            case GL_INT:
                {
                    int32_t colorelem[4] = { bkgd_color[0] * INT32_MAX / UINT8_MAX,
                        bkgd_color[1] * INT32_MAX / UINT8_MAX,
                        bkgd_color[2] * INT32_MAX / UINT8_MAX,
                        bkgd_color[3] * INT32_MAX / UINT8_MAX };
                    for (uint32_t i=0; i<count; i++)
                    {
                        memcpy((int32_t*)pointer + size * i ,colorelem, size * sizeof(int32_t));
                    }
                    return;
                }
            case GL_UNSIGNED_INT:
                {
                    uint32_t colorelem[4] = { bkgd_color[0] * UINT32_MAX / UINT8_MAX,
                        bkgd_color[1] * UINT32_MAX / UINT8_MAX,
                        bkgd_color[2] * UINT32_MAX / UINT8_MAX,
                        bkgd_color[3] * UINT32_MAX / UINT8_MAX };
                    for (uint32_t i=0; i<count; i++)
                    {
                        memcpy((uint32_t*)pointer + size * i ,colorelem, size * sizeof(uint32_t));
                    }
                    return;
                }
            case GL_FLOAT:
                {
                    float colorelem[4] = { (float)bkgd_color[0] * 1.0f / UINT8_MAX,
                        (float)bkgd_color[1] * 1.0f / UINT8_MAX,
                        (float)bkgd_color[2] * 1.0f / UINT8_MAX,
                        (float)bkgd_color[3] * 1.0f / UINT8_MAX };
                    for (uint32_t i=0; i<count; i++)
                    {
                        memcpy((float*)pointer + size * i ,colorelem, size * sizeof(float));
                    }
                    return;
                }
            case GL_DOUBLE:
                {
                    double colorelem[4] = { (double)bkgd_color[0] * 1.0 / UINT8_MAX,
                        (double)bkgd_color[1] * 1.0 / UINT8_MAX,
                        (double)bkgd_color[2] * 1.0 / UINT8_MAX,
                        (double)bkgd_color[3] * 1.0 / UINT8_MAX };
                    for (uint32_t i=0; i<count; i++)
                    {
                        memcpy((double*)pointer + size * i ,colorelem, size * sizeof(double));
                    }
                    return;
                }
            default:
                 throw(GL_INVALID_VALUE);
        }
    }
    else
    {
        throw(GL_INVALID_VALUE);
    }
}


theme::theme()
{
	bkgd_color[0] = 236; //red
	bkgd_color[1] = 233; //green
	bkgd_color[2] = 216; //blue
    bkgd_color[3] = 0; //alpha
}

theme* theme::Instance()
{
	static theme TheTheme;
	return &TheTheme;
}
