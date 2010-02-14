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

#include <GL/glui/Texture.h>
#include<iostream>
#include<fstream>
#include <memory>

using namespace GLUI;
using namespace std;
#warning "clean the use of cerr and use glui loging facility"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////            TEXTURE CLASS         //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Texture::Texture()
{
        ID = 0;
        texturepipeid = 0;
}

//////////////////////////////////////////////////////////////////////////////
Texture::Texture(NCRC_AutoPtr<DataArray> TexCoord,
                NCRC_AutoPtr<TextureData> TexData)
{
        ID = 0;
        texturepipeid = 0;
        this->TexCoord = TexCoord;
        this->TexData = TexData;
}


//////////////////////////////////////////////////////////////////////////////
int  Texture::SetTexCoord(DataArray::datatype vertices_t,
                 uint8_t ComponentsCount,
                 void* vertices,
                 uint32_t count)
{
        NCRC_AutoPtr<DataArray> array(new DataArray(count, ComponentsCount, vertices_t, vertices));
        TexCoord = array;
}

///////////////////////////////////////////////////////////////////////////
int Texture::SetTexCoord(NCRC_AutoPtr<DataArray> array)
{
        this->TexCoord = array;
        return 0;
}

/////////////////////////////////////////////////////////////////////////////
NCRC_AutoPtr<DataArray> Texture::GetTexCoord()
{
        return this->TexCoord;
}

#warning "todo : make an autotype detection and loading"
////////////////////////////////////////////////////////////////////////////
//int Texture::SetTexData(const std::string& filename)
//{
//}
////////////////////////////////////////////////////////////////////////////
int Texture::SetTexData(NCRC_AutoPtr<TextureData> data)
{
        this->TexData = data;
        return 0;
}
////////////////////////////////////////////////////////////////////////////
NCRC_AutoPtr<TextureData> Texture::GetTexData()
{
        return this->TexData;
}

