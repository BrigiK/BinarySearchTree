#pragma once
#include <iostream>

class BinarySearchTree
{
private:
	struct Node
	{
		Node(int value) : value(value), left(nullptr), right(nullptr) {}

		int value;
		Node* left;
		Node* right;
	};

public:
	BinarySearchTree();

	void insert(int value);

	bool exists(int value);

	void remove(int value);

	int size();

	friend void operator<<(std::ostream& os, const BinarySearchTree& binSearchTree);

private:
	Node* m_root;

};