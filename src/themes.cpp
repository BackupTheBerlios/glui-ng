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
#include <GL/glui/DefaultTheme.h>
#include <GL/glui/container.h>
#include <GL/glui/Exception.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


using namespace GLUI;
//////////////////////////////////////////////////////////////////////////
theme* GLUI::GetTheme(const Control& ctrl)
{
        if (NULL != getenv("GLUI_THEME"))
        {
                //todo dlopen the theme,
                // get the handle,
                // update currentTheme
        }
        return NULL;
}
////////////////////////////////////////////////////////////
theme::theme()
{
}
////////////////////////////////////////////////////////////
theme::~theme()
{
}

////////////////////////////////////////////////////////////
// fill a array of pixels with the same color
// a color is a pointer to an array of uint8_t
void theme::FillglColorPointer(
        uint8_t *inColor,
        GLint size,
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


        ConvertglColorPointer(size, GL_UNSIGNED_BYTE, inColor, type, CurrentPos);
    }
    return;
}
////////////////////////////////////////////////////////////////////////////
// convert a pointer to a pixel color type to another type
// a pixel is an array of components (RGB or RGBA)
void theme::ConvertglColorPointer(GLint size, //<  how many components 3 (RGB) or 4(RGBA)
                    GLenum intype,  //< type of the input
                    const GLvoid *inpointer, //< pointer of the datas
                    GLenum outype,  //< type of the output
                    const GLvoid *outpointer  //<pointer to the outputdata
                    )
{
    if (!(
                (size >= 3 || size <= 4) &&
                (intype == GL_BYTE           ||
                 intype == GL_UNSIGNED_BYTE  ||
                 intype == GL_SHORT          ||
                 intype == GL_UNSIGNED_SHORT ||
                 intype == GL_INT            ||
                 intype == GL_UNSIGNED_INT   ||
                 intype == GL_FLOAT          ||
                 intype == GL_DOUBLE)    &&
                (outype == GL_BYTE           ||
                 outype == GL_UNSIGNED_BYTE  ||
                 outype == GL_SHORT          ||
                 outype == GL_UNSIGNED_SHORT ||
                 outype == GL_INT            ||
                 outype == GL_UNSIGNED_INT   ||
                 outype == GL_FLOAT          ||
                 outype == GL_DOUBLE)    &&
                ( inpointer != NULL )    &&
                ( outpointer != NULL )
         )
         )
         {
        throw(GL_INVALID_VALUE);
    }
    double colorelem[4];
    colorelem[3] = 0.0;
    switch (intype)
    {
        case GL_BYTE :
            {
                int8_t *bkgd_color = (int8_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / INT8_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / INT8_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / INT8_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / INT8_MAX;
            }
            break;
        case GL_UNSIGNED_BYTE :
            {
                uint8_t *bkgd_color = (uint8_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / UINT8_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / UINT8_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / UINT8_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / UINT8_MAX;
            }
            break;
        case GL_SHORT:
            {
                int16_t *bkgd_color = (int16_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / INT16_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / INT16_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / INT16_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / INT16_MAX;
            }
            break;
        case GL_UNSIGNED_SHORT:
            {
                uint16_t *bkgd_color = (uint16_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / UINT16_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / UINT16_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / UINT16_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / UINT16_MAX;
            }
            break;
        case GL_INT:
            {
                int32_t *bkgd_color = (int32_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / INT32_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / INT32_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / INT32_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / INT32_MAX;
            }
            break;
        case GL_UNSIGNED_INT:
            {
                uint32_t *bkgd_color = (uint32_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / UINT32_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / UINT32_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / UINT32_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / UINT32_MAX;
            }
            break;
        case GL_FLOAT:
            {
                float *bkgd_color = (float*) inpointer;
                colorelem[0] = (double)bkgd_color[0];
                colorelem[1] = (double)bkgd_color[1];
                colorelem[2] = (double)bkgd_color[2];
                if (size==4) colorelem[3] = (double)bkgd_color[3];
            }
            break;
        case GL_DOUBLE:
            {
                double *bkgd_color = (double*) inpointer;
                colorelem[0] = (double)bkgd_color[0];
                colorelem[1] = (double)bkgd_color[1];
                colorelem[2] = (double)bkgd_color[2];
                if (size==4) colorelem[3] = (double)bkgd_color[3];
            }
            break;
        default:
            throw(GL_INVALID_VALUE);
    }
    switch (outype)
    {
        case GL_BYTE :
            {
                int8_t *bkgd_color = (int8_t*) outpointer;
                bkgd_color[0] = (int8_t)(colorelem[0] * INT8_MAX);
                bkgd_color[1] = (int8_t)(colorelem[1] * INT8_MAX);
                bkgd_color[2] = (int8_t)(colorelem[2] * INT8_MAX);
                if (size==4) bkgd_color[3] = (int8_t)(colorelem[3] * INT8_MAX);
            }
            break;
        case GL_UNSIGNED_BYTE :
            {
                uint8_t *bkgd_color = (uint8_t*) outpointer;
                bkgd_color[0] = (uint8_t)(colorelem[0] * UINT8_MAX);
                bkgd_color[1] = (uint8_t)(colorelem[1] * UINT8_MAX);
                bkgd_color[2] = (uint8_t)(colorelem[2] * UINT8_MAX);
                if (size==4) bkgd_color[3] = (uint8_t)(colorelem[3] * UINT8_MAX);
            }
            break;
        case GL_SHORT:
            {
                int16_t *bkgd_color = (int16_t*) outpointer;
                bkgd_color[0] = (int16_t)(colorelem[0] * INT16_MAX);
                bkgd_color[1] = (int16_t)(colorelem[1] * INT16_MAX);
                bkgd_color[2] = (int16_t)(colorelem[2] * INT16_MAX);
                if (size==4) bkgd_color[3] = (int16_t)(colorelem[3] * INT16_MAX);
            }
            break;
        case GL_UNSIGNED_SHORT:
            {
                uint16_t *bkgd_color = (uint16_t*) outpointer;
                bkgd_color[0] = (uint16_t)(colorelem[0] * UINT16_MAX);
                bkgd_color[1] = (uint16_t)(colorelem[1] * UINT16_MAX);
                bkgd_color[2] = (uint16_t)(colorelem[2] * UINT16_MAX);
                if (size==4) bkgd_color[3] = (uint16_t)(colorelem[3] * UINT16_MAX);
            }
            break;
        case GL_INT:
            {
                int32_t *bkgd_color = (int32_t*) outpointer;
                bkgd_color[0] = (int32_t)(colorelem[0] * INT32_MAX);
                bkgd_color[1] = (int32_t)(colorelem[1] * INT32_MAX);
                bkgd_color[2] = (int32_t)(colorelem[2] * INT32_MAX);
                if (size==4) bkgd_color[3] = (int32_t)(colorelem[3] * INT32_MAX);
            }
            break;
        case GL_UNSIGNED_INT:
            {
                uint32_t *bkgd_color = (uint32_t*) outpointer;
                bkgd_color[0] = (uint32_t)(colorelem[0] * UINT32_MAX);
                bkgd_color[1] = (uint32_t)(colorelem[1] * UINT32_MAX);
                bkgd_color[2] = (uint32_t)(colorelem[2] * UINT32_MAX);
                if (size==4) bkgd_color[3] = (uint32_t)(colorelem[3] * UINT32_MAX);
            }
            break;
        case GL_FLOAT:
            {
                float *bkgd_color = (float*) outpointer;
                bkgd_color[0] = (float)colorelem[0];
                bkgd_color[1] = (float)colorelem[1];
                bkgd_color[2] = (float)colorelem[2];
                if (size==4) bkgd_color[3] = (float)colorelem[3];
            }
            break;
        case GL_DOUBLE:
            {
                double *bkgd_color = (double*) outpointer;
                bkgd_color[0] = (double)colorelem[0];
                bkgd_color[1] = (double)colorelem[1];
                bkgd_color[2] = (double)colorelem[2];
                if (size==4) bkgd_color[3] = (double)colorelem[3];
            }
            break;
        default:
            throw(GL_INVALID_VALUE);
    }
}

////////////////////////////////////////////////////////////////////////////
// convert an array of pixels from one type into another
// a pixel is an array of components (RGB or RGBA)
void theme::ConvertglColorArray(
                    GLint size, //<  how many components 3 (RGB) or 4(RGBA)
                    GLenum intype,  //< type of the input
                    const GLvoid *inpointer, //< pointer of the datas
                    GLenum outype,  //< type of the output
                    const GLvoid *outpointer,  //<pointer to the outputdata
                    uint32_t count //< count of the numbers of elements in the array (an element in 3 or 4 components)
                    )
{
    if (!(
                (size >= 3 || size <= 4) &&
                (intype == GL_BYTE           ||
                 intype == GL_UNSIGNED_BYTE  ||
                 intype == GL_SHORT          ||
                 intype == GL_UNSIGNED_SHORT ||
                 intype == GL_INT            ||
                 intype == GL_UNSIGNED_INT   ||
                 intype == GL_FLOAT          ||
                 intype == GL_DOUBLE)    &&
                (outype == GL_BYTE           ||
                 outype == GL_UNSIGNED_BYTE  ||
                 outype == GL_SHORT          ||
                 outype == GL_UNSIGNED_SHORT ||
                 outype == GL_INT            ||
                 outype == GL_UNSIGNED_INT   ||
                 outype == GL_FLOAT          ||
                 outype == GL_DOUBLE)    &&
                ( inpointer != NULL )    &&
                ( outpointer != NULL )
         )
         )
           {
             throw(GL_INVALID_VALUE);
           }

    void *CurrentInPos;
    void *CurrentOutPos;
    for (uint32_t i=0; i<count; i++)
    {
        switch (intype)
        {
            case GL_BYTE:
                CurrentInPos = (void*)(((int8_t *) inpointer ) + i * size);
                break;
            case GL_SHORT:
                CurrentInPos = (void*)(((int16_t *) inpointer ) + i * size);
                break;
            case GL_INT:
                CurrentInPos = (void*)(((int32_t *) inpointer ) + i * size);
                break;
            case GL_UNSIGNED_BYTE:
                CurrentInPos = (void*)(((uint8_t *) inpointer ) + i * size);
                break;
            case GL_UNSIGNED_SHORT:
                CurrentInPos = (void*)(((uint16_t *) inpointer ) + i * size);
                break;
            case GL_UNSIGNED_INT:
                CurrentInPos = (void*)(((uint32_t *) inpointer ) + i * size);
                break;
            case GL_FLOAT:
                CurrentInPos = (void*)(((float *) inpointer ) + i * size);
                break;
            case GL_DOUBLE:
                CurrentInPos = (void*)(((double *) inpointer ) + i * size);
                break;
        }
        switch (outype)
        {
            case GL_BYTE:
                CurrentOutPos = (void*)(((int8_t *) outpointer ) + i * size);
                break;
            case GL_SHORT:
                CurrentOutPos = (void*)(((int16_t *) outpointer ) + i * size);
                break;
            case GL_INT:
                CurrentOutPos = (void*)(((int32_t *) outpointer ) + i * size);
                break;
            case GL_UNSIGNED_BYTE:
                CurrentOutPos = (void*)(((uint8_t *) outpointer ) + i * size);
                break;
            case GL_UNSIGNED_SHORT:
                CurrentOutPos = (void*)(((uint16_t *) outpointer ) + i * size);
                break;
            case GL_UNSIGNED_INT:
                CurrentOutPos = (void*)(((uint32_t *) outpointer ) + i * size);
                break;
            case GL_FLOAT:
                CurrentOutPos = (void*)(((float *) outpointer ) + i * size);
                break;
            case GL_DOUBLE:
                CurrentOutPos = (void*)(((double *) outpointer ) + i * size);
                break;
        }
        ConvertglColorPointer(size, intype, CurrentInPos, outype, CurrentOutPos);
    }
    return;

}
/////////////////////////////////////////////////////////////////////////////
void theme::PostRedisplay(Control* ctrl)
{
        ::XEvent EventToForward;
        //ask for redisplay of window
        EventToForward.xexpose.type=Expose;
        EventToForward.xexpose.send_event=true;
        EventToForward.xexpose.x = ctrl->X();
        EventToForward.xexpose.y = ctrl->Y();
        EventToForward.xexpose.width = ctrl->Width();
        EventToForward.xexpose.height = ctrl->Height();
        Container* cont  = dynamic_cast<Container*>(ctrl->GetRootNode());
        if ( cont != NULL)
        {
                cont->AddEvent(&EventToForward);
        }
}


