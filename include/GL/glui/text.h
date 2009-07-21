#ifndef __GLUI_TEXT_H
#define __GLUI_TEXT_H
#include <stdarg.h>
#include <cstring>
#include <string>
#include <GL/glui/commondefs.h>
#include <GL/glui/DefaultTheme.h>
#include <GL/gl.h>

/************************************************************/
/*                                                          */
/*               Text class                                 */
/*                                                          */
/************************************************************/
namespace GLUI
{
        /** Size of the character width hash table for faster lookups.
          Make sure to keep this a power of two to avoid the slow divide.
          This is also a speed/memory tradeoff; 128 is enough for low ASCII.
          */
#define CHAR_WIDTH_HASH_SIZE 128

        class GLUIAPI Text : public std::string, public _DefaultTheme
        {


                public:
                        void         set_font( void *new_font );
                        void         *get_font( void ) const;
                        void         SetColor(const GLubyte *v) {Color[0]=v[0];Color[1]=v[1];Color[2]=v[2];}
                        int          graph_Width();
                        int          graph_Length();
                        int          draw();
                        int          update();

                        int          char_width( char c );

                        Text (const std::string txt="");

                        //operators
                        Text& operator=( Text& copy);
                        Text& operator=(std::string& str);
                        Text& operator=(const std::string& str);

                protected:
                        void           *font;       //< Our glutbitmap font
                        GLubyte Color[3];
                        int          char_widths[CHAR_WIDTH_HASH_SIZE][2]; // Character width hash table
                        int tests;

                        int flags;

        };


}
#endif
