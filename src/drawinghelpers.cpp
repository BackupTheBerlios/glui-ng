
#define __STDC_LIMIT_MACROS
#include <GL/gl.h>
#include <GL/glui/themes.h>
#include <GL/glui/debug.h>
#include <string.h>
#include <GL/glui/container.h>

using namespace GLUI;
/////////////////////////////////////////////////////////////////////////
VertexObject* drawinghelpers::raised_box( uint32_t w, uint32_t h, uint32_t thickness, uint8_t size, GLenum intype, void *color_array)
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
        theme::Instance()->FillglColorPointer(3,
                GL_FLOAT,
                0,
                Colors,
                8 );

      }
    VertexObject* vo = new VertexObject(3, 3, 4);
    vo->SetVerticesArray(VertexObject::FLOAT, Vertices, 8);
    vo->SetFaceIndicesArray (VertexObject::UINT8_T, indices, 5);
    vo->SetColorArray (VertexObject::FLOAT, Colors, 8);
    //vo->ComputeNormals();
    vo->SetNormalArray (VertexObject::FLOAT, Normals, 8);
    return vo;

}


/////////////////////////////////////////////////////////////////////////////
VertexObject* drawinghelpers::lowered_box( uint32_t w, uint32_t h, uint32_t thickness, uint8_t size, GLenum intype, void *color_array)
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
        theme::Instance()->FillglColorPointer(3,
                GL_FLOAT,
                0,
                Colors,
                8 );

      }
    VertexObject* vo = new VertexObject(3, 3, 4);
    vo->SetVerticesArray(VertexObject::FLOAT, Vertices, 8);
    vo->SetFaceIndicesArray (VertexObject::UINT8_T, indices, 5);
    vo->SetColorArray (VertexObject::FLOAT, Colors, 8);
    vo->ComputeNormals();
    return vo;


}

/////////////////////////////////////////////////////////////////////////////

void drawinghelpers::set_to_bkgd_color( void )
{
  glColor3ubv( theme::Instance()->Get_bkgd_color() );
}

/////////////////////////////////////////////////////////////////////////////

void drawinghelpers::draw_box_inwards_outline(int enabled, int x_min, int x_max, int y_min, int y_max )
{
  glBegin( GL_LINES );
  glColor3f( .5, .5, .5 );
  glVertex2i( x_min, y_min );     glVertex2i( x_max, y_min );
  glVertex2i( x_min, y_min );     glVertex2i( x_min, y_max );

  glColor3f( 1., 1., 1. );
  glVertex2i( x_min, y_max );     glVertex2i( x_max, y_max );
  glVertex2i( x_max, y_max );     glVertex2i( x_max, y_min );

  if ( enabled )
    glColor3f( 0., 0., 0. );
  else
    glColor3f( .25, .25, .25 );

  glVertex2i( x_min+1, y_min+1 );     glVertex2i( x_max-1, y_min+1 );
  glVertex2i( x_min+1, y_min+1 );     glVertex2i( x_min+1, y_max-1 );

  glColor3f( .75, .75, .75 );
  glVertex2i( x_min+1, y_max-1 );     glVertex2i( x_max-1, y_max-1 );
  glVertex2i( x_max-1, y_max-1 );     glVertex2i( x_max-1, y_min+1 );
  glEnd();
}


/////////////////////////////////////////////////////////////////////////////

void drawinghelpers::draw_box(uint32_t w, uint32_t h, uint8_t size, GLenum intype, void *color_array)
{
    GLfloat Vertices[4][3] = { {  0.0,   0.0, 0.0}, //0
        {  0.0,     h, 0.0}, //1
        {    w,     h, 0.0}, //2
        {    w,   0.0, 0.0}}; //3
    GLubyte indices[] = { 0, 1, 2, 3};
    float Colors[] = {0.0, 0.0, 0.0, 0.0,
                      0.0, 0.0, 0.0, 0.0,
                      0.0, 0.0, 0.0, 0.0,
                      0.0, 0.0, 0.0, 0.0}; //allow enough size for a RGBA, however by default 3 will be used

    if (color_array)
      {
        ConvertglColorArray(
                size, //<  how many components 3 (RGB) or 4(RGBA)
                intype,  //< type of the input
                color_array, //< pointer of the datas
                GL_FLOAT,  //< type of the output
                Colors,  //<pointer to the outputdata
                4 //< count of the numbers of elements in the array (an element in 3 or 4 components)
                );

      }
    else
      {
        theme::Instance()->FillglColorPointer(
                3,
                GL_FLOAT,
                0,
                Colors,
                4 );
      }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glColorPointer(size, GL_FLOAT, 0, Colors);
    glVertexPointer(3, GL_FLOAT, 0, Vertices);
    //go through our index array and draw our vertex array
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    debug::Instance()->FlushGL();
}



