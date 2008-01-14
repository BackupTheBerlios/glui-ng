#ifndef __GLUI_NODE_H
#define __GLUI_NODE_H

/************************************************************/
/*                                                          */
/*          Base class, for hierarchical relationships      */
/*                                                          */
/************************************************************/

class GLUI_Control;

/**
 GLUI_Node is a node in a sort of tree of GLUI controls.
 Each GLUI_Node has a list of siblings (in a circular list)
 and a linked list of children.

 Everything onscreen is a GLUI_Node--windows, buttons, etc.
 The nodes are traversed for event processing, sizing, redraws, etc.
*/
class GLUIAPI GLUI_Node
{
    friend class GLUI_Tree;     /* JVK */
    friend class GLUI_Rollout;
    friend class GLUI_Main;

public:
    GLUI_Node(const char* name);

    virtual ~GLUI_Node() {}

    GLUI_Node *first_sibling();
    GLUI_Node *last_sibling();
    GLUI_Node *prev();
    GLUI_Node *next();

    GLUI_Node *first_child()   { return child_head; }
    GLUI_Node *last_child()    { return child_tail; }
    GLUI_Node *parent()        { return parent_node; }

    /** Link in a new child control */
    virtual int  add_control( GLUI_Control *control );

    void link_this_to_parent_last (GLUI_Node *parent  );
    void link_this_to_parent_first(GLUI_Node *parent  );
    void link_this_to_sibling_next(GLUI_Node *sibling );
    void link_this_to_sibling_prev(GLUI_Node *sibling );
    void unlink();

    void dump( FILE *out, const char *name );
    const char* whole_tree(int start=1);
    const char* NodeName;


protected:
    GLUI_Node();
    static void add_child_to_control(GLUI_Node *parent,GLUI_Control *child);
    GLUI_Node *parent_node;
    GLUI_Node *child_head;
    GLUI_Node *child_tail;
    GLUI_Node *next_sibling;
    GLUI_Node *prev_sibling;
};

#endif
