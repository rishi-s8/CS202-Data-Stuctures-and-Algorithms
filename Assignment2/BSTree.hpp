/*
  * CS202 Assignment 2
  * Author: Rishi Sharma (B17138)
  * BSTree.hpp - Contains the class BSTree
*/

#ifndef BSTREE_HPP
#define BSTREE_HPP 1
#include "BinaryTree.hpp"
template <typename Key, typename Value>
class BSTree : public BinaryTree<Key, Value> {

/* Inherit as many functions as possible from BinaryTree.
 * Only override those where you can decrease the time complexity and where you absolutely need to do it.
 * Also make sure that all inherited functions work correctly in the context of a binary search tree.
 */
 protected:
 int elements;
 using BinaryTree<Key,Value>::root;
 using BinaryTree<Key,Value>::deleteNode;
 using BinaryTree<Key,Value>::getHeight;
 using BinaryTree<Key,Value>::updateHeight;

 Value get(const Key& key, BinaryNode<Key,Value> * current)
	{
		if(current->key == key)
			return current->val;
		else
		{
			if(key<current->key && current->left!=nullptr)
				return get(key, current->left);
			else if(current->right!=nullptr)
				return get(key, current->right);
      return Value();
		}
	}

  virtual void remove(const Key& key, BinaryNode<Key,Value>*& current)
 	{
		if(current->key==key)
		{
      --elements;
			deleteNode(current);
      return;
		}
		else
		{
			if(key<current->key && current->left!=nullptr)
				remove(key, current->left);
			else if(current->right!=nullptr)
				remove(key, current->right);
		}
    updateHeight(current);
 	}

  bool has(const Key& key, BinaryNode<Key,Value>* current)
 	{
		if(current->key == key)
			return true;
		if(key<current->key && current->left!=nullptr)
			return has(key, current->left);
		else if(current->right!=nullptr)
			return has(key, current->right);
		return false;
 	}

  virtual void put(const Key& key, const Value& value, BinaryNode<Key,Value>*& current)
  {
    if(key<current->key)
    {
      if(current->left==nullptr)
      {
        ++elements;
        current->left = new BinaryNode<Key,Value>(key, value);
        current->left->parent = current;
      }
      else
        put(key, value, current->left);
    }
    else
    {
      if(current->right==nullptr)
      {
        ++elements;
        current->right = new BinaryNode<Key,Value>(key, value);
        current->right->parent = current;
      }
      else
        put(key, value, current->right);
    }
    updateHeight(current);
  }

 public:
  using BinaryTree<Key,Value>::print_in_order;
  using BinaryTree<Key,Value>::print_pre_order;
  using BinaryTree<Key,Value>::print_post_order;
  using BinaryTree<Key,Value>::get;
  using BinaryTree<Key, Value>:: has;
  /* Implement get function to retrieve the value corresponding to given key in binary search tree.
  */

  BSTree()
  {
    elements = 0;
  }

  /* Implement remove function that can delete a node in binary search tree with given key.
     */
  void remove(const Key& key)
	{
		remove(key, root);
	}

  /* Implement has function which will return true if the given key is present in binary search tree
   * otherwise return false.
   */

  /* Implement put function.
   */
  virtual void put(const Key& key, const Value& value)
	{
    if(root==nullptr)
    {
      root=new BinaryNode<Key,Value>(key,value);
      return;
    }
    else
      put(key, value, root);
  }

  /*
   *This method returns the minimum element in the binary search tree.
   */

	virtual Key minimum()
	{
		if(root==nullptr)
			return Key();
		else
		{
      BinaryNode<Key,Value> * temp = root;
      while(temp->left!=nullptr)
        temp=temp->left;
			return temp->key;
		}
	}

  /*
   *This method returns the maximum element in the binary search tree.
   */

	virtual Key maximum()
	{
		if(root==nullptr)
			return Key();
		else
		{
      BinaryNode<Key,Value> * temp = root;
      while(temp->right!=nullptr)
        temp=temp->right;
			return temp->key;
		}
	}

  /*
   *This method returns the successor, i.e, the next larget element in the
   *binary search tree, after Key.
   */

  virtual Key successor(const Key& key)
	{
		if(root==nullptr) return Key();
		else
		{
      Key suc = Key();
      BinaryNode<Key,Value> * current = root;
      while(current!=nullptr)
      {
        if(current->key>key && (suc==Key() || (current->key > key && current->key<suc)))
			     suc=current->key;
        if(key<current->key) current=current->left;
        else current=current->right;
      }
      return suc;
		}

	}

  /*
   * This method returns the predecessor, ie, the next smallest element in the
   * binary search tree, after Key.
   */

  virtual Key predecessor(const Key& key)
	{
		if(root==nullptr) return Key();
		else
		{
      Key pred = Key();
      BinaryNode<Key,Value> * current = root;
      while(current!=nullptr)
      {
        if(current->key<key && (pred==Key() || (current->key < key && current->key > pred)))
		      pred=current->key;
        if(key<=current->key) current=current->left;
        else current=current->right;
      }
      return pred;
		}
	}

  /*
   * This method returns the current height of the binary search tree.
   */
  virtual int getHeight()
  {
    return root->height;
  }
  /*
   * This method returns the total number of elements in the binary search tree.
   */
  virtual int size()
  {
    return elements;
  }
  /*
   * This method prints the key value pairs of the binary search tree, sorted by
   * their keys.
   */
  virtual void print()
  {
    print_in_order();
  }
};

#endif /* ifndef BSTREE_HPP */
