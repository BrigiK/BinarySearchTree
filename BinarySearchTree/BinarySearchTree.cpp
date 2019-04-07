#include "BinarySearchTree.h"

#include <stack>

BinarySearchTree::BinarySearchTree() : m_root(nullptr)
{
}

BinarySearchTree::~BinarySearchTree()
{
	if (m_root)
	{
		delete m_root;
		m_root = nullptr;
	}
}

BinarySearchTree::Node::~Node()
{
	if (left)
	{
		delete left;
	}
	if (right)
	{
		delete right;
	}
}

void BinarySearchTree::insert(int value)
{
	if (m_root == nullptr)
	{
		m_root = new Node(value);
		return;
	}
	
	Node* currentNode = m_root;

	if (currentNode->value == value)
	{
		return;
	}

	while (currentNode->value != value)
	{
		if (value < currentNode->value)
		{
			if (currentNode->left == nullptr)
			{
				Node* newNode = new Node(value);
				currentNode->left = newNode;
				break;
			}
			else
			{
				currentNode = currentNode->left;
			}
		}

		if (value > currentNode->value)
		{
			if (currentNode->right == nullptr)
			{
				Node* newNode = new Node(value);
				currentNode->right = newNode;
				break;
			}
			else
			{
				currentNode = currentNode->right;
			}
		}
	}
}

BinarySearchTree::Node* BinarySearchTree::find(int value) const
{
	Node* currentNode = m_root;

	while (currentNode != nullptr && currentNode->value != value)
	{
		if (value < currentNode->value)
		{
			currentNode = currentNode->left;
		}
		else
		{
			currentNode = currentNode->right;
		}
	}

	return currentNode;
}

bool BinarySearchTree::exists(int value) const
{
	if (find(value))
	{
		return true;
	}

	return false;
}

std::pair<BinarySearchTree::Node*, BinarySearchTree::Node*> BinarySearchTree::min(Node* node, Node* parent)
{
	Node* currentNode = node;
	Node* currentParent = parent;

	while (currentNode->left != nullptr)
	{
		currentParent = currentNode;
		currentNode = currentNode->left;
	}
	
	return std::make_pair(currentNode, currentParent);
}

void BinarySearchTree::remove(int value)
{
	if (m_root == nullptr)
	{
		return;
	}

	if (!exists(value))
	{
		return;
	}

	Node* currentNode = m_root;
	Node* currentNodeParent = nullptr;

	// find node to be deleted
	while (currentNode->value != value)
	{
		currentNodeParent = currentNode;

		if (value < currentNode->value)
		{
			currentNode = currentNode->left;
		}
		else
		{
			currentNode = currentNode->right;
		}
	}

	// see if node to be deleted is a leaf
	if (currentNode->left == nullptr && currentNode->right == nullptr)
	{
		if (currentNodeParent->left == currentNode)
		{
			currentNodeParent->left = nullptr;
			currentNode->left = nullptr;
			currentNode->right = nullptr;
			delete currentNode;
			return;
		}
		else if (currentNodeParent->right == currentNode)
		{
			currentNodeParent->right = nullptr;
			currentNode->left = nullptr;
			currentNode->right = nullptr;
			delete currentNode;
			return;
		}
	}

	// see if node to be deleted has only one child
	if (currentNode->left != nullptr && currentNode->right == nullptr)
	{
		currentNode->value = currentNode->left->value;
		currentNode->left = nullptr;
		currentNode->right = nullptr;
		delete currentNode->left;
		return;
	}
	else if (currentNode->left == nullptr && currentNode->right != nullptr)
	{
		currentNode->value = currentNode->right->value;
		currentNode->left = nullptr;
		currentNode->right = nullptr;
		delete currentNode->right;
		return;
	}

	// see if node to be deleted has two children
	if (currentNode->left != nullptr && currentNode->right != nullptr)
	{
		std::pair<Node*, Node*> minNodeAndParent = min(currentNode->right, currentNode);
		Node* minNode = minNodeAndParent.first;
		Node* minNodeParent = minNodeAndParent.second;

		// rewiring
		minNode->left = currentNode->left; // 1
		if (currentNodeParent->left == currentNode) // 2
		{
			currentNodeParent->left = minNode;
		}
		else if (currentNodeParent->right == currentNode)
		{
			currentNodeParent->right = minNode;
		}
		if (minNodeParent != currentNode)
		{
			minNodeParent->left = minNode->right; // 3
			minNode->right = currentNode->right; // 4
		}

		currentNode->left = nullptr;
		currentNode->right = nullptr;
		delete currentNode;
		return;
	}
}

int BinarySearchTree::size() const
{
	int count = 0;

	std::stack<Node*> stack;
	Node* currentNode = m_root;

	while (!stack.empty() || currentNode != nullptr)
	{
		while (currentNode != nullptr)
		{
			stack.push(currentNode);
			currentNode = currentNode->left;
		}

		if (!stack.empty())
		{
			BinarySearchTree::Node* top = stack.top();
			stack.pop();
			count++;
			currentNode = top->right;
		}
	}

	return count;
}

void operator<<(std::ostream & os, const BinarySearchTree & binSearchTree)
{
	std::stack<BinarySearchTree::Node*> stack;
	BinarySearchTree::Node* currentNode = binSearchTree.m_root;

	while (!stack.empty() || currentNode != nullptr)
	{ 
		while (currentNode != nullptr)
		{
			stack.push(currentNode);
			currentNode = currentNode->left;
		}

		if (!stack.empty())
		{
			BinarySearchTree::Node* top = stack.top();
			stack.pop();
			os << top->value << " ";
			currentNode = top->right;
		}
	}
}