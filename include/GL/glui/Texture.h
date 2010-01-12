#ifndef __GLUI_TEXTURE_H
#define __GLUI_TEXTURE_H

/*
   GLUI, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

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
*/
#include <cstring>
#include <string>
#include <stdint.h>
#include <GL/gl.h>
#include <GL/glui/NonCopyableClass.h>
#include <GL/glui/DataArray.h>
#include <GL/glui/SmartPointer.h>

namespace GLUI
{
        class Texture : public NonCopyableReferenceCountedClass
        {
                public :
                        Texture(const std::string& filename);
                        int SetTexCoord(DataArray::datatype vertices_t,
                                        uint8_t ComponentsCount,
                                        DataArray::pointers vertices,      //< buffer to the array
                                        uint32_t count);
                        int SetTexCoord(NCRC_AutoPtr<DataArray> array);
                        virtual ~Texture();
                        int32_t Width();
                        int32_t Height();
                        const uint8_t* data;
                public: //operator
                        Texture& operator=(const Texture&);
                protected:
                        void Flip();
                protected :
                        NCRC_AutoPtr<DataArray> Array;
                        uint8_t* pdata;
                        std::string filename;
                        int32_t width;
                        int32_t height;
                        uint8_t BitsPerPixel;
        };

        class PPMTexture : public Texture
        {
                public :
                        PPMTexture(const std::string& filename);
        };
}

#endif //__GLUI_TEXTURE_H

