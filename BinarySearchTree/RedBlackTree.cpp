#include "RedBlackTree.h"

#include <stack>

RedBlackTree::RedBlackTree() : m_root(nullptr)
{
}

RedBlackTree::~RedBlackTree()
{
}

void RedBlackTree::rotateLeft(Node* currentNode, Node* currentNodeParent)
{
	if (currentNode->right == nullptr)
	{
		return;
	}

	Node* currentNodeRight = currentNode->right;

	if (currentNodeParent == nullptr)
	{
		m_root = currentNodeRight;
	}
	else if (currentNode == currentNodeParent->left)
	{
		currentNodeParent->left = currentNodeRight;
	}
	else
	{
		currentNodeParent->right = currentNodeRight;
	}

	currentNode->right = currentNodeRight->left;
	currentNodeRight->left = currentNode;
}

void RedBlackTree::rotateRight(Node* currentNode, Node* currentNodeParent)
{
	if (currentNode->left == nullptr)
	{
		return;
	}

	auto currentNodeLeft = currentNode->left;

	if (currentNodeParent == nullptr)
	{
		m_root = currentNodeLeft;
	}
	else if (currentNode == currentNodeParent->left)
	{
		currentNodeParent->left = currentNodeLeft;
	}
	else
	{
		currentNodeParent->right = currentNodeLeft;
	}

	currentNode->left = currentNodeLeft->right;
	currentNodeLeft->right = currentNode;
}

void RedBlackTree::rearrange(Node * currentNode, Node * currentNodeParent)
{

}

void RedBlackTree::insert(int value)
{
	if (m_root == nullptr)
	{
		m_root = new Node(value, RedBlackTree::Node::Color::Black);
		return;
	}

	Node* currentNode = m_root;

	if (currentNode->value == value)
	{
		return;
	}

	Node* newNode = nullptr;
	Node* newNodeParent = nullptr;

	while (currentNode->value != value)
	{
		if (value < currentNode->value)
		{
			newNodeParent = currentNode;
			if (currentNode->left == nullptr)
			{
				newNode = new Node(value, RedBlackTree::Node::Color::Red);
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
			newNodeParent = currentNode;
			if (currentNode->right == nullptr)
			{
				newNode = new Node(value, RedBlackTree::Node::Color::Red);
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

bool RedBlackTree::exists(int value)
{
	if (find(value))
	{
		return true;
	}

	return false;
}

RedBlackTree::Node * RedBlackTree::find(int value)
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

void RedBlackTree::remove(int value)
{
	rotateRight(m_root->right, m_root);
}

int RedBlackTree::size()
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
			RedBlackTree::Node* top = stack.top();
			stack.pop();
			count++;
			currentNode = top->right;
		}
	}

	return count;
}

std::pair<RedBlackTree::Node*, RedBlackTree::Node*> RedBlackTree::min(Node * node, Node * parent)
{
	return std::pair<Node*, Node*>();
}

void operator<<(std::ostream & os, const RedBlackTree & redBlackTree)
{
	std::stack<RedBlackTree::Node*> stack;
	RedBlackTree::Node* currentNode = redBlackTree.m_root;

	while (!stack.empty() || currentNode != nullptr)
	{
		while (currentNode != nullptr)
		{
			stack.push(currentNode);
			currentNode = currentNode->left;
		}

		if (!stack.empty())
		{
			RedBlackTree::Node* top = stack.top();
			stack.pop();
			os << top->value << " ";
			currentNode = top->right;
		}
	}
}
