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

#define MODULE_KEY "GLUI_DEBUG_VERTEXOBJECT"

using namespace GLUI;
/////////////////////////////////////////////////////////////////
VertexObject::VertexObject (
        uint8_t verticessize,
        uint8_t colorsize,
        uint8_t verticebyfacescount
        )
{
    IN("");
    this->VerticesSize = verticessize;
    this->ColorSize = colorsize;
    this->VerticeByFacesCount = verticebyfacescount;
    Vertices = NULL;
    indices  = NULL;
    Colors   = NULL;
    Normals  = NULL;
    Texture  = NULL;

    float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float mat_ambient_color[] = {0.1f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
    float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};

    memcpy(this->no_mat, no_mat, sizeof(no_mat)/sizeof(no_mat[0]));
    memcpy(this->mat_ambient, mat_ambient, sizeof(mat_ambient)/sizeof(mat_ambient[0]));
    memcpy(this->mat_ambient_color, mat_ambient_color, sizeof(mat_ambient_color)/sizeof(mat_ambient_color[0]));
    memcpy(this->mat_diffuse, mat_diffuse, sizeof(mat_diffuse)/sizeof(mat_diffuse[0]));
    memcpy(this->mat_specular, mat_specular, sizeof(mat_specular)/sizeof(mat_specular[0]));
    memcpy(this->mat_emission, mat_emission, sizeof(mat_emission)/sizeof(mat_emission[0]));


    this->no_shininess = 0.0f;
    this->low_shininess = 5.0f;
    this->high_shininess = 100.0f;
    OUT("");

};

/////////////////////////////////////////////////////////////////
VertexObject::~VertexObject()
{
    IN("");
    delete this->Vertices;
    this->Vertices = NULL;
    delete this->indices;
    this->indices = NULL;
    delete this->Colors;
    this->Colors = NULL;
    delete this->Normals;
    this->Normals = NULL;
    delete this->Texture;
    this->Texture = NULL;
    OUT("");

};
/////////////////////////////////////////////////////////////////
VertexObject::DataArray::~DataArray()
{
    IN("array %x, data@%x\n", this, this->array.all);
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
    OUT("");
};



/////////////////////////////////////////////////////////////////
VertexObject::DataArray::DataArray (uint32_t count, datatype data_t)
{
    pointers data;
    data.all = NULL;
    _DataArray (count, data_t, data);
}


VertexObject::DataArray::DataArray (uint32_t count, datatype data_t, pointers data)
{
    _DataArray (count, data_t, data);
}

