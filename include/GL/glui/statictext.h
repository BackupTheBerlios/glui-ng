#ifndef __GLUI_STATICTEXT_H
#define __GLUI_STATICTEXT_H
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
                                        DefaultTheme(StaticText& owner) : Owner(owner) {};
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

		protected:
                        virtual themeData* GetDefaultTheme();

	};
}
#endif
