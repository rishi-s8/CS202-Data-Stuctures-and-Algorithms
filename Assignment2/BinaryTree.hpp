/*
  * CS202 Assignment 2
  * Author: Rishi Sharma (B17138)
  * BinaryTree.hpp - Contains the class BinaryNode, BinaryTree and Queue
*/

#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP 1
#define inf -100010007
#include <iostream>
#include <limits.h>
using namespace std;

template <typename Item>
class Queue
{
	struct node
	{
		Item addr;
		node* next;
	};
	node *head, *tail;

public:
	Queue()
	{
		head=tail=nullptr;
	}
	node* createNode(Item addr)
	{
		node *temp = new node;
		temp->addr = addr;
		temp->next=NULL;
		return temp;
	}

	bool isEmpty()
	{
		if(head==nullptr)
			return true;
		else
			return false;
	}

	void push(Item addr)
	{
		node* temp = createNode(addr);
		if(head==nullptr)
		{
			head=tail=temp;
		}
		else
		{
			tail->next=temp;
			tail=temp;
		}
	}

	Item front()
	{
			return head->addr;
	}
	void pop()
	{
		if(isEmpty())
			return;
		node *temp = head;
		if(head->next==nullptr)
		{
			head=tail=nullptr;
		}
		else
		{
			head=head->next;
		}
		delete temp;
	}
	void printQueue()
	{
		node * temp = head;
		while(temp!=nullptr)
		{
			cout << temp->addr << " ";
			temp=temp->next;
		}
		cout << endl;
	}
};

template <typename Key, typename Value>
class BinaryNode
{
public:
	Key key;
	Value val;
	int height, size;
	Value maxValue;
	BinaryNode<Key,Value> * root,* left,* right,* parent;
    /*Default constructor. Should assign the default value to key and value
     */
	BinaryNode()
	{
		root = left = right = parent = nullptr;
		key=Key();
		maxValue = val=Value();
		height = 0;
		size = 1;
	}
	/*This contructor should assign the key and val from the passed parameters
     */
	BinaryNode(Key key, Value value)
	{
		this->key = key;
		maxValue = val = value;
		root = left = right = parent = nullptr;
		height = 0;
		size = 1;
	}
};

template<typename Key, typename Value>
class BinaryTree
{
	/* You can implement your own helper functions whenever required.
	 */

protected:
	BinaryNode<Key,Value> * root;
	virtual Value get(const Key& key, BinaryNode<Key,Value> * current)
	{
		if(current->key == key)
			return current->val;
		else
		{
			Value val1 = Value();
			if(current->left!=nullptr)
				val1 = get(key, current->left);
			if(val1==Value() && current->right!=nullptr)
				val1 = get(key, current->right);
			return val1;
		}
	}

	void deleteNode(BinaryNode<Key,Value>*& current)
	{
		//Case 1: No child
		BinaryNode<Key,Value> * temp;
		if(current->left==nullptr && current->right==nullptr)
		{
			temp = current;
			current = nullptr;
			delete temp;
			return ;
		}
		//Case 2: No left child
		else if(current->left==nullptr)
		{

			temp = current;
			current->right->parent = current->parent;
			current = current->right;
			delete temp;
			return ;
		}
		//Case 3: No right child
		else if(current->right==nullptr)
		{
			temp = current;
			current->left->parent = current->parent;
			current = current->left;
			delete temp;
			return ;
		}
		//Case 4: Both children
		else
		{
			//Get right-element

			BinaryNode<Key,Value> * temp2 = current->right;
			while(temp2->left!=nullptr)
				temp2=temp2->left;

			swap(temp2->val, current->val);
			swap(temp2->key, current->key);

			BinaryNode<Key,Value> * temp3 = temp2->parent;
			deleteNode(temp3->left);
			while(temp3!=current)
			{
				updateHeight(temp3);
				temp3=temp3->parent;
			}
			return ;
		}
	}

	virtual bool removeHelper(const Key& key, BinaryNode<Key,Value>*& current)
 	{
		if(current->key==key)
		{
			deleteNode(current);
			return true;
		}
		else
		{
			bool removed = false;
			if(current->left!=nullptr)
				removed = removeHelper(key, current->left);
			if(!removed && current->right!=nullptr)
				removed = removeHelper(key, current->right);
			if(removed)
				updateHeight(current);
			return removed;
		}
 	}

	virtual bool has(const Key& key, BinaryNode<Key,Value>* current)
 	{
		if(current->key == key)
			return true;
		bool ans1=false, ans2=false;
		if(current->left!=nullptr)
			ans1=has(key, current->left);
		if(current->right!=nullptr)
			ans2=has(key, current->right);
		if(ans1 || ans2)
			return true;
		else
			return false;
 	}

	virtual void print_in_order(BinaryNode<Key,Value> * current)
	{
		if(current->left!=nullptr)
			print_in_order(current->left);
		cout << current->key << ": " << current->val  << endl;
		if(current->right!=nullptr)
			print_in_order(current->right);
	}

	virtual void print_pre_order(BinaryNode<Key,Value> * current)
 	{
		cout << current->key << ": " << current->val << endl;
		if(current->left!=nullptr)
			print_pre_order(current->left);
		if(current->right!=nullptr)
			print_pre_order(current->right);
 	}

