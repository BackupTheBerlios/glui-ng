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

#ifndef __GLUI_BUTTON_H
#define __GLUI_BUTTON_H
/************************************************************/
/*                                                          */
/*               Button class (container)                   */
/*                                                          */
/************************************************************/
/**
  An onscreen, clickable button--an outlined label that
  can be clicked.  When clicked, a button
  calls its CB callback with its ID.
*/
#include <GL/glui/container.h>
#include <GL/glui/statictext.h>
#include <GL/glui/callback.h>
#include <GL/glui/live.h>
#include <GL/glui/DefaultTheme.h>
namespace GLUI
{
	class Node;

	class GLUIAPI Button : public Container, public EventInterpreter
	{
                public: //types
                        class DefaultTheme : public _DefaultTheme
                        {
                                public : //methods
                                        DefaultTheme(Button& owner) : Owner(owner) {};
                                        ~DefaultTheme();
                                        virtual int draw();
                                        virtual int update();
                                protected: //variable
                                        Button& Owner;
                                        VertexObject* un_pressed;
                                        VertexObject* pressed;
                        };
		public:
			//LiveInt value;
		public:
			/**
			  Create a new button.

			  @param parent The panel our object is inside; or the main GLUI object.
			  @param name The text inside the button.
			  @param id Optional ID number, to pass to the optional callback function.
			  @param callback Optional callback function, taking either the int ID or control.
			  */
			Button( const char *name,
					int id=-1, CB cb=CB() );
			virtual int AddEvent(::XEvent *event);
                        bool GetValue();

		protected:
                        bool value;
			void common_init(void) ;

	};


/*        class GLUIAPI ToggleButton : public Button
        {
                public://types
                        class DefaultToggleButtonTheme : public DefaultThemeData
                {
                        public : //methods
                                DefaultToggleButtonTheme(ToggleButton& owner) : Owner(owner) {};
                                virtual int draw();
                                virtual int update();
                        protected: //variable
                                ToggleButton& Owner;

                };

                protected :
                        int state;
        };
*/

	class GLUIAPI TextButton : public Button
	{
                public : //types
                        class DefaultTheme : public _DefaultTheme
                        {
                                public : //methods
                                        DefaultTheme(TextButton& owner) : Owner(owner) {};
                                        virtual int draw();
                                        virtual int update();
                                protected: //variable
                                        TextButton& Owner;
                        };

		public :
			 void SetText(char* newtext);
			 TextButton (const char *name,
					int id=-1, CB cb=CB() ) ;

		protected:
			//		void draw_text( int sunken );
			StaticText text;
	};



}
#endif
