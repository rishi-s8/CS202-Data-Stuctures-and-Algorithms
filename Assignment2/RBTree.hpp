/*
  * CS202 Assignment 2
  * Author: Rishi Sharma (B17138)
  * RBTree.hpp - Contains the class RBTree and RBTreeNode
*/
#ifndef RBTree_HPP_
#define RBTree_HPP_ 1
#include "AVL.hpp"
/* The color enumeration.
 * Please use this and not integers or characters to store the color of the node
 * in your red black tree.
 * Also create a class RBTNode which should inherit from BinaryNode and has the attribute color in it.
 */
#define clr(x) ((RBTreeNode<Key,Value>*)x)->color
enum Color { RED, BLACK, DOUBLE_BLACK };

template <class Key, class Value>
class RBTreeNode : public BinaryNode<Key, Value>
{
public:
	using BinaryNode<Key, Value>::key;
	using BinaryNode<Key, Value>::val;
	using BinaryNode<Key, Value>::left;
	using BinaryNode<Key, Value>::right;
	using BinaryNode<Key, Value>::parent;
	using BinaryNode<Key, Value>::root;
	Color color;
	RBTreeNode() : BinaryNode<Key, Value>()
	{
		color =  RED;
	}
	RBTreeNode(Key key, Value val) : BinaryNode<Key, Value>(key, val)
	{
		color =  RED;
	}
};

template <class Key, class Value>
class RBTree : public BSTree<Key, Value> {
/* Inherit as many functions as possible from BSTree.
 * Only override those which absolutely need it.
 * Also make sure that all inherited functions work correctly in the context of a red black tree.
 * node_ptr in the following piece of code refers to a pointer to the node you may be using for your red black tree.
 * Use a typedef to refer to a pointer to your node via node_ptr
 */
 	using BSTree<Key, Value> :: root;
	using BSTree<Key, Value> :: elements;
	typedef BinaryNode<Key, Value>* node_ptr;

	node_ptr getSibling(node_ptr current)
	{
		if(current==nullptr || current->parent==nullptr)
			return nullptr;
		else if(current==current->parent->left)
			return current->parent->right;
		else
			return current->parent->left;
	}

	Color getColor(node_ptr current)
	{
		if(current == nullptr) return BLACK;
		else if(clr(current) == RED) return RED;
		else return BLACK;
	}

	void rightRotate(node_ptr z)
	{
		node_ptr temp = z->left, grandParent = z->parent;
		z->left = temp->right;
		if(temp->right!=nullptr)
		 temp->right->parent = z;
		temp->right = z;
		z->parent = temp;
		temp->parent = grandParent;
		if(grandParent==nullptr) root = temp;
		else if(grandParent->right == z) grandParent->right = temp;
		else grandParent->left = temp;
	}

	void leftRotate(node_ptr z)
	{
		node_ptr temp = z->right, grandParent = z->parent;
		z->right = temp->left;
		if(temp->left!=nullptr)
		 temp->left->parent = z;
		temp->left = z;
		z->parent = temp;
		temp->parent = grandParent;
		if(grandParent==nullptr) root = temp;
		else if(grandParent->right == z) grandParent->right = temp;
		else grandParent->left = temp;
	}

  void put(const Key& key, const Value& value, node_ptr& current)
	{
		if(key<current->key)
    {
      if(current->left==nullptr)
      {
        ++elements;
        current->left =  (new RBTreeNode<Key,Value>(key, value));
        current->left->parent = current;
				insertRBFixup(current->left);
      }
      else
        put(key, value, current->left);
    }
    else
    {
      if(current->right==nullptr)
      {
        ++elements;
        current->right = new RBTreeNode<Key,Value>(key, value);
        current->right->parent = current;
				insertRBFixup(current->right);
      }
      else
        put(key, value, current->right);
    }
	}

	/* Function insertRBFixup
	 *
	 * Used for:
	 * Used after an insertion in the rb tree.
	 * It applies fixing mechanisms to make sure that the tree remains a valid red black tree after an insertion.
	 */
	void insertRBFixup(BinaryNode<Key, Value>* current)
	{
		// If Collision between red nodes
		while(current!=root && getColor(current) == RED && getColor(current->parent) == RED)
		{
			node_ptr parentCurrent = current->parent;
			node_ptr grandParentCurrent = parentCurrent->parent; // Not nullptr because root is always black

			// Case 0: Only recoloring is required
			if(getColor(getSibling(current->parent))==RED)
			{
				clr(grandParentCurrent) = RED;
				clr(parentCurrent) = BLACK;
				clr(getSibling(parentCurrent)) = BLACK;
				current=grandParentCurrent;
			}
			// Restructuring required
			else
			{
				// Left - X - Insertion
				if(parentCurrent == grandParentCurrent->left)
				{
					// Case 1: Left Left insertion
					if(current==parentCurrent->left)
					{
						rightRotate(grandParentCurrent);
						clr(parentCurrent) = BLACK;
						clr(grandParentCurrent)= RED;
						current=parentCurrent;
					}
					// Case 2: Left Right insertion
					else
					{
						leftRotate(parentCurrent);
						rightRotate(grandParentCurrent);
						clr(current) = BLACK;
						clr(grandParentCurrent)= RED;
					}
				}
				// Right - X - Insertion
				else
				{
					// Case 3: Right Right insertion
					if(current==parentCurrent->right)
					{
						leftRotate(grandParentCurrent);
						clr(parentCurrent) = BLACK;
						clr(grandParentCurrent) = RED;
						current=parentCurrent;
					}
					// Case 4: Right Left insertion
					else
					{
						rightRotate(parentCurrent);
						leftRotate(grandParentCurrent);
						clr(current) = BLACK;
						clr(grandParentCurrent) = RED;
					}
				}
			}
		}
		clr(root) = BLACK;
	}

