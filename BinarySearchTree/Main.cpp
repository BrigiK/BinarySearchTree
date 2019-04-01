#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree binarySearchTree;
	binarySearchTree.insert(9);
	binarySearchTree.insert(15);
	binarySearchTree.insert(21);
	binarySearchTree.insert(2);
	binarySearchTree.insert(4);
	binarySearchTree.insert(6);
	binarySearchTree.insert(14);
	binarySearchTree.insert(1);

	std::cout << binarySearchTree;
	return 0;
}