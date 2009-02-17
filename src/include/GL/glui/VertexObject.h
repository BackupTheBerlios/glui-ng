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

namespace GLUI
{

    class VertexObject
      {
          public: //types
              enum datatype { UNDEF, UINT8_T, INT8_T, UINT16_T, INT16_T, UINT32_T, INT32_T, FLOAT, DOUBLE};
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
        protected : //variables
            uint8_t VerticesSize;          //< number of components per vertice
            uint32_t VerticeCount;         //< number of vertices in the object
            uint8_t ColorSize;             //< number of components per colors (3 = RGB, 4 = RGBA)
            uint8_t VerticeByFacesCount;   //< number of vertices per face of the object

            datatype Vertices_t;           //< type of the vertice array
            pointers Vertices;             //< array containing the vertices size*VerticeCount wide, for glVertexPointer

            datatype indices_t;            //< type of the indices array (float and double not allowed)
            pointers indices;              //< array containing the indices of each faces, for glDrawElements

            datatype Colors_t;             //< type of the color array
            pointers Colors;               //< array containing the Colors of each Vertice, for glColorPointer

            datatype Normals_t;            //< type of the Normal array
            pointers Normals;              //< array containing the computed normals of the vertice, for glNormalPointer

            datatype Texture_t;            //< type of the Texture array
            pointers Texture;              //< array containing the texture coordinates of the vertice, for glTexCoordPointer


        protected : //methods
            VertexObject();
            void FreeVertex();
            void FreeIndices();
            void FreeColors();
            void FreeNormals();
            void FreeTexture();

        public:
            ~VertexObject();
            VertexObject(
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
                    );
            int Describe(
                    uint8_t verticessize,
                    uint32_t verticecount,
                    uint8_t colorsize,
                    uint8_t verticebyfacescount);
            int SetVerticesArray (datatype vertices_t, pointers vertices);
            int SetIndicesArray (datatype indices_t, pointers indices);
            int SetColorArray (datatype colors_t, pointers colors);
            int SetNormalArray (datatype normals_t, pointers normals);
            int SetTextureArray (datatype texture_t, pointers texture);



            void draw();                        //< draw the object at current place current opengl state

      };



}

#endif //__GLUI_VERTEXOBJECT_H
