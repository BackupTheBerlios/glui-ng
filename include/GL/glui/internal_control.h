#ifndef __GLUI_INTERNAL_CONTROL_H
#define __GLUI_INTERNAL_CONTROL_H
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

/* This is the main GLUI external header */

/* Here's some utility routines */
#include <GL/glui/internal.h>

namespace GLUI
{
	/**
	  A GLUI_Control-drawing sentinal object.
	  On creation, saves the current draw buffer and window.
	  On destruction, restores draw buffer and window.
	  This is way nicer than calling save/restore manually.
	  */
	class Control;

	class DrawingSentinal
	{
		int orig_buf, orig_win;
		Control *c;
		public:
		DrawingSentinal(Control *c_); ///< The constructor sets up the drawing system
		~DrawingSentinal(); ///< The destructor cleans up drawing back how it was 

		 void avoid_warning(void) {} // Do-nothing routine to avoid compiler warning about unused variable
	};



}
#endif
