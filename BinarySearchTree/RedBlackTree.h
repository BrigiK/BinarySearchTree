#pragma once
#include <iostream>

class RedBlackTreePrivate;

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

	void insert(int value);
	bool exists(int value) const;
	Node* find(int value) const;
	static Node* min(Node* node);
	static Node* successor(Node* node);
	void remove(int value);
	int size() const;

	friend void operator<<(std::ostream& os, const RedBlackTree& redBlackTree);

private:
	void rotateLeft(Node* currentNode);
	void rotateRight(Node* currentNode);
	void rearrange(Node* currentNode);
	void fixStructure(Node* node);

private:
	Node* m_root;

	friend class RedBlackTreePrivate;
};


// Use this class only for unit testing
class RedBlackTreePrivate
{
public:
	static void RotateLeftRoot(RedBlackTree& tree)
	{
		tree.rotateLeft(tree.m_root);
	}

	static void RotateLeftRootLeft(RedBlackTree& tree)
	{
		tree.rotateLeft(tree.m_root->left);
	}

	static void RotateRightRoot(RedBlackTree& tree)
	{
		tree.rotateRight(tree.m_root);
	}

	static void RotateRightRootRight(RedBlackTree& tree)
	{
		tree.rotateRight(tree.m_root->right);
	}
};