#ifndef __GLUI_TEXT_H
#define __GLUI_TEXT_H
#include <stdarg.h>
#include <cstring>
#include <string>
#include <GL/glui/commondefs.h>
#include <GL/gl.h>

/************************************************************/
/*                                                          */
/*               Text class                                 */
/*                                                          */
/************************************************************/
namespace GLUI
{
    class GLUIAPI Text : public std::string
    {
        public:
            void         set_font( void *new_font );
            void         *get_font( void ) const;
            void         SetColor(const GLubyte *v) {Color[0]=v[0];Color[1]=v[1];Color[2]=v[2];}
            int          graph_Width();
            int          graph_Length();
            void         draw();

            int          char_width( char c );

            Text (const std::string txt="");

            //operators
            Text& operator=( Text& copy);
            Text& operator=(std::string& str);
            Text& operator=(const std::string& str);

        protected:
            GLubyte Color[3];
            void           *font;       /**< Our glutbitmap font */
            int          char_widths[CHAR_WIDTH_HASH_SIZE][2]; /* Character width hash table */

            int flags;

    };


}
#endif
