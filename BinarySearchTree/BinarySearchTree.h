#pragma once
#include <iostream>

class BinarySearchTree
{
private:
	struct Node
	{
		Node(int value) : value(value), left(nullptr), right(nullptr) {}
		Node(const Node &node) = delete;
		Node& operator=(const Node &node) = delete;
		~Node();

		int value;
		Node* left;
		Node* right;
	};

public:
	BinarySearchTree();

	BinarySearchTree(const BinarySearchTree &binarySearchTree) = delete;

	BinarySearchTree& operator=(const BinarySearchTree &binarySearchTree) = delete;
	
	~BinarySearchTree();

	void insert(int value);

	bool exists(int value) const;

	Node* find(int value) const;

	void remove(int value);

	int size() const;

	static std::pair<Node*, Node*> min(Node* node, Node* parent);

	friend void operator<<(std::ostream& os, const BinarySearchTree& binSearchTree);

	Node* successor(Node* node);

private:
	Node* m_root;

};