#include "RedBlackTree.h"

#include <stack>

RedBlackTree::RedBlackTree() : m_root(nullptr)
{
}

RedBlackTree::~RedBlackTree()
{
	if (m_root)
	{
		delete m_root;
		m_root = nullptr;
	}
}

RedBlackTree::Node::~Node()
{
	if (left)
	{
		delete left;
		left = nullptr;
	}
	if (right)
	{
		delete right;
		right = nullptr;
	}
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

	while (currentNode->value != value)
	{
		if (value < currentNode->value)
		{
			if (currentNode->left == nullptr)
			{
				newNode = new Node(value, RedBlackTree::Node::Color::Red);
				currentNode->left = newNode;
				newNode->parent = currentNode;
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
				newNode = new Node(value, RedBlackTree::Node::Color::Red);
				currentNode->right = newNode;
				newNode->parent = currentNode;
				break;
			}
			else
			{
				currentNode = currentNode->right;
			}
		}
	}
	rearrange(newNode);
}

bool RedBlackTree::exists(int value)
{
	if (find(value))
	{
		return true;
	}

	return false;
}

RedBlackTree::Node* RedBlackTree::find(int value)
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

RedBlackTree::Node* RedBlackTree::min(Node* node)
{
	Node* currentnode = node;

	while (currentnode->left != nullptr)
	{
		currentnode = currentnode->left;
	}

	return currentnode;
}

void RedBlackTree::remove(int value)
{
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

void RedBlackTree::rotateLeft(Node* currentNode)
{
	if (currentNode->right == nullptr)
	{
		return;
	}

	Node* currentNodeRight = currentNode->right;

	if (currentNode->parent == nullptr)
	{
		m_root = currentNodeRight;
	}
	else if (currentNode == currentNode->parent->left)
	{
		currentNode->parent->left = currentNodeRight;
	}
	else
	{
		currentNode->parent->right = currentNodeRight;
	}
	currentNodeRight->parent = currentNode->parent;

	currentNode->right = currentNodeRight->left;
	if(currentNodeRight->left)
		currentNodeRight->left->parent = currentNode;

	currentNodeRight->left = currentNode;
	currentNode->parent = currentNodeRight;
}

void RedBlackTree::rotateRight(Node* currentNode)
{
	if (currentNode->left == nullptr)
	{
		return;
	}

	auto currentNodeLeft = currentNode->left;

	if (currentNode->parent == nullptr)
	{
		m_root = currentNodeLeft;
	}
	else if (currentNode == currentNode->parent->left)
	{
		currentNode->parent->left = currentNodeLeft;
	}
	else
	{
		currentNode->parent->right = currentNodeLeft;
	}
	currentNodeLeft->parent = currentNode->parent;

	currentNode->left = currentNodeLeft->right;
	if(currentNodeLeft->right)
		currentNodeLeft->right->parent = currentNode;

	currentNodeLeft->right = currentNode;
	currentNode->parent = currentNodeLeft;
}

void RedBlackTree::rearrange(Node* currentNode)
{	
	while (currentNode->parent != nullptr && currentNode->parent->color == Node::Color::Red)
	{
		Node* grandParent = currentNode->parent->parent;
		if (grandParent == nullptr)
			break;

		if (currentNode->parent == grandParent->left)
		{
			Node* uncle = grandParent->right;
			if (uncle && uncle->color == Node::Color::Red)
			{
				currentNode->parent->color = Node::Color::Black;
				uncle->color = Node::Color::Black;
				grandParent->color = Node::Color::Red;
				currentNode = grandParent;
			}
			else
			{
				if (currentNode == currentNode->parent->right)
				{
					// crt becomes parent; parent becomes crt; really
					currentNode = currentNode->parent;
					rotateLeft(currentNode);
				}

				currentNode->parent->color = Node::Color::Black;
				grandParent->color = Node::Color::Red;
				rotateRight(currentNode->parent->parent);
			}
		}
		else
		{
			Node* uncle = grandParent->left;
			if (uncle && uncle->color == Node::Color::Red)
			{
				currentNode->parent->color = Node::Color::Black;
				uncle->color = Node::Color::Black;
				grandParent->color = Node::Color::Red;
				currentNode = grandParent;
			}
			else
			{
				if (currentNode == currentNode->parent->left)
				{
					// crt becomes parent; parent becomes crt; really
					currentNode = currentNode->parent;
					rotateRight(currentNode);
				}

				currentNode->parent->color = Node::Color::Black;
				grandParent->color = Node::Color::Red;
				rotateLeft(currentNode->parent->parent);
			}
		}
	}

	m_root->color = Node::Color::Black;
}
