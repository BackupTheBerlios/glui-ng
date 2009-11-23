#ifndef __GLUI_NODE_H
#define __GLUI_NODE_H

/************************************************************/
/*                                                          */
/*          Base class, for hierarchical relationships      */
/*                                                          */
/************************************************************/
#include <GL/glui/commondefs.h>
#include <cstdio>
/**
 Node is a node in a sort of tree of GLUI controls.
 Each Node has a list of siblings (in a circular list)
 and a linked list of children.

 Everything onscreen is a Node--windows, buttons, etc.
 The nodes are traversed for event processing, sizing, redraws, etc.
*/
namespace GLUI
{
        class GLUIAPI Node
        {
                public:
                        Node(const char* name);

                        virtual ~Node();

                        Node *first_sibling();
                        Node *last_sibling();
                        Node *prev();
                        Node *next();

                        Node *first_child()   { return child_head; }
                        Node *last_child()    { return child_tail; }
                        Node *parent()        { return parent_node; }
                        Node *GetRootNode();

                        /** Link in a new child control */
                        virtual int  add_control( Node *control );

                        void link_this_to_parent_last (Node *parent  );
                        void link_this_to_parent_first(Node *parent  );
                        void link_this_to_sibling_next(Node *sibling );
                        void link_this_to_sibling_prev(Node *sibling );
                        void unlink();

                        void dump( FILE *out, const char *name );
                        const char* whole_tree(int start=1);
                        const char* NodeName;

                        int level() { return _level;}


                protected:
                        int _level;   //node level, used for debug purpose
                        Node();
                        Node *parent_node;
                        Node *child_head;
                        Node *child_tail;
                        Node *next_sibling;
                        Node *prev_sibling;
        };
}
#endif
