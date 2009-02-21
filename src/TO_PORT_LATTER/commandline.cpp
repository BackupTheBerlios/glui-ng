/****************************************************************************
  
  GLUI User Interface Toolkit
  ---------------------------

     glui_commandline.cpp - CommandLine control class


      --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher, 2005 William Baxter

  This software is provided 'as-is', without any express or implied 
  warranty. In no event will the authors be held liable for any damages 
  arising from the use of this software. 

  Permission is granted to anyone to use this software for any purpose, 
  including commercial applications, and to alter it and redistribute it 
  freely, subject to the following restrictions: 

  1. The origin of this software must not be misrepresented; you must not 
  claim that you wrote the original software. If you use this software 
  in a product, an acknowledgment in the product documentation would be 
  appreciated but is not required. 
  2. Altered source versions must be plainly marked as such, and must not be 
  misrepresented as being the original software. 
  3. This notice may not be removed or altered from any source distribution. 

  This program is -not- in the public domain.

*****************************************************************************/

#include "GL/glui/commandline.h"
#include "GL/glui/internal.h"
#include <GL/glui/debug.h>

using namespace GLUI;
/////////////////////////////////////////////////////////////////////
void CommandLine::common_init() {
    hist_list.resize(HIST_SIZE);
    curr_hist = 0;
    oldest_hist = 0;
    newest_hist = 0;
    commit_flag = false;
}
/****************************** CommandLine::CommandLine() **********/
CommandLine::CommandLine( Node *parent, const char *name, 
                                    std::string *data, int id, CB cb )
    : EditText (this, name, data, id, cb)
{
  common_init();

  parent->add_control( this );

}

/****************************** CommandLine::key_handler() **********/
int  CommandLine::AddEvent(::XEvent event)
{
	EventInterpreter::AddEvent(event);
	if (GetStatus() & EventInterpreter::keypressed )
	{
		debug::Instance ()->print (__FILE__, __LINE__, "key: %d mod:%d\n", 
				event.xkey.keycode, event.xkey.state);
		if (event.xkey.keycode == 13) //return
		{
			commit_flag = true;
			return 0;
		}
#warning "todo add keycode interpreter"
		if ( event.xkey.keycode == -1 )  // PREVIOUS HISTORY
		{
			scroll_history(-1);
			return 0;
		}
		else if ( event.xkey.keycode == -1 )  // NEXT HISTORY
		{
			scroll_history(+1);
			return 0;
		}
		return EditText::AddEvent( event );
	}
  return false;
}




/****************************** CommandLine::deactivate() **********/

void    CommandLine::deactivate( void )
{
  // if the commit_flag is set, add the current command to 
  // history and call deactivate as normal

  // Trick deactivate into calling callback if and only if commit_flag set.
  // A bit subtle, but deactivate checks that orig_text and text
  // are the same to decide whether or not to call the callback.
  // Force them to be different for commit, and the same for no commit.
  if (commit_flag) {
    add_to_history(text->c_str());
    orig_text.SetVal("");
    EditText::deactivate( );
    set_text( "" );
    commit_flag = false;
  }
  else {
    *(dynamic_cast<std::string*>(&orig_text)) = *text;
  }
}



/**************************** CommandLine::scroll_history() ********/

void    CommandLine::scroll_history( int direction )
{
  recall_history(curr_hist + direction);
}

/**************************** CommandLine::recall_history() ********/

void    CommandLine::recall_history( int hist_num )
{
  if (hist_num < oldest_hist OR
      hist_num > newest_hist OR
      hist_num == curr_hist)
    return;

  // Commit the current text first before we blow it away!
  if (curr_hist == newest_hist) {
    get_history_str(newest_hist) = *text;
  }

  curr_hist = hist_num;
  set_text(get_history_str(curr_hist));
  sel_end = sel_start = insertion_pt = (int)text->length();
  update_and_draw_text();
}

/**************************** CommandLine::add_to_history() ********/

void    CommandLine::add_to_history( const char *cmd )
{
  if (cmd[0]=='\0') return; // don't add if it's empty

  curr_hist = newest_hist;
  get_history_str(newest_hist) = *text;

  newest_hist = ++curr_hist;
  if ( newest_hist >= HIST_SIZE )
  {
    // bump oldest off the list
    hist_list.erase(hist_list.begin());
    hist_list.push_back("");

    oldest_hist++;
  }
}

/**************************** CommandLine::reset_history() ********/

void    CommandLine::reset_history( void )
{
  oldest_hist = newest_hist = curr_hist = 0;
}



/*************************************** CommandLine::dump() **************/

void   CommandLine::dump( FILE *out, const char *name )
{
  fprintf( out, 
	   "%s (commandline@%p):  ins_pt:%d  subs:%d/%d  sel:%d/%d   len:%d\n",
	   name, this, 
	   insertion_pt, substring_start, substring_end, sel_start, sel_end,
	   (int)text->length());
}


