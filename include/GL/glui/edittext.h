#ifndef __GLUI_EDITTEXT_H
#define __GLUI_EDITTEXT_H
/*
   GLUI-ng, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

   This library is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the 
   Free Software Foundation; either version 2.1 of the License, 
   or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License along with this library;
   if not, write to the 
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

   based on the work of Paul Rademacher (orignal software http://glui.sourceforge.net/)
*/

/************************************************************/
/*                                                          */
/*               EditText class                             */
/*                                                          */
/************************************************************/
#include <GL/glui/container.h>
#include <GL/glui/statictext.h>
#include <GL/glui/TextBox.h>
#include <GL/glui/live.h>

namespace GLUI
{


#define GLUI_EDITTEXT_BOXINNERMARGINX   3
#define GLUI_EDITTEXT_HEIGHT           20
#define GLUI_EDITTEXT_WIDTH           130
#define GLUI_EDITTEXT_MIN_INT_WIDTH    35
#define GLUI_EDITTEXT_MIN_TEXT_WIDTH   50
    /*** Codes for different type of edittext boxes and spinners ***/
#define GLUI_EDITTEXT_TEXT             1
#define GLUI_EDITTEXT_INT              2
#define GLUI_EDITTEXT_FLOAT            3
    // This is only for deprecated interface
#define GLUI_EDITTEXT_STRING           4


    class GLUIAPI EditText : public Container
    {
        public:
            int                 has_limits;
            int                 data_type;
            LiveText            orig_text;
            int                 insertion_pt;
            int                 title_x_offset;
            int                 text_x_offset;
            int                 substring_start; /*substring that gets displayed in box*/
            int                 substring_end;
            int                 sel_start, sel_end;  /* current selection */
            int                 num_periods;
            int                 last_insertion_pt;
            int                 debug;
            int                 draw_text_only;


            int  mouse_down_handler( int local_x, int local_y );
            int  mouse_up_handler( int local_x, int local_y, bool inside );
            int  mouse_held_down_handler( int local_x, int local_y, bool inside );
            int  key_handler( unsigned char key,int modifiers );
            int  special_handler( int key, int modifiers );

            void activate( int how );
            void deactivate( void );

            void draw( void );

            int  mouse_over( int state, int x, int y );

            int  find_word_break( int start, int direction );
            int  substring_width( int start, int end );
            void clear_substring( int start, int end );
            int  find_insertion_pt( int x, int y );
            int  update_substring_bounds( void );
            void update_and_draw_text( void );
            void draw_text( int x, int y );
            void draw_insertion_pt( void );
            void set_numeric_text( void );
            void update_x_offsets( void );
            void update_size( void );

            void set_text( const char *text );
            void set_text( const std::string &s) { set_text(s.c_str()); }
            const char *get_text()               { return text->c_str(); }

            void dump( FILE *out, const char *text );

            // Constructor, char* live variable
            EditText( Node *parent, const char *name,
                    char *live_var,
                    int id=-1, CB callback=CB() );
            // Constructor, std::string live variable
            EditText( Node *parent, const char *name,
                    std::string *live_var,
                    int id=-1, CB callback=CB() );

        protected:
             void common_init( void );
            void common_construct( Node *parent, const char *name,
                    int data_type, int live_type, void *live_var,
                    int id, CB callback );
            StaticText label;
            TextBox    Caption;
    };

    class GLUIAPI EditFloatText : public EditText
    {
        public : //variables
        public : //methods
            // Constructor, float live variable
            EditFloatText( Node *parent, const char *name,
                    float *live_var,
                    int id=-1, CB callback=CB() );

            void set_float_limits( float low,float high,int limit_type=GLUI_LIMIT_CLAMP);
            void set_float_val( float new_val );
        protected : //variables
            LiveFloat value;
            float               float_low, float_high;

    };

    class GLUIAPI EditIntText : public EditText
    {
        public : //variables
        public : //methods
            // Constructor, int live variable
            EditIntText( Node *parent, const char *name,
                    int *live_var,
                    int id=-1, CB callback=CB() );
            void set_int_val( int new_val );
            void set_int_limits( int low, int high, int limit_type=GLUI_LIMIT_CLAMP );
        protected : //variables
            LiveInt value;
            int                 int_low, int_high;
    };



}

#endif
