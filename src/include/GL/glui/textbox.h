#ifndef __GLUI_TEXTBOX_H
#define __GLUI_TEXTBOX_H

#include <GL/glui/container.h>
#include <GL/glui/scrollbar.h>

/************************************************************/
/*                                                          */
/*               TextBox class - JVK                        */
/*                                                          */
/************************************************************/

namespace GLUI
{
	class GLUIAPI TextBox : public Container
	{

#define GLUI_TEXTBOX_HEIGHT          130
#define GLUI_TEXTBOX_WIDTH           130
#define GLUI_TAB_WIDTH                50 /* In pixels */

		public:
			/* GLUI Textbox - JVK */
			TextBox( Node *parent, const char* name, std::string &live_var,
					bool scroll = false, int id=-1, CB callback=CB() );
			TextBox( Node *parent,
					const char* name,
					bool scroll = false, int id=-1,
					CB callback=CB() );

			std::string         orig_text;
			int                 insertion_pt;
			int                 substring_start; /*substring that gets displayed in box*/
			int                 substring_end;
			int                 sel_start, sel_end;  /* current selection */
			int                 last_insertion_pt;
			int                 debug;
			int                 draw_text_only;
			int                 tab_width;
			int                 start_line;
			int                 num_lines;
			int                 curr_line;
			int                 visible_lines;
			int                 insert_x;        /* Similar to "insertion_pt", these variables keep */
			int                 insert_y;        /* track of where the ptr is, but in pixels */
			int                 keygoal_x;       /* where up down keys would like to put insertion pt*/
			Scrollbar     *scrollbar;

			int  mouse_down_handler( int local_x, int local_y );
			int  mouse_up_handler( int local_x, int local_y, bool inside );
			int  mouse_held_down_handler( int local_x, int local_y, bool inside );
			int  key_handler( unsigned char key,int modifiers );
			int  special_handler( int key,int modifiers );

			void activate( int how );
			void deactivate( void );

			void enable( void );
			void disable( void );

			void draw( void );

			int  mouse_over( int state, int x, int y );

			int get_box_width();
			int  find_word_break( int start, int direction );
			int  substring_width( int start, int end, int initial_width=0 );
			void clear_substring( int start, int end );
			int  find_insertion_pt( int x, int y );
			int  update_substring_bounds( void );
			void update_and_draw_text( void );
			void draw_text( int x, int y );
			void draw_insertion_pt( void );
			void update_x_offsets( void );
			void update_size( void );

			void set_text( const char *text );
			const char *get_text( void )         { return text.c_str(); }

			void dump( FILE *out, char *text );
			void set_tab_w(int w) { tab_width = w; }
			void set_start_line(int l) { start_line = l; }
			static void scrollbar_callback(Control*);

			bool wants_tabs( void ) const { return true; }

		protected:

			void common_init()
			{
				CurrentSize.size.h                     = GLUI_TEXTBOX_HEIGHT;
				CurrentSize.size.w                     = GLUI_TEXTBOX_WIDTH;
				tab_width             = GLUI_TAB_WIDTH;
				num_lines             = 0;
				visible_lines         = 0;
				start_line            = 0;
				curr_line             = 0;
				insert_y              = -1;
				insert_x              = -1;
				insertion_pt          = -1;
				last_insertion_pt     = -1;
				substring_start       = 0;
				substring_end         = 2;
				sel_start             = 0;
				sel_end               = 0;
				active_type           = GLUI_CONTROL_ACTIVE_PERMANENT;
				can_activate          = true;
				spacebar_mouse_click  = false;
				scrollbar             = NULL;
				debug                 = false;
				draw_text_only        = false;
			}
			void common_construct(
					Node *parent, std::string *live_var,
					bool scroll, int id, CB callback);
			Text text;
			Text name;
	};

}


#endif // __GLUI_TEXTBOX_H
