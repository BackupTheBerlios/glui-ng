#ifndef __GLUI_SEPARATOR_H
#define __GLUI_SEPARATOR_H

/************************************************************/
/*                                                          */
/*               Separator class                            */
/*                                                          */
/************************************************************/
#include <GL/glui/Control.h>
namespace GLUI
{
	class GLUIAPI Separator : public Control
	{
        public: //enums/constants
            static const int default_height = 8;
		public:
			void draw( void );

			Separator( Node *parent, const char* name );

		protected:
			void common_init();
	};

    ///////////////////INLINES///////
    inline void Separator::common_init()
    {
        CurrentSize.size.w            = 100;
        CurrentSize.size.h            = default_height;
    }
}
#endif
