#ifndef __GLUI_STATICTEXT_H
#define __GLUI_STATICTEXT_H
/************************************************************/
/*                                                          */
/*               StaticText class                           */
/*                                                          */
/************************************************************/
#include <GL/glui/text.h>
#include <GL/glui/control.h>
namespace GLUI
{
	class GLUIAPI StaticText : public Control, public Text
	{
		public:
			void set_text( const char *text );
			void draw( void );
			void update_size( void );

			StaticText(Node *parent, const char *name);

		protected:
			void common_init() {
			}

			void erase_text( void );
	};
}
#endif
