#ifndef __GLUI_PANEL_H
#define __GLUI_PANEL_H

/************************************************************/
/*                                                          */
/*               Panel class (container)                    */
/*                                                          */
/************************************************************/

/**
 A GLUI_Panel contains a group of related controls.
*/
class GLUIAPI GLUI_Panel : public GLUI_Container
{
public:

/**
 Create a new panel.  A panel groups together a set of related controls.

  @param parent The outer panel our panel is inside; or the main GLUI object.
  @param name The string name at the top of our panel.
  @param type Optional style to display the panel with--GLUI_PANEL_EMBOSSED by default.
      GLUI_PANEL_RAISED causes the panel to appear higher than the surroundings.
      GLUI_PANEL_NONE causes the panel's outline to be invisible.
*/
    GLUI_Panel( GLUI_Node *parent, const char *name,
                int type=GLUI_PANEL_EMBOSSED );
	~GLUI_Panel();

    void draw( void );
    void set_name( char *text );
    void set_type( int new_type );

    void update_size( void );
    int min_w();
    int min_h();
protected:
    GLUI_Panel( const char *name ) : GLUI_Container(name) {}
    void common_init( void ) {
        w            = 300;
        h            = GLUI_DEFAULT_CONTROL_HEIGHT + 7;
        int_val      = GLUI_PANEL_EMBOSSED;
        alignment    = GLUI_ALIGN_CENTER;
        is_container = true;
        can_activate = false;
    };
	GLUI_StaticText* title;

};

#endif
