#ifndef __GLUI_TEXT_H
#define __GLUI_TEXT_H
#include <stdarg.h>

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
		int          graph_Width();
		int          graph_Length();
		void         draw();

		int          char_width( char c );

		GLUI_Text (void* newfont, const string txt="") : std::string(txt) {
			memset(char_widths, -1, sizeof(char_widths)); /* JVK */
			font           = newfont;

		}
		int Length( );
		int Width( );

    //operators
    GLUI_Text& operator=( GLUI_Text& copy);
    GLUI_Text& operator=(std::string& str);
    GLUI_Text& operator=(const std::string& str);

	private:
		GLUI_Text() {}
		void           *font;       /**< Our glutbitmap font */
		int          char_widths[CHAR_WIDTH_HASH_SIZE][2]; /* Character width hash table */

		int flags;

};

#endif