/////////////////////////////////////////////////////////////////////////////

void drawinghelpers::draw_active_box( int active, int x_min, int x_max, int y_min, int y_max )
{

  if ( active ) {
    glEnable( GL_LINE_STIPPLE );
    glLineStipple( 1, 0x5555 );
    glColor3f( 0., 0., 0. );
  } else {
    set_to_bkgd_color();
  }

  glBegin( GL_LINE_LOOP );
  glVertex2i(x_min, y_min);      glVertex2i( x_max, y_min );
  glVertex2i(x_max, y_max);      glVertex2i( x_min, y_max );
  glEnd();

  glDisable( GL_LINE_STIPPLE );
}


/////////////////////////////////////////////////////////////////////////////

void drawinghelpers::draw_emboss_box(int x_min,int x_max,int y_min,int y_max)
{
  glLineWidth( 1.0 );
  glColor3f( 1.0, 1.0, 1.0 );

  glBegin( GL_LINE_LOOP );
  glVertex2i( x_min, y_min );    glVertex2i( x_max, y_min );
  glVertex2i( x_max, y_max );    glVertex2i( x_min, y_max );
  glEnd();

  glBegin( GL_LINE_LOOP );
  glVertex2i( x_min+1, y_min+1 );    glVertex2i( x_max-1, y_min+1 );
  glVertex2i( x_max-1, y_max-1 );    glVertex2i( x_min+1, y_max-1 );
  glEnd();

  glColor3f( .5, .5, .5 );
  glBegin( GL_LINE_LOOP );
  glVertex2i( x_min, y_min );
  glVertex2i( x_max-1, y_min );
  glVertex2i( x_max-1, y_max-1 );
  glVertex2i( x_min, y_max-1 );
  glEnd();
}

/////////////////////////////////////////////////////////////////////////////
#warning "move get_buffer_mode to window class since it belongs more there"
drawinghelpers::buffer_mode_t drawinghelpers::get_buffer_mode() {
    char* bufferModeEnv = getenv("GLUI_BUFFER_MODE");
    if ( bufferModeEnv != NULL &&
            0 ==  strcmp(bufferModeEnv, "buffer_front") ) return buffer_front;
    else return buffer_back;
}

/////////////////////////////////////////////////////////////////////////////
void drawinghelpers::PostRedisplay(Control* ctrl)
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

