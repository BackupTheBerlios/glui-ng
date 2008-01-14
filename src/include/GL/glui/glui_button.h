#ifndef __GLUI_BUTTON_H
#define __GLUI_BUTTON_H
/************************************************************/
/*                                                          */
/*               Button class (container)                   */
/*                                                          */
/************************************************************/
/**
  An onscreen, clickable button--an outlined label that
  can be clicked.  When clicked, a button
  calls its GLUI_CB callback with its ID.
*/
#include <GL/glui/glui_container.h>
class GLUIAPI GLUI_Button : public GLUI_Container
{
public:
    bool currently_inside;

    int  mouse_down_handler( int local_x, int local_y );
    int  mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );
    int  key_handler( unsigned char key,int modifiers );

    void draw( void );

/**
 Create a new button.

  @param parent The panel our object is inside; or the main GLUI object.
  @param name The text inside the button.
  @param id Optional ID number, to pass to the optional callback function.
  @param callback Optional callback function, taking either the int ID or control.
*/
    GLUI_Button( GLUI_Node *parent, const char *name,
                 int id=-1, GLUI_CB cb=GLUI_CB() );

protected:
	void draw_pressed( void );
    void common_init(void) {
        h            = GLUI_BUTTON_SIZE;
        w            = 100;
        alignment    = GLUI_ALIGN_CENTER;
        can_activate = true;
    }
};

#include <GL/glui/glui_statictext.h>

class GLUIAPI GLUI_TextButton : public GLUI_Button
{
	public :
		void SetText(char* newtext)
		      {text.set_text(newtext);}
		GLUI_TextButton (GLUI_Node *parent, const char *name,
                 int id=-1, GLUI_CB cb=GLUI_CB() ) :
			GLUI_Button(parent, name, id, cb),
			text(this, "text")
	           {}

	private:
//		void draw_text( int sunken );
		GLUI_StaticText text;


};

#endif