void VertexObject::DataArray::_DataArray (uint32_t count, datatype data_t, pointers data)
{
    IN("array %x\n", this);
    this->array.all=NULL;
    this->count = count;
    this->datatype_t = data_t;
    try
    {
        if (this->count == 0) GLUI_THROW(EINVAL, "count is zero, cowardly refuse to allocate empty array");
        switch (this->datatype_t)
        {
            case UINT8_T:
                this->array.puint8 = new uint8_t[this->count];
                break;
            case INT8_T:
                this->array.pint8 = new int8_t[this->count];
                break;
            case UINT16_T:
                this->array.puint16 = new uint16_t[this->count];
                break;
            case INT16_T:
                this->array.pint16 = new int16_t[this->count];
                break;
            case UINT32_T:
                this->array.puint32 = new uint32_t[this->count];
                break;
            case INT32_T:
                this->array.pint32 = new int32_t[this->count];
                break;
            case FLOAT:
                this->array.pfloat = new float[this->count];
                break;
            case DOUBLE:
                this->array.pdouble = new double[this->count];
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
    OUT("data@%x\n", this->array.all);

}
/////////////////////////////////////////////////////////////////
int VertexObject::DataArray::CpyArray(pointers data)
{
    IN("");
    if (this->count == 0) GLUI_THROW(EINVAL, "count is zero, cowardly refuse to copy empty array");
    switch (this->datatype_t)
    {
        case UINT8_T:
            memcpy(this->array.puint8, data.all, this->count * sizeof(uint8_t) );
            break;
        case INT8_T:
            memcpy(this->array.pint8, data.all, this->count * sizeof(int8_t) );
            break;
        case UINT16_T:
            memcpy(this->array.puint16, data.all, this->count * sizeof(uint16_t) );
            break;
        case INT16_T:
            memcpy(this->array.pint16, data.all, this->count * sizeof(int16_t) );
            break;
        case UINT32_T:
            memcpy(this->array.puint32, data.all, this->count * sizeof(uint32_t) );
            break;
        case INT32_T:
            memcpy(this->array.pint32, data.all, this->count * sizeof(uint32_t) );
            break;
        case FLOAT:
            memcpy(this->array.pfloat, data.all, this->count * sizeof(float) );
            break;
        case DOUBLE:
            memcpy(this->array.pdouble, data.all, this->count * sizeof(double) );
            break;
        default:
            GLUI_THROW(EINVAL, "unkown datatype");
    }
    OUT("");
    return 0;
}

/////////////////////////////////////////////////////////////////
int VertexObject::SetVerticesArray (datatype vertices_t, void* vertices, uint32_t count)
{
    IN("");
    pointers data;
    data.all = vertices;
    if (this->Vertices != NULL) delete this->Vertices;
    this->Vertices = NULL;
    this->Vertices = new DataArray(count*this->VerticesSize, vertices_t, data);
    OUT("");
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetFaceIndicesArray (datatype indices_t, void* indices, uint32_t count)
{
    IN("");
    pointers data;
    data.all = indices;
    if (this->indices != NULL) delete this->indices;
    this->indices = NULL;
    this->indices = new DataArray(count*this->VerticeByFacesCount, indices_t, data);
    OUT("");
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetColorArray (datatype colors_t, void* colors, uint32_t count)
{
    IN("");
    pointers data;
    data.all = colors;
    if (this->Colors != NULL) delete this->Colors;
    this->Colors = NULL;
    this->Colors = new DataArray(count*this->ColorSize, colors_t, data);
    OUT("");
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetNormalArray (datatype normals_t, void* normals, uint32_t count)
{
    IN("");
    pointers data;
    data.all = normals;
    this->Normals = NULL;
    if ( this->Normals != NULL) delete this->Normals;
    this->Normals = new DataArray(count * 3, normals_t, data);
    OUT("");
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetTextureArray (datatype texture_t, void* texture, uint32_t count)
{
    IN("");
    pointers data;
    data.all = texture;
    if ( this->Texture != NULL) delete this->Texture;
    this->Texture = NULL;
    this->Texture = new DataArray(count, texture_t, data);
    OUT("");
}
/////////////////////////////////////////////////////////////////
void VertexObject::draw()
{
    IN("");
    glPushClientAttrib(0);

    if (this->Colors != NULL)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(ColorSize, Colors->datatype_t, 0, Colors->array.all);
    }
    if (this->Normals != NULL)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(Normals->datatype_t, 0, Normals->array.all);
    }
    if (this->Vertices != NULL)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(VerticesSize, Vertices->datatype_t, 0, Vertices->array.all);
        //go through our index array and draw our vertex array
        GLenum mode;
        if ( VerticeByFacesCount == 3 ) mode = GL_TRIANGLES;
        else mode = GL_QUADS;

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);


        //indices->count has allready the right count of indices (VerticeByFacesCount*nbfaces)
        glDrawElements(mode, indices->count, indices->datatype_t, indices->array.all);
    }

    glPopClientAttrib();

    debug::Instance()->FlushGL();
    OUT("");
}
//////////////////////////////////////////////////////////////////
VertexObject::V3List::V3List()
{
    IN("");
    next = NULL;
    OUT("");
}
//////////////////////////////////////////////////////////////////
VertexObject::V3List::V3List(vec3 vert)
{
    IN("");
    next = NULL;
    vertex = vert;
    OUT("");
}
//////////////////////////////////////////////////////////////////
void VertexObject::V3List::print()
{
    V3List* last = this;
    do
      {
        RAWMSG("%f,%f,%f ",last->vertex[VX],last->vertex[VY],last->vertex[VZ]);
        last = last->next;
      }
    while (last != NULL);
    RAWMSG("\n");
}
//////////////////////////////////////////////////////////////////
int VertexObject::ComputeNormals()
{
    IN("");
    try
    {
        if (this->Normals != NULL) delete this->Normals;
        this->Normals = NULL;
        this->Normals = new DataArray(Vertices->count/VerticesSize * 3, FLOAT);
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
    V3List** VerticeAndNormalsArray;
    try
      {
        VerticeAndNormalsArray = new V3List*[Vertices->count];
        memset(VerticeAndNormalsArray, 0, Vertices->count * sizeof(V3List*));
      }
    catch(std::bad_alloc err)
    {
        std::cerr << err.what();
        throw;
    }

    int nbOfFaces = this->indices->count / this->VerticeByFacesCount;
    for (int face = 0; face < nbOfFaces; face++)
    {
        uint32_t index1;
        uint32_t index2;
        uint32_t index3;
        uint32_t index4; //optional index if QUAD is used
        double fVertice0[3];
        double fVertice1[3];
        double fVertice2[3];

        switch ( indices->datatype_t)
        {
            case UINT8_T :
                index1 = indices->array.puint8[face * VerticeByFacesCount];
                index2 = indices->array.puint8[face * VerticeByFacesCount + 1 ];
                index3 = indices->array.puint8[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices->array.puint8[face * VerticeByFacesCount + 3 ];
                break;
            case INT8_T:
                index1 = indices->array.pint8[face * VerticeByFacesCount];
                index2 = indices->array.pint8[face * VerticeByFacesCount + 1 ];
                index3 = indices->array.pint8[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices->array.pint8[face * VerticeByFacesCount + 3 ];
                break;
            case UINT16_T:
                index1 = indices->array.puint16[face * VerticeByFacesCount];
                index2 = indices->array.puint16[face * VerticeByFacesCount + 1 ];
                index3 = indices->array.puint16[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices->array.puint16[face * VerticeByFacesCount + 3 ];
                break;
            case INT16_T:
                index1 = indices->array.pint16[face * VerticeByFacesCount];
                index2 = indices->array.pint16[face * VerticeByFacesCount + 1 ];
                index3 = indices->array.pint16[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices->array.pint16[face * VerticeByFacesCount + 3 ];
                break;
            case UINT32_T:
                index1 = indices->array.puint32[face * VerticeByFacesCount];
                index2 = indices->array.puint32[face * VerticeByFacesCount + 1 ];
                index3 = indices->array.puint32[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices->array.puint32[face * VerticeByFacesCount + 3 ];
                break;
            case INT32_T:
                index1 = indices->array.pint32[face * VerticeByFacesCount];
                index2 = indices->array.pint32[face * VerticeByFacesCount + 1 ];
                index3 = indices->array.pint32[face * VerticeByFacesCount + 2 ];
                if (VerticeByFacesCount == 4) index4 = indices->array.pint32[face * VerticeByFacesCount + 3 ];
                break;
            default:
                throw new Exception(EINVAL, "indices has not an int type");

        }
        switch ( Vertices->datatype_t)
        {
            case UINT8_T :
                fVertice0[0] = Vertices->array.puint8[index1*VerticesSize +0];
                fVertice0[1] = Vertices->array.puint8[index1*VerticesSize +1];
                fVertice0[2] = Vertices->array.puint8[index1*VerticesSize +2];
                fVertice1[0] = Vertices->array.puint8[index2*VerticesSize +0];
                fVertice1[1] = Vertices->array.puint8[index2*VerticesSize +1];
                fVertice1[2] = Vertices->array.puint8[index2*VerticesSize +2];
                fVertice2[0] = Vertices->array.puint8[index3*VerticesSize +0];
                fVertice2[1] = Vertices->array.puint8[index3*VerticesSize +1];
                fVertice2[2] = Vertices->array.puint8[index3*VerticesSize +2];
                break;
            case INT8_T:
                fVertice0[0] = Vertices->array.pint8[index1*VerticesSize +0];
                fVertice0[1] = Vertices->array.pint8[index1*VerticesSize +1];
                fVertice0[2] = Vertices->array.pint8[index1*VerticesSize +2];
                fVertice1[0] = Vertices->array.pint8[index2*VerticesSize +0];
                fVertice1[1] = Vertices->array.pint8[index2*VerticesSize +1];
                fVertice1[2] = Vertices->array.pint8[index2*VerticesSize +2];
                fVertice2[0] = Vertices->array.pint8[index3*VerticesSize +0];
                fVertice2[1] = Vertices->array.pint8[index3*VerticesSize +1];
                fVertice2[2] = Vertices->array.pint8[index3*VerticesSize +2];
                break;
            case UINT16_T:
                fVertice0[0] = Vertices->array.puint16[index1*VerticesSize +0];
                fVertice0[1] = Vertices->array.puint16[index1*VerticesSize +1];
                fVertice0[2] = Vertices->array.puint16[index1*VerticesSize +2];
                fVertice1[0] = Vertices->array.puint16[index2*VerticesSize +0];
                fVertice1[1] = Vertices->array.puint16[index2*VerticesSize +1];
                fVertice1[2] = Vertices->array.puint16[index2*VerticesSize +2];
                fVertice2[0] = Vertices->array.puint16[index3*VerticesSize +0];
                fVertice2[1] = Vertices->array.puint16[index3*VerticesSize +1];
                fVertice2[2] = Vertices->array.puint16[index3*VerticesSize +2];
                break;
            case INT16_T:
                fVertice0[0] = Vertices->array.pint16[index1*VerticesSize +0];
                fVertice0[1] = Vertices->array.pint16[index1*VerticesSize +1];
                fVertice0[2] = Vertices->array.pint16[index1*VerticesSize +2];
                fVertice1[0] = Vertices->array.pint16[index2*VerticesSize +0];
                fVertice1[1] = Vertices->array.pint16[index2*VerticesSize +1];
                fVertice1[2] = Vertices->array.pint16[index2*VerticesSize +2];
                fVertice2[0] = Vertices->array.pint16[index3*VerticesSize +0];
                fVertice2[1] = Vertices->array.pint16[index3*VerticesSize +1];
                fVertice2[2] = Vertices->array.pint16[index3*VerticesSize +2];
                break;
            case UINT32_T:
                fVertice0[0] = Vertices->array.puint32[index1*VerticesSize +0];
                fVertice0[1] = Vertices->array.puint32[index1*VerticesSize +1];
                fVertice0[2] = Vertices->array.puint32[index1*VerticesSize +2];
                fVertice1[0] = Vertices->array.puint32[index2*VerticesSize +0];
                fVertice1[1] = Vertices->array.puint32[index2*VerticesSize +1];
                fVertice1[2] = Vertices->array.puint32[index2*VerticesSize +2];
                fVertice2[0] = Vertices->array.puint32[index3*VerticesSize +0];
                fVertice2[1] = Vertices->array.puint32[index3*VerticesSize +1];
                fVertice2[2] = Vertices->array.puint32[index3*VerticesSize +2];
                break;
            case INT32_T:
                fVertice0[0] = Vertices->array.pint32[index1*VerticesSize +0];
                fVertice0[1] = Vertices->array.pint32[index1*VerticesSize +1];
                fVertice0[2] = Vertices->array.pint32[index1*VerticesSize +2];
                fVertice1[0] = Vertices->array.pint32[index2*VerticesSize +0];
                fVertice1[1] = Vertices->array.pint32[index2*VerticesSize +1];
                fVertice1[2] = Vertices->array.pint32[index2*VerticesSize +2];
                fVertice2[0] = Vertices->array.pint32[index3*VerticesSize +0];
                fVertice2[1] = Vertices->array.pint32[index3*VerticesSize +1];
                fVertice2[2] = Vertices->array.pint32[index3*VerticesSize +2];
                break;
            case FLOAT:
                fVertice0[0] = Vertices->array.pfloat[index1*VerticesSize +0];
                fVertice0[1] = Vertices->array.pfloat[index1*VerticesSize +1];
                fVertice0[2] = Vertices->array.pfloat[index1*VerticesSize +2];
                fVertice1[0] = Vertices->array.pfloat[index2*VerticesSize +0];
                fVertice1[1] = Vertices->array.pfloat[index2*VerticesSize +1];
                fVertice1[2] = Vertices->array.pfloat[index2*VerticesSize +2];
                fVertice2[0] = Vertices->array.pfloat[index3*VerticesSize +0];
                fVertice2[1] = Vertices->array.pfloat[index3*VerticesSize +1];
                fVertice2[2] = Vertices->array.pfloat[index3*VerticesSize +2];
                break;
            case DOUBLE:
                fVertice0[0] = Vertices->array.pdouble[index1*VerticesSize +0];
                fVertice0[1] = Vertices->array.pdouble[index1*VerticesSize +1];
                fVertice0[2] = Vertices->array.pdouble[index1*VerticesSize +2];
                fVertice1[0] = Vertices->array.pdouble[index2*VerticesSize +0];
                fVertice1[1] = Vertices->array.pdouble[index2*VerticesSize +1];
                fVertice1[2] = Vertices->array.pdouble[index2*VerticesSize +2];
                fVertice2[0] = Vertices->array.pdouble[index3*VerticesSize +0];
                fVertice2[1] = Vertices->array.pdouble[index3*VerticesSize +1];
                fVertice2[2] = Vertices->array.pdouble[index3*VerticesSize +2];
                break;
            default :
                throw new Exception(EINVAL, "Vertices has an undefined type");

        }
        vec3 v0( fVertice0 );
        vec3 v1( fVertice1 );
        vec3 v2( fVertice2 );

        vec3 vp1 = v1 - v0;
        vec3 vp2 = v2 - v0;

        vec3 vnormal = vp1 ^ vp2;
        vnormal.normalize();
        MSG("index : %d\n", index1);
          {
            V3List* backup = VerticeAndNormalsArray[index1];
            VerticeAndNormalsArray[index1] = new V3List(vnormal);
            VerticeAndNormalsArray[index1]->next = backup;
            VerticeAndNormalsArray[index1]->print();
          }
        MSG("index : %d\n", index2);
          {
            V3List* backup = VerticeAndNormalsArray[index2];
            VerticeAndNormalsArray[index2] = new V3List(vnormal);
            VerticeAndNormalsArray[index2]->next = backup;
            VerticeAndNormalsArray[index2]->print();
          }
        MSG("index : %d\n", index3);
          {
            V3List* backup = VerticeAndNormalsArray[index3];
            VerticeAndNormalsArray[index3] = new V3List(vnormal);
            VerticeAndNormalsArray[index3]->next = backup;
            VerticeAndNormalsArray[index3]->print();
          }
        if (VerticeByFacesCount == 4) 
          {
            MSG("index : %d\n", index4);
              {
                V3List* backup = VerticeAndNormalsArray[index4];
                VerticeAndNormalsArray[index4] = new V3List(vnormal);
                VerticeAndNormalsArray[index4]->next = backup;
                VerticeAndNormalsArray[index4]->print();
              }
          }
    }
    //we have processed all the faces and created the normals associated, now compute the average and fill the array
    for (uint32_t i=0; i < Vertices->count/VerticesSize; i++)
      {
        RAWMSG("vertice %d :",i);
        V3List* normals = VerticeAndNormalsArray[i];
        vec3 normal = normals->vertex;
        RAWMSG("%f,%f,%f ", normal[VX], normal[VY],normal[VZ]);
        while (normals->next != NULL)
          {
            normals= normals->next;
            RAWMSG("%f,%f,%f ", normals->vertex[VX], normals->vertex[VY],normals->vertex[VZ]);
            normal = normal + normals->vertex;
          }
        normals = VerticeAndNormalsArray[i];
        while (normals)
          {
            V3List* next = normals->next;
            delete normals;
            normals = next;
          }
        RAWMSG("\n");
        RAWMSG("%f,%f,%f\n", normal[VX], normal[VY],normal[VZ]);
        normal.normalize();
        Normals->array.pfloat[i*3 + 0] = normal[VX];
        Normals->array.pfloat[i*3 + 1] = normal[VY];
        Normals->array.pfloat[i*3 + 2] = normal[VZ];
      }
    if (NULL != getenv("GLUI_DEBUG_VERTEXOBJECT_DUMP_COMPUTED_NORMALS"))
    {
        for (uint32_t i=0; i< Normals->count/3; i++)
        {
            MSG("%f, %f, %f\n", Normals->array.pfloat[i*3 + 0],  Normals->array.pfloat[i*3 + 1], Normals->array.pfloat[i*3 + 2]);
        }
    }
    else
    {
        MSG("add GLUI_DEBUG_VERTEXOBJECT_DUMP_COMPUTED_NORMALS into env to dump computed normals on traces\n");
    }
    OUT("");

}
