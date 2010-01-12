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
        NonCopyableReferenceCountedClass::addReference();
        this->filename = filename;
}

Texture::~Texture()
{
        delete[] pdata;
        pdata = NULL;
        data = NULL;
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


int Texture::SetTexCoord(NCRC_AutoPtr<DataArray> array)
{
        this->Array = array;
        return 0;
}

 int  Texture::SetTexCoord(DataArray::datatype vertices_t,
                 uint8_t ComponentsCount,
                 DataArray::pointers vertices,
                 uint32_t count)
{
        NCRC_AutoPtr<DataArray> array(new DataArray(count, ComponentsCount, vertices_t, vertices));
        Array = array;
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

        fp.read(buff, this->BitsPerPixel);
        if (fp.bad()){
                cerr <<"Unable to open file " << filename << endl;
                throw 0;
        }

        if (buff[0] != 'P' || buff[1] != '6'){
                cerr << "Invalid image format (must be `P6')\n" ;
                throw 0;
        }

        if (buff[2] != 0x0a)
                fp.seekg(-1,ios::cur);

        while (fp.read(buff, 1), buff[0] == '#'){
                lig_comm++;
                while (fp.read(buff, 1), buff[0] != '\n');
        }

        fp.seekg(-1,ios::cur);

        fp >> width;
        fp >> height;
        if (fp.bad()){
                cerr << "Error loading image " << filename << endl ;
                throw 0;
        }

        fp >> maxval;
        if (fp.bad()){
                cerr << "Error loading image " << filename << endl ;
                throw 0;
        }

        while (fp.read(buff, 1), buff[0] != '\n')
                ;

        pdata = new  uint8_t[this->BitsPerPixel * width * height];
        if (!data)
        {
                cerr <<  "Unable to allocate memory\n";
                throw 0;
        }

        fp.read((char*)data, this->BitsPerPixel*width*height );
        if (fp.bad())
        {
                cerr <<  "Error loading image " << filename << endl;
                throw 0;
        }

        fp.close();
        Flip();
        data = const_cast<const uint8_t*>(pdata);
}

