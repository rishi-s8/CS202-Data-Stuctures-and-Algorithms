/*
  * CS202 Assignment 2
  * Author: Rishi Sharma (B17138)
  * main.cpp - To evaluate queries on all trees.
  * Usage: ./trees tree-name
  * Data-Type: Change the typedef Statements for KEY and VALUE.
*/

#include "AVL.hpp"
#include "RBTree.hpp"
#include "BSTree.hpp"
#include "BinaryTree.hpp"


template<class TREE, class KEY>
void evaluate(TREE t, KEY k)
{
  int q;
  cin >> q;
  int option;
  KEY x;
  while(q--)
  {
    cin >> option;
    switch(option)
    {
      case 1:
        cin >> x;
        t.put(x, 0);
        break;
      case 2:
        cin >> x;
        t.remove(x);
        break;
      case 3:
        cin >> x;
        cout << t.has(x) << endl;
        break;
      case 4:
        cout << t.maximum() << endl;
        break;
      case 5:
        cout << t.minimum() << endl;
        break;
    }
  }
}



int main(int argc, char *argv[])
{
  if(argc<2)
  {
    cout << "Usage:  ./trees tree-name\n";
    return -1;
  }
  typedef int KEY;
  typedef int VALUE;
  string tree = argv[1];
  if(tree == "bst")
  {
    BSTree<KEY, VALUE> bst;
    evaluate(bst, KEY());
  }
  else if(tree == "avl")
  {
    AVL<KEY, VALUE> avl;
    evaluate(avl, KEY());

  }
  else if(tree == "rbt")
  {
    RBTree<KEY, VALUE> rbt;
    evaluate(rbt, KEY());
  }
  else if(tree == "bt")
  {
    BinaryTree<KEY, VALUE> bt;
    evaluate(bt, KEY());
  }
  return 0;
}
