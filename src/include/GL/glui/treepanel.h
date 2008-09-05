#ifndef __GLUI_TREEPANEL_H
#define __GLUI_TREEPANEL_H

#include <GL/glui/glui_glui.h>
/************************************************************/
/*                                                          */
/*               Tree    Panel class (container)            */
/*                         JVK                              */
/************************************************************/

/**
  One collapsible entry in a GLUI_TreePanel.
*/
class GLUIAPI GLUI_Tree : public GLUI_Panel
{
public:
    GLUI_Tree(GLUI_Node *parent, const char *name,
              int open=false, int inset=0);

private:
    int level;   // how deep is this node
    float red;   //Color coding of column line
    float green;
    float blue;
    float lred;   //Color coding of level name
    float lgreen;
    float lblue;
    int id;
    GLUI_Splitter *column;
    int is_current;          // Whether this tree is the
    // current root in a treePanel
    int child_number;
    int format;

public:
    bool        currently_inside, initially_inside;
    GLUI_Button  button;
    GLUI_Text  level_name; // level name, eg: 1.1.2, III, or 3
    GLUI_TreePanel *panel;

    void draw( void );
    void draw_pressed( void );
    int mouse_down_handler( int local_x, int local_y );
    int mouse_up_handler( int local_x, int local_y, bool inside );
    int  mouse_held_down_handler( int local_x, int local_y, bool inside );
    void  open( void );
    void  close( void );

    /*   void set_name( char *text )   { panel.set_name( text ); }; */
    void update_size( void );
    void set_id(int i) { id = i; }
    void set_level(int l) { level = l; }
    void set_format(int f) { format = f; }
    void set_current(int c) { is_current = c; }
    int get_id() { return id; }
    int get_level() { return level; }
    int get_child_number() { return child_number; }
    void enable_bar() { if (column) { column->int_val = 1;  set_color(red, green, blue); } }
    void disable_bar() { if (column) { column->int_val = 0;  } }
    void set_child_number(int c) { child_number = c; }
    void set_level_color(float r, float g, float b) {
        lred = r;
        lgreen = g;
        lblue  = b;
    }
    void set_color(float r, float g, float b) {
        red = r;
        green = g;
        blue  = b;
    }
protected:
    GLUI_Splitter splitter;
    void common_init()
    {
        currently_inside = false;
        initially_inside = false;
        can_activate     = true;
        h                = GLUI_DEFAULT_CONTROL_HEIGHT + 7;
        w                = GLUI_DEFAULT_CONTROL_WIDTH;
        y_off_top        = 21;
        collapsible      = true;
        red              = .5;
        green            = .5;
        blue             = .5;
        lred             = 0;
        lgreen           = 0;
        lblue            = 0;
        column           = NULL;
        is_current       = 0;
        child_number     = 0;
        format           = 0;
        panel            = NULL;
        level            = 0;
#warning fixthis
		//level_name = GLUI_Text(this->glui->font, "");
    };
};


/************************************************************/
/*                                                          */
/*               TreePanel class (container) JVK            */
/*                                                          */
/************************************************************/

/**
  Manages, maintains, and formats a tree of GLUI_Tree objects.
  These are shown in a heirarchical, collapsible display.

  FIXME: There's an infinite loop in the traversal code (OSL 2006/06)
*/
class GLUIAPI GLUI_TreePanel : public GLUI_Panel
{
public:
    GLUI_TreePanel(GLUI_Node *parent, const char *name,
                   bool open=false, int inset=0);

    int max_levels;
    int next_id;
    int format;
    float red;
    float green;
    float blue;
    float lred;
    float lgreen;
    float lblue;
    int root_children;
    /* These variables allow the tree panel to traverse the tree
       using only two function calls. (Well, four, if you count
       going in reverse */

    GLUI_Tree    *curr_branch; /* Current Branch */
    GLUI_Panel *curr_root;   /* Current Root */

public:
    void            set_color(float r, float g, float b);
    void            set_level_color(float r, float g, float b);
    void            set_format(int f) { format = f; }

    /* Adds branch to curr_root */
    GLUI_Tree *     ab(const char *name, GLUI_Tree *root = NULL);
    /* Goes up one level, resets curr_root and curr_branch to parents*/
    void            fb(GLUI_Tree *branch= NULL);
    /* Deletes the curr_branch, goes up one level using fb */
    void            db(GLUI_Tree *branch = NULL);
    /* Finds the very last branch of curr_root, resets vars */
    void            descendBranch(GLUI_Panel *root = NULL);
    /* Resets curr_root and curr branch to TreePanel and lastChild */
    void            resetToRoot(GLUI_Panel *new_root = NULL);
    void            next( void );
    void            expand_all( void );
    void            collapse_all( void );
    void            update_all( void );
    void            initNode(GLUI_Tree *temp);
    void            formatNode(GLUI_Tree *temp);

protected:
    int uniqueID( void ) { next_id++; return next_id - 1; }
    void common_init()
    {
        next_id = 0;
        curr_root = this;
        curr_branch = NULL;
        red = .5;
        green = .5;
        blue = .5;
        root_children = 0;
    }
};


#endif
