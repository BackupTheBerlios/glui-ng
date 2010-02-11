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
			Button( Node *parent, const char *name,
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
			 TextButton (Node *parent, const char *name,
					int id=-1, CB cb=CB() ) ;

		protected:
			//		void draw_text( int sunken );
			StaticText text;
	};



}
#endif
