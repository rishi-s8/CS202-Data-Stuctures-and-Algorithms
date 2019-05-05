/*
  * CS202 Assignment 2
  * Author: Rishi Sharma (B17138)
  * prob1.cpp - Solution to Problem-1
  * Input:
  *         n - Number of values
  *         n space seperated values
*/

#include <iostream>
#include "seqLinearList.hpp"
#include "AVL.hpp"

template <class Key, class Value>
void AVL<Key,Value>::insert1(Key key, Value value, BinaryNode<Key, Value>* current, LinearList<Value>& indexOfGreater)
{
  if(key<current->key)
  {
    Value nearestRight = (current->right==nullptr) ? current->val : current->right->maxValue;
    nearestRight = max(nearestRight,current->val);
    Value distanceCurrent = indexOfGreater[value] - value;
    distanceCurrent *= (distanceCurrent<0) ? -1 : 1;
    Value distanceNew = nearestRight - value;
    distanceNew *= (distanceNew<0) ? -1 : 1;
    if(distanceNew<distanceCurrent)
      indexOfGreater[value] = nearestRight;

    if(current->left==nullptr)
    {
      ++elements;
      current->left = new BinaryNode<Key,Value>(key, value);
      current->left->parent = current;
    }
    else
      insert1(key, value, current->left, indexOfGreater);
  }
  else
  {
    // cout << "Here.." << endl;
    if(current->right==nullptr)
    {
      // cout << "Inserting: " << key << " as right child of: " << current->key << endl;
      ++elements;
      current->right = new BinaryNode<Key,Value>(key, value);
      current->right->parent = current;
    }
    else
      insert1(key, value, current->right, indexOfGreater);
  }
  (current->size)++;
  // cout << "Updated size of: " << current->key << endl;
  updateHeight(current);
  int balanceFactor = getBalance(current);
  if(balanceFactor>1 || balanceFactor<-1)
  {
    doBalance(current, balanceFactor);
    // cout << "Done balancing." << endl;
  }
}

template <class Key, class Value>
void AVL<Key,Value>::insert1(Key key, Value value, LinearList<Value>& indexOfGreater)
{
  if(root==nullptr)
  {
    put(key, value);
  }
  else
  {
    insert1(key, value, root, indexOfGreater);
  }
}


void calculateDistanceLeft(LinearList<long long>& list, LinearList<long long>& distance, long long n )
{
  AVL<long long, long long> tree;
  LinearList<long long> indexOfGreater(n);
  for(int i=0; i<n; ++i) indexOfGreater[i] = INT_MAX, distance[i]=INT_MAX;
  for(int i=0; i<n; ++i)
    tree.insert1(list[i], i, indexOfGreater);
  for(int i = 0; i<n; ++i)
  {
    distance[i] = (indexOfGreater[i] == INT_MAX) ? INT_MAX : i - indexOfGreater[i];
    distance[i] *= (distance[i] < 0) ? -1 : 1;
  }
}

int main()
{
  int n;
  cin >> n;
  LinearList<long long> list(n);
  for(int i=0; i<n; ++i)
    cin >> list[i];


  // Calculating previous Greater element from left to right
  LinearList<long long> distanceLeft(n);
  calculateDistanceLeft(list, distanceLeft, n);



  // Calculating previous Greater element from right to left
  LinearList<long long> listReverse(n);
  for(int i=0; i<n; ++i)
    listReverse[i] = list[n-i-1];

  LinearList<long long> distanceRight(n);
  calculateDistanceLeft(listReverse, distanceRight, n);

  for(int i=0; i<n; ++i)
  {
    long long distance = min(distanceLeft[i], distanceRight[n-i-1]);
    if(distance == INT_MAX)
      cout << -1 << " ";
    else
      cout << distance << " ";
  }
  cout << endl;

}
