/*
   GLUI-ng, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

   This library is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the 
   Free Software Foundation; either version 2.1 of the License, 
   or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License along with this library;
   if not, write to the 
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

   based on the work of Paul Rademacher (orignal software http://glui.sourceforge.net/)
*/

#include <GL/glui/Node.h>
#include <GL/glui/debug.h>
#include <GL/glui/MasterObject.h>
#include <GL/glui/Exception.h>
using namespace GLUI;

#define MODULE_KEY  "GLUI_DEBUG_NODE"
/********************************************* Node::Node() *******/

Node::Node()
{
    _level = 0;
    ChildCount = 0;
}

Node::Node(const char* name)
{
    NodeName = name;
    _level = 0;
    ChildCount = 0;
}

Node::~Node()
{
        if (this->ChildCount != GetCount())
        {
                GLUI_THROW(ENOTSUP,
                                "trying to delete a node that have still owners...");
        }
        if (this->next_sibling != NULL)
        {
                this->next_sibling->prev_sibling = this->prev_sibling;
        }

        if (this->prev_sibling != NULL)
        {
                this->prev_sibling->next_sibling = this->next_sibling;
        }

        while (this->child_head != NULL)
        {
                RemoveChild(this->child_head);
        }
}


////////////////////////////////////////////////////////////////////////
const char* Node::Name()
{
        return this->NodeName;
}

/********************************************* Node::first() *******/
/* Returns first sibling in 'this' node's sibling list                  */

NCRC_AutoPtr<Node> Node::first_sibling( void )
{
  if ( parent_node == NULL )  
    return this;           /* root node has no siblings */
  else
    return parent_node->child_head;
}

/********************************************* Node::last() *******/
/* Returns last sibling in 'this' node's sibling list                  */

NCRC_AutoPtr<Node> Node::last_sibling( void )
{
  if ( parent_node == NULL )
    return this;            /* root node has no siblings */
  else
    return parent_node->child_tail;
}

/******************************************** Node::prev() ********/
/* Returns prev sibling in 'this' node's sibling list                  */

NCRC_AutoPtr<Node> Node::prev( void )
{
  return prev_sibling;
}


/******************************************** Node::next() ********/
/* Returns next sibling in 'this' node's sibling list                  */

NCRC_AutoPtr<Node> Node::next( void )
{
  return next_sibling;
}

///////////////////////////////////////////////////////////////////////
// returns root node or NULL if already the root node
NCRC_AutoPtr<Node> Node::GetRootNode()
{
    NCRC_AutoPtr<Node> current = this->parent_node;
    if(current == NULL || current == MasterObject::Instance() ) return this;
    while (current != NULL && current->parent() != NULL)
    {
        current = current->parent();
    }
    return current;
}

////////////////////////////////////////////////////////////////////////
int Node:: RemoveParent( NCRC_AutoPtr<Node> parent )
{
        if (parent_node == parent)
        {
                parent_node = NULL;
                delete this;
        }
        else
        {
                GLUI_THROW(EINVAL,
                                "trying to remove a parent that isn't in parent list");
        }
	return 0;
}


/////////////////////////////////////////////////////////////////////////
void Node::removeReference()
{
        if (ChildCount == (GetCount()-1))
        {
                while (child_head != NULL)
                {
                        RemoveChild(child_head);
                }
        }
        NonCopyableReferenceCountedClass::removeReference();
}

/************************************ Node::add_control() **************/
int Node::add_control( NCRC_AutoPtr<Node> child )
{
	LinkLast( child );
        ChildCount ++;
	return 0;
}

int Node::RemoveChild(  NCRC_AutoPtr<Node> child  )
{
        NCRC_AutoPtr<Node> curr = this->child_head;
        this->ChildCount--;
        while ( curr != NULL && curr != child)
        {
                curr = curr->next();
        }
        if (curr != NULL)
        {
                // if the node is in middle of the chain
                if ( curr->prev_sibling != NULL && curr->next_sibling != NULL) 
                {
                        curr->prev_sibling->next_sibling = curr->next_sibling;
                        curr->next_sibling->prev_sibling = curr->prev_sibling;
                }
                else
                {
                        if (curr == this->child_head )
                        {    //first child
                                this->child_head = curr->next_sibling;
                                if (this->child_head != NULL)
                                {
                                        this->child_head->prev_sibling = NULL;
                                }
                        }
                        if (curr == this->child_tail)
                        {  // last child
                                this->child_tail = curr->prev_sibling;
                                if (this->child_tail != NULL)
                                {
                                        this->child_tail->next_sibling = NULL;
                                }
                        }
                }

                curr->_level = 0;
                curr->parent_node  = NULL;
                curr->next_sibling = NULL;
                curr->prev_sibling = NULL;
        }
        else
        {
                GLUI_THROW(EINVAL,
                                "trying to unlink a node that isn't in the childs list");
        }
}