	virtual void print_post_order(BinaryNode<Key,Value> * current)
	{
		if(current->left!=nullptr)
			print_post_order(current->left);
		if(current->right!=nullptr)
			print_post_order(current->right);
		cout << current->key << ": " << current->val << endl;
	}

	virtual Key minimum(BinaryNode<Key,Value> * current, Key &min)
 	{
		if(current->key < min)
			min = current->key;
		if(current->left!=nullptr)
			minimum(current->left, min);
		if(current->right!=nullptr)
			minimum(current->right, min);
		return min;
 	}

	virtual Key maximum(BinaryNode<Key,Value> * current, Key &max)
	{
	if(current->key > max)
	 max = current->key;
	if(current->left!=nullptr)
	 maximum(current->left, max);
	if(current->right!=nullptr)
	 maximum(current->right, max);
	return max;
	}

	virtual Key successor(const Key& key, BinaryNode<Key,Value> * current, Key& suc)
	{
		if(current->key>key && (suc==Key() || (current->key > key && current->key<suc)))
			suc=current->key;
		if(current->left!=nullptr)
			successor(key, current->left, suc);
		if(current->right!=nullptr)
			successor(key, current->right, suc);
		return suc;
	}

	virtual Key predecessor(const Key& key, BinaryNode<Key,Value> * current, Key& pred)
	{
		if(current->key<key && (pred==Key() || (current->key < key && current->key > pred)))
		 pred=current->key;
		if(current->left!=nullptr)
		 predecessor(key, current->left, pred);
		if(current->right!=nullptr)
		 predecessor(key, current->right, pred);
		 return pred;
	}

	int getHeight(BinaryNode<Key,Value> *current)
	{
		if(current == nullptr) return -1;
		else return current->height;
	}

	void updateHeight(BinaryNode<Key,Value> *current)
	{
    current->height = max(getHeight(current->left), getHeight(current->right)) + 1;
	}

public:

	BinaryTree()
	{
		root=nullptr;
	}

	/* Implement get function to retrieve the value corresponding to given key in binary tree.
   */

  virtual Value get(const Key& key)
	{
		if(root!=nullptr)
			return get(key, root);
		else return Value();
	}

	/* Implement remove function that can delete a node in binary tree with given key.
   */

  virtual void remove(const Key& key)
	{
		if(root!=nullptr)
			removeHelper(key, root);
	}
  /* Implement has function which will return true if the given key is present in binary tree
   * otherwise return false.
   */

	virtual bool has(const Key& key)
	{
		if(root != nullptr)
			return has(key, root);
		else return false;
	}
  /* Implement put function such that newly inserted node keep the tree balanced.
   */
  virtual void put(const Key& key, const Value& value)
	{
		BinaryNode<Key,Value> * current = new BinaryNode<Key,Value>(key, value);
		if(root==nullptr)
		{
			root = current;
			current->root=root;
			return;
		}
		Queue< BinaryNode<Key,Value> * > q;
		q.push(root);
		while(q.front()->left!=nullptr && q.front()->right!=nullptr)
		{
			q.push(q.front()->left);
			q.push(q.front()->right);
			q.pop();
		}
		current->parent=q.front();
		current->root=root;
		if(q.front()->left==nullptr)
			q.front()->left=current;
		else
			q.front()->right=current;
		current=current->parent;
		while(current!=nullptr)
		{
			updateHeight(current);
			current=current->parent;
		}

	}
  /*
   *This method print all the key value pairs of the binary tree, as
   *observed in an in order traversal.
   */
	virtual void print_in_order()
	{
		if(root!=nullptr)
			print_in_order(root);
	}
  /*
   *This method print all the key value pairs of the binary tree, as
   *observed in an pre order traversal.
   */

	virtual void print_pre_order()
	{
		if(root!=nullptr)
			print_pre_order(root);
	}

  /*
   *This method print all the key value pairs of the binary tree, as
   *observed in a post order traversal.
   */

	virtual void print_post_order()
	{
		if(root!=nullptr)
			print_post_order(root);
	}
  /*
   *This method returns the minimum element in the binary tree.
   */

	virtual Key minimum()
	{
		Key min;
		if(root==nullptr)
			return Key();
		else
		{
			min = root->key;
			min = minimum(root, min);
			return min;
		}
	}
  /*
   * This method returns the maximum element in the binary tree.
   */

 	virtual Key maximum()
 	{
 		Key max;
 		if(root==nullptr)
 			return Key();
 		else
 		{
 			max = root->key;
 			max = maximum(root, max);
 			return max;
 		}
 	}
  /*
   *This method returns the successor, i.e, the next larget element in the
   *binary tree, after Key.
   */

  virtual Key successor(const Key& key)
	{
		Key suc = Key();
		if(root==nullptr) return Key();
		else
		{
			suc = successor(key, root, suc);
			return suc;
		}
	}
  /*
   * This method returns the predecessor, ie, the next smallest element in the
   * binary tree, after Key.
   */

   virtual Key predecessor(const Key& key)
 	{
 		Key pred = Key();
 		if(root==nullptr) return Key();
 		else
 		{
 			pred = predecessor(key, root, pred);
 			return pred;
 		}
 	}
};

#endif /* ifndef BINARYTREE_HPP */
