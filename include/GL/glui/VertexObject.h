#ifndef __GLUI_VERTEXOBJECT_H
#define __GLUI_VERTEXOBJECT_H
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

#include <GL/glui/algebra3.h>
#include <GL/glui/SmartPointer.h>
#include <GL/glui/Texture.h>
#include <GL/glui/DataArray.h>

namespace GLUI
{

        class VertexObject : public NonCopyableReferenceCountedClass
        {
                public:
                        ~VertexObject();
                        VertexObject();
                        int SetVerticesArray (NCRC_AutoPtr<DataArray> vertices);
                        int SetVerticesArray (
                                        DataArray::datatype vertices_t, //< type of the data in the array
                                        uint8_t ComponentsCount,        //<number of components per entry
                                        void* vertices,      //< buffer to the array
                                        uint32_t count);     //< number of vertices (the array is count* VerticesSize wide)
                        int SetFaceIndicesArray (NCRC_AutoPtr<DataArray> FaceIndices);
                        int SetFaceIndicesArray (
                                        DataArray::datatype indices_t,  //< type of the data in the array
                                        uint8_t ComponentsCount,        //<number of components per entry
                                        void* indices,       //< buffer to the array
                                        uint32_t count);     //< number of faces (the array is count* VerticeByFacesCount wide)
                        int SetColorArray (NCRC_AutoPtr<DataArray> ColorArray);
                        int SetColorArray (
                                        DataArray::datatype colors_t,  //< type of the data in the array
                                        uint8_t ComponentsCount,        //<number of components per entry
                                        void* colors,       //< buffer to the array
                                        uint32_t count);    //< number of colors (the array is count* ColorSizet wide)
                        int SetNormalArray (NCRC_AutoPtr<DataArray> NormalArray);
                        int SetNormalArray (
                                        DataArray::datatype normals_t, //< type of the data in the array
                                        uint8_t ComponentsCount,        //<number of components per entry
                                        void* normals,      //< buffer to the array
                                        uint32_t count);    //< number of normals (the array is count*3 wide)
                        int AddTexture (
                                        NCRC_AutoPtr<Texture> texture   //< pointer to the class 
                                        //< containing the texture
                                       );

                        //int RemoveTexture (uint8_t index); //<remove the 'index'th texture

                        int ComputeNormals();       //< this function computes normals according to faces
                        //< and face indices, this is a rather expensive function so it
                        //< shall not be used on object with static geometry
                        //< (normals can be computed once for all
                        //<  with this function and then stored into an array and SetNormalArray)



                        int draw();                        //< draw the object at current place current opengl state
                protected : //types
                        struct V3List
                        {
                                vec3 vertex;
                                V3List* next;
                                V3List();                //< constructor
                                V3List(vec3 vert);       //< constructor
                                void print();            //< print the list
                        };

                protected : //variables
                        NCRC_AutoPtr<DataArray> Vertices; //< array containing the vertices size*VerticeCount wide, for glVertexPointer
                        NCRC_AutoPtr<DataArray> Indices;  //< array containing the indices of each faces, for glDrawElements
                        NCRC_AutoPtr<DataArray> Colors;   //< array containing the Colors of each Vertice, for glColorPointer
                        NCRC_AutoPtr<DataArray> Normals;  //< array containing the computed normals of the vertice, for glNormalPointer
                        NCRC_AutoPtr<Texture> TextureData;//< array containing the texture coordinates of the vertice, for glTexCoordPointer
                        uint8_t   TextureCount;           //< number of textures to apply (multitexturing)


                        float no_mat[4];
                        float mat_ambient[4];
                        float mat_ambient_color[4];
                        float mat_diffuse[4];
                        float mat_specular[4];
                        float mat_emission[4];
                        float no_shininess;
                        float low_shininess;
                        float high_shininess;





        };

        //bezier spline class
        class Bezier : public VertexObject
        {
        };

        class Nurbs : public VertexObject
        {
        };



}

#endif //__GLUI_VERTEXOBJECT_H