/*************************** Node::link_this_to_parent_last() *******/
/* Links as last child of parent                                         */

void   Node::LinkLast( NCRC_AutoPtr<Node> new_child )
{
    if ( this->child_tail == NULL ) {   /* parent has no children */
        this->child_head = new_child;
    }
    else {                                 /* parent has children */
        this->child_tail->next_sibling = new_child;
        new_child->prev_sibling        = this->child_tail;
    }
    this->child_tail = new_child;
    new_child->parent_node             = this;
    new_child->_level = this->_level+1;
}


/*************************** Node::link_this_to_parent_first() *******/
/* Links as first child of parent                                         */

void   Node::link_this_to_parent_first( NCRC_AutoPtr<Node> new_parent )
{
    if ( new_parent->child_head == NULL ) {   /* parent has no children */
        new_parent->child_tail               = this;
    }
    else {                                 /* parent has children */
        new_parent->child_head->prev_sibling = this;
        this->next_sibling                   = new_parent->child_head;
    }
    new_parent->child_head               = this;
    this->parent_node                    = new_parent;
    this->_level = parent_node->level()+1;
}

/**************************** Node::link_this_to_sibling_next() *****/

void   Node::link_this_to_sibling_next( NCRC_AutoPtr<Node> sibling )
{
  if ( sibling->next_sibling == NULL ) {    /* node has no next sibling */
    sibling->next_sibling  = this;
    this->prev_sibling     = sibling;

    /* This was the parent's last child, so update that as well */
    if ( sibling->parent_node  != NULL ) {
      sibling->parent_node->child_tail = this;
    }
  }
  else {                            /* node already has a next sibling */
    sibling->next_sibling->prev_sibling = this;
    this->next_sibling                  = sibling->next_sibling;
    sibling->next_sibling               = this;
    this->prev_sibling                  = sibling;
  }

  this->parent_node = sibling->parent_node;
  this->_level = parent_node->level()+1;
}


/**************************** Node::link_this_to_sibling_prev() *****/

void   Node::link_this_to_sibling_prev( NCRC_AutoPtr<Node> sibling )
{
  if ( sibling->prev_sibling == NULL ) {    /* node has no prev sibling */
    sibling->prev_sibling  = this;
    this->next_sibling     = sibling;

    /* This was the parent's first child, so update that as well */
    if ( sibling->parent_node  != NULL ) {
      sibling->parent_node->child_head = this;
    }
  }
  else {                            /* node already has a prev sibling */
    sibling->prev_sibling->next_sibling = this;
    this->prev_sibling                  = sibling->prev_sibling;
    sibling->prev_sibling               = this;
    this->next_sibling                  = sibling;
  }

  this->parent_node = sibling->parent_node;
  this->_level = parent_node->level()+1;
}




/**************************************** Node::dump() **************/

void Node::dump( FILE *out, const char *name )
{
	MSG( "node: " << name << endl );
	MSG("   parent: " << (void *) parent_node.getPointee()
                   <<"    child_head: " << (void *) child_head.getPointee()
                   <<"    child_tail: " << (void *) child_tail.getPointee()
                   << endl);
	MSG("   next: " << (void *) next_sibling.getPointee() 
                        << "       prev: " << (void *) prev_sibling.getPointee() << endl);
}

const char* Node::whole_tree(int start)
{
    static std::string tree;
    if (start) {
        tree.clear();
        tree += "\"";
    }
    if (parent_node != NULL) {
        parent_node->whole_tree(0);
        tree += ".";
    }
    if (NodeName)
    {
        tree += NodeName;
    }
    else
    {
        tree += "some widget have no name!";
    }
    if (start) {
        tree += "\"";
    }
    return tree.c_str();
}
