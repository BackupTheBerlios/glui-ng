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

#ifndef __GLUI_CALLBACK_H
#define __GLUI_CALLBACK_H

/********** List of GLUT callbacks ********/
namespace GLUI
{
	class Control;

	enum Glut_CB_Types
	{
		GLUT_RESHAPE,
		GLUT_KEYBOARD,
		GLUT_DISPLAY,
		GLUT_MOUSE,
		GLUT_MOTION,
		GLUT_SPECIAL,
		GLUT_PASSIVE_MOTION,
		GLUT_ENTRY,
		GLUT_VISIBILITY
	};
	/*** Definition of callbacks ***/
	typedef void (*Update_CB) (int id);
	typedef void (*Control_CB)(Control *);
	typedef void (*Int1_CB)        (int);
	typedef void (*Int2_CB)        (int, int);
	typedef void (*Int3_CB)        (int, int, int);
	typedef void (*Int4_CB)        (int, int, int, int);

	/************************************************************/
	/**
	  Callback Adapter Class
	  Allows us to support different types of callbacks;
	  like a Update_CB function pointer--which takes an int;
	  and a Control_CB function pointer--which takes a GUI_Control object.
	  */
	class GLUIAPI CB
	{
		public:
			CB() : idCB(0),objCB(0) {}
			CB(Update_CB cb) : idCB(cb),objCB(0) {}
			CB(Control_CB cb) : idCB(0),objCB(cb) {}
			// (Compiler generated copy constructor)

			/** This control just activated.  Fire our callback.*/
			void operator()(Control *ctrl) const;
			bool operator!() const { return !idCB && !objCB; }
			operator bool() const { return !(!(*this)); }
			void         execute_callback( void );
		private:
			Update_CB idCB;
			Control_CB objCB;
	};
}
#endif
