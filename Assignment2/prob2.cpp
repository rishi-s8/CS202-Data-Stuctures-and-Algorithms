/*
  * CS202 Assignment 2
  * Author: Rishi Sharma (B17138)
  * prob2.cpp - Solution to Problem-2
  * Input:
  *         n - Number of values
  *         n space seperated values
*/

#include <iostream>
#include "seqLinearList.hpp"
#include "AVL.hpp"

template <class Key, class Value>
long long AVL<Key,Value>::insert2(Key key, Value value, BinaryNode<Key, Value>* current, long long &smallerNodes)
{
  if(key<=current->key)
  {
    if(current->left==nullptr)
    {
      ++elements;
      current->left = new BinaryNode<Key,Value>(key, value);
      current->left->parent = current;
    }
    else
      insert2(key, value, current->left, smallerNodes);
  }
  else
  {
    smallerNodes+=getSize(current->left) + 1;
    if(current->right==nullptr)
    {
      ++elements;
      current->right = new BinaryNode<Key,Value>(key, value);
      current->right->parent = current;
    }
    else
      insert2(key, value, current->right, smallerNodes);
  }
  (current->size)++;
  updateHeight(current);
  int balanceFactor = getBalance(current);
  if(balanceFactor>1 || balanceFactor<-1)
    doBalance(current, balanceFactor);
  return smallerNodes;
}

template <class Key, class Value>
long long AVL<Key,Value>::insert2(Key key, Value value)
{
  if(root==nullptr)
  {
    put(key, value);
    return 0;
  }
  else
  {
    long long ans = 0;
    ans = insert2(key, value, root, ans);
    return ans;
  }
}

int main()
{
  int n;
  cin >> n;
  LinearList<long long> list(n+1);
  for(int i=0; i<n; ++i)
    cin >> list[i];
  LinearList<long long> smallerNodes(n+1);
  AVL<long long, long long> tree;
  long long ans = 0;
  for(int i=n-1; i>=0; --i)
    smallerNodes[i]=tree.insert2(list[i], list[i]);
  for(int i=0; i<n; ++i)
    cout << smallerNodes[i] << " ";
  cout << endl;


}
