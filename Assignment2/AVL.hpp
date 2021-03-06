/*
  * CS202 Assignment 2
  * Author: Rishi Sharma (B17138)
  * AVL.hpp - Contains the class AVL
*/

#ifndef AVL_HPP
#define AVL_HPP 1
#include "BSTree.hpp"
#include "seqLinearList.hpp"
template <typename Key, typename Value>
class AVL : public BSTree<Key, Value> {
  /*
   * Inherit as much functionality as possible from the BSTree class.
   * Then provide custom AVL Tree functionality on top of that.
   * The AVL Tree should make use of as many BST functions as possible.
   * Override only those methods which are extremely necessary.
   */
 protected:
   using BSTree<Key,Value>::root;
   using BinaryTree<Key,Value>::getHeight;
   using BinaryTree<Key,Value>::updateHeight;
   using BSTree<Key,Value>::elements;

   void updateMaxValue(BinaryNode<Key,Value>* current)
   {
     Value leftValue = (current->left == nullptr) ? Value() : current->left->maxValue;
     Value rightValue = (current->right == nullptr) ? Value() : current->right->maxValue;
     current->maxValue = max(max(leftValue, rightValue), current->val);
   }

   virtual void deleteNode(BinaryNode<Key,Value>*& current)
 	{
 		//Case 1: No child
 		BinaryNode<Key,Value> * temp;
 		if(current->left==nullptr && current->right==nullptr)
 		{
 			temp = current;
 			current = nullptr;
 			delete temp;
 			return;
 		}
 		//Case 2: No left child
 		else if(current->left==nullptr)
 		{

 			temp = current;
 			current->right->parent = current->parent;
 			current = current->right;
 			delete temp;
 			return;
 		}
 		//Case 3: No right child
 		else if(current->right==nullptr)
 		{
 			temp = current;
 			current->left->parent = current->parent;
 			current = current->left;
 			delete temp;
 			return;
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
      if(temp2==temp3->left) deleteNode(temp3->left);
      else  deleteNode(temp3->right);
 			while(temp3!=current)
 			{
 				updateHeight(temp3);
        int balanceFactor = getBalance(temp3);
        if(balanceFactor>1 || balanceFactor<-1)
          doBalance(temp3, balanceFactor);
 				temp3=temp3->parent;
 			}
 			return;
 		}
 	}

   virtual int getBalance(BinaryNode<Key, Value> *current)
   {
     return getHeight(current->left) - getHeight(current->right);
   }

   void updateSize(BinaryNode<Key, Value> *current)
   {
     int leftSize = (current->left!=nullptr) ? current->left->size : 0;
     int rightSize = (current->right!=nullptr) ? current->right->size : 0;
     current->size = leftSize + rightSize + 1;
   }

   void rightRotate(BinaryNode<Key,Value>* z)
   {
     BinaryNode<Key,Value>* temp = z->left, *grandParent = z->parent;
     z->left = temp->right;
     if(temp->right!=nullptr)
      temp->right->parent = z;
     temp->right = z;
     z->parent = temp;
     temp->parent = grandParent;
     if(grandParent==nullptr) root = temp;
     else if(grandParent->right == z) grandParent->right = temp;
     else grandParent->left = temp;
     updateHeight(z);
     updateSize(z);
     updateMaxValue(z);
     updateHeight(temp);
     updateSize(temp);
     updateMaxValue(temp);
   }

   void leftRotate(BinaryNode<Key,Value>* z)
   {
     BinaryNode<Key,Value>* temp = z->right, *grandParent = z->parent;
     z->right = temp->left;
     if(temp->left!=nullptr)
      temp->left->parent = z;
     temp->left = z;
     z->parent = temp;
     temp->parent = grandParent;
     if(grandParent==nullptr) root = temp;
     else if(grandParent->right == z) grandParent->right = temp;
     else grandParent->left = temp;
     updateHeight(z);
     updateSize(z);
     updateMaxValue(z);
     updateHeight(temp);
     updateSize(temp);
     updateMaxValue(temp);
   }

   void doBalance(BinaryNode<Key,Value> * current, int balanceFactor)
   {
     // Case 1: Left Left Insertion
     if(balanceFactor>1 && getBalance(current->left)>=0)
      rightRotate(current);

     // Case 2: Left Right Insertion
     else if(balanceFactor>1)
     {
       leftRotate(current->left);
       rightRotate(current);
     }

     // Case 3: Right Right Insertion
     else if(balanceFactor<-1 && getBalance(current->right)<=0)
      leftRotate(current);

     // Case 4: Right Left Insertion
     else if(balanceFactor<-1)
     {
       rightRotate(current->right);
       leftRotate(current);
     }
   }

   virtual void put(const Key& key, const Value& value, BinaryNode<Key,Value>* current)
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
     (current->size)++;
     updateHeight(current);
     updateMaxValue(current);
     int balanceFactor = getBalance(current);
     if(balanceFactor>1 || balanceFactor<-1)
       doBalance(current, balanceFactor);
   }

    void remove(const Key& key, BinaryNode<Key,Value>*& current)
  	{
      BinaryNode<Key,Value> * temp;
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
     int balanceFactor = getBalance(current);
     if(balanceFactor>1 || balanceFactor<-1)
       doBalance(current, balanceFactor);
  	}



  /*
   * Apart from that, your code should have the following four functions:
   * getBalance(node) -> To get the balance at any given node;
   * doBalance(node) -> To fix the balance at the given node;
   * rightRotate(node) -> Perform a right rotation about the given node.
   * leftRotate(node) -> Perform a left rotation about the given node.
   *
   * The signature of these functions are not provided in order to provide you
   * some flexibility in how you implement the internals of your AVL Tree. But
   * make sure these functions are there.
   */

 public:
   using BSTree<Key, Value>::get;
   using BSTree<Key, Value>::has;
   using BSTree<Key, Value>::remove;

   void insert1(Key key, Value val, LinearList<Value>& indexOfGreater); // For problem 1
   void insert1(Key key, Value val, BinaryNode<Key, Value>* current, LinearList<Value>& indexOfGreater); // For problem 1

   long long insert2(Key key, Value val); // For problem 2
   long long insert2(Key key, Value val, BinaryNode<Key, Value>* current, long long &smallerNodes); // For problem 2

  void put(const Key& key, const Value& value)
  {
     if(root==nullptr)
     {
       root=new BinaryNode<Key,Value>(key,value);
       return;
     }
     else
       put(key, value, root);
   }

  int getSize(BinaryNode<Key, Value> *current)
  {
    if(current==nullptr)
      return 0;
    else return current->size;
  }


};

#endif /* ifndef AVL_HPP */