/////////////////////////////////////////////////////////////////////////////
int Texture::Finalise()
{
        glBindTexture(TexData->TextureType(),ID);
        //glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        glTexImage2D (
                        TexData->TextureType(),
                        0,
                        TexData->ComponentsCount(),
                        TexData->Width(),
                        TexData->Height(),
                        0,
                        TexData->Format(),
                        TexData->Type(),
                        TexData->data
                     );
        glTexParameteri(TexData->TextureType(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(TexData->TextureType(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//////////////////////////////////////////////////////////////////////////////
void Texture::ClientActiveTexture( GLenum texture )
{
        texturepipeid = texture;
        glEnable( TexData->TextureType() );
        glActiveTextureARB( texturepipeid );
        glClientActiveTexture(texturepipeid);

        if (ID == 0)
        {
                GLuint textureID;
                glGenTextures(1,&textureID);
                this->ID = textureID;
                Finalise();
        }
        glDisable( GL_BLEND );
        glBindTexture(TexData->TextureType(),ID);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(TexCoord->ComponentsCount,
                        (GLenum)*(TexCoord),
                        0,
                        TexCoord->array.all);

}
////////////////////////////////////////////////////////////////////////////
void Texture::ReleaseTexture()
{
        //unbind the texture occupying the second texture unit
        glActiveTextureARB( texturepipeid );
        glDisable( TexData->TextureType() );
        texturepipeid = 0;
}


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////        TEXTUREDATA CLASS         //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

TextureData::TextureData(const std::string& filename)
{
        this->filename = filename;
        texturetype = GL_TEXTURE_2D;
        data = 0;
        pdata = 0;
}

//////////////////////////////////////////////////////////////////////////////
TextureData::~TextureData()
{
        delete[] pdata;
        pdata = NULL;
        data = NULL;
}



//////////////////////////////////////////////////////////////////////////////
int32_t TextureData::Width()
{
        return this->width;
}

//////////////////////////////////////////////////////////////////////////////
int32_t TextureData::Height()
{
        return this->height;
}

//////////////////////////////////////////////////////////////////////////////
GLenum TextureData::TextureType()
{
        return this->texturetype;
}

//////////////////////////////////////////////////////////////////////////////
GLenum TextureData::Format()
{
        return this->format;
}

//////////////////////////////////////////////////////////////////////////////
GLenum TextureData::Type()
{
        return this->type;
}



//////////////////////////////////////////////////////////////////////////////
int32_t TextureData::OctetsPerPixel()
{
        return this->octetsperpixel;
}

//////////////////////////////////////////////////////////////////////////////
int8_t TextureData::ComponentsCount()
{
        return this->componentscount;
}

//////////////////////////////////////////////////////////////////////////////
void TextureData::Flip()
{
        uint8_t* lineBuffer = NULL;
        lineBuffer = new uint8_t[this->octetsperpixel * this->width ];
        for (int j=0; j <= (this->height/2); j++)
        {
                memcpy(lineBuffer, 
                                pdata + j*this->width*octetsperpixel, 
                                sizeof(uint8_t)*this->width*octetsperpixel);
                memcpy(pdata + j*this->width*octetsperpixel, 
                                pdata + (this->height - j - 1 )*this->width*octetsperpixel,
                                sizeof(uint8_t)*this->width*octetsperpixel);
                memcpy(pdata + (this->height - j)*this->width*octetsperpixel,
                                lineBuffer, 
                                sizeof(uint8_t)*this->width*octetsperpixel);
        }
        delete[] lineBuffer;
}





/////////////////////////////////////////////////////////////////////////////
///////////////////////        PPM  Loader         //////////////////////////
/////////////////////////////////////////////////////////////////////////////

PPMTexture::PPMTexture(const std::string& filename) : TextureData(filename)
{
        char buff[16];

        ifstream fp(filename.c_str(), ios::in|ios::binary);
        int maxval,lig_comm=0;

        if (!fp.is_open()){
                cerr <<"Unable to open file " << filename << endl;
                throw 0;
        }

        fp.read(buff,3);
        if (fp.bad())
        {
                cerr << "Error loading image " << filename << endl ;
                throw 0;
        }


        if (buff[0] != 'P' || buff[1] != '6')
        {
                cerr << "Invalid image format (must be `P6')\n" ;
                throw 0;
        }

        if (buff[2] != '\n' && buff[2] != '\t' && buff[2] != ' ')
        {
                 cerr << "Invalid image format (delimiter must be a newline or a tab or a space)\n" ;
                throw 0;
       }

        while (fp.read(buff, 1), buff[0] == '#'){
                lig_comm++;
                while (fp.read(buff, 1), buff[0] != '\n');
        }
        fp.seekg(-1,ios::cur);

        fp >> this->width;
        fp >> this->height;
        int32_t BitsPerPixel;
        fp >> BitsPerPixel;
        switch (BitsPerPixel)
        {
                case 255 : 
                        this->octetsperpixel = 3;
                        this->componentscount = 3;
                        this->format = GL_RGB;
                        this->type = GL_UNSIGNED_BYTE;
                        break;
                default   :
                             cerr << "Invalid image format (max value uknown)\n" ;
                             throw 0;
        }
        if (fp.bad()){
                cerr << "Error loading image " << filename << endl ;
                throw 0;
        }

        while (fp.read(buff, 1), buff[0] != '\n')
                ;

        pdata = new  uint8_t[this->octetsperpixel * this->width * this->height];
        if (!pdata)
        {
                cerr <<  "Unable to allocate memory\n";
                throw 0;
        }

        fp.read((char*)pdata, this->octetsperpixel * this->width * this->height );
        if (fp.bad())
        {
                cerr <<  "Error loading image " << filename << endl;
                throw 0;
        }

        fp.close();
        //Flip();
        data = const_cast<const uint8_t*>(pdata);
}

