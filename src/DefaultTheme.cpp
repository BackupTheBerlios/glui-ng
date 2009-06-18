#include <GL/glui/DefaultTheme.h>
#include <GL/glui/Container.h>
#include <GL/glui/VertexObject.h>
#include <GL/glui/button.h>

using namespace GLUI;
////////////////////////////////////////////////////////////
int DefaultButtonTheme::draw()
{
        if (((Button&)owner).GetValue())
        {
                this->pressed->draw();
        }
        else
        {
                this->un_pressed->draw();
        }
}

int DefaultButtonTheme::update()
{
        if (this->un_pressed != NULL ) delete this->un_pressed;
        if (this->pressed != NULL ) delete this->pressed;

        this->un_pressed =  TheTheme.lowered_box(owner.Width(), owner.Height());
        this->pressed = TheTheme.raised_box(owner.Width(), owner.Height());

}

DefaultButtonTheme::~DefaultButtonTheme()
{
        if (this->un_pressed != NULL ) delete this->un_pressed;
        if (this->pressed != NULL ) delete this->pressed;
}
////////////////////////////////////////////////////////////
int DefaultToggleButtonTheme::draw()
{
}
int DefaultToggleButtonTheme::update()
{
}
////////////////////////////////////////////////////////////
int DefaultTextButtonTheme::draw()
{
}
int DefaultTextButtonTheme::update()
{
}

////////////////////////////////////////////////////////////
int DefaultArcballTheme::draw()
{
}
int DefaultArcballTheme::update()
{
}

/////////////////////////////////////////////////////////////////////////////
void DefaultTheme::PostRedisplay(Control* ctrl)
{
        ::XEvent EventToForward;
        //ask for redisplay of window
        EventToForward.xexpose.type=Expose;
        EventToForward.xexpose.send_event=true;
        EventToForward.xexpose.x = ctrl->X();
        EventToForward.xexpose.y = ctrl->Y();
        EventToForward.xexpose.width = ctrl->Width();
        EventToForward.xexpose.height = ctrl->Height();
        Container* cont  = dynamic_cast<Container*>(ctrl->GetRootNode());
        if ( cont != NULL)
        {
                cont->AddEvent(&EventToForward);
        }
}
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
        border_color[0] = 0; //red
        border_color[1] = 0; //green
        border_color[2] = 0; //blue
        border_color[3] = 0; //alpha
        bkgd_color[0] = 236; //red
        bkgd_color[1] = 233; //green
        bkgd_color[2] = 216; //blue
        bkgd_color[3] = 0; //alpha
}

