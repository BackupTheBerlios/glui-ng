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

#include <GL/glui/VertexObject.h>
#include <GL/glui/Exception.h>
#include <GL/glui/debug.h>
#include <GL/glui/algebra3.h>
#include <iostream>
#include <fstream>
#include <new>

#define MODULE_KEY "GLUI_DEBUG_VERTEXOBJECT"

using namespace GLUI;
/////////////////////////////////////////////////////////////////
VertexObject::VertexObject ()
{
    IN("\n");
    TextureCount = 0;

    float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float mat_ambient_color[] = {0.1f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
    float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};


    memset(this->no_mat, 0, 4*sizeof(float));
    memset(this->mat_ambient, 0, 4*sizeof(float));
    memset(this->mat_ambient_color, 0, 4*sizeof(float));
    memset(this->mat_diffuse, 0, 4*sizeof(float));
    memset(this->mat_specular, 0, 4*sizeof(float));
    memset(this->mat_emission, 0, 4*sizeof(float));

    memcpy(this->no_mat, no_mat, sizeof(no_mat)/sizeof(no_mat[0]));
    memcpy(this->mat_ambient, mat_ambient, sizeof(mat_ambient)/sizeof(mat_ambient[0]));
    memcpy(this->mat_ambient_color, mat_ambient_color, sizeof(mat_ambient_color)/sizeof(mat_ambient_color[0]));
    memcpy(this->mat_diffuse, mat_diffuse, sizeof(mat_diffuse)/sizeof(mat_diffuse[0]));
    memcpy(this->mat_specular, mat_specular, sizeof(mat_specular)/sizeof(mat_specular[0]));
    memcpy(this->mat_emission, mat_emission, sizeof(mat_emission)/sizeof(mat_emission[0]));


    this->no_shininess = 0.0f;
    this->low_shininess = 5.0f;
    this->high_shininess = 100.0f;
    OUT("\n");

};

/////////////////////////////////////////////////////////////////
VertexObject::~VertexObject()
{
    IN("\n");
    OUT("\n");

};
/////////////////////////////////////////////////////////////////
int VertexObject::SetVerticesArray (NCRC_AutoPtr<DataArray> vertices)
{
        Vertices = vertices;
}

