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
namespace GLUI
{
	class Node;

	class GLUIAPI Button : public Container, public EventInterpreter
	{
		public:
			LiveInt value;
		public:
			void draw( void );
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

		protected:
			void draw_pressed( void );
			void common_init(void) ;
	};


	/*class GLUIAPI ToggleButton : public Button
	  {
	  protected :
	  int state;
	  };*/


	class GLUIAPI TextButton : public Button
	{
		public :
			void SetText(char* newtext);
			TextButton (Node *parent, const char *name,
					int id=-1, CB cb=CB() ) ;

		private:
			//		void draw_text( int sunken );
			StaticText text;


	};


	inline void Button::common_init(void) {
		CurrentSize.size.h            = GLUI_BUTTON_SIZE;
		CurrentSize.size.w            = 100;
		alignment    = Control::CENTER;
	}


	inline TextButton::TextButton (Node *parent, const char *name,
			int id, CB cb ) :
		Button(parent, name, id, cb),
		text(this, "text")
	{
		this->resizeable == AdaptThisToFitChilds;
	};

	inline void TextButton::SetText(char* newtext)
	{
		text.set_text(newtext);
	};
}
#endif
