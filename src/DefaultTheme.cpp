#include <GL/glui/DefaultTheme.h>
#include <GL/glui/VertexObject.h>
#include <string.h>

using namespace GLUI;




/////////////////////////////////////////////////////////////////////////
VertexObject* _DefaultTheme::raised_box( uint32_t w, uint32_t h, uint32_t thickness)
{
        GLfloat Vertices[8][3] = { {  0.0,   0.0, 0.0}, //0
                {    w,   0.0, 0.0}, //1
                {    w,     h, 0.0}, //2
                {  0.0,     h, 0.0}, //3
                {  (float) thickness,   (float) thickness, (float) thickness}, //4
                {w-(float) thickness,   (float) thickness, (float) thickness}, //5
                {w-(float) thickness, h-(float) thickness, (float) thickness}, //6
                {  (float) thickness, h-(float) thickness, (float) thickness}}; //7
        GLfloat Normals[8][3]   = { {  0.0, 0.0, 1.0}, //0
                {  0.0, 0.0, 1.0}, //1
                {  0.0, 0.0, 1.0}, //2
                {  0.0, 0.0, 1.0}, //3
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


        VertexObject* vo = new VertexObject();
        vo->SetVerticesArray(DataArray::FLOAT, 3, Vertices, 8);
        vo->SetFaceIndicesArray (DataArray::UINT8_T, 4, indices, 5);
        vo->SetColorArray (DataArray::FLOAT, 3, Colors, 8);
        //vo->ComputeNormals();
        vo->SetNormalArray (DataArray::FLOAT, 3, Normals, 8);
        return vo;

}


/////////////////////////////////////////////////////////////////////////////
VertexObject* _DefaultTheme::lowered_box( uint32_t w, uint32_t h, uint32_t thickness)
{
        GLfloat Vertices[8][3] = { {  0.0,   0.0, 0.0}, //0
                {    w,   0.0, 0.0}, //1
                {    w,     h, 0.0}, //2
                {  0.0,     h, 0.0}, //3
                {  (float) thickness,   (float) thickness, (float) thickness}, //4
                {w-(float) thickness,   (float) thickness, (float) thickness}, //5
                {w-(float) thickness, h-(float) thickness, (float) thickness}, //6
                {  (float) thickness, h-(float) thickness, (float) thickness}}; //7
        GLfloat Normals[8][3]   = { {  0.0, 0.0, 1.0}, //0
                {  0.0, 0.0, 1.0}, //1
                {  0.0, 0.0, 1.0}, //2
                {  0.0, 0.0, 1.0}, //3
                {  0.0, 0.0, 1.0}, //4
                {  0.0, 0.0, 1.0}, //5
                {  0.0, 0.0, 1.0}, //6
                {  0.0, 0.0, 1.0}}; //7


        GLubyte indices[] = {
                4, 7, 6, 5,		//front
                0, 4, 7, 3,		//top slope
                7, 3, 2, 6,		//right slope
                6, 2, 1, 5,		//bottom slope
                5, 4, 0, 1};	//left slope

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

        VertexObject* vo = new VertexObject();
        vo->SetVerticesArray(DataArray::FLOAT, 3, Vertices, 8);
        vo->SetFaceIndicesArray (DataArray::UINT8_T, 4, indices, 5);
        vo->SetColorArray (DataArray::FLOAT, 3, Colors, 8);
        vo->ComputeNormals();
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
