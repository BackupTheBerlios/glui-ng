#ifndef __GLUI_TEXT_H
#define __GLUI_TEXT_H
#include <stdarg.h>
#include <cstring>
#include <string>

/************************************************************/
/*                                                          */
/*               Text class                                 */
/*                                                          */
/************************************************************/
class GLUIAPI GLUI_Text : public std::string
{
	public:
		void         set_font( void *new_font );
		void         *get_font( void ) const;
        void         SetColor(const GLubyte *v) {Color[0]=v[0];Color[1]=v[1];Color[2]=v[2];}
		int          graph_Width();
		int          graph_Length();
		void         draw();

		int          char_width( char c );

		GLUI_Text (void* newfont, const std::string txt="") : std::string(txt) {
			memset(char_widths, -1, sizeof(char_widths)); /* JVK */
			font           = newfont;
            memset(Color, 0, sizeof(Color));
		}

    //operators
    GLUI_Text& operator=( GLUI_Text& copy);
    GLUI_Text& operator=(std::string& str);
    GLUI_Text& operator=(const std::string& str);

	protected:
		GLUI_Text() {}
        GLubyte Color[3];
		void           *font;       /**< Our glutbitmap font */
		int          char_widths[CHAR_WIDTH_HASH_SIZE][2]; /* Character width hash table */

		int flags;

};

#endif
