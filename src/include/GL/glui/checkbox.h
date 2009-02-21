#ifndef __GLUI_CHECKBOX_H
#define __GLUI_CHECKBOX_H
/************************************************************/
/*                                                          */
/*               Checkbox class (container)                 */
/*                                                          */
/************************************************************/

/**
 A checkbox, which can be checked on or off.  Can be linked
 to an int value, which gets 1 for on and 0 for off.
*/
#include <GL/glui/container.h>
#include <GL/glui/to_clean.h>
#include <GL/glui/live.h>

namespace GLUI
{
	class StaticText;

	class GLUIAPI Checkbox : public Container, public EventInterpreter
	{
		public: //enums
		public: //variables
			LiveInt value;
		public: //methods
			int AddEvent (::XEvent *event);

			void update_size( void );

			void draw( void );

			void draw_active_area( void );
			void draw_empty_box( void );

			/**
			  Create a new checkbox object.

			  @param parent The panel our object is inside; or the main GLUI object.
			  @param name Label next to our checkbox.
			  @param value_ptr Optional integer value to attach to this checkbox.  When the
			  checkbox is checked or unchecked, *value_ptr will also be changed. ("Live Vars").
			  @param id Optional ID number, to pass to the optional callback function.
			  @param callback Optional callback function, taking either the int ID or control.
			  */
			Checkbox(Node *parent, const char *name, int *value_ptr=NULL,
					int id=-1, CB callback=CB());

			~Checkbox();

		protected:
			 void common_init(void) ;
			StaticText* text;
			//	Button button;
	};




}
#endif