////////////////////////////////////////////////////////////////////////////
void drawinghelpers::ConvertglColorPointer(GLint size, //<  how many components 3 (RGB) or 4(RGBA)
                    GLenum intype,  //< type of the input
                    const GLvoid *inpointer, //< pointer of the datas
                    GLenum outype,  //< type of the output
                    const GLvoid *outpointer  //<pointer to the outputdata
                    )
{
    if (!(
                (size >= 3 || size <= 4) &&
                (intype == GL_BYTE           ||
                 intype == GL_UNSIGNED_BYTE  ||
                 intype == GL_SHORT          ||
                 intype == GL_UNSIGNED_SHORT ||
                 intype == GL_INT            ||
                 intype == GL_UNSIGNED_INT   ||
                 intype == GL_FLOAT          ||
                 intype == GL_DOUBLE)    &&
                (outype == GL_BYTE           ||
                 outype == GL_UNSIGNED_BYTE  ||
                 outype == GL_SHORT          ||
                 outype == GL_UNSIGNED_SHORT ||
                 outype == GL_INT            ||
                 outype == GL_UNSIGNED_INT   ||
                 outype == GL_FLOAT          ||
                 outype == GL_DOUBLE)    &&
                ( inpointer != NULL )    &&
                ( outpointer != NULL )
         )
         )
         {
        throw(GL_INVALID_VALUE);
    }
    double colorelem[4];
    colorelem[3] = 0.0;
    switch (intype)
    {
        case GL_BYTE :
            {
                int8_t *bkgd_color = (int8_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / INT8_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / INT8_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / INT8_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / INT8_MAX;
            }
            break;
        case GL_UNSIGNED_BYTE :
            {
                uint8_t *bkgd_color = (uint8_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / UINT8_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / UINT8_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / UINT8_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / UINT8_MAX;
            }
            break;
        case GL_SHORT:
            {
                int16_t *bkgd_color = (int16_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / INT16_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / INT16_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / INT16_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / INT16_MAX;
            }
            break;
        case GL_UNSIGNED_SHORT:
            {
                uint16_t *bkgd_color = (uint16_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / UINT16_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / UINT16_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / UINT16_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / UINT16_MAX;
            }
            break;
        case GL_INT:
            {
                int32_t *bkgd_color = (int32_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / INT32_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / INT32_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / INT32_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / INT32_MAX;
            }
            break;
        case GL_UNSIGNED_INT:
            {
                uint32_t *bkgd_color = (uint32_t*) inpointer;
                colorelem[0] = (double)bkgd_color[0] * 1.0 / UINT32_MAX;
                colorelem[1] = (double)bkgd_color[1] * 1.0 / UINT32_MAX;
                colorelem[2] = (double)bkgd_color[2] * 1.0 / UINT32_MAX;
                if (size==4) colorelem[3] = (double)bkgd_color[3] * 1.0 / UINT32_MAX;
            }
            break;
        case GL_FLOAT:
            {
                float *bkgd_color = (float*) inpointer;
                colorelem[0] = (double)bkgd_color[0];
                colorelem[1] = (double)bkgd_color[1];
                colorelem[2] = (double)bkgd_color[2];
                if (size==4) colorelem[3] = (double)bkgd_color[3];
            }
            break;
        case GL_DOUBLE:
            {
                double *bkgd_color = (double*) inpointer;
                colorelem[0] = (double)bkgd_color[0];
                colorelem[1] = (double)bkgd_color[1];
                colorelem[2] = (double)bkgd_color[2];
                if (size==4) colorelem[3] = (double)bkgd_color[3];
            }
            break;
        default:
            throw(GL_INVALID_VALUE);
    }
    switch (outype)
    {
        case GL_BYTE :
            {
                int8_t *bkgd_color = (int8_t*) outpointer;
                bkgd_color[0] = (int8_t)(colorelem[0] * INT8_MAX);
                bkgd_color[1] = (int8_t)(colorelem[1] * INT8_MAX);
                bkgd_color[2] = (int8_t)(colorelem[2] * INT8_MAX);
                if (size==4) bkgd_color[3] = (int8_t)(colorelem[3] * INT8_MAX);
            }
            break;
        case GL_UNSIGNED_BYTE :
            {
                uint8_t *bkgd_color = (uint8_t*) outpointer;
                bkgd_color[0] = (uint8_t)(colorelem[0] * UINT8_MAX);
                bkgd_color[1] = (uint8_t)(colorelem[1] * UINT8_MAX);
                bkgd_color[2] = (uint8_t)(colorelem[2] * UINT8_MAX);
                if (size==4) bkgd_color[3] = (uint8_t)(colorelem[3] * UINT8_MAX);
            }
            break;
        case GL_SHORT:
            {
                int16_t *bkgd_color = (int16_t*) outpointer;
                bkgd_color[0] = (int16_t)(colorelem[0] * INT16_MAX);
                bkgd_color[1] = (int16_t)(colorelem[1] * INT16_MAX);
                bkgd_color[2] = (int16_t)(colorelem[2] * INT16_MAX);
                if (size==4) bkgd_color[3] = (int16_t)(colorelem[3] * INT16_MAX);
            }
            break;
        case GL_UNSIGNED_SHORT:
            {
                uint16_t *bkgd_color = (uint16_t*) outpointer;
                bkgd_color[0] = (uint16_t)(colorelem[0] * UINT16_MAX);
                bkgd_color[1] = (uint16_t)(colorelem[1] * UINT16_MAX);
                bkgd_color[2] = (uint16_t)(colorelem[2] * UINT16_MAX);
                if (size==4) bkgd_color[3] = (uint16_t)(colorelem[3] * UINT16_MAX);
            }
            break;
        case GL_INT:
            {
                int32_t *bkgd_color = (int32_t*) outpointer;
                bkgd_color[0] = (int32_t)(colorelem[0] * INT32_MAX);
                bkgd_color[1] = (int32_t)(colorelem[1] * INT32_MAX);
                bkgd_color[2] = (int32_t)(colorelem[2] * INT32_MAX);
                if (size==4) bkgd_color[3] = (int32_t)(colorelem[3] * INT32_MAX);
            }
            break;
        case GL_UNSIGNED_INT:
            {
                uint32_t *bkgd_color = (uint32_t*) outpointer;
                bkgd_color[0] = (uint32_t)(colorelem[0] * UINT32_MAX);
                bkgd_color[1] = (uint32_t)(colorelem[1] * UINT32_MAX);
                bkgd_color[2] = (uint32_t)(colorelem[2] * UINT32_MAX);
                if (size==4) bkgd_color[3] = (uint32_t)(colorelem[3] * UINT32_MAX);
            }
            break;
        case GL_FLOAT:
            {
                float *bkgd_color = (float*) outpointer;
                bkgd_color[0] = (float)colorelem[0];
                bkgd_color[1] = (float)colorelem[1];
                bkgd_color[2] = (float)colorelem[2];
                if (size==4) bkgd_color[3] = (float)colorelem[3];
            }
            break;
        case GL_DOUBLE:
            {
                double *bkgd_color = (double*) outpointer;
                bkgd_color[0] = (double)colorelem[0];
                bkgd_color[1] = (double)colorelem[1];
                bkgd_color[2] = (double)colorelem[2];
                if (size==4) bkgd_color[3] = (double)colorelem[3];
            }
            break;
        default:
            throw(GL_INVALID_VALUE);
    }
}

void drawinghelpers::ConvertglColorArray(
                    GLint size, //<  how many components 3 (RGB) or 4(RGBA)
                    GLenum intype,  //< type of the input
                    const GLvoid *inpointer, //< pointer of the datas
                    GLenum outype,  //< type of the output
                    const GLvoid *outpointer,  //<pointer to the outputdata
                    uint32_t count //< count of the numbers of elements in the array (an element in 3 or 4 components)
                    )
{
    if (!(
                (size >= 3 || size <= 4) &&
                (intype == GL_BYTE           ||
                 intype == GL_UNSIGNED_BYTE  ||
                 intype == GL_SHORT          ||
                 intype == GL_UNSIGNED_SHORT ||
                 intype == GL_INT            ||
                 intype == GL_UNSIGNED_INT   ||
                 intype == GL_FLOAT          ||
                 intype == GL_DOUBLE)    &&
                (outype == GL_BYTE           ||
                 outype == GL_UNSIGNED_BYTE  ||
                 outype == GL_SHORT          ||
                 outype == GL_UNSIGNED_SHORT ||
                 outype == GL_INT            ||
                 outype == GL_UNSIGNED_INT   ||
                 outype == GL_FLOAT          ||
                 outype == GL_DOUBLE)    &&
                ( inpointer != NULL )    &&
                ( outpointer != NULL )
         )
         )
           {
             throw(GL_INVALID_VALUE);
           }

    void *CurrentInPos;
    void *CurrentOutPos;
    for (uint32_t i=0; i<count; i++)
    {
        switch (intype)
        {
            case GL_BYTE:
                CurrentInPos = (void*)(((int8_t *) inpointer ) + i * size);
                break;
            case GL_SHORT:
                CurrentInPos = (void*)(((int16_t *) inpointer ) + i * size);
                break;
            case GL_INT:
                CurrentInPos = (void*)(((int32_t *) inpointer ) + i * size);
                break;
            case GL_UNSIGNED_BYTE:
                CurrentInPos = (void*)(((uint8_t *) inpointer ) + i * size);
                break;
            case GL_UNSIGNED_SHORT:
                CurrentInPos = (void*)(((uint16_t *) inpointer ) + i * size);
                break;
            case GL_UNSIGNED_INT:
                CurrentInPos = (void*)(((uint32_t *) inpointer ) + i * size);
                break;
            case GL_FLOAT:
                CurrentInPos = (void*)(((float *) inpointer ) + i * size);
                break;
            case GL_DOUBLE:
                CurrentInPos = (void*)(((double *) inpointer ) + i * size);
                break;
        }
        switch (outype)
        {
            case GL_BYTE:
                CurrentOutPos = (void*)(((int8_t *) outpointer ) + i * size);
                break;
            case GL_SHORT:
                CurrentOutPos = (void*)(((int16_t *) outpointer ) + i * size);
                break;
            case GL_INT:
                CurrentOutPos = (void*)(((int32_t *) outpointer ) + i * size);
                break;
            case GL_UNSIGNED_BYTE:
                CurrentOutPos = (void*)(((uint8_t *) outpointer ) + i * size);
                break;
            case GL_UNSIGNED_SHORT:
                CurrentOutPos = (void*)(((uint16_t *) outpointer ) + i * size);
                break;
            case GL_UNSIGNED_INT:
                CurrentOutPos = (void*)(((uint32_t *) outpointer ) + i * size);
                break;
            case GL_FLOAT:
                CurrentOutPos = (void*)(((float *) outpointer ) + i * size);
                break;
            case GL_DOUBLE:
                CurrentOutPos = (void*)(((double *) outpointer ) + i * size);
                break;
        }
        drawinghelpers::ConvertglColorPointer(size, intype, CurrentInPos, outype, CurrentOutPos);
    }
    return;

}

