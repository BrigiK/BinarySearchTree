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
	}
}

RedBlackTree::Node::~Node()
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

bool RedBlackTree::exists(int value) const
{
	if (find(value))
	{
		return true;
	}

	return false;
}

RedBlackTree::Node* RedBlackTree::find(int value) const
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
	Node* currentNode = node;

	while (currentNode->left != nullptr)
	{
		currentNode = currentNode->left;
	}

	return currentNode;
}

RedBlackTree::Node* RedBlackTree::successor(Node* node)
{
	if (node->right != nullptr)
	{
		return min(node->right);
	}

	Node* successor = node->parent;

	while (successor != nullptr && node == successor->right)
	{
		node = successor;
		successor = successor->parent;
	}

	return successor;
}

void RedBlackTree::fixStructure(Node* node)
{
	Node* uncle = nullptr;
	while (node != m_root && node->color == Node::Color::Black)
	{
		if (node == node->parent->left)
		{
			// uncl?
			uncle = node->parent->right;

			if (uncle->color == Node::Color::Red)
			{
				uncle->color = Node::Color::Black;
				node->parent->color = Node::Color::Red;
				rotateLeft(node->parent);
				uncle = node->parent->right;
			}

			// uncl?
			if ((uncle->left == nullptr || uncle->left->color == Node::Color::Black) &&
				(uncle->right == nullptr || uncle->right->color == Node::Color::Black))
			{
				uncle->color = Node::Color::Red;
				node = node->parent;
			}
			else
			{
				if (uncle->right == nullptr || uncle->right->color == Node::Color::Black)
				{
					if(uncle->left != nullptr)
					{
						uncle->left->color = Node::Color::Black;
					}
					
					uncle->color = Node::Color::Red;
					rotateRight(uncle);
					// uncl?
					uncle = node->parent->right;
				}
				uncle->color = node->parent->color;
				node->parent->color = Node::Color::Black;
				if (uncle->right != nullptr)
				{
					uncle->right->color = Node::Color::Black;
				}
				rotateLeft(node->parent);
				node = m_root;
			}
		}
		else
		{
			if (node == node->parent->right)
			{
				uncle = node->parent->left;

				if (uncle->color == Node::Color::Red)
				{
					uncle->color = Node::Color::Black;
					node->parent->color = Node::Color::Red;
					rotateRight(node->parent);
					uncle = node->parent->left;
				}
				if ((uncle->right == nullptr || uncle->right->color == Node::Color::Black) && 
					(uncle->left == nullptr || uncle->left->color == Node::Color::Black))
				{
					uncle->color = Node::Color::Red;
					node = node->parent;
				}
				else
				{
					if (uncle->left == nullptr || uncle->left->color == Node::Color::Black)
					{
						if (uncle->right != nullptr)
						{
							uncle->right->color = Node::Color::Black;
						}
						uncle->color = Node::Color::Red;
						rotateLeft(uncle);
						uncle = node->parent->left;
					}
					uncle->color = node->parent->color;
					node->parent->color = Node::Color::Black;
					if (uncle->left != nullptr)
					{
						uncle->left->color = Node::Color::Black;
					}
					rotateRight(node->parent);
					node = m_root;
				}
			}
		}
	}
	node->color = Node::Color::Black;
}

void RedBlackTree::remove(int value)
{
	if (m_root == nullptr)
	{
		return;
	}

	if (!exists(value))
	{
		return;
	}

	Node* crtNode = find(value);
	Node* nodeToBeDeleted = nullptr;
	Node* descendent = nullptr;

	if (crtNode->left == nullptr || crtNode->right == nullptr)
	{
		nodeToBeDeleted = crtNode;
	}
	else
	{
		nodeToBeDeleted = successor(crtNode);
	}

	if (nodeToBeDeleted->left != nullptr)
	{
		descendent = nodeToBeDeleted->left;
	}
	else
	{
		descendent = nodeToBeDeleted->right;
	}

	if (descendent != nullptr)
	{
		descendent->parent = nodeToBeDeleted->parent;
	}

	if (nodeToBeDeleted->parent == nullptr)
	{
		m_root = descendent;
	}
	else
	{
		if (nodeToBeDeleted == nodeToBeDeleted->parent->left)
		{
			nodeToBeDeleted->parent->left = descendent;
		}
		else
		{
			nodeToBeDeleted->parent->right = descendent;
		}
	}

	if (crtNode->value < nodeToBeDeleted->value)
	{
		crtNode->value = nodeToBeDeleted->value;
	}

	if (descendent != nullptr && nodeToBeDeleted->color == Node::Color::Black)
	{
		fixStructure(descendent);
	}

	nodeToBeDeleted->left = nullptr;
	nodeToBeDeleted->right = nullptr;
	delete nodeToBeDeleted;
}

int RedBlackTree::size() const
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
