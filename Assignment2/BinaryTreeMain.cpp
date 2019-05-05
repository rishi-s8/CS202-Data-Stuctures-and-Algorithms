/*
  * CS202 Assignment 2
  * Author: Rishi Sharma (B17138)
  * BinaryTreeMain.cpp - To evaluate queries on Binary Trees.
*/

#include "BinaryTree.hpp"

void printMenu()
{
  cout << endl << endl;
  cout << "[1 x y] Insert (x,y) in the tree." << endl;
  cout << "[2 x] Remove x from the tree." << endl;
  cout << "[3 x] Find x in the tree." << endl;
  cout << "[4] Print Value of maximum element in the tree." << endl;
  cout << "[5] Print Value of minimum element in the tree." << endl;
  cout << "[6] Print Pre_Order_Traversal of the tree." << endl;
  cout << "[7] Print In_Order_Traversal of the tree." << endl;
  cout << "[8] Print Post_Order_Traversal of the tree." << endl;
  cout << "[9 x] Get Value corresponding to x in the tree." << endl;
  cout << "[10 x] Get successor of x in the tree." << endl;
  cout << "[11 x] Get predecessor of x in the tree." << endl;
}


int main()
{

  BinaryTree<int, string> tree;
  int queries;
  cout << "Enter Number of Queries: ";
  cin >> queries;
  int decision, x;
  string y;
  while(queries--)
  {
    printMenu();
    cin >> decision;
    switch (decision) {
      case 1:
        cin >> x >> y;
        tree.put(x,y);
        break;
      case 2:
        cin >> x;
        tree.remove(x);
        break;
      case 3:
        cin >> x;
        cout << tree.has(x) << endl;
        break;
      case 4:
        cout << tree.maximum() << endl;
        break;
      case 5:
        cout << tree.minimum() << endl;
        break;
      case 6:
        tree.print_pre_order();
        break;
      case 7:
        tree.print_in_order();
        break;
      case 8:
        tree.print_post_order();
        break;
      case 9:
        cin >> x;
        cout << tree.get(x) << endl;
        break;
      case 10:
        cin >> x;
        cout << tree.successor(x) << endl;
        break;
      case 11:
        cin >> x;
        cout << tree.predecessor(x) << endl;
        break;
      default:
        cout << "Invalid Query.\n";
        break;
    }
  }
  return 0;
}
