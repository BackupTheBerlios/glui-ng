#include <GL/glui/window.h>
#include <GL/glui/Texture.h>
#include <GL/glui/VertexObject.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
using namespace GLUI;

class myGluiWin : public GLUI::Window
{
        public :
                class myGluiWinTheme : public _Window::DefaultTheme
                {
                        public:
                                myGluiWinTheme(myGluiWin& owner) : _Window::DefaultTheme(owner) 
                                {
                                        bkgd_color[0] = 255;
                                        bkgd_color[1] = 0;
                                        bkgd_color[2] = 0;

                                        border_color[0] = 0;
                                        border_color[0] = 0;
                                        border_color[0] = 255;

                                        int w = 50;
                                        int h = 50;
                                        int thickness = 50;
                                        GLfloat col_values[8][3]   = { {  0.0, 0.0, 1.0}, //0
                                                {  1.0, 0.0, 1.0}, //1
                                                {  0.0, 1.0, 1.0}, //2
                                                {  1.0, 0.0, 0.0}, //3
                                                {  0.0, 1.0, 0.0}, //4
                                                {  1.0, 1.0, 1.0}, //5
                                                {  1.0, 1.0, 0.0}, //6
                                                {  0.0, 1.0, 0.0}}; //7
                                        NCRC_AutoPtr<DataArray> colors(new DataArray(8, 3, DataArray::FLOAT, col_values));



                                        /////////////first vertex object creation
                                        std::string texturename(getenv("GLUI_THEME_DATA_DIR"));
                                        texturename += "/200px-OpenGL_logo.bin.pnm";

                                        GLfloat Vertices[8][3] = { {  0.0,   0.0, 0.0}, //0
                                                {    w,   0.0, 0.0}, //1
                                                {    w,     h, 0.0}, //2
                                                {  0.0,     h, 0.0}, //3
                                                {  0.0,   0.0, (float) thickness}, //4
                                                {    w,   0.0, (float) thickness}, //5
                                                {    w,     h, (float) thickness}, //6
                                                {  0.0,     h, (float) thickness}}; //7
                                        GLfloat Normals[8][3]   = { {  0.0, 0.0, 1.0}, //0
                                                {  0.0, 0.0, 1.0}, //1
                                                {  0.0, 0.0, 1.0}, //2
                                                {  0.0, 0.0, 1.0}, //3
                                                {  0.0, 0.0, 1.0}, //4
                                                {  0.0, 0.0, 1.0}, //5
                                                {  0.0, 0.0, 1.0}, //6
                                                {  0.0, 0.0, 1.0}}; //7

                                        GLubyte indices[] = {
                                                0, 1, 2, 3,             //bottom
                                                4, 5, 6, 7,             //front
                                                7, 6, 2, 3,             //top slope
                                                5, 1, 2, 6,             //right slope
                                                0, 1, 5, 4,             //bottom slope
                                                0, 4, 7, 3              //left slope
                                                };


                                        NCRC_AutoPtr<Texture> texture(new PPMTexture(texturename));
#warning "to investigate this don't work (segfault)"
                                        /*
                                        uint32_t TexCoord[8][2] = 
                                        { { texture->Width()    , 0}, // 0
                                                { texture->Width()*2/3, 0 }, //1
                                                { texture->Width()*2/3, texture->Height() }, //2
                                                { texture->Width()    , texture->Height() }, //3
                                                { 0                   , 0 }, //4
                                                { texture->Width()/3  , 0 }, //5
                                                { texture->Width()/3  , texture->Height() }, //6
                                                { 0                   , texture->Height() }}; //7
                                        NCRC_AutoPtr<DataArray> texcoord(new DataArray(8, 2, DataArray::UINT32_T, TexCoord));
                                        texture->SetTexCoord(texcoord);*/

                                        float TexCoord[8][2] = 
                                        { { 1.0    , 0.0}, // 0
                                                { 2.0/3, 0 }, //1
                                                { 2.0/3, 1.0 }, //2
                                                { 1.0  , 1.0 }, //3
                                                { 0                   , 0 }, //4
                                                { 1.0/3  , 0 }, //5
                                                { 1.0/3  , 1.0 }, //6
                                                { 0      , 1.0 }}; //7
                                        NCRC_AutoPtr<DataArray> texcoord(new DataArray(8, 2, DataArray::FLOAT, TexCoord));
                                        texture->SetTexCoord(texcoord);



                                        textureVO = new VertexObject();
                                        textureVO->SetVerticesArray(DataArray::FLOAT, 3, Vertices, 8);
                                        //textureVO->SetColorArray(colors);
                                        textureVO->SetFaceIndicesArray (DataArray::UINT8_T, 4, indices, 6);
                                        textureVO->AddTexture(texture);


                                        /////////////////// Second vertex object creation
                                        themeVO = raised_box(30, 50, 10);

                                        //////////////////// Third VO creation
                                        std::string texturename2(getenv("GLUI_THEME_DATA_DIR"));
                                        texturename2 += "/200px-OpenGL_logo.bin.pnm";

                                        rectangleTextureVO =  new VertexObject();
                                        GLfloat Vertices3[4][3] = { {  0.0,   0.0, 0.0}, //0
                                                {    w,   0.0, 0.0}, //1
                                                {    w,     h, 0.0}, //2
                                                {  0.0,     h, 0.0}};//3
                                        rectangleTextureVO->SetVerticesArray(DataArray::FLOAT, 3, Vertices3, 4);
                                        GLubyte indices3[] = {
                                                0, 1, 2, 3
                                                };
                                        rectangleTextureVO->SetFaceIndicesArray (DataArray::UINT8_T, 4, indices3, 1);

                                        NCRC_AutoPtr<Texture> texture3(new PPMTexture(texturename2));
                                        float TexCoord3[4][2] = 
                                        {       { 0.0, 0.0 }, // 0
                                                { 1.0, 0.0 }, //1
                                                { 1.0, 1.0 }, //2
                                                { 0.0, 1.0 } //3
                                        };
                                        NCRC_AutoPtr<DataArray> texcoord3(new DataArray(4, 2, DataArray::FLOAT, TexCoord3));
                                        texture3->SetTexCoord(texcoord3);

                                        rectangleTextureVO->AddTexture(texture3);
                                        //rectangleTextureVO->SetColorArray(colors);


                                }
                                int draw()
                                {
                                        _Window::DefaultTheme::draw();

                                        // Reset The Current Modelview Matrix
                                        glLoadIdentity();
                                        // Move Left 1.5 Units And Into The Screen 6.0
                                        glTranslatef(60.0f,40.0f,-60.0f);
                                        glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
                                        textureVO->draw();

                                        glLoadIdentity();
                                        glTranslatef(20.0f,10.0f,-60.0f);
                                        glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
                                        themeVO->draw();

                                        glLoadIdentity();
                                        glTranslatef(100.0f,100.0f,-60.0f);
                                        glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
                                        rectangleTextureVO->draw();
                                }
                                //int update()
                                //{
                                //        NCRC_AutoPtr<VertexObject>& ownervo = dynamic_cast<myGluiWin&>(Owner).vo();
                                //        if (ownervo == NULL)
                                //        {
                                //        }
                                //}
                        protected :
                                NCRC_AutoPtr<VertexObject> rectangleTextureVO;
                                NCRC_AutoPtr<VertexObject> textureVO;
                                NCRC_AutoPtr<VertexObject> themeVO;


                };
        public :
                myGluiWin(GLUI::Display& TheDisplay) : GLUI::Window(TheDisplay,
                                TheDisplay.XDefaultScreenOfDisplay()->XRootWindowOfScreen(),
                                -1, -1,
                                200, 200,
                                1,
                                1,
                                0)
                {
                        set_resize_policy(FixedSize);
                        SetTheme(new myGluiWinTheme(*this));
                        //TheDefaultTheme->update();
                        Start();
                }


       private :
};


int main(int argc, char** argv)
{

        struct timespec sleeptime = { 500, 0 };
        GLUI::Window::init(&argc, argv);  //optional
        GLUI::Display*    TheDisplay = new GLUI::Display();
        GLUI::Window* Window = new myGluiWin(*TheDisplay);
        Window->XMapWindow();
        nanosleep(&sleeptime, NULL);
        Window->XUnmapWindow();
        nanosleep(&sleeptime, NULL);
        delete(Window); 
        delete(TheDisplay);
        exit(0);

}

