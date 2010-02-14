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




}

#endif
