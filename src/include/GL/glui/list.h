#ifndef __GLUI_LIST_H
#define __GLUI_LIST_H

#include <GL/glui/glui_node.h>
#include <GL/glui/glui_container.h>

/************************************************************/
/*                                                          */
/*                   List class - JVK                       */
/*                                                          */
/************************************************************/

class GLUIAPI GLUI_List_Item : public GLUI_Node
{
public:
    std::string text;
    int         id;
};

/************************************************************/
/*                                                          */
/*               List class - JVK                           */
/*                                                          */
/************************************************************/

class GLUIAPI GLUI_List : public GLUI_Container
{
public:
    /* GLUI List - JVK */
    GLUI_List( GLUI_Node *parent, const char* name, bool scroll = false,
               int id=-1, GLUI_CB callback=GLUI_CB() );
               /*, GLUI_Control *object = NULL
               ,GLUI_InterObject_CB obj_cb = NULL);*/

    GLUI_List( GLUI_Node *parent,
               const char* name,
               std::string& live_var, bool scroll = false,
               int id=-1,
               GLUI_CB callback=GLUI_CB()
               /*,GLUI_Control *object = NULL */
               /*,GLUI_InterObject_CB obj_cb = NULL*/);


    std::string         orig_text;
    int                 debug;
    int                 draw_text_only;
    int                 start_line;
    int                 num_lines;
    int                 curr_line;
    int                 visible_lines;
    GLUI_Scrollbar      *scrollbar;
    GLUI_List_Item      items_list;
    GLUI_Control        *associated_object;
    GLUI_CB             obj_cb;
    int                 cb_click_type;
    int                 last_line;
    int                 last_click_time;

    int  mouse_down_handler( int local_x, int local_y );
    int  mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );
    int  key_handler( unsigned char key,int modifiers );
    int  special_handler( int key,int modifiers );

    void activate( int how );
    void deactivate( void );

    void draw( void );

    int  mouse_over( int state, int x, int y );

    int get_box_width();
    int  find_word_break( int start, int direction );
    int  substring_width( const char *t, int start, int end );
    int  find_line( int x, int y );
    void update_and_draw_text( void );
    void draw_text( const char *t, int selected, int x, int y );
    void update_size( void );


    int  add_item( int id, const char *text );
    int  delete_item( const char *text );
    int  delete_item( int id );
    int  delete_all();

    GLUI_List_Item *get_item_ptr( const char *text );
    GLUI_List_Item *get_item_ptr( int id );

    void dump( FILE *out, const char *text );
    void set_start_line(int l) { start_line = l; }
    static void scrollbar_callback(GLUI_Control*);
    int get_current_item() { return curr_line; }
    void set_click_type(int d) {
        cb_click_type = d; }
    void set_object_callback(GLUI_CB cb=GLUI_CB(), GLUI_Control*obj=NULL)
    { obj_cb=cb; associated_object=obj; }

protected:
    void common_init()
    {
        h                     = GLUI_LIST_HEIGHT;
        w                     = GLUI_LIST_WIDTH;
        num_lines             = 0;
        visible_lines         = 0;
        start_line            = 0;
        curr_line             = 0;
        active_type           = GLUI_CONTROL_ACTIVE_PERMANENT;
        can_activate          = true;
        spacebar_mouse_click  = false;
        scrollbar             = NULL;
        debug                 = false;
        draw_text_only        = false;
        cb_click_type         = GLUI_SINGLE_CLICK;
        last_line             = -1;
        last_click_time       = 0;
        associated_object     = NULL;
    };
    void common_construct(
        GLUI_Node *parent,
        std::string* live_var, bool scroll,
        int id,
        GLUI_CB callback
        /*,GLUI_Control *object*/
        /*,GLUI_InterObject_CB obj_cb*/);
    GLUI_Text name;
};



#endif //__GLUI_LIST_H
