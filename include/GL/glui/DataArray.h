/*
   GLUI-ng, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

   This library is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the 
   Free Software Foundation; either version 2.1 of the License, 
   or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License along with this library;
   if not, write to the 
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

   based on the work of Paul Rademacher (orignal software http://glui.sourceforge.net/)
*/
#ifndef __GLUI_DATAARRAY_H
#define __GLUI_DATAARRAY_H
#include <GL/glui/NonCopyableClass.h>
#include <stdint.h>
#include <GL/gl.h>

namespace GLUI
{
        class DataArray  : public NonCopyableReferenceCountedClass
        {
                public : //types
                        enum datatype { UNDEF   = 0,
                                UINT8_T = GL_UNSIGNED_BYTE,
                                INT8_T  = GL_BYTE,
                                UINT16_T= GL_UNSIGNED_SHORT,
                                INT16_T = GL_SHORT,
                                UINT32_T= GL_UNSIGNED_INT,
                                INT32_T = GL_INT,
                                FLOAT   = GL_FLOAT,
                                DOUBLE  = GL_DOUBLE
                        };
                        union pointers {
                                void*    all;
                                uint8_t* puint8;
                                int8_t* pint8;
                                uint16_t* puint16;
                                int16_t* pint16;
                                uint32_t* puint32;
                                int32_t* pint32;
                                float* pfloat;
                                double* pdouble;
                        };
                public : //variables
                        uint8_t ComponentsCount;    //< number of components per entry
                                                    //< for vertices it is the number of
                                                    //< vertices per entry (3d=3, 2d=2)
                                                    //< for color arrays, it is the number
                                                    //< of components per entry (RGBA=4, RGB=3)
                        uint32_t count;
                        datatype datatype_t;
                        pointers array;
                public: // methods
                        DataArray(uint32_t count,
                                        uint8_t ComponentsCount,
                                        datatype datatype_t);
                        DataArray(uint32_t count,
                                        uint8_t ComponentsCount,
                                        datatype datatype_t,
                                        void* data);
                        virtual ~DataArray();
                public : //operators
                        operator GLenum();
                private: //methods
                        void _DataArray(uint32_t count, uint8_t ComponentsCount, datatype datatype_t,pointers data);
                        int CpyArray(pointers data);
        };
}

#endif //__GLUI_DATAARRAY_H

