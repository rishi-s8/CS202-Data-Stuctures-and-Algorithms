trees:	RBTree.hpp BSTree.hpp BinaryTree.hpp AVL.hpp main.cpp
					g++ -o trees main.cpp
BinaryTreeMain :	BinaryTreeMain.cpp BinaryTree.hpp seqLinearList.hpp seqLinearList.cpp
					g++ -o BinaryTreeMain BinaryTreeMain.cpp
BSTreeMain:	BSTreeMain.cpp BSTree.hpp BinaryTree.hpp seqLinearList.hpp seqLinearList.cpp
					g++ -o BSTreeMain BSTreeMain.cpp
AVLMain:	AVLMain.cpp AVL.hpp BSTree.hpp BinaryTree.hpp seqLinearList.hpp seqLinearList.cpp
					g++ -o AVLMain AVLMain.cpp
RBTreeMain:	RBTreeMain.cpp RBTree.hpp BSTree.hpp BinaryTree.hpp seqLinearList.hpp seqLinearList.cpp
					g++ -o RBTreeMain RBTreeMain.cpp
prob1:	prob1.cpp AVLMain.cpp AVL.hpp BSTree.hpp BinaryTree.hpp seqLinearList.hpp seqLinearList.cpp
					g++ -o prob1 prob1.cpp
prob2:	prob2.cpp AVLMain.cpp AVL.hpp BSTree.hpp BinaryTree.hpp seqLinearList.hpp seqLinearList.cpp
					g++ -o prob2 prob2.cpp
clean :
					rm trees BinaryTreeMain BSTreeMain AVLMain RBTreeMain prob1 prob2
