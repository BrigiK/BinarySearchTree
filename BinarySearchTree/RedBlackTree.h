#pragma once
#include <iostream>

class RedBlackTree
{
private:
	struct Node
	{
		enum class Color : char
		{
			Red,
			Black
		};

		Node(int value, Node::Color color) : value(value), color(color), left(nullptr), right(nullptr), parent(nullptr) {}
		Node(const Node &node) = delete;
		Node& operator=(const Node &node) = delete;
		~Node();

		int value;
		Node::Color color;
		Node* left;
		Node* right;
		Node* parent;
	};

public:
	RedBlackTree();

	RedBlackTree(const RedBlackTree &redBlackTree) = delete;

	RedBlackTree& operator=(const RedBlackTree &redBlackTree) = delete;

	~RedBlackTree();

	void rotateLeft(Node* currentNode, Node* currentNodeParent);

	void rotateRight(Node* currentNode, Node* currentNodeParent);

	void rearrange(Node* currentNode);

	void insert(int value);

	bool exists(int value);

	Node* find(int value);

	void remove(int value);

	int size();

	std::pair<Node*, Node*> min(Node* node, Node* parent);

	friend void operator<<(std::ostream& os, const RedBlackTree& redBlackTree);

private:
	Node* m_root;

};