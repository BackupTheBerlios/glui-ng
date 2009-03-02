#ifndef __GLUI_VERTEXOBJECT_H
#define __GLUI_VERTEXOBJECT_H

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
#include <stdint.h>
#include <GL/gl.h>
#include <GL/glui/algebra3.h>
namespace GLUI
{

    class VertexObject
      {
          public: //types
              enum datatype { UNDEF   = 0,
                              UINT8_T = GL_UNSIGNED_BYTE,
                              INT8_T  = GL_BYTE,
                              UINT16_T= GL_UNSIGNED_SHORT,
                              INT16_T = GL_SHORT,
                              UINT32_T= GL_UNSIGNED_INT,
                              INT32_T = GL_INT,
                              FLOAT   = GL_FLOAT,
                              DOUBLE  = GL_DOUBLE};
              union pointers {
                  void*    all;
                  uint8_t* puint8;
                  int8_t* pint8;
                  uint16_t* puint16;
                  int16_t* pint16;
                  uint32_t* puint32;
                  int32_t* pint32;
                  float* pfloat;
                  double* pdouble;
              };

              struct DataArray
              {
                  public :
                      uint32_t count;
                      datatype datatype_t;
                      pointers array;
                      /// methods
                      DataArray(uint32_t count, datatype datatype_t);
                      DataArray(uint32_t count, datatype datatype_t,pointers data);
                      ~DataArray();
                  private:
                      void _DataArray(uint32_t count, datatype datatype_t,pointers data);
                      DataArray();
                      int CpyArray(pointers data);
              };

              struct V3List
                {
                  vec3 vertex;
                  V3List* next;
                  V3List();                //< constructor
                  V3List(vec3 vert);       //< constructor
                  void clean();            //< recursively delete the list
                  void add(V3List* newv3); //< add a V3List at the end of the list
                };

        protected : //variables
            uint8_t VerticesSize;          //< number of components per vertice
            uint8_t ColorSize;             //< number of components per colors (3 = RGB, 4 = RGBA)
            uint8_t VerticeByFacesCount;   //< number of vertices per face of the object

            DataArray* Vertices;             //< array containing the vertices size*VerticeCount wide, for glVertexPointer
            DataArray* indices;              //< array containing the indices of each faces, for glDrawElements
            DataArray* Colors;               //< array containing the Colors of each Vertice, for glColorPointer
            DataArray* Normals;              //< array containing the computed normals of the vertice, for glNormalPointer
            DataArray* Texture;              //< array containing the texture coordinates of the vertice, for glTexCoordPointer


            float no_mat[4];
            float mat_ambient[4];
            float mat_ambient_color[4];
            float mat_diffuse[4];
            float mat_specular[4];
            float no_shininess;
            float low_shininess;
            float high_shininess;
            float mat_emission[4];



        protected : //methods
            VertexObject();

        public:
            ~VertexObject();
            VertexObject(
                    uint8_t verticessize,
                    uint8_t colorsize,
                    uint8_t verticebyfacescount
                    );
            int SetVerticesArray (
                    datatype vertices_t, //< type of the data in the array
                    void* vertices,      //< buffer to the array
                    uint32_t count);     //< number of vertices (the array is count* VerticesSize wide)
            int SetFaceIndicesArray (
                    datatype indices_t,  //< type of the data in the array
                    void* indices,       //< buffer to the array
                    uint32_t count);     //< number of faces (the array is count* VerticeByFacesCount wide)
            int SetColorArray (
                    datatype colors_t,  //< type of the data in the array
                    void* colors,       //< buffer to the array
                    uint32_t count);    //< number of colors (the array is count* ColorSizet wide)
            int SetNormalArray (
                    datatype normals_t, //< type of the data in the array
                    void* normals,      //< buffer to the array
                    uint32_t count);    //< number of normals (the array is count*3 wide)
            int SetTextureArray (
                    datatype texture_t, //< type of the data in the array
                    void* texture,      //< buffer to the array
                    uint32_t count);    //< number of texture components (the array is count wide)

            int ComputeNormals();       //< this function computes normals according to faces
                                        //< and face indices, this is a rather expensive function so it
                                        //< shall not be used on object with static geometry
                                        //< (normals can be computed once for all
                                        //<  with this function and then stored into an array and SetNormalArray)



            void draw();                        //< draw the object at current place current opengl state

      };



}

#endif //__GLUI_VERTEXOBJECT_H
