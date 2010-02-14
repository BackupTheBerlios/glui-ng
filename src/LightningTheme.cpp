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

#include <GL/glui/LightningTheme.h>
#include <GL/glui/VertexObject.h>
#include <string.h>
using namespace GLUI;

/////////////////////////////////////////////////////////////////////////
int LigthningWindowTheme::draw()
{
#warning "glPushAttrib"
/*    glDisable ( GL_LIGHTING );

    //< http://jerome.jouvie.free.fr/OpenGl/Tutorials/Tutorial13.php
    glEnable ( GL_LIGHTING );
    GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightDiffuse[]= { 0.2f, 0.5f, 0.5f, 1.0f };
    GLfloat LightPosition[]= { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
    glEnable(GL_LIGHT1);
*/
}
int LigthningWindowTheme::update()
{
}
/////////////////////////////////////////////////////////////////////////
VertexObject* LigthningTheme::raised_box( uint32_t w, uint32_t h, uint32_t thickness, uint8_t size, GLenum intype, void *color_array)
{
    GLfloat Vertices[8][3] = { {  0.0,   0.0, 0.0}, //0
                                {    w,   0.0, 0.0}, //1
                                {    w,     h, 0.0}, //2
                                {  0.0,     h, 0.0}, //3
                                {  (float) thickness,   (float) thickness, (float) thickness}, //4
                                {w-(float) thickness,   (float) thickness, (float) thickness}, //5
                                {w-(float) thickness, h-(float) thickness, (float) thickness}, //6
                                {  (float) thickness, h-(float) thickness, (float) thickness}}; //7
    GLfloat Normals[8][3]   = { {  -0.408248, -0.408248, 0.816497}, //0
                                {  0.408248, -0.408248, 0.816497}, //1
                                {  0.408248, 0.408248, 0.816497}, //2
                                {  -0.408248, 0.408248, 0.816497}, //3
                                {  0.0, 0.0, 1.0}, //4
                                {  0.0, 0.0, 1.0}, //5
                                {  0.0, 0.0, 1.0}, //6
                                {  0.0, 0.0, 1.0}}; //7


    GLubyte indices[] = {
                            4, 5, 6, 7,		//front
                            7, 6, 2, 3,		//top slope
                            5, 1, 2, 6,		//right slope
                            0, 1, 5, 4,		//bottom slope
                            0, 4, 7, 3};	//left slope

    float Colors[8][3];
    memset(Colors, 0, 8*3*sizeof(float));
    if (color_array)
      {
        ConvertglColorArray(
                size, //<  how many components 3 (RGB) or 4(RGBA)
                intype,  //< type of the input
                color_array, //< pointer of the datas
                GL_FLOAT,  //< type of the output
                Colors,  //<pointer to the outputdata
                8 //< count of the numbers of elements in the array (an element in 3 or 4 components)
                );

      }
    else
      {
        this->FillglColorPointer(
                bkgd_color,
                3,
                GL_FLOAT,
                0,
                Colors,
                8 );

      }
    VertexObject* vo = new VertexObject();
    vo->SetVerticesArray(DataArray::FLOAT, 3, Vertices, 8);
    vo->SetFaceIndicesArray (DataArray::UINT8_T, 4, indices, 5);
    vo->SetColorArray (DataArray::FLOAT, 3, Colors, 8);
    //vo->ComputeNormals();
    vo->SetNormalArray (DataArray::FLOAT, 3, Normals, 8);
    return vo;

}


/////////////////////////////////////////////////////////////////////////////
VertexObject* LigthningTheme::lowered_box( uint32_t w, uint32_t h, uint32_t thickness, uint8_t size, GLenum intype, void *color_array)
{
    float Vertices[8][3] = { {  0.0,   0.0,  0.0},
                                {  0.0,     h,  0.0},
                                {    w,     h,  0.0},
                                {    w,   0.0,  0.0},
                                {  0.5,   0.5, -0.5},
                                {  0.5, h-0.5, -0.5},
                                {w-0.5, h-0.5, -0.5},
                                {w-0.5,   0.5, -0.5}};
    GLubyte indices[] = {
                            4, 7, 6, 5,		//front
                            0, 4, 7, 3,		//top slope
                            7, 3, 2, 6,		//right slope
                            6, 2, 1, 5,		//bottom slope
                            5, 4, 0, 1};	//left slope

    float Colors[8][3];
    memset(Colors, 0, 8*3*sizeof(float));
    if (color_array)
      {
        ConvertglColorArray(
                size, //<  how many components 3 (RGB) or 4(RGBA)
                intype,  //< type of the input
                color_array, //< pointer of the datas
                GL_FLOAT,  //< type of the output
                Colors,  //<pointer to the outputdata
                8 //< count of the numbers of elements in the array (an element in 3 or 4 components)
                );

      }
    else
      {
        this->FillglColorPointer(
                bkgd_color,
                3,
                GL_FLOAT,
                0,
                Colors,
                8 );

      }
    VertexObject* vo = new VertexObject();
    vo->SetVerticesArray(DataArray::FLOAT, 3, Vertices, 8);
    vo->SetFaceIndicesArray (DataArray::UINT8_T, 4, indices, 5);
    vo->SetColorArray (DataArray::FLOAT, 3, Colors, 8);
    vo->ComputeNormals();
    return vo;


}
