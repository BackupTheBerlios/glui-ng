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
#include <GL/glui/drawinghelpers.h>
#include <string.h>
#include <stdint.h>

using namespace GLUI;

////////////////////////////////////////////////////////////
void theme::FillglColorPointer(GLint size,
        GLenum type,
        GLsizei stride,
        const GLvoid *pointer,
        uint32_t count)
{
    if (!(
                (size >= 3 || size <= 4) &&
                (type == GL_BYTE           ||
                 type == GL_UNSIGNED_BYTE  ||
                 type == GL_SHORT          ||
                 type == GL_UNSIGNED_SHORT ||
                 type == GL_INT            ||
                 type == GL_UNSIGNED_INT   ||
                 type == GL_FLOAT          ||
                 type == GL_DOUBLE)    &&
                ( pointer != NULL )
         )
       )
    {
        throw(GL_INVALID_VALUE);
    }
    void *CurrentPos;
    for (uint32_t i=0; i<count; i++)
    {
        switch (type)
        {
            case GL_BYTE:
                CurrentPos = (void*)(((int8_t *) pointer ) + i * size * (stride+1));
                break;
            case GL_SHORT:
                CurrentPos = (void*)(((int16_t *) pointer ) + i * size * (stride+1));
                break;
            case GL_INT:
                CurrentPos = (void*)(((int32_t *) pointer ) + i * size * (stride+1));
                break;
            case GL_UNSIGNED_BYTE:
                CurrentPos = (void*)(((uint8_t *) pointer ) + i * size * (stride+1));
                break;
            case GL_UNSIGNED_SHORT:
                CurrentPos = (void*)(((uint16_t *) pointer ) + i * size * (stride+1));
                break;
            case GL_UNSIGNED_INT:
                CurrentPos = (void*)(((uint32_t *) pointer ) + i * size * (stride+1));
                break;
            case GL_FLOAT:
                CurrentPos = (void*)(((float *) pointer ) + i * size * (stride+1));
                break;
            case GL_DOUBLE:
                CurrentPos = (void*)(((double *) pointer ) + i * size * (stride+1));
                break;
        }


        drawinghelpers::ConvertglColorPointer(size, GL_UNSIGNED_BYTE, bkgd_color, type, CurrentPos);
    }
    return;
}
////////////////////////////////////////////////////////////
theme::theme()
{
	bkgd_color[0] = 236; //red
	bkgd_color[1] = 233; //green
	bkgd_color[2] = 216; //blue
    bkgd_color[3] = 0; //alpha
}
////////////////////////////////////////////////////////////
theme* theme::Instance()
{
	static theme TheTheme;
	return &TheTheme;
}
////////////////////////////////////////////////////////////
uint8_t* theme::Get_bkgd_color()
{
#warning "protect this with a const cast"
    return bkgd_color;
}
////////////////////////////////////////////////////////////
void theme::GetVersion(uint32_t* Major, uint32_t* Minor, uint32_t* revision)
{
    *Major = 0;
    *Minor = 0;
    *revision = 0;
}
////////////////////////////////////////////////////////////
void theme::DoLightning()
{
#warning "glPushAttrib"
/*    glDisable ( GL_LIGHTING );

    //< http://jerome.jouvie.free.fr/OpenGl/Tutorials/Tutorial13.php
    glEnable ( GL_LIGHTING );
    GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightDiffuse[]= { 0.2f, 0.5f, 0.5f, 1.0f };
    GLfloat LightPosition[]= { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
    glEnable(GL_LIGHT1);
*/
}

