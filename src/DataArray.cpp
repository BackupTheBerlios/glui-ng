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
#include <GL/glui/DataArray.h>
#include <GL/glui/debug.h>
#include <GL/glui/Exception.h>
#include <string.h>

#define MODULE_KEY "GLUI_DEBUG_DATAARRAY"

using namespace GLUI;
/////////////////////////////////////////////////////////////////
DataArray::~DataArray()
{
    IN("array " << this << " data@" << this->array.all << endl);
    switch (this->datatype_t)
    {
        case UINT8_T: delete[] this->array.puint8; break;
        case INT8_T: delete[] this->array.pint8; break;
        case UINT16_T: delete[] this->array.puint16; break;
        case INT16_T: delete[] this->array.pint16; break;
        case UINT32_T: delete[] this->array.puint32; break;
        case INT32_T: delete[] this->array.pint32; break;
        case FLOAT: delete[] this->array.pfloat; break;
        case DOUBLE: delete[] this->array.pdouble; break;
        case UNDEF : break;
    }
    this->count = 0;
    this->array.all = NULL;
    OUT("\n");
};



/////////////////////////////////////////////////////////////////
DataArray::DataArray (uint32_t count, uint8_t ComponentsCount, datatype data_t)
{
    pointers data;
    data.all = NULL;
    _DataArray (count, ComponentsCount, data_t, data);
}

//////////////////////////////////////////////////////////////////
DataArray::DataArray (uint32_t count, uint8_t ComponentsCount, datatype data_t, void* data)
{
        pointers _data;
        _data.all = data;
        _DataArray (count, ComponentsCount, data_t, _data);
}

//////////////////////////////////////////////////////////////////
void DataArray::_DataArray (uint32_t count, uint8_t ComponentsCount, datatype data_t, pointers data)
{
    IN("array " << this << endl);
    this->array.all=NULL;
    this->count = count;
    this->datatype_t = data_t;
    this->ComponentsCount = ComponentsCount;
    try
    {
        if (this->count == 0) GLUI_THROW(EINVAL, "count is zero, cowardly refuse to allocate empty array");
        if (this->ComponentsCount == 0) GLUI_THROW(EINVAL, "ComponentsCount is zero, cowardly refuse to allocate empty array");
        switch (this->datatype_t)
        {
            case UINT8_T:
                this->array.puint8 = new uint8_t[this->count * this->ComponentsCount];
                break;
            case INT8_T:
                this->array.pint8 = new int8_t[this->count * this->ComponentsCount];
                break;
            case UINT16_T:
                this->array.puint16 = new uint16_t[this->count * this->ComponentsCount];
                break;
            case INT16_T:
                this->array.pint16 = new int16_t[this->count * this->ComponentsCount];
                break;
            case UINT32_T:
                this->array.puint32 = new uint32_t[this->count * this->ComponentsCount];
                break;
            case INT32_T:
                this->array.pint32 = new int32_t[this->count * this->ComponentsCount];
                break;
            case FLOAT:
                this->array.pfloat = new float[this->count * this->ComponentsCount];
                break;
            case DOUBLE:
                this->array.pdouble = new double[this->count * this->ComponentsCount];
                break;
            default:
                GLUI_THROW(EINVAL, "unkown datatype");
        }

        if (data.all != NULL)
        {
            CpyArray(data);
        }
    }
    catch(std::bad_alloc err)
    {
        std::cerr << err.what();
        throw;
    }
    catch(Exception* err)
    {
        std::cerr << err->what();
        throw;
    }
    OUT("data" << this->array.all << endl);

}
/////////////////////////////////////////////////////////////////
int DataArray::CpyArray(pointers data)
{
    IN("\n");
    if (this->count == 0) GLUI_THROW(EINVAL, "count is zero, cowardly refuse to copy empty array");
    switch (this->datatype_t)
    {
        case UINT8_T:
            memcpy(this->array.puint8, data.all, this->count * this->ComponentsCount * sizeof(uint8_t) );
            break;
        case INT8_T:
            memcpy(this->array.pint8, data.all, this->count * this->ComponentsCount * sizeof(int8_t) );
            break;
        case UINT16_T:
            memcpy(this->array.puint16, data.all, this->count * this->ComponentsCount * sizeof(uint16_t) );
            break;
        case INT16_T:
            memcpy(this->array.pint16, data.all, this->count * this->ComponentsCount * sizeof(int16_t) );
            break;
        case UINT32_T:
            memcpy(this->array.puint32, data.all, this->count * this->ComponentsCount * sizeof(uint32_t) );
            break;
        case INT32_T:
            memcpy(this->array.pint32, data.all, this->count * this->ComponentsCount * sizeof(uint32_t) );
            break;
        case FLOAT:
            memcpy(this->array.pfloat, data.all, this->count * this->ComponentsCount * sizeof(float) );
            break;
        case DOUBLE:
            memcpy(this->array.pdouble, data.all, this->count * this->ComponentsCount * sizeof(double) );
            break;
        default:
            GLUI_THROW(EINVAL, "unkown datatype");
    }
    OUT("\n");
    return 0;
}

/////////////////////////////////////////////////////////////////
DataArray::operator GLenum()
{
        return datatype_t;
}

