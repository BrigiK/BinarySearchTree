#include "BinarySearchTree.h"

#include <stack> 

BinarySearchTree::BinarySearchTree() : m_root(nullptr)
{
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

bool BinarySearchTree::exists(int value)
{
	std::stack<Node*> stack;
	Node* currentNode = m_root;

	while (!stack.empty() || currentNode != nullptr)
	{
		while (currentNode != nullptr)
		{
			stack.push(currentNode);

			if (currentNode->value == value)
			{
				return true;
			}

			currentNode = currentNode->left;
		}

		if (!stack.empty())
		{
			BinarySearchTree::Node* top = stack.top();
			stack.pop();
			currentNode = top->right;
		}
	}

	return false;
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
	
	while (true)
	{
		if (value < currentNode->value)
		{
			if (currentNode->left->value == value)
			{
				// has one child
				auto currentsLeft = currentNode->left;
				if (currentsLeft->left != nullptr)
				{
					currentNode->left = currentsLeft->left;
					break;
				}
				if (currentsLeft->right != nullptr)
				{
					currentNode->left = currentsLeft->right;
					break;
				}
				// is a leaf
				else
				{
					currentNode->left = nullptr;
					break;
				}
			}
			else
			{
				currentNode = currentNode->left;
			}
		}

		if (value > currentNode->value)
		{
			if (currentNode->right->value == value)
			{
				// has one child
				auto currentsRight = currentNode->right;
				if (currentsRight->right != nullptr)
				{
					currentNode->right = currentsRight->right;
					break;
				}
				if (currentsRight->left != nullptr)
				{
					currentNode->right = currentsRight->left;
					break;
				}
				// is a leaf
				else
				{
					currentNode->right = nullptr;
					break;
				}
			}
			else
			{
				currentNode = currentNode->right;
			}
		}
	}

	// Node to be deleted has two children: Find inorder successor of the node. Copy contents 
	// of the inorder successor to the node and delete the inorder successor. Note that inorder 
	// predecessor can also be used.
}

int BinarySearchTree::size()
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