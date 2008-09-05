#ifndef __GLUI_PANEL_H
#define __GLUI_PANEL_H

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
			enum panelType
			{
				NONE,
				EMBOSSED,
				RAISED,
			};
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
					panelType type=EMBOSSED);
			~Panel();

			void draw( void );
			void set_type( int new_type );

			void update_size( void );
			int min_w();
			int min_h();
		protected:
			Panel( const char *name ) : Container(name) {}
			void common_init( void ) {
				w            = 300;
				h            = GLUI_DEFAULT_CONTROL_HEIGHT + 7;
				int_val      = EMBOSSED;
				alignment    = GLUI_ALIGN_CENTER;
				can_activate = false;
			};

	};

}
#endif
