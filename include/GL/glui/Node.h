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

                        virtual int add_control( NCRC_AutoPtr<Node> control ); //< Link in a new child control
                        virtual int RemoveChild(  NCRC_AutoPtr<Node> child  ); //< remove child from child list
                        virtual int RemoveParent( NCRC_AutoPtr<Node> parent ); //< remove parent from parents list

                        virtual void removeReference();


                        void dump( FILE *out, const char *name );
                        const char* whole_tree(int start=1);

                        int level() { return _level;}

                protected:// methodes
                        void LinkLast( NCRC_AutoPtr<Node> new_child );
                        void link_this_to_parent_first(NCRC_AutoPtr<Node> parent  );
                        void link_this_to_sibling_next(NCRC_AutoPtr<Node> sibling );
                        void link_this_to_sibling_prev(NCRC_AutoPtr<Node> sibling );

                protected:
                        int _level;   //node level, used for debug purpose
                        int ChildCount;
                        NCRC_AutoPtr<Node> parent_node;
                        NCRC_AutoPtr<Node> child_head;
                        NCRC_AutoPtr<Node> child_tail;
                        NCRC_AutoPtr<Node> next_sibling;
                        NCRC_AutoPtr<Node> prev_sibling;
                        const char* NodeName;
                private:
                        Node();
        };
}
#endif