int VertexObject::SetVerticesArray (DataArray::datatype vertices_t,uint8_t ComponentsCount, void* vertices, uint32_t count)
{
    IN("\n");
    this->Vertices = NCRC_AutoPtr<DataArray>(
                    new DataArray(count, ComponentsCount, vertices_t, vertices));
    OUT("\n");
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetFaceIndicesArray (NCRC_AutoPtr<DataArray> FaceIndices)
{
        Indices = FaceIndices;
}

int VertexObject::SetFaceIndicesArray (DataArray::datatype indices_t,uint8_t ComponentsCount, void* indices, uint32_t count)
{
    IN("\n");
    this->Indices = NCRC_AutoPtr<DataArray>(
                    new DataArray(count, ComponentsCount, indices_t, indices));
    OUT("\n");
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetColorArray (NCRC_AutoPtr<DataArray> ColorArray)
{
        Colors = ColorArray;
}

int VertexObject::SetColorArray (DataArray::datatype colors_t,uint8_t ComponentsCount, void* colors, uint32_t count)
{
    IN("\n");
    this->Colors = NCRC_AutoPtr<DataArray>(
                    new DataArray(count, ComponentsCount, colors_t, colors));
    OUT("\n");
}
/////////////////////////////////////////////////////////////////
int VertexObject::SetNormalArray (NCRC_AutoPtr<DataArray> NormalArray)
{
        Normals = NormalArray;
}

int VertexObject::SetNormalArray (DataArray::datatype normals_t,uint8_t ComponentsCount, void* normals, uint32_t count)
{
    IN("\n");
    this->Normals = NCRC_AutoPtr<DataArray>(
                    new DataArray(count, ComponentsCount, normals_t, normals));
    OUT("\n");
}
/////////////////////////////////////////////////////////////////
int VertexObject::AddTexture (NCRC_AutoPtr<Texture> texture)
{
    IN("\n");
    this->TextureData = texture;
    OUT("\n");
}
/////////////////////////////////////////////////////////////////
int VertexObject::draw()
{
    IN("\n");
    glPushClientAttrib(0);

    if (this->Colors != NULL)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        printf("%d %d %d\n" ,Colors->ComponentsCount, Colors->datatype_t,  Colors->array.all);
        glColorPointer(Colors->ComponentsCount, Colors->datatype_t, 0, Colors->array.all);
    }
    if (this->Normals != NULL)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(Normals->datatype_t, 0, Normals->array.all);
    }
    if (this->TextureData != NULL)
    {
            this->TextureData->ClientActiveTexture(GL_TEXTURE0);
            /* for multitexturing
            GlMultiTexCoord1f(GLenum texUnit, GLfloat s);
            glMultiTexCoord2f(GLenum texUnit, GLfloat s, GLfloat t);
            glMultiTexCoord3f(GLenum texUnit, GLfloat s, GLfloat t, Glfloat r);

               glClientActiveTextureARB(GL_TEXTURE1_ARB);
               glTexCoordPointer(2, GL_FLOAT, 0, g_texcoordArrayTWO);
               glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            //bind the detail texture to the second texture unit
            glActiveTextureARB( GL_TEXTURE1_ARB );
            glEnable( GL_TEXTURE_2D );
            glBindTexture( GL_TEXTURE_2D, Texture_Detail.ID);
            GlMultiTexCoord1f(GLenum texUnit, GLfloat s);
            glMultiTexCoord2f(GLenum texUnit, GLfloat s, GLfloat t);
            glMultiTexCoord3f(GLenum texUnit, GLfloat s, GLfloat t, Glfloat r);


            glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB );
            glTexEnvi( GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2 );
            */

    }
    if (this->Vertices != NULL && this->Indices != NULL)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        printf("%d %d %d\n" ,Vertices->ComponentsCount, Vertices->datatype_t,  Vertices->array.all);
        glVertexPointer(Vertices->ComponentsCount, Vertices->datatype_t, 0, Vertices->array.all);
        //go through our index array and draw our vertex array
        GLenum mode;
        if ( Indices->ComponentsCount == 3 ) mode = GL_TRIANGLES;
        else mode = GL_QUADS;

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);


        //Indices->count has allready the right count of Indices (Indices->ComponentsCount*nbfaces)
        glDrawElements(mode,
                        this->Indices->count * this->Indices->ComponentsCount,
                        this->Indices->datatype_t,
                        this->Indices->array.all);
        glDisableClientState(GL_VERTEX_ARRAY);        
    }
    if (this->Normals != NULL)
    {
        glDisableClientState(GL_NORMAL_ARRAY);
    }
    if (this->TextureData != NULL)
    {
            this->TextureData->ReleaseTexture();

            /* for multitexturing
            //unbind the texture occupying the first texture unit
            glActiveTextureARB( GL_TEXTURE0_ARB );
            glDisable( GL_TEXTURE_2D );
            glBindTexture( GL_TEXTURE_2D, 0 );
            */
    }
    if (this->Colors != NULL)
    {
        glDisableClientState(GL_COLOR_ARRAY);
    }


    glPopClientAttrib();

    debug::Instance()->FlushGL();
    OUT("\n");
    return 0;
}
//////////////////////////////////////////////////////////////////
VertexObject::V3List::V3List()
{
    IN("\n");
    next = NULL;
    OUT("\n");
}
//////////////////////////////////////////////////////////////////
VertexObject::V3List::V3List(vec3 vert)
{
    IN("\n");
    next = NULL;
    vertex = vert;
    OUT("\n");
}
//////////////////////////////////////////////////////////////////
void VertexObject::V3List::print()
{
    V3List* last = this;
    do
      {
        MSG(last->vertex[VX] << "," << last->vertex[VY] << "," << last->vertex[VZ] << " " );
        last = last->next;
      }
    while (last != NULL);
    MSG("\n");
}
//////////////////////////////////////////////////////////////////
int VertexObject::ComputeNormals()
{
    IN("\n");
    try
    {
        this->Normals = new DataArray(Vertices->count, 3, DataArray::FLOAT);
    }
    catch(std::bad_alloc err)
    {
        std::cerr << err.what();
        throw;
    }
    catch(Exception& err)
    {
        std::cerr << err.what();
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

    int nbOfFaces = this->Indices->count / this->Indices->ComponentsCount;
    for (int face = 0; face < nbOfFaces; face++)
    {
        uint32_t index1;
        uint32_t index2;
        uint32_t index3;
        uint32_t index4; //optional index if QUAD is used
        double fVertice0[3];
        double fVertice1[3];
        double fVertice2[3];

        switch ( Indices->datatype_t)
        {
                case DataArray::UINT8_T :
                        index1 = Indices->array.puint8[face * Indices->ComponentsCount];
                        index2 = Indices->array.puint8[face * Indices->ComponentsCount + 1 ];
                        index3 = Indices->array.puint8[face * Indices->ComponentsCount + 2 ];
                        if (Indices->ComponentsCount == 4) index4 = Indices->array.puint8[face * Indices->ComponentsCount + 3 ];
                        break;
                case DataArray::INT8_T:
                        index1 = Indices->array.pint8[face * Indices->ComponentsCount];
                        index2 = Indices->array.pint8[face * Indices->ComponentsCount + 1 ];
                        index3 = Indices->array.pint8[face * Indices->ComponentsCount + 2 ];
                        if (Indices->ComponentsCount == 4) index4 = Indices->array.pint8[face * Indices->ComponentsCount + 3 ];
                        break;
                case DataArray::UINT16_T:
                        index1 = Indices->array.puint16[face * Indices->ComponentsCount];
                        index2 = Indices->array.puint16[face * Indices->ComponentsCount + 1 ];
                        index3 = Indices->array.puint16[face * Indices->ComponentsCount + 2 ];
                        if (Indices->ComponentsCount == 4) index4 = Indices->array.puint16[face * Indices->ComponentsCount + 3 ];
                        break;
                case DataArray::INT16_T:
                        index1 = Indices->array.pint16[face * Indices->ComponentsCount];
                        index2 = Indices->array.pint16[face * Indices->ComponentsCount + 1 ];
                        index3 = Indices->array.pint16[face * Indices->ComponentsCount + 2 ];
                        if (Indices->ComponentsCount == 4) index4 = Indices->array.pint16[face * Indices->ComponentsCount + 3 ];
                        break;
                case DataArray::UINT32_T:
                        index1 = Indices->array.puint32[face * Indices->ComponentsCount];
                        index2 = Indices->array.puint32[face * Indices->ComponentsCount + 1 ];
                        index3 = Indices->array.puint32[face * Indices->ComponentsCount + 2 ];
                        if (Indices->ComponentsCount == 4) index4 = Indices->array.puint32[face * Indices->ComponentsCount + 3 ];
                        break;
                case DataArray::INT32_T:
                        index1 = Indices->array.pint32[face * Indices->ComponentsCount];
                        index2 = Indices->array.pint32[face * Indices->ComponentsCount + 1 ];
                        index3 = Indices->array.pint32[face * Indices->ComponentsCount + 2 ];
                        if (Indices->ComponentsCount == 4) index4 = Indices->array.pint32[face * Indices->ComponentsCount + 3 ];
                        break;
                default:
                        GLUI_THROW(EINVAL, "Indices has not an int type");

        }
        switch ( Vertices->datatype_t)
        {
                case DataArray::UINT8_T :
                        fVertice0[0] = Vertices->array.puint8[index1*Vertices->ComponentsCount +0];
                        fVertice0[1] = Vertices->array.puint8[index1*Vertices->ComponentsCount +1];
                        fVertice0[2] = Vertices->array.puint8[index1*Vertices->ComponentsCount +2];
                        fVertice1[0] = Vertices->array.puint8[index2*Vertices->ComponentsCount +0];
                        fVertice1[1] = Vertices->array.puint8[index2*Vertices->ComponentsCount +1];
                        fVertice1[2] = Vertices->array.puint8[index2*Vertices->ComponentsCount +2];
                        fVertice2[0] = Vertices->array.puint8[index3*Vertices->ComponentsCount +0];
                        fVertice2[1] = Vertices->array.puint8[index3*Vertices->ComponentsCount +1];
                        fVertice2[2] = Vertices->array.puint8[index3*Vertices->ComponentsCount +2];
                        break;
                case DataArray::INT8_T:
                        fVertice0[0] = Vertices->array.pint8[index1*Vertices->ComponentsCount +0];
                        fVertice0[1] = Vertices->array.pint8[index1*Vertices->ComponentsCount +1];
                        fVertice0[2] = Vertices->array.pint8[index1*Vertices->ComponentsCount +2];
                        fVertice1[0] = Vertices->array.pint8[index2*Vertices->ComponentsCount +0];
                        fVertice1[1] = Vertices->array.pint8[index2*Vertices->ComponentsCount +1];
                        fVertice1[2] = Vertices->array.pint8[index2*Vertices->ComponentsCount +2];
                        fVertice2[0] = Vertices->array.pint8[index3*Vertices->ComponentsCount +0];
                        fVertice2[1] = Vertices->array.pint8[index3*Vertices->ComponentsCount +1];
                        fVertice2[2] = Vertices->array.pint8[index3*Vertices->ComponentsCount +2];
                        break;
                case DataArray::UINT16_T:
                        fVertice0[0] = Vertices->array.puint16[index1*Vertices->ComponentsCount +0];
                        fVertice0[1] = Vertices->array.puint16[index1*Vertices->ComponentsCount +1];
                        fVertice0[2] = Vertices->array.puint16[index1*Vertices->ComponentsCount +2];
                        fVertice1[0] = Vertices->array.puint16[index2*Vertices->ComponentsCount +0];
                        fVertice1[1] = Vertices->array.puint16[index2*Vertices->ComponentsCount +1];
                        fVertice1[2] = Vertices->array.puint16[index2*Vertices->ComponentsCount +2];
                        fVertice2[0] = Vertices->array.puint16[index3*Vertices->ComponentsCount +0];
                        fVertice2[1] = Vertices->array.puint16[index3*Vertices->ComponentsCount +1];
                        fVertice2[2] = Vertices->array.puint16[index3*Vertices->ComponentsCount +2];
                        break;
                case DataArray::INT16_T:
                        fVertice0[0] = Vertices->array.pint16[index1*Vertices->ComponentsCount +0];
                        fVertice0[1] = Vertices->array.pint16[index1*Vertices->ComponentsCount +1];
                        fVertice0[2] = Vertices->array.pint16[index1*Vertices->ComponentsCount +2];
                        fVertice1[0] = Vertices->array.pint16[index2*Vertices->ComponentsCount +0];
                        fVertice1[1] = Vertices->array.pint16[index2*Vertices->ComponentsCount +1];
                        fVertice1[2] = Vertices->array.pint16[index2*Vertices->ComponentsCount +2];
                        fVertice2[0] = Vertices->array.pint16[index3*Vertices->ComponentsCount +0];
                        fVertice2[1] = Vertices->array.pint16[index3*Vertices->ComponentsCount +1];
                        fVertice2[2] = Vertices->array.pint16[index3*Vertices->ComponentsCount +2];
                        break;
                case DataArray::UINT32_T:
                        fVertice0[0] = Vertices->array.puint32[index1*Vertices->ComponentsCount +0];
                        fVertice0[1] = Vertices->array.puint32[index1*Vertices->ComponentsCount +1];
                        fVertice0[2] = Vertices->array.puint32[index1*Vertices->ComponentsCount +2];
                        fVertice1[0] = Vertices->array.puint32[index2*Vertices->ComponentsCount +0];
                        fVertice1[1] = Vertices->array.puint32[index2*Vertices->ComponentsCount +1];
                        fVertice1[2] = Vertices->array.puint32[index2*Vertices->ComponentsCount +2];
                        fVertice2[0] = Vertices->array.puint32[index3*Vertices->ComponentsCount +0];
                        fVertice2[1] = Vertices->array.puint32[index3*Vertices->ComponentsCount +1];
                        fVertice2[2] = Vertices->array.puint32[index3*Vertices->ComponentsCount +2];
                        break;
                case DataArray::INT32_T:
                        fVertice0[0] = Vertices->array.pint32[index1*Vertices->ComponentsCount +0];
                        fVertice0[1] = Vertices->array.pint32[index1*Vertices->ComponentsCount +1];
                        fVertice0[2] = Vertices->array.pint32[index1*Vertices->ComponentsCount +2];
                        fVertice1[0] = Vertices->array.pint32[index2*Vertices->ComponentsCount +0];
                        fVertice1[1] = Vertices->array.pint32[index2*Vertices->ComponentsCount +1];
                        fVertice1[2] = Vertices->array.pint32[index2*Vertices->ComponentsCount +2];
                        fVertice2[0] = Vertices->array.pint32[index3*Vertices->ComponentsCount +0];
                        fVertice2[1] = Vertices->array.pint32[index3*Vertices->ComponentsCount +1];
                        fVertice2[2] = Vertices->array.pint32[index3*Vertices->ComponentsCount +2];
                        break;
                case DataArray::FLOAT:
                        fVertice0[0] = Vertices->array.pfloat[index1*Vertices->ComponentsCount +0];
                        fVertice0[1] = Vertices->array.pfloat[index1*Vertices->ComponentsCount +1];
                        fVertice0[2] = Vertices->array.pfloat[index1*Vertices->ComponentsCount +2];
                        fVertice1[0] = Vertices->array.pfloat[index2*Vertices->ComponentsCount +0];
                        fVertice1[1] = Vertices->array.pfloat[index2*Vertices->ComponentsCount +1];
                        fVertice1[2] = Vertices->array.pfloat[index2*Vertices->ComponentsCount +2];
                        fVertice2[0] = Vertices->array.pfloat[index3*Vertices->ComponentsCount +0];
                        fVertice2[1] = Vertices->array.pfloat[index3*Vertices->ComponentsCount +1];
                        fVertice2[2] = Vertices->array.pfloat[index3*Vertices->ComponentsCount +2];
                        break;
                case DataArray::DOUBLE:
                        fVertice0[0] = Vertices->array.pdouble[index1*Vertices->ComponentsCount +0];
                        fVertice0[1] = Vertices->array.pdouble[index1*Vertices->ComponentsCount +1];
                        fVertice0[2] = Vertices->array.pdouble[index1*Vertices->ComponentsCount +2];
                        fVertice1[0] = Vertices->array.pdouble[index2*Vertices->ComponentsCount +0];
                        fVertice1[1] = Vertices->array.pdouble[index2*Vertices->ComponentsCount +1];
                        fVertice1[2] = Vertices->array.pdouble[index2*Vertices->ComponentsCount +2];
                        fVertice2[0] = Vertices->array.pdouble[index3*Vertices->ComponentsCount +0];
                        fVertice2[1] = Vertices->array.pdouble[index3*Vertices->ComponentsCount +1];
                        fVertice2[2] = Vertices->array.pdouble[index3*Vertices->ComponentsCount +2];
                        break;
                default :
                        GLUI_THROW(EINVAL, "Vertices has an undefined type");

        }
        vec3 v0( fVertice0 );
        vec3 v1( fVertice1 );
        vec3 v2( fVertice2 );

        vec3 vp1 = v1 - v0;
        vec3 vp2 = v2 - v0;

        vec3 vnormal = vp1 ^ vp2;
        vnormal.normalize();
        MSG("index : " << index1 << endl);
        {
                V3List* backup = VerticeAndNormalsArray[index1];
                VerticeAndNormalsArray[index1] = new V3List(vnormal);
                VerticeAndNormalsArray[index1]->next = backup;
                VerticeAndNormalsArray[index1]->print();
        }
        MSG("index : " << index2 << endl);
        {
                V3List* backup = VerticeAndNormalsArray[index2];
                VerticeAndNormalsArray[index2] = new V3List(vnormal);
                VerticeAndNormalsArray[index2]->next = backup;
                VerticeAndNormalsArray[index2]->print();
        }
        MSG("index : " << index3 << endl);
        {
                V3List* backup = VerticeAndNormalsArray[index3];
                VerticeAndNormalsArray[index3] = new V3List(vnormal);
                VerticeAndNormalsArray[index3]->next = backup;
                VerticeAndNormalsArray[index3]->print();
        }
        if (Indices->ComponentsCount == 4) 
        {
                MSG("index : " << index4 << endl);
                {
                        V3List* backup = VerticeAndNormalsArray[index4];
                        VerticeAndNormalsArray[index4] = new V3List(vnormal);
                        VerticeAndNormalsArray[index4]->next = backup;
                        VerticeAndNormalsArray[index4]->print();
                }
        }
    }
    //we have processed all the faces and created the normals associated, now compute the average and fill the array
    for (uint32_t i=0; i < Vertices->count/Vertices->ComponentsCount; i++)
    {
            MSG("vertice " << i << " :");
            V3List* normals = VerticeAndNormalsArray[i];
            vec3 normal = normals->vertex;
            MSG(normal[VX] << "," << normal[VY] << "," << normal[VZ]);
            while (normals->next != NULL)
            {
                    normals= normals->next;
                    MSG(normals->vertex[VX] << "," << normals->vertex[VY] << "," << normals->vertex[VZ]);
                    normal = normal + normals->vertex;
            }
            normals = VerticeAndNormalsArray[i];
            while (normals)
            {
                    V3List* next = normals->next;
                    delete normals;
                    normals = next;
            }
            MSG("\n");
            MSG(normal[VX] << "," << normal[VY] << "," << normal[VZ] << endl);
            normal.normalize();
            Normals->array.pfloat[i*3 + 0] = normal[VX];
            Normals->array.pfloat[i*3 + 1] = normal[VY];
            Normals->array.pfloat[i*3 + 2] = normal[VZ];
    }
    if (NULL != getenv("GLUI_DEBUG_VERTEXOBJECT_DUMP_COMPUTED_NORMALS"))
    {
            for (uint32_t i=0; i< Normals->count/3; i++)
            {
                    MSG( Normals->array.pfloat[i*3 + 0] << ", " 
                                    << Normals->array.pfloat[i*3 + 1] << ", " 
                                    << Normals->array.pfloat[i*3 + 2] << endl);
            }
    }
    else
    {
            MSG("add GLUI_DEBUG_VERTEXOBJECT_DUMP_COMPUTED_NORMALS into env to dump computed normals on traces\n");
    }
    OUT("\n");

}
