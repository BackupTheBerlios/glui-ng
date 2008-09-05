#ifndef __GLUI_COMMANDLINE_H
#define __GLUI_COMMANDLINE_H
/************************************************************/
/*                                                          */
/*               CommandLine class                          */
/*                                                          */
/************************************************************/
#include <GL/glui/edittext.h>
#include <vector>
#include <string>

namespace GLUI
{
	class Node;

	class GLUIAPI CommandLine : public EditText, public EventInterpreter
	{
		public:

			enum { HIST_SIZE = 100 };

#ifdef _MSC_VER
			// Explicit template instantiation needed for dll
			template class GLUIAPI std::allocator<std::string>;
			template class GLUIAPI std::vector<std::string, std::allocator<std::string> >;
#endif

			std::vector<std::string> hist_list;
			int  curr_hist;
			int  oldest_hist;
			int  newest_hist;
			bool commit_flag;

		public:
			virtual int AddEvent(::XEvent event);
			void deactivate( void );

			virtual const char *get_history( int command_number ) const
			{ return hist_list[command_number - oldest_hist].c_str(); }
			virtual std::string& get_history_str( int command_number )
			{ return hist_list[command_number - oldest_hist]; }
			virtual const std::string& get_history_str( int command_number ) const
			{ return hist_list[command_number - oldest_hist]; }
			virtual void recall_history( int history_number );
			virtual void scroll_history( int direction );
			virtual void add_to_history( const char *text );
			virtual void reset_history( void );

			void dump( FILE *out, const char *text );


			CommandLine( Node *parent, const char *name, std::string *live_var=NULL,
					int id=-1, CB callback=CB() );
		protected:
			void common_init();
	};


	inline 	void CommandLine::common_init() {
				hist_list.resize(HIST_SIZE);
				curr_hist = 0;
				oldest_hist = 0;
				newest_hist = 0;
				commit_flag = false;
			}

}

#endif
