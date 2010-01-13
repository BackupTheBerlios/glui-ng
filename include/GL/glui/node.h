#ifndef __GLUI_NODE_H
#define __GLUI_NODE_H

/************************************************************/
/*                                                          */
/*          Base class, for hierarchical relationships      */
/*                                                          */
/************************************************************/
#include <GL/glui/commondefs.h>
#include <GL/glui/NonCopyableClass.h>
#include <GL/glui/SmartPointer.h>
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
        class GLUIAPI Node : public NonCopyableReferenceCountedClass
        {
                public:
                        Node(const char* name);

                        virtual ~Node();

                        NCRC_AutoPtr<Node> first_sibling();
                        NCRC_AutoPtr<Node> last_sibling();
                        NCRC_AutoPtr<Node> prev();
                        NCRC_AutoPtr<Node> next();

                        NCRC_AutoPtr<Node> first_child()   { return child_head; }
                        NCRC_AutoPtr<Node> last_child()    { return child_tail; }
                        NCRC_AutoPtr<Node> parent()        { return parent_node; }
                        NCRC_AutoPtr<Node> GetRootNode();

                        /** Link in a new child control */
                        virtual int  add_control( NCRC_AutoPtr<Node> control );

                        void link_this_to_parent_last (NCRC_AutoPtr<Node> parent  );
                        void link_this_to_parent_first(NCRC_AutoPtr<Node> parent  );
                        void link_this_to_sibling_next(NCRC_AutoPtr<Node> sibling );
                        void link_this_to_sibling_prev(NCRC_AutoPtr<Node> sibling );
                        void unlink();

                        void dump( FILE *out, const char *name );
                        const char* whole_tree(int start=1);
                        const char* NodeName;

                        int level() { return _level;}


                protected:
                        int _level;   //node level, used for debug purpose
                        Node();
                        NCRC_AutoPtr<Node> parent_node;
                        NCRC_AutoPtr<Node> child_head;
                        NCRC_AutoPtr<Node> child_tail;
                        NCRC_AutoPtr<Node> next_sibling;
                        NCRC_AutoPtr<Node> prev_sibling;
        };
}
#endif