	/* Function deleteRBFixup
		 * Used for:
		 * Used after a deletion in the rb tree.
		 * It applies fixing mechanisms to make sure that the tree remains a valid red black tree after a deletion.
		 */
		 void deleteRBFixup(node_ptr doubleBlackNode)
		 {
			 	// Case: 1
				if(doubleBlackNode == root)
					return;
				else
				{
					node_ptr sibling = getSibling(doubleBlackNode);
					node_ptr parent = doubleBlackNode->parent;
					if(getColor(sibling)==RED)
					{
						if(doubleBlackNode==parent->left)
							leftRotate(parent);
						else
							rightRotate(parent);
						clr(parent)=RED;
						clr(sibling)=BLACK;
						deleteRBFixup(doubleBlackNode);
					}
					// Case: 3
					else if(getColor(parent) == BLACK && getColor(sibling) == BLACK && getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK)
					{
						clr(sibling) = RED;
						deleteRBFixup(parent);
					}
					// Case: 4
					else if(getColor(parent)==RED && getColor(sibling) == BLACK && getColor(sibling->left)==BLACK && getColor(sibling->right)==BLACK)
					{
						clr(parent) = BLACK, clr(sibling) = RED;
						return;
					}
					// Case: 5.1
					else if(getColor(sibling) == BLACK && doubleBlackNode==parent->left && getColor(sibling->left)==RED)
					{
						clr(sibling->left) = BLACK;
						clr(sibling) = RED;
						rightRotate(sibling);
						deleteRBFixup(doubleBlackNode);
					}
					// Case 5.2
					else if(getColor(sibling) == BLACK && doubleBlackNode==parent->right && getColor(sibling->right)==RED)
					{
						clr(sibling->right) = BLACK;
						clr(sibling) = RED;
						leftRotate(sibling);
						deleteRBFixup(doubleBlackNode);
					}
					// Case 6
					else
					{
						// Case 6.1

						clr(sibling) = getColor(parent);
						clr(parent) = BLACK;
						if(doubleBlackNode==parent->left)
						{
							clr(sibling->right)=BLACK;
							leftRotate(parent);
						}
						else
						{
							clr(sibling->left)=BLACK;
							rightRotate(parent);
						}
					}
				}
		 }

		 void deleteNode(node_ptr &current)
	 	{
	 		node_ptr toBeDeleted = current;
	 		node_ptr child = (current->left==nullptr) ? current->right : current->left;
	 		bool nullAdded = false;
	 		if(child==nullptr)
	 		{
	 			nullAdded = true;
	 			child = new RBTreeNode<Key,Value>(Key(), Value());
	 			clr(child)=BLACK;
	 		}
	 		child->parent = current->parent;
	 		current = child;
	 		if(getColor(toBeDeleted)==BLACK)
	 		{
	 			if(getColor(child)==RED)
	 				clr(child) = BLACK;
	 			else
	 				deleteRBFixup(child);
	 		}
	 		if(nullAdded)
	 		{
	 			current = nullptr;
	 			delete child;
	 		}
	 		delete toBeDeleted;

	 	}

		void remove(const Key& key, node_ptr& current)
	   {
		   if(current->key==key)
		   {
		      --elements;
					if(current->left==nullptr || current->right==nullptr)
						deleteNode(current);
					else
					{
						node_ptr temp = current->right;
						while(temp->left!=nullptr)
							temp=temp->left;
						current->key = temp->key;
						current->val = temp->val;
						remove(current->key, current->right);
					}
		   }
		   else
		   {
		     if(key<current->key && current->left!=nullptr)
		       remove(key, current->left);
		     else if(current->right!=nullptr)
		       remove(key, current->right);
		   }
	   }


public:
	using BSTree<Key,Value>::print_in_order;
  using BSTree<Key,Value>::print_pre_order;
  using BSTree<Key,Value>::print_post_order;
  using BSTree<Key,Value>::get;
  using BSTree<Key, Value>:: has;
	using BSTree<Key, Value>:: remove;
	RBTree()
	{
		root = nullptr;
	}

	void put(const Key& key, const Value& value)
	{
    if(root==nullptr)
    {
      root=new RBTreeNode<Key,Value>(key,value);
			clr(root) = BLACK;
      return;
    }
    else
      put(key, value, root);
  }

	/* Function : blackHeight
	 *
	 * Returns:
	 * the black height of the red black tree which begins at node_ptr root
	 */
	int blackHeight(node_ptr root)
	{
		int count = 1;
		root=root->left;
		while(root!=nullptr)
		{
			if(getColor(root)==BLACK) count++;
			root=root->left;
		}
		return count;
	}

	int blackHeight(Key key)
	{
			node_ptr temp = root;
			while(temp!=nullptr && temp->key!=key)
			{
				if(key<temp->key)
					temp=temp->left;
				else
					temp=temp->right;
			}
			if(temp==nullptr)
				return 0;
			else
				return blackHeight(temp);
	}


	/*
	 * Apart from these functions, also provide functions for rotations in the tree.
	 * The signature of the rotation functions is omitted to provide you flexibility in how you implement the internals of your node.
	 */

};
#endif /* ifndef RBTree_HPP_ */
