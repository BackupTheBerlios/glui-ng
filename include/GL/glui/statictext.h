#ifndef __GLUI_STATICTEXT_H
#define __GLUI_STATICTEXT_H
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
/*               StaticText class                           */
/*                                                          */
/************************************************************/
#include <GL/glui/control.h>
#include <GL/glui/text.h>
#include <GL/glui/DefaultTheme.h>
namespace GLUI
{
	class GLUIAPI StaticText : public Control
	{
                public: //types
                        class DefaultTheme : public Text
                        {
                                public : //methods
                                        DefaultTheme(StaticText& owner);
                                        ~DefaultTheme();
                                        virtual int draw();
                                        virtual int update();
                                protected: //variable
                                        StaticText& Owner;
                        };
		public:
			void set_text( const char *text );
			void update_size( void );

			StaticText(Node *parent, const char *name);

	};
}
#endif
