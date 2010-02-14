#ifndef __GLUI_PANEL_H
#define __GLUI_PANEL_H
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

/************************************************************/
/*                                                          */
/*               Panel class (container)                    */
/*                                                          */
/************************************************************/

/**
 A GLUI_Panel contains a group of related controls.
*/
#include <GL/glui/container.h>
#include <GL/glui/statictext.h>


#define GLUI_PANEL_NAME_DROP            8
#define GLUI_PANEL_EMBOSS_TOP           4


namespace GLUI
{
	class GLUIAPI Panel : public Container
	{
		public: //types enums
			enum panelType {none, embossed, raised};
		public:

			/**
			  Create a new panel.  A panel groups together a set of related controls.

			  @param parent The outer panel our panel is inside; or the main GLUI object.
			  @param name The string name at the top of our panel.
			  @param type Optional style to display the panel with--EMBOSSED by default.
			  RAISED causes the panel to appear higher than the surroundings.
			  NONE causes the panel's outline to be invisible.
			  */
			Panel( Node *parent, const char *name,
					panelType type=embossed);
			~Panel();

			void draw( void );
			void set_type( int new_type );

			void update_size( void );
			int min_w();
			int min_h();
		protected:
			Panel( const char *name ) : Container(name) {}
			 void common_init( void );

        protected : //variables
            panelType val;

	};



}
#endif
