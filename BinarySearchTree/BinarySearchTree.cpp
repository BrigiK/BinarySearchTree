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

	while (true)
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
	return false;
}

void BinarySearchTree::remove(int value)
{
}

int BinarySearchTree::size()
{
	int count = 0;

	std::stack<BinarySearchTree::Node*> stack;
	BinarySearchTree::Node* currentNode = m_root;

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