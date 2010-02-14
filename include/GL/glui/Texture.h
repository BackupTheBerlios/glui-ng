#ifndef __GLUI_TEXTURE_H
#define __GLUI_TEXTURE_H
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
#include <cstring>
#include <string>
#include <stdint.h>
#include <GL/gl.h>
#include <GL/glui/NonCopyableClass.h>
#include <GL/glui/DataArray.h>
#include <GL/glui/SmartPointer.h>

namespace GLUI
{
        class TextureData;
        class Texture : public NonCopyableReferenceCountedClass
        {
                public : //methods
                        Texture();
                        Texture(NCRC_AutoPtr<DataArray> TexCoord,
                                        NCRC_AutoPtr<TextureData> TexData);
                        int SetTexCoord(DataArray::datatype vertices_t,
                                        uint8_t ComponentsCount,
                                        void* vertices,      //< buffer to the array
                                        uint32_t count);

                        int SetTexCoord(NCRC_AutoPtr<DataArray> array);
                        NCRC_AutoPtr<DataArray> GetTexCoord();

                        //int SetTexData(const std::string& filename);
                        int SetTexData(NCRC_AutoPtr<TextureData> data);
                        NCRC_AutoPtr<TextureData> GetTexData();

                        void ClientActiveTexture( GLenum texture );
                        void ReleaseTexture();
                protected: //methods
                        virtual int Finalise();
                protected: //data
                        NCRC_AutoPtr<DataArray> TexCoord;
                        NCRC_AutoPtr<TextureData> TexData;
                        GLuint ID; //<value returned by glGenTextures
                        GLenum texturepipeid; //<GL_TEXTURE0..

        };

        class TextureData : public NonCopyableReferenceCountedClass
        {
                public :
                        TextureData(const std::string& filename);
                        virtual ~TextureData();

                        int32_t Width();
                        int32_t Height();
                        GLenum TextureType();
                        GLenum Format();
                        GLenum Type();
                        int32_t OctetsPerPixel();
                        int8_t ComponentsCount();
                        const uint8_t* data;
                public: //operator
                        Texture& operator=(const Texture&);
                        operator GLenum();
                protected:
                        void Flip();
                protected :
                        GLenum texturetype; //< GL_TEXTURE_1D,GL_TEXTURE_2D,GL_TEXTURE_3D
                        GLenum format; //< one of the GL_RGBA, GL_RGB... 
                                       //< see man glTexImage2D
                        GLenum type;   //< one of the GL_UNSIGNED_BYTE, GL_BYTE...
                                       //< see man glTexImage2D
                        uint8_t* pdata;
                        std::string filename;
                        int32_t width;
                        int32_t height;
                        int32_t octetsperpixel;
                        int8_t componentscount;
        };

        class PPMTexture : public TextureData
        {
                public :
                        PPMTexture(const std::string& filename);
        };
}

#endif //__GLUI_TEXTURE_H

