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

/////////////////////////////////////////////////////////////////
VertexObject::VertexObject (
        uint8_t verticessize,
        uint32_t verticecount,
        uint8_t colorsize,
        uint8_t verticebyfacescount,
        datatype vertices_t = UNDEF,
        pointers vertices = NULL,
        datatype indices_t = UNDEF,
        pointers indices = NULL,
        datatype colors_t = UNDEF,
        pointers colors = NULL,
        datatype normals_t = UNDEF,
        pointers normals = NULL,
        datatype texture_t = UNDEF,
        pointers texture = NULL
        )
{
    Describe(verticessize,
             verticecount,
             colorsize,
             verticebyfacescount);
    SetVerticesArray (vertices_t, vertices);
    SetIndicesArray (indices_t, indices);
    SetColorArray (colors_t, colors);
    SetNormalArray (normals_t, normals);
    SetTextureArray (texture_t, texture);

};

/////////////////////////////////////////////////////////////////
VertexObject::~VertexObject()
{
    FreeVertex();
    FreeIndices();
    FreeColors();
    FreeNormals();
    FreeTexture();
};
/////////////////////////////////////////////////////////////////
void VertexObject::FreeVertex()
{
    switch (Vertices_t)
    {
        case UINT8_T: delete[] Vertices.puint8; break;
        case INT8_T: delete[] Vertices.pint8; break;
        case UINT16_T: delete[] Vertices.puint16; break;
        case INT16_T: delete[] Vertices.pint16; break;
        case UINT32_T: delete[] Vertices.puint32; break;
        case INT32_T: delete[] Vertices.pint32; break;
        case FLOAT: delete[] Vertices.pfloat; break;
        case DOUBLE: delete[] Vertices.pdouble; break;
    }
    Vertices_t = UNDEF;
    Vertices.all = NULL;
};
/////////////////////////////////////////////////////////////////
void VertexObject::FreeIndices()
{
    switch (indices_t)
    {
        case UINT8_T: delete[] indices.puint8; break;
        case INT8_T: delete[] indices.pint8; break;
        case UINT16_T: delete[] indices.puint16; break;
        case INT16_T: delete[] indices.pint16; break;
        case UINT32_T: delete[] indices.puint32; break;
        case INT32_T: delete[] indices.pint32; break;
        case FLOAT: delete[] indices.pfloat; break;
    }
    indices_t = UNDEF;
    indices.all = NULL;
}
/////////////////////////////////////////////////////////////////
void VertexObject::FreeColors()
{
    switch (Colors_t)
    {
        case UINT8_T: delete[] Colors.puint8; break;
        case INT8_T: delete[] Colors.pint8; break;
        case UINT16_T: delete[] Colors.puint16; break;
        case INT16_T: delete[] Colors.pint16; break;
        case UINT32_T: delete[] Colors.puint32; break;
        case INT32_T: delete[] Colors.pint32; break;
        case FLOAT: delete[] Colors.pfloat; break;
        case DOUBLE: delete[] Colors.pdouble; break;
    }
    Colors_t = UNDEF;
    Colors.all = NULL;
}
/////////////////////////////////////////////////////////////////
void VertexObject::FreeNormals()
{
    switch (Normals_t)
    {
        case UINT8_T: delete[] Normals.puint8; break;
        case INT8_T: delete[] Normals.pint8; break;
        case UINT16_T: delete[] Normals.puint16; break;
        case INT16_T: delete[] Normals.pint16; break;
        case UINT32_T: delete[] Normals.puint32; break;
        case INT32_T: delete[] Normals.pint32; break;
        case FLOAT: delete[] Normals.pfloat; break;
        case DOUBLE: delete[] Normals.pdouble; break;
    }
    Normals_t = UNDEF;
    Normals.all = NULL;

}
/////////////////////////////////////////////////////////////////
void VertexObject::FreeTexture()
{
    switch (Texture_t)
    {
        case UINT8_T: delete[] Texture.puint8; break;
        case INT8_T: delete[] Texture.pint8; break;
        case UINT16_T: delete[] Texture.puint16; break;
        case INT16_T: delete[] Texture.pint16; break;
        case UINT32_T: delete[] Texture.puint32; break;
        case INT32_T: delete[] Texture.pint32; break;
        case FLOAT: delete[] Texture.pfloat; break;
        case DOUBLE: delete[] Texture.pdouble; break;
    }
    Texture_t = UNDEF;
    Texture.all = NULL;
}




//////////////////////////////////////////////////////////////////
int VertexObject::Describe(
        uint8_t verticessize,
        uint32_t verticecount,
        uint8_t colorsize,
        uint8_t verticebyfacescount)
{
    this->VerticesSize = verticessize;
    this->VerticeCount = verticecount;
    this->ColorSize = colorsize;
    this->VerticeByFacesCount = verticebyfacescount;
}
//////////////////////////////////////////////////////////////////
int VertexObject::SetVerticesArray (datatype vertices_t, pointers vertices)
{
    FreeVertex();
    switch (Vertices_t)
    {
        case UINT8_T:
            delete Vertices.puint8; break;
        case INT8_T: Vertices.pint8; break;
        case UINT16_T: Vertices.puint16; break;
        case INT16_T: Vertices.pint16; break;
        case UINT32_T: Vertices.puint32; break;
        case INT32_T: Vertices.pint32; break;
        case FLOAT: Vertices.pfloat; break;
        case DOUBLE: Vertices.pdouble; break;
    }
}

int VertexObject::SetIndicesArray (datatype indices_t, pointers indices)
{
    FreeIndices();
    switch (indices_t)
    {
        case UINT8_T: indices.puint8; break;
        case INT8_T: indices.pint8; break;
        case UINT16_T: indices.puint16; break;
        case INT16_T: indices.pint16; break;
        case UINT32_T: indices.puint32; break;
        case INT32_T: indices.pint32; break;
        case FLOAT: indices.pfloat; break;
    }

}

int VertexObject::SetColorArray (datatype colors_t, pointers colors)
{
    FreeColors();
    switch (Colors_t)
    {
        case UINT8_T: Colors.puint8; break;
        case INT8_T: Colors.pint8; break;
        case UINT16_T: Colors.puint16; break;
        case INT16_T: Colors.pint16; break;
        case UINT32_T: Colors.puint32; break;
        case INT32_T: Colors.pint32; break;
        case FLOAT: Colors.pfloat; break;
        case DOUBLE: Colors.pdouble; break;
    }

}

int VertexObject::SetNormalArray (datatype normals_t, pointers normals)
{
    FreeNormals();
    switch (Normals_t)
    {
        case UINT8_T: Normals.puint8; break;
        case INT8_T: Normals.pint8; break;
        case UINT16_T: Normals.puint16; break;
        case INT16_T: Normals.pint16; break;
        case UINT32_T: Normals.puint32; break;
        case INT32_T: Normals.pint32; break;
        case FLOAT: Normals.pfloat; break;
        case DOUBLE: Normals.pdouble; break;
    }

}

int VertexObject::SetTextureArray (datatype texture_t, pointers texture)
{
    FreeTexture();
    switch (Texture_t)
    {
        case UINT8_T: Texture.puint8; break;
        case INT8_T: Texture.pint8; break;
        case UINT16_T: Texture.puint16; break;
        case INT16_T: Texture.pint16; break;
        case UINT32_T: Texture.puint32; break;
        case INT32_T: Texture.pint32; break;
        case FLOAT: Texture.pfloat; break;
        case DOUBLE: Texture.pdouble; break;
    }

}

