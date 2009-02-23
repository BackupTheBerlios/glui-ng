/*

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

#include <GL/glui/VertexObject.h>
#include <GL/glui/Exception.h>
#include <GL/glui/debug.h>
#include <GL/glui/algebra3.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <new>

using namespace GLUI;
/////////////////////////////////////////////////////////////////
VertexObject::VertexObject (
        uint8_t verticessize,
        uint8_t colorsize,
        uint8_t verticebyfacescount
        )
{
    this->VerticesSize = verticessize;
    this->ColorSize = colorsize;
    this->VerticeByFacesCount = verticebyfacescount;
    Vertices.array.all = NULL;
    Vertices.datatype_t = UNDEF;
    Vertices.count = 0;

    indices.array.all = NULL;
    indices.datatype_t = UNDEF;
    indices.count = 0;

    Colors.array.all = NULL;
    Colors.datatype_t = UNDEF;
    Colors.count = 0;

    Normals.array.all = NULL;
    Normals.datatype_t = UNDEF;
    Normals.count = 0;

    Texture.array.all = NULL;
    Texture.datatype_t = UNDEF;
    Texture.count = 0;
};

/////////////////////////////////////////////////////////////////
VertexObject::~VertexObject()
{
    FreeArray(&Vertices);
    FreeArray(&indices);
    FreeArray(&Colors);
    FreeArray(&Normals);
    FreeArray(&Texture);
};
/////////////////////////////////////////////////////////////////
void VertexObject::FreeArray(DataArray* array)
{
    if (array->state != free)
    {
        switch (array->datatype_t)
        {
            case UINT8_T: delete[] array->array.puint8; break;
            case INT8_T: delete[] array->array.pint8; break;
            case UINT16_T: delete[] array->array.puint16; break;
            case INT16_T: delete[] array->array.pint16; break;
            case UINT32_T: delete[] array->array.puint32; break;
            case INT32_T: delete[] array->array.pint32; break;
            case FLOAT: delete[] array->array.pfloat; break;
            case DOUBLE: delete[] array->array.pdouble; break;
            case UNDEF : break;
        }
    }
    array->array.all = NULL;
    array->state = free;
};


//////////////////////////////////////////////////////////////////
int VertexObject::AllocateArray (DataArray* array)
{
    FreeArray(array);
    if (array->count == 0) GLUI_THROW(EINVAL, "count is zero, cowardly refuse to allocate empty array");
    switch (array->datatype_t)
    {
        case UINT8_T:
            array->array.puint8 = new uint8_t[array->count];
            break;
        case INT8_T:
            array->array.pint8 = new int8_t[array->count];
            break;
        case UINT16_T:
            array->array.puint16 = new uint16_t[array->count];
            break;
        case INT16_T:
            array->array.pint16 = new int16_t[array->count];
            break;
        case UINT32_T:
            array->array.puint32 = new uint32_t[array->count];
            break;
        case INT32_T:
            array->array.pint32 = new int32_t[array->count];
            break;
        case FLOAT:
            array->array.pfloat = new float[array->count];
            break;
        case DOUBLE:
            array->array.pdouble = new double[array->count];
            break;
        default:
            GLUI_THROW(EINVAL, "unkown datatype");
    }
    array->state = allocated;
    return 0;
}

/////////////////////////////////////////////////////////////////
int VertexObject::SetArray (DataArray* array, datatype data_t, pointers data, uint32_t count)
{
    FreeArray(array);
    array->count = count;
    array->datatype_t = data_t;
    try
    {
        AllocateArray(array);
        CpyArray(array, data);
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

}

/////////////////////////////////////////////////////////////////
int VertexObject::SetVerticesArray (datatype vertices_t, void* vertices, uint32_t count)
{
    pointers data;
    data.all = vertices;
    SetArray(&this->Vertices, vertices_t, data, count*VerticesSize);
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetFaceIndicesArray (datatype indices_t, void* indices, uint32_t count)
{
    pointers data;
    data.all = indices;
    SetArray(&this->indices, indices_t, data, count*VerticeByFacesCount);
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetColorArray (datatype colors_t, void* colors, uint32_t count)
{
    pointers data;
    data.all = colors;
    SetArray(&this->Colors, colors_t, data, count*ColorSize);
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetNormalArray (datatype normals_t, void* normals, uint32_t count)
{
    pointers data;
    data.all = normals;
    SetArray(&this->Normals, normals_t, data, count * 3);
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetTextureArray (datatype texture_t, void* texture, uint32_t count)
{
    pointers data;
    data.all = texture;
    SetArray(&this->Texture, texture_t, data, count);
}
/////////////////////////////////////////////////////////////////
int VertexObject::CpyArray(DataArray* array, pointers data)
{
    if (array->count == 0) GLUI_THROW(EINVAL, "count is zero, cowardly refuse to copy empty array");
    switch (array->datatype_t)
    {
        case UINT8_T:
            memcpy(array->array.puint8, data.all, array->count * sizeof(uint8_t) );
            break;
        case INT8_T:
            memcpy(array->array.pint8, data.all, array->count * sizeof(int8_t) );
            break;
        case UINT16_T:
            memcpy(array->array.puint16, data.all, array->count * sizeof(uint16_t) );
            break;
        case INT16_T:
            memcpy(array->array.pint16, data.all, array->count * sizeof(int16_t) );
            break;
        case UINT32_T:
            memcpy(array->array.puint32, data.all, array->count * sizeof(uint32_t) );
            break;
        case INT32_T:
            memcpy(array->array.pint32, data.all, array->count * sizeof(uint32_t) );
            break;
        case FLOAT:
            memcpy(array->array.pfloat, data.all, array->count * sizeof(float) );
            break;
        case DOUBLE:
            memcpy(array->array.pdouble, data.all, array->count * sizeof(double) );
            break;
        default:
            GLUI_THROW(EINVAL, "unkown datatype");
    }
    return 0;
}
/////////////////////////////////////////////////////////////////
void VertexObject::draw()
{
#warning "TODO: save and restore client state"
    glEnableClientState(GL_VERTEX_ARRAY);

    if (Colors.datatype_t != UNDEF  && Colors.state == allocated)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(ColorSize, Colors.datatype_t, 0, Colors.array.all);
    }
    glVertexPointer(VerticesSize, Vertices.datatype_t, 0, Vertices.array.all);
    //go through our index array and draw our vertex array
    GLenum mode;
    if ( VerticeByFacesCount == 3 ) mode = GL_TRIANGLES;
    else mode = GL_QUADS;

    //indices.count has allready the right count of indices (VerticeByFacesCount*nbfaces)
    glDrawElements(mode, indices.count, indices.datatype_t, indices.array.all);

    glDisableClientState(GL_VERTEX_ARRAY);
    if (Colors.datatype_t != UNDEF  && Colors.state == allocated)
    {
        glDisableClientState(GL_COLOR_ARRAY);
    }
    debug::Instance()->FlushGL();
}
//////////////////////////////////////////////////////////////////
VertexObject::V3List::V3List()
{
    next = NULL;
}

//////////////////////////////////////////////////////////////////
void VertexObject::V3List::clean()
{
    if (next != NULL)
      {
        next->clean();
      }
    if (next == NULL)
      {
        return;
      }
    //next is not null and shall have cleaned itself
    delete next;
    next = NULL;
    return;
}
//////////////////////////////////////////////////////////////////
void VertexObject::V3List::add(V3List* newv3)
{
    if (newv3 != NULL)
      {
        V3List* last = this;
        while (last->next != NULL)
          {
            last = last->next;
          }
        last->next = newv3;
      }
}
//////////////////////////////////////////////////////////////////
int VertexObject::ComputeNormals()
{
    FreeArray(&Normals);
    Normals.count = Vertices.count;
    Normals.datatype_t = FLOAT;
    try
    {
        AllocateArray(&Normals);
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
    V3List* VerticeAndNormalsArray;
    try
      {
        VerticeAndNormalsArray = new V3List[Vertices.count];
      }
    catch(std::bad_alloc err)
    {
        std::cerr << err.what();
        throw;
    }

    int nbOfFaces = this->Vertices.count / this->VerticeByFacesCount;
    for (int face = 0; face < nbOfFaces; face++)
    {
        uint32_t index1;
        uint32_t index2;
        uint32_t index3;
        uint32_t index4; //optional index if QUAD is used
        double fVertice0[3];
        double fVertice1[3];
        double fVertice2[3];

        switch ( indices.datatype_t)
        {
            case UINT8_T :
                index1 = indices.array.puint8[face * VerticeByFacesCount];
                index2 = indices.array.puint8[face * VerticeByFacesCount + 1 ];
                index3 = indices.array.puint8[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices.array.puint8[face * VerticeByFacesCount + 3 ];
                break;
            case INT8_T:
                index1 = indices.array.pint8[face * VerticeByFacesCount];
                index2 = indices.array.pint8[face * VerticeByFacesCount + 1 ];
                index3 = indices.array.pint8[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices.array.pint8[face * VerticeByFacesCount + 3 ];
                break;
            case UINT16_T:
                index1 = indices.array.puint16[face * VerticeByFacesCount];
                index2 = indices.array.puint16[face * VerticeByFacesCount + 1 ];
                index3 = indices.array.puint16[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices.array.puint16[face * VerticeByFacesCount + 3 ];
                break;
            case INT16_T:
                index1 = indices.array.pint16[face * VerticeByFacesCount];
                index2 = indices.array.pint16[face * VerticeByFacesCount + 1 ];
                index3 = indices.array.pint16[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices.array.pint16[face * VerticeByFacesCount + 3 ];
                break;
            case UINT32_T:
                index1 = indices.array.puint32[face * VerticeByFacesCount];
                index2 = indices.array.puint32[face * VerticeByFacesCount + 1 ];
                index3 = indices.array.puint32[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices.array.puint32[face * VerticeByFacesCount + 3 ];
                break;
            case INT32_T:
                index1 = indices.array.pint32[face * VerticeByFacesCount];
                index2 = indices.array.pint32[face * VerticeByFacesCount + 1 ];
                index3 = indices.array.pint32[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices.array.pint32[face * VerticeByFacesCount + 3 ];
                break;
            default:
                throw new Exception(EINVAL, "indices has not an int type");

        }
        switch ( Vertices.datatype_t)
        {
            case UINT8_T :
                fVertice0[0] = Vertices.array.puint8[index1*VerticesSize +0];
                fVertice0[1] = Vertices.array.puint8[index1*VerticesSize +1];
                fVertice0[2] = Vertices.array.puint8[index1*VerticesSize +2];
                fVertice1[0] = Vertices.array.puint8[index2*VerticesSize +0];
                fVertice1[1] = Vertices.array.puint8[index2*VerticesSize +1];
                fVertice1[2] = Vertices.array.puint8[index2*VerticesSize +2];
                fVertice2[0] = Vertices.array.puint8[index3*VerticesSize +0];
                fVertice2[1] = Vertices.array.puint8[index3*VerticesSize +1];
                fVertice2[2] = Vertices.array.puint8[index3*VerticesSize +2];
                break;
            case INT8_T:
                fVertice0[0] = Vertices.array.pint8[index1*VerticesSize +0];
                fVertice0[1] = Vertices.array.pint8[index1*VerticesSize +1];
                fVertice0[2] = Vertices.array.pint8[index1*VerticesSize +2];
                fVertice1[0] = Vertices.array.pint8[index2*VerticesSize +0];
                fVertice1[1] = Vertices.array.pint8[index2*VerticesSize +1];
                fVertice1[2] = Vertices.array.pint8[index2*VerticesSize +2];
                fVertice2[0] = Vertices.array.pint8[index3*VerticesSize +0];
                fVertice2[1] = Vertices.array.pint8[index3*VerticesSize +1];
                fVertice2[2] = Vertices.array.pint8[index3*VerticesSize +2];
                break;
            case UINT16_T:
                fVertice0[0] = Vertices.array.puint16[index1*VerticesSize +0];
                fVertice0[1] = Vertices.array.puint16[index1*VerticesSize +1];
                fVertice0[2] = Vertices.array.puint16[index1*VerticesSize +2];
                fVertice1[0] = Vertices.array.puint16[index2*VerticesSize +0];
                fVertice1[1] = Vertices.array.puint16[index2*VerticesSize +1];
                fVertice1[2] = Vertices.array.puint16[index2*VerticesSize +2];
                fVertice2[0] = Vertices.array.puint16[index3*VerticesSize +0];
                fVertice2[1] = Vertices.array.puint16[index3*VerticesSize +1];
                fVertice2[2] = Vertices.array.puint16[index3*VerticesSize +2];
                break;
            case INT16_T:
                fVertice0[0] = Vertices.array.pint16[index1*VerticesSize +0];
                fVertice0[1] = Vertices.array.pint16[index1*VerticesSize +1];
                fVertice0[2] = Vertices.array.pint16[index1*VerticesSize +2];
                fVertice1[0] = Vertices.array.pint16[index2*VerticesSize +0];
                fVertice1[1] = Vertices.array.pint16[index2*VerticesSize +1];
                fVertice1[2] = Vertices.array.pint16[index2*VerticesSize +2];
                fVertice2[0] = Vertices.array.pint16[index3*VerticesSize +0];
                fVertice2[1] = Vertices.array.pint16[index3*VerticesSize +1];
                fVertice2[2] = Vertices.array.pint16[index3*VerticesSize +2];
                break;
            case UINT32_T:
                fVertice0[0] = Vertices.array.puint32[index1*VerticesSize +0];
                fVertice0[1] = Vertices.array.puint32[index1*VerticesSize +1];
                fVertice0[2] = Vertices.array.puint32[index1*VerticesSize +2];
                fVertice1[0] = Vertices.array.puint32[index2*VerticesSize +0];
                fVertice1[1] = Vertices.array.puint32[index2*VerticesSize +1];
                fVertice1[2] = Vertices.array.puint32[index2*VerticesSize +2];
                fVertice2[0] = Vertices.array.puint32[index3*VerticesSize +0];
                fVertice2[1] = Vertices.array.puint32[index3*VerticesSize +1];
                fVertice2[2] = Vertices.array.puint32[index3*VerticesSize +2];
                break;
            case INT32_T:
                fVertice0[0] = Vertices.array.pint32[index1*VerticesSize +0];
                fVertice0[1] = Vertices.array.pint32[index1*VerticesSize +1];
                fVertice0[2] = Vertices.array.pint32[index1*VerticesSize +2];
                fVertice1[0] = Vertices.array.pint32[index2*VerticesSize +0];
                fVertice1[1] = Vertices.array.pint32[index2*VerticesSize +1];
                fVertice1[2] = Vertices.array.pint32[index2*VerticesSize +2];
                fVertice2[0] = Vertices.array.pint32[index3*VerticesSize +0];
                fVertice2[1] = Vertices.array.pint32[index3*VerticesSize +1];
                fVertice2[2] = Vertices.array.pint32[index3*VerticesSize +2];
                break;
            case FLOAT:
                fVertice0[0] = Vertices.array.pfloat[index1*VerticesSize +0];
                fVertice0[1] = Vertices.array.pfloat[index1*VerticesSize +1];
                fVertice0[2] = Vertices.array.pfloat[index1*VerticesSize +2];
                fVertice1[0] = Vertices.array.pfloat[index2*VerticesSize +0];
                fVertice1[1] = Vertices.array.pfloat[index2*VerticesSize +1];
                fVertice1[2] = Vertices.array.pfloat[index2*VerticesSize +2];
                fVertice2[0] = Vertices.array.pfloat[index3*VerticesSize +0];
                fVertice2[1] = Vertices.array.pfloat[index3*VerticesSize +1];
                fVertice2[2] = Vertices.array.pfloat[index3*VerticesSize +2];
                break;
            case DOUBLE:
                fVertice0[0] = Vertices.array.pdouble[index1*VerticesSize +0];
                fVertice0[1] = Vertices.array.pdouble[index1*VerticesSize +1];
                fVertice0[2] = Vertices.array.pdouble[index1*VerticesSize +2];
                fVertice1[0] = Vertices.array.pdouble[index2*VerticesSize +0];
                fVertice1[1] = Vertices.array.pdouble[index2*VerticesSize +1];
                fVertice1[2] = Vertices.array.pdouble[index2*VerticesSize +2];
                fVertice2[0] = Vertices.array.pdouble[index3*VerticesSize +0];
                fVertice2[1] = Vertices.array.pdouble[index3*VerticesSize +1];
                fVertice2[2] = Vertices.array.pdouble[index3*VerticesSize +2];
                break;
            default :
                throw new Exception(EINVAL, "Vertices has an undefined type");

        }
        vec3 v0( fVertice0 );
        vec3 v1( fVertice1 );
        vec3 v2( fVertice2 );
        vec3 vnormal = (v1 - v0) ^ (v2 - v0);
        VerticeAndNormalsArray[index1].add(new V3List(vnormal));
        VerticeAndNormalsArray[index2].add(new V3List(vnormal));
        VerticeAndNormalsArray[index3].add(new V3List(vnormal));
        if (VerticeByFacesCount == 4)  VerticeAndNormalsArray[index4].add(new V3List(vnormal));
    }
    //we have processed all the faces and created the normals associated, now compute the average and fill the array
    for (uint32_t i=0; i < Vertices.count; i++)
      {
        V3List* normals = &VerticeAndNormalsArray[i];
        vec3 normal = normals->vertex;
        while (normals->next != NULL)
          {
            normals= normals->next;
            normal = normal + normals->vertex;
          }
        normal.normalize();
        Normals.array.pfloat[i*3 + 0] = normal[VX];
        Normals.array.pfloat[i*3 + 1] = normal[VY];
        Normals.array.pfloat[i*3 + 2] = normal[VZ];
      }

}
