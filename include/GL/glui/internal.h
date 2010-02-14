#ifndef GLUI_INTERNAL_H
#define GLUI_INTERNAL_H
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

#include <cstdio>
#include <cmath>


namespace GLUI
{
#ifndef AND
#define AND &&
#define OR  ||
#define NOT !
#endif

#ifndef MAX
#define MAX(a,b)  ((a)>(b) ? (a) : (b))
#define MIN(a,b)  ((a)<(b) ? (a) : (b))
#endif

#ifndef ABS
#define ABS(a) ((a)>=0 ? (a) : (-(a)))
#endif

	/********************  bit comparisons and operations ***************/
#ifndef TEST_BIT
#define TEST_BIT( x, b )   (((x) & (1<<(b))) != 0 )
#define SET_BIT( x, b )    ((x) |= (1 << (b)))
#define CLEAR_BIT( x, b )  ((x) &= ~(1 << (b)))
#define TOGGLE_BIT( x, b ) ((TEST_BIT(x,b)) ?(CLEAR_BIT(x,b)):(SET_BIT(x,b)))
#endif

#ifndef TEST_AND
#define TEST_AND( a, b ) ((a&b)==b)
#endif


#ifndef M_PI
#define M_PI 3.141592654
#endif

	/*********** flush the stdout and stderr output streams *************/
#ifndef flushout
#define flushout fflush(stdout)
#define flusherr fflush(stderr)
#endif

	/********** Debugging functions *************************************/
#ifndef error_return
#define error_return( c ); {fprintf(stderr,c);return;}
#endif

	/************************* floating-point random ********************/
#ifndef randf
#define randf()  ((float) rand() / (float)RAND_MAX )
#endif

#ifndef SIGN
#define SIGN(x) ((x)>=0 ?  1  :  -1)
#endif

	/****************** conversion between degrees and radians **********/
#ifndef DEG2RAD
#define DEG2RAD(x) ((x)/180.0*M_PI)
#define RAD2DEG(x) ((x)/M_PI*180.0)
#endif

	/***************** clamp a value to some fixed interval *************/
#ifndef CLAMP
#define CLAMP(x,lo,hi)  {if ((x) < (lo)) {(x)=(lo);} else if((x) > (hi)) {(x)=(hi);}}
#endif

	/************ check if a value lies within a closed interval *********/
#ifndef IN_BOUNDS
#define IN_BOUNDS( x, lo, hi ) ( (x) >= (lo) AND (x) <= (hi) )
#endif

	/************ check if a 2D point lies within a 2D box ***************/
#ifndef PT_IN_BOX
#define PT_IN_BOX( x, y, lo_x, hi_x, lo_y, hi_y ) \
	( IN_BOUNDS(x,lo_x,hi_x) AND IN_BOUNDS(y,lo_y,hi_y) )
#endif

	/****** check if value lies on proper side of another value     *****/
	/*** if side is positive => proper side is positive, else negative **/
#ifndef CHECK_PROPER_SIDE
#define CHECK_PROPER_SIDE(x,val,side) ((side) > 0 ? (x) > (val) : (x) < (val))
#endif


	/***** Small value when we want to do a comparison to 'close to zero' *****/
#ifndef FUDGE
#define FUDGE .00001
#endif


	/******************* swap two values, using a temp variable *********/
#ifndef SWAP2
#define SWAP2(a,b,t) {t=a;a=b;b=t;}     
#endif

#define VEC3_TO_ARRAY(v,a)  a[0]=v[0], a[1]=v[1], a[2]=v[2]

	/**** Return the ASCII control code given the non-control ASCII character */
#define CTRL(c) ( (c>=('a'-1)) ? (c-'a'+1) : (c-'A'+1) )

	/*
	   typedef unsigned char Byte;

#ifndef _RGBC_
class RGBc 
{
public:
Byte r, g, b;

void set(Byte r,Byte g,Byte b) {this->r=r;this->g=g;this->b=b;}

RGBc( void ) {}
RGBc( Byte r, Byte g, Byte b ) { set( r, g, b ); }
};
#define _RGBC_
#endif
*/
}
#endif /* GLUI_INTERNAL_H */
