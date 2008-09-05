#ifndef __GLUI_SEPARATOR_H
#define __GLUI_SEPARATOR_H

/************************************************************/
/*                                                          */
/*               Separator class                            */
/*                                                          */
/************************************************************/
#include <GL/glui/Control.h>
#define GLUI_SEPARATOR_HEIGHT           8
namespace GLUI
{
	class GLUIAPI Separator : public Control
	{
		public:
			void draw( void );

			Separator( Node *parent, const char* name );

		protected:
			void common_init() {
				w            = 100;
				h            = GLUI_SEPARATOR_HEIGHT;
				can_activate = false;
			}
	};
}
#endif
