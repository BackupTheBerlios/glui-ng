#include <GL/gl.h>
#include <GL/glui/drawinghelpers.h>
#include <GL/glui/debug.h>

using namespace GLUI;
/************************************ drawinghelpers::draw_raised_box() **********/

void      drawinghelpers::draw_raised_box( int x, int y, int w, int h )
{
	GLfloat Vertices[8][3] = { {  0.0,   0.0, 0.0}, //0
							   {  0.0,     h, 0.0}, //1
							   {    w,     h, 0.0}, //2
							   {    w,   0.0, 0.0}, //3
							   {  1.0,   1.0, 1.0}, //4
							   {  1.0, h-1.0, 1.0}, //5
							   {w-1.0, h-1.0, 1.0}, //6
							   {w-1.0,   1.0, 1.0}}; //7
	GLubyte indices[] = {
						4, 7, 6, 5,		//front
						0, 4, 7, 3,		//top slope
						7, 3, 2, 6,		//right slope
						6, 2, 1, 5,		//bottom slope
						5, 4, 0, 1};	//left slope

	GLint Colors[] = {            0,            0,            0,
						0,            0,            0,
						0,            0,            0,
						0,            0,            0,
						theme::Instance()->bkgd_color[0],theme::Instance()->bkgd_color[1],theme::Instance()->bkgd_color[2],
						theme::Instance()->bkgd_color[0],theme::Instance()->bkgd_color[1],theme::Instance()->bkgd_color[2],
						theme::Instance()->bkgd_color[0],theme::Instance()->bkgd_color[1],theme::Instance()->bkgd_color[2],
						theme::Instance()->bkgd_color[0],theme::Instance()->bkgd_color[1],theme::Instance()->bkgd_color[2]};



	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_INT, 0, Colors);
	glVertexPointer(3, GL_FLOAT, 0, Vertices);
	//go through our index array and draw our vertex array
	glDrawElements(GL_QUADS, 20, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	debug::Instance()->FlushGL();
}


/************************************ drawinghelpers::draw_lowered_box() **********/
void      drawinghelpers::draw_lowered_box( int x, int y, int w, int h )
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

	GLint Colors[] = {            0,            0,            0,
						0,            0,            0,
						0,            0,            0,
						0,            0,            0,
						theme::Instance()->bkgd_color[0],theme::Instance()->bkgd_color[1],theme::Instance()->bkgd_color[2],
						theme::Instance()->bkgd_color[0],theme::Instance()->bkgd_color[1],theme::Instance()->bkgd_color[2],
						theme::Instance()->bkgd_color[0],theme::Instance()->bkgd_color[1],theme::Instance()->bkgd_color[2],
						theme::Instance()->bkgd_color[0],theme::Instance()->bkgd_color[1],theme::Instance()->bkgd_color[2]};


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_INT, 0, Colors);
	glVertexPointer(3, GL_FLOAT, 0, Vertices);
	//go through our index array and draw our vertex array
	glDrawElements(GL_QUADS, 20, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	debug::Instance()->FlushGL();
}

/********** drawinghelpers::set_to_bkgd_color() ********/

void drawinghelpers::set_to_bkgd_color( void )
{
  glColor3ubv( theme::Instance()->bkgd_color );
}

/******** drawinghelpers::draw_box_inwards_outline() ********/

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


/******* drawinghelpers::draw_box() **********/

void drawinghelpers::draw_box(int enabled, int x_min, int x_max, int y_min, int y_max, float r, float g, float b)
{
  if ( r == 1.0 && g == 1.0 && b == 1.0 && (! enabled) ) {
    draw_bkgd_box( x_min, x_max, y_min, y_max );
    return;
  }

  glColor3f( r, g, b );
  glBegin( GL_QUADS );
  glVertex2i( x_min, y_min );       glVertex2i( x_max, y_min );
  glVertex2i( x_max, y_max );       glVertex2i( x_min, y_max );
  glEnd();
}


/******* drawinghelpers::draw_bkgd_box() **********/

void drawinghelpers::draw_bkgd_box( int x_min, int x_max, int y_min, int y_max )
{
  set_to_bkgd_color();

  glBegin( GL_QUADS );
  glVertex2i( x_min, y_min );       glVertex2i( x_max, y_min );
  glVertex2i( x_max, y_max );       glVertex2i( x_min, y_max );
  glEnd();
}


/**** drawinghelpers::draw_active_area() ********/

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


/**** drawinghelpers::draw_emboss_box() ********/

void   drawinghelpers::draw_emboss_box(int x_min,int x_max,int y_min,int y_max)
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



