#ifndef __GLUI_LISTBOX_H
#define __GLUI_LISTBOX_H

#include <GL/glui/glui_node.h>
#include <GL/glui/glui_control.h>

/************************************************************/
/*                                                          */
/*                   Listbox class                          */
/*                                                          */
/************************************************************/

class GLUIAPI GLUI_Listbox_Item : public GLUI_Node
{
public:
    std::string text;
    int         id;
};

class GLUIAPI GLUI_Listbox : public GLUI_Control
{
public:
    std::string       curr_text;
    GLUI_Listbox_Item items_list;
    int               depressed;

    int  orig_value;
    bool currently_inside;
    int  text_x_offset, title_x_offset;
    int  glut_menu_id;

    int  mouse_down_handler( int local_x, int local_y );
    int  mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );
    int  key_handler( unsigned char key,int modifiers );
    int  special_handler( int key,int modifiers );

    void update_size( void );
    void draw( void );
    int  mouse_over( int state, int x, int y );

    void set_int_val( int new_val );
    void dump( FILE *output );

    int  add_item( int id, const char *text );
    int  delete_item( const char *text );
    int  delete_item( int id );
    int  sort_items( void );

    int  do_selection( int item );

    GLUI_Listbox_Item *get_item_ptr( const char *text );
    GLUI_Listbox_Item *get_item_ptr( int id );


    GLUI_Listbox( GLUI_Node *parent,
                  const char *name, int *live_var=NULL,
                  int id=-1, GLUI_CB callback=GLUI_CB() );

protected:
    /** Change w and return true if we need to be widened to fit the current item. */
    bool recalculate_item_width( void );
    void common_init() {
        w              = GLUI_EDITTEXT_WIDTH;
        h              = GLUI_EDITTEXT_HEIGHT;
        orig_value     = -1;
        title_x_offset = 0;
        text_x_offset  = 55;
        can_activate   = true;
        curr_text      = "";
        live_type      = GLUI_LIVE_INT;  /* This has an integer live var */
        depressed      = false;
        glut_menu_id   = -1;
    }

    ~GLUI_Listbox();
};




#endif //__GLUI_LISTBOX_H
