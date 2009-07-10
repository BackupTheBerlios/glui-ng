#include <GL/glui/DefaultTheme.h>
#include <GL/glui/VertexObject.h>
#include <string.h>

using namespace GLUI;




/////////////////////////////////////////////////////////////////////////
VertexObject* DefaultTheme::raised_box( uint32_t w, uint32_t h, uint32_t thickness)
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


        VertexObject* vo = new VertexObject(3, 3, 4);
        vo->SetVerticesArray(VertexObject::FLOAT, Vertices, 8);
        vo->SetFaceIndicesArray (VertexObject::UINT8_T, indices, 5);
        vo->SetColorArray (VertexObject::FLOAT, Colors, 8);
        //vo->ComputeNormals();
        vo->SetNormalArray (VertexObject::FLOAT, Normals, 8);
        return vo;

}


/////////////////////////////////////////////////////////////////////////////
VertexObject* DefaultTheme::lowered_box( uint32_t w, uint32_t h, uint32_t thickness)
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

        VertexObject* vo = new VertexObject(3, 3, 4);
        vo->SetVerticesArray(VertexObject::FLOAT, Vertices, 8);
        vo->SetFaceIndicesArray (VertexObject::UINT8_T, indices, 5);
        vo->SetColorArray (VertexObject::FLOAT, Colors, 8);
        vo->ComputeNormals();
        return vo;


}

////////////////////////////////////////////////////////////////////
// constructor
DefaultTheme::DefaultTheme()
{

}
        uint8_t DefaultTheme::border_color[4] = { 0, 0, 0, 0 };
        uint8_t DefaultTheme::bkgd_color[4] = { 236, 233, 216, 0};


////////////////////////////////////////////////////////////////////
DefaultThemeData::DefaultThemeData()
{
}


