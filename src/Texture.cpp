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

#include <GL/glui/Texture.h>
#include<iostream>
#include<fstream>
#include <memory>

using namespace GLUI;
using namespace std;
#warning "clean the use of cerr and use glui loging facility"


Texture::Texture(const std::string& filename)
{
        this->filename = filename;
        TextureType = GL_TEXTURE_2D;
        texturePipeID = 0;
        ID = 0;
        data = 0;
        pdata = 0;
}

Texture::~Texture()
{
        delete[] pdata;
        pdata = NULL;
        data = NULL;
}

int  Texture::SetTexCoord(DataArray::datatype vertices_t,
                 uint8_t ComponentsCount,
                 void* vertices,
                 uint32_t count)
{
        NCRC_AutoPtr<DataArray> array(new DataArray(count, ComponentsCount, vertices_t, vertices));
        TexCoord = array;
}


int Texture::Finalise()
{
        glBindTexture(TextureType,ID);
        glTexImage2D (
                        TextureType,
                        0,
                        this->ComponentsCount,
                        this->width,
                        this->height,
                        0,
                        this->format,
                        this->type,
                        pdata
                     );
        glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

int Texture::SetTexCoord(NCRC_AutoPtr<DataArray> array)
{
        this->TexCoord = array;
        return 0;
}

NCRC_AutoPtr<DataArray> Texture::GetTexCoord()
{
        return this->TexCoord;
}

int32_t Texture::Width()
{
        return this->width;
}

int32_t Texture::Height()
{
        return this->height;
}

void Texture::Flip()
{
        uint8_t* lineBuffer = new uint8_t[this->BitsPerPixel * width * height];
        for (int j=0; j <= (height/2); j++)
        {
                memcpy(lineBuffer, 
                                pdata + j*width*BitsPerPixel, 
                                sizeof(uint8_t)*width*BitsPerPixel);
                memcpy(pdata + j*width*BitsPerPixel, 
                                pdata + (height - j)*width*BitsPerPixel,
                                sizeof(uint8_t)*width*BitsPerPixel);
                memcpy(pdata + (height - j)*width*BitsPerPixel,
                                lineBuffer, 
                                sizeof(uint8_t)*width*BitsPerPixel);
        }
        delete lineBuffer;
}

/////////////////////////////////////////////////////////////////////////////
void Texture::ClientActiveTexture( GLenum texture )
{
        if (ID == 0)
        {
                glGenTextures(1,&(this->ID));
                Finalise();
        }
        texturePipeID = texture;
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisable( GL_BLEND );
        glClientActiveTexture(texturePipeID);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(TexCoord->ComponentsCount,
                        (GLenum)*(TexCoord),
                        0,
                        TexCoord->array.all);

        //bind the primary texture to the first texture unit
        glActiveTextureARB( texturePipeID );
        glEnable( TextureType );
        glBindTexture( TextureType, ID);

}

////////////////////////////////////////////////////////////////////////////
void Texture::ReleaseTecture()
{
        //unbind the texture occupying the second texture unit
        glActiveTextureARB( texturePipeID );
        glDisable( TextureType );
        glBindTexture( TextureType, 0 );
        texturePipeID = 0;
}


/////////////////////////////////////////////////////////////////////////////
///////////////////////        PPM  Loader         //////////////////////////
/////////////////////////////////////////////////////////////////////////////

PPMTexture::PPMTexture(const std::string& filename) : Texture(filename)
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
        fp >> this->BitsPerPixel;
        switch (this->BitsPerPixel)
        {
                case 255 : 
                        this->BitsPerPixel = 32;
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

        pdata = new  uint8_t[this->BitsPerPixel * width * height];
        if (!pdata)
        {
                cerr <<  "Unable to allocate memory\n";
                throw 0;
        }

        fp.read((char*)pdata, this->BitsPerPixel*width*height );
        if (fp.bad())
        {
                cerr <<  "Error loading image " << filename << endl;
                throw 0;
        }

        fp.close();
        Flip();
        data = const_cast<const uint8_t*>(pdata);
}

