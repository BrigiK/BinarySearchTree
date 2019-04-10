#pragma once
#include <iostream>
#include<stack>

template <class KeyType>
class RedBlackTreePrivate;

template <class KeyType>
class RedBlackTree;

template <class KeyType>
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

		Node(KeyType key, Node::Color color) : key(key), color(color), left(nullptr), right(nullptr), parent(nullptr) {}
		Node(const Node &node) = delete;
		Node& operator=(const Node &node) = delete;
		~Node();

		KeyType key;
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

	void insert(KeyType key);
	bool exists(KeyType key) const;
	Node* find(KeyType key) const;
	static Node* min(Node* node);
	static Node* successor(Node* node);
	void remove(KeyType key);
	int size() const;

	friend void operator<<(std::ostream& os, const RedBlackTree<KeyType>& redBlackTree)
	{
		std::stack<RedBlackTree<KeyType>::Node*> stack;
		RedBlackTree<KeyType>::Node* currentNode = redBlackTree.m_root;

		while (!stack.empty() || currentNode != nullptr)
		{
			while (currentNode != nullptr)
			{
				stack.push(currentNode);
				currentNode = currentNode->left;
			}

			if (!stack.empty())
			{
				RedBlackTree<KeyType>::Node* top = stack.top();
				stack.pop();
				os << top->key << " ";
				currentNode = top->right;
			}
		}
	}

private:
	void rotateLeft(Node* currentNode);
	void rotateRight(Node* currentNode);
	void rearrange(Node* currentNode);
	void fixStructure(Node* node);

private:
	Node* m_root;

	friend class RedBlackTreePrivate<KeyType>;
};

// Use this class only for unit testing
template <class KeyType>
class RedBlackTreePrivate
{
public:
	static void RotateLeftRoot(RedBlackTree<KeyType>& tree)
	{
		tree.rotateLeft(tree.m_root);
	}

	static void RotateLeftRootLeft(RedBlackTree<KeyType>& tree)
	{
		tree.rotateLeft(tree.m_root->left);
	}

	static void RotateRightRoot(RedBlackTree<KeyType>& tree)
	{
		tree.rotateRight(tree.m_root);
	}

	static void RotateRightRootRight(RedBlackTree<KeyType>& tree)
	{
		tree.rotateRight(tree.m_root->right);
	}
};

template <class KeyType>
RedBlackTree<KeyType>::Node::~Node()
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

template <class KeyType>
RedBlackTree<KeyType>::RedBlackTree() : m_root(nullptr)
{
}

template <class KeyType>
RedBlackTree<KeyType>::~RedBlackTree()
{
	if (m_root)
	{
		delete m_root;
	}
}

template <class KeyType>
void RedBlackTree<KeyType>::insert(KeyType key)
{
	if (m_root == nullptr)
	{
		m_root = new Node(key, Node::Color::Black);
		return;
	}

	Node* currentNode = m_root;

	if (currentNode->key == key)
	{
		return;
	}

	Node* newNode = nullptr;

	while (currentNode->key != key)
	{
		if (key < currentNode->key)
		{
			if (currentNode->left == nullptr)
			{
				newNode = new Node(key, RedBlackTree::Node::Color::Red);
				currentNode->left = newNode;
				newNode->parent = currentNode;
				break;
			}
			else
			{
				currentNode = currentNode->left;
			}
		}

		if (key > currentNode->key)
		{
			if (currentNode->right == nullptr)
			{
				newNode = new Node(key, RedBlackTree::Node::Color::Red);
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

template <class KeyType>
bool RedBlackTree<KeyType>::exists(KeyType key) const
{
	if (find(key))
	{
		return true;
	}

	return false;
}

template <class KeyType>
typename RedBlackTree<KeyType>::Node* RedBlackTree<KeyType>::find(KeyType key) const
{
	Node* currentNode = m_root;

	while (currentNode != nullptr && currentNode->key != key)
	{
		if (key < currentNode->key)
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

template <class KeyType>
typename RedBlackTree<KeyType>::Node* RedBlackTree<KeyType>::min(Node* node)
{
	Node* currentNode = node;

	while (currentNode->left != nullptr)
	{
		currentNode = currentNode->left;
	}

	return currentNode;
}

template <class KeyType>
typename RedBlackTree<KeyType>::Node* RedBlackTree<KeyType>::successor(Node* node)
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

template <class KeyType>
void RedBlackTree<KeyType>::remove(KeyType key)
{
	if (m_root == nullptr)
	{
		return;
	}

	if (!exists(key))
	{
		return;
	}

	Node* crtNode = find(key);
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

	if (crtNode->key < nodeToBeDeleted->key)
	{
		crtNode->key = nodeToBeDeleted->key;
	}

	if (descendent != nullptr && nodeToBeDeleted->color == Node::Color::Black)
	{
		fixStructure(descendent);
	}

	nodeToBeDeleted->left = nullptr;
	nodeToBeDeleted->right = nullptr;
	delete nodeToBeDeleted;
}

template <class KeyType>
int RedBlackTree<KeyType>::size() const
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

template <class KeyType>
void RedBlackTree<KeyType>::rotateLeft(Node* currentNode)
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
	if (currentNodeRight->left)
		currentNodeRight->left->parent = currentNode;

	currentNodeRight->left = currentNode;
	currentNode->parent = currentNodeRight;
}

template <class KeyType>
void RedBlackTree<KeyType>::rotateRight(Node* currentNode)
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
	if (currentNodeLeft->right)
		currentNodeLeft->right->parent = currentNode;

	currentNodeLeft->right = currentNode;
	currentNode->parent = currentNodeLeft;
}

template <class KeyType>
void RedBlackTree<KeyType>::rearrange(Node* currentNode)
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

template <class KeyType>
void RedBlackTree<KeyType>::fixStructure(Node* node)
{
	Node* uncle = nullptr;
	while (node != m_root && node->color == Node::Color::Black)
	{
		if (node == node->parent->left)
		{
			uncle = node->parent->right;

			if (uncle->color == Node::Color::Red)
			{
				uncle->color = Node::Color::Black;
				node->parent->color = Node::Color::Red;
				rotateLeft(node->parent);
				uncle = node->parent->right;
			}

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
					if (uncle->left != nullptr)
					{
						uncle->left->color = Node::Color::Black;
					}

					uncle->color = Node::Color::Red;
					rotateRight(uncle);
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