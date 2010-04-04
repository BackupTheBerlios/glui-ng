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

#include <GL/glui/DefaultTheme.h>
#include <GL/glui/VertexObject.h>
#include <string.h>

using namespace GLUI;




/////////////////////////////////////////////////////////////////////////
NCRC_AutoPtr<VertexObject> _DefaultTheme::raised_box( uint32_t w, uint32_t h, uint32_t thickness, uint32_t BorderWidth,
                                                          uint32_t flags)
{
        if (BorderWidth >= w || BorderWidth >= h)
        {
                return NULL;
        }
        uint32_t b = BorderWidth;
        GLfloat Vertices[8][3] = { {  0.0,   0.0, 0.0}, //0
                {    w,   0.0, 0.0}, //1
                {    w,     h, 0.0}, //2
                {  0.0,     h, 0.0}, //3
                 {   b,     b, (float) thickness}, //4
                {  w-b,     b, (float) thickness}, //5
                {  w-b,   h-b, (float) thickness}, //6
                {    b,   h-b, (float) thickness}}; //7
        NCRC_AutoPtr<DataArray> vert(new DataArray(8, 3, DataArray::FLOAT, Vertices));
        NCRC_AutoPtr<DataArray> norm;
        if (flags & enablenormals)
        {
                GLfloat Normals[8][3]   = { {  0.0, 0.0, 1.0}, //0
                        {  0.0, 0.0, 1.0}, //1
                        {  0.0, 0.0, 1.0}, //2
                        {  0.0, 0.0, 1.0}, //3
                        {  0.0, 0.0, 1.0}, //4
                        {  0.0, 0.0, 1.0}, //5
                        {  0.0, 0.0, 1.0}, //6
                        {  0.0, 0.0, 1.0}}; //7
                norm = new DataArray(8, 3, DataArray::FLOAT, Normals);

        }
        return box(vert, norm, flags);
 
}

/////////////////////////////////////////////////////////////////////////////
NCRC_AutoPtr<VertexObject> _DefaultTheme::lowered_box( uint32_t w, uint32_t h, uint32_t thickness, uint32_t BorderWidth,
                                                          uint32_t flags)
{
        if (BorderWidth >= w || BorderWidth >= h)
        {
                return NULL;
        }
        uint32_t b = BorderWidth;

        GLfloat Vertices[8][3] = { {  0.0,   0.0, 0.0}, //0
                {    w,   0.0, 0.0}, //1
                {    w,     h, 0.0}, //2
                {  0.0,     h, 0.0}, //3
                {   b,     b, (float) -thickness}, //4
                {  w-b,     b, (float) -thickness}, //5
                {  w-b,   h-b, (float) -thickness}, //6
                {    b,   h-b, (float) -thickness}}; //7
        NCRC_AutoPtr<DataArray> vert(new DataArray(8, 3, DataArray::FLOAT, Vertices));
        NCRC_AutoPtr<DataArray> norm;
        if (flags & enablenormals)
        {
                GLfloat Normals[8][3]   = { {  0.0, 0.0, 1.0}, //0
                        {  0.0, 0.0, 1.0}, //1
                        {  0.0, 0.0, 1.0}, //2
                        {  0.0, 0.0, 1.0}, //3
                        {  0.0, 0.0, 1.0}, //4
                        {  0.0, 0.0, 1.0}, //5
                        {  0.0, 0.0, 1.0}, //6
                        {  0.0, 0.0, 1.0}}; //7
                norm = new DataArray(8, 3, DataArray::FLOAT, Normals);

        }
        return box(vert, norm, flags);

}

/////////////////////////////////////////////////////////////////////////////
NCRC_AutoPtr<VertexObject> _DefaultTheme::box( NCRC_AutoPtr<DataArray> vertices,
                                        NCRC_AutoPtr<DataArray> normals,
                                        uint32_t flags)
{

        GLubyte indices[] = {
                4, 5, 6, 7,		//front
                7, 6, 2, 3,		//top slope
                5, 1, 2, 6,		//right slope
                0, 1, 5, 4,		//bottom slope
                0, 4, 7, 3,
                0, 1, 2, 3              //bottom
        };	//left slope

        
        NCRC_AutoPtr<VertexObject> vo(new VertexObject());
        vo->SetVerticesArray(vertices);
        vo->SetFaceIndicesArray (DataArray::UINT8_T, 4, indices, 6);
        if (flags & enablecolor)
        {
                float Colors[8][3];
                memset(Colors, 0, 8*3*sizeof(float));
                this->FillglColorPointer(
                                border_color,
                                3,
                                GL_FLOAT,
                                0,
                                Colors,
                                4 );
                this->FillglColorPointer(
                                bkgd_color,
                                3,
                                GL_FLOAT,
                                0,
                                &(Colors[4][0]),
                                4 );


                vo->SetColorArray (DataArray::FLOAT, 3, Colors, 8);
        }
        vo->SetNormalArray (normals);
        if (flags & enablenormalcomputation)
        {
                vo->ComputeNormals();
        }
     
        return vo;

}



////////////////////////////////////////////////////////////////////
// constructor
_DefaultTheme::_DefaultTheme()
{
        border_color[0] = 0;
        border_color[1] = 0;
        border_color[2] = 0;
        border_color[3] = 0;
        bkgd_color[0] = 236;
        bkgd_color[1] = 233;
        bkgd_color[2] = 216;
        bkgd_color[3] = 0;
}


////////////////////////////////////////////////////////////////////
int _DefaultTheme::draw()
{
        return 0;
}
////////////////////////////////////////////////////////////////////
int _DefaultTheme::update()
{
        return 0;
}

////////////////////////////////////////////////////////////////////
void _DefaultTheme::SetBorderColor(uint8_t border_color[4])
{
        memcpy(this->border_color,border_color,4*sizeof(uint8_t));
}
////////////////////////////////////////////////////////////////////
void _DefaultTheme::SetBkgdColor(uint8_t bkgd_color[4])
{
        memcpy(this->bkgd_color,bkgd_color,4*sizeof(uint8_t));
}
////////////////////////////////////////////////////////////////////
void _DefaultTheme::SetActivatedColor(uint8_t activated_color[4])
{
        memcpy(this->activated_color,activated_color,4*sizeof(uint8_t));
}
////////////////////////////////////////////////////////////////////
void _DefaultTheme::SetHoverColor(uint8_t hover_color[4])
{
        memcpy(this->hover_color,hover_color,4*sizeof(uint8_t));
}
////////////////////////////////////////////////////////////////////
void _DefaultTheme::GetBorderColor(uint8_t border_color[4])
{
        memcpy(border_color,this->border_color,4*sizeof(uint8_t));
}
////////////////////////////////////////////////////////////////////
void _DefaultTheme::GetBkgdColor(uint8_t bkgd_color[4])
{
        memcpy(bkgd_color,this->bkgd_color,4*sizeof(uint8_t));
}
////////////////////////////////////////////////////////////////////
void _DefaultTheme::GetActivatedColor(uint8_t activated_color[4])
{
        memcpy(activated_color,this->activated_color,4*sizeof(uint8_t));
}
////////////////////////////////////////////////////////////////////
void _DefaultTheme::GetHoverColor(uint8_t hover_color[4])
{
        memcpy(hover_color,this->hover_color,4*sizeof(uint8_t));
}
