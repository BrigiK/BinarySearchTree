#pragma once

class BinarySearchTree
{
private:
	struct Node
	{
		Node() : value(0), left(nullptr), right(nullptr) {}

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

	void printLRR();

private:
	Node* root;

};