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
                                myGluiWinTheme(myGluiWin& owner) : _Window::DefaultTheme(owner) {}
                                int draw()
                                {
                                        // Clear Screen And Depth Buffer
                                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                        // Reset The Current Modelview Matrix
                                        glLoadIdentity();
                                        // Move Left 1.5 Units And Into The Screen 6.0
                                        glTranslatef(40.0f,40.0f,-6.0f);
                                        dynamic_cast<myGluiWin&>(Owner).vo().draw();
                                }
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
                        std::string texturename(getenv("GLUI_THEME_DATA_DIR"));
                        texturename += "/200px-OpenGL_logo.bin.pnm";

                        int w = 30;
                        int h = 30;
                        int thickness = 30;

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


                        NCRC_AutoPtr<Texture> texture(new PPMTexture(texturename));

                        GLint TexCoord[8][2] = 
                              { { texture->Width()    , 0}, // 0
                                { texture->Width()*2/3, 0 }, //1
                                { texture->Width()*2/3, texture->Height() }, //2
                                { texture->Width()    , texture->Height() }, //3
                                { 0                   , 0 }, //4
                                { texture->Width()/3  , 0 }, //5
                                { texture->Width()/3  , texture->Height() }, //6
                                { 0                   , texture->Height() }}; //7
                        NCRC_AutoPtr<DataArray> texcoord(new DataArray(8, 2, DataArray::FLOAT, TexCoord));
                        texture->SetTexCoord(texcoord);

                        GLfloat col_values[8][3]   = { {  0.0, 0.0, 1.0}, //0
                                {  1.0, 0.0, 1.0}, //1
                                {  0.0, 1.0, 1.0}, //2
                                {  1.0, 0.0, 0.0}, //3
                                {  0.0, 1.0, 0.0}, //4
                                {  1.0, 1.0, 1.0}, //5
                                {  1.0, 1.0, 0.0}, //6
                                {  0.0, 1.0, 0.0}}; //7
                        NCRC_AutoPtr<DataArray> colors(new DataArray(8, 3, DataArray::FLOAT, col_values));



                        VO.SetVerticesArray(DataArray::FLOAT, 3, Vertices, 8);
                        VO.SetColorArray(colors);
                        VO.SetFaceIndicesArray (DataArray::UINT8_T, 4, indices, 5);
                        VO.AddTexture(texture);

                        set_resize_policy(FixedSize);
                        SetTheme(new myGluiWinTheme(*this));
                        Start();
                }

                theme* GetDefaultTheme() { return new myGluiWinTheme(*this); }
                VertexObject& vo() { return VO; }

       private :
                VertexObject VO;

};


int main(int argc, char** argv)
{

        struct timespec sleeptime = { 5, 0 };
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

