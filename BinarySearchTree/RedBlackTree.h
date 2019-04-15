#pragma once
#include <iostream>
#include<stack>

template <class KeyType, class ValueType>
class RedBlackTreePrivate;

template <class KeyType, class ValueType>
class RedBlackTree
{
public:
	struct Node
	{
		enum class Color : char
		{
			Red,
			Black
		};

		Node(KeyType key, ValueType value, Node::Color color) : key(key), value(value), color(color), left(nullptr), right(nullptr), parent(nullptr) {}
		Node(const Node &node) = delete;
		Node& operator=(const Node &node) = delete;
		~Node();

		KeyType key;
		ValueType value;
		Node::Color color;
		Node* left;
		Node* right;
		Node* parent;
	};

	RedBlackTree();
	RedBlackTree(const RedBlackTree &redBlackTree) = delete;
	RedBlackTree& operator=(const RedBlackTree &redBlackTree) = delete;
	~RedBlackTree();

	Node* insert(KeyType key, ValueType value = ValueType());
	bool exists(KeyType key) const;
	Node* find(KeyType key) const;
	static Node* min(Node* node);
	static Node* successor(Node* node);
	void remove(KeyType key);
	int size() const;
	Node* getMinNode();
	Node* getMaxNode();

	friend void operator<<(std::ostream& os, const RedBlackTree<KeyType, ValueType>& redBlackTree)
	{
		std::stack<RedBlackTree<KeyType, ValueType>::Node*> stack;
		RedBlackTree<KeyType, ValueType>::Node* currentNode = redBlackTree.m_root;

		while (!stack.empty() || currentNode != nullptr)
		{
			while (currentNode != nullptr)
			{
				stack.push(currentNode);
				currentNode = currentNode->left;
			}

			if (!stack.empty())
			{
				RedBlackTree<KeyType, ValueType>::Node* top = stack.top();
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

	friend class RedBlackTreePrivate<KeyType, ValueType>;
};

// Use this class only for unit testing
template <class KeyType, class ValueType>
class RedBlackTreePrivate
{
public:
	static void RotateLeftRoot(RedBlackTree<KeyType, ValueType>& tree)
	{
		tree.rotateLeft(tree.m_root);
	}

	static void RotateLeftRootLeft(RedBlackTree<KeyType, ValueType>& tree)
	{
		tree.rotateLeft(tree.m_root->left);
	}

	static void RotateRightRoot(RedBlackTree<KeyType, ValueType>& tree)
	{
		tree.rotateRight(tree.m_root);
	}

	static void RotateRightRootRight(RedBlackTree<KeyType, ValueType>& tree)
	{
		tree.rotateRight(tree.m_root->right);
	}
};

template <class KeyType, class ValueType>
RedBlackTree<KeyType, ValueType>::Node::~Node()
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

template <class KeyType, class ValueType>
RedBlackTree<KeyType, ValueType>::RedBlackTree() : m_root(nullptr)
{
}

template <class KeyType, class ValueType>
RedBlackTree<KeyType, ValueType>::~RedBlackTree()
{
	if (m_root)
	{
		delete m_root;
	}
}

template <class KeyType, class ValueType>
typename RedBlackTree<KeyType, ValueType>::Node* RedBlackTree<KeyType, ValueType>::insert(KeyType key, ValueType value) //!!!!!!
{
	if (m_root == nullptr)
	{
		m_root = new Node(key, value, Node::Color::Black);
		return m_root;
	}

	Node* currentNode = m_root;

	if (currentNode->key == key)
	{
		return currentNode;
	}

	Node* newNode = nullptr;

	while (currentNode->key != key)
	{
		if (key < currentNode->key)
		{
			if (currentNode->left == nullptr)
			{
				newNode = new Node(key, value, RedBlackTree::Node::Color::Red);
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
				newNode = new Node(key, value, RedBlackTree::Node::Color::Red);
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
	return newNode;
}

template <class KeyType, class ValueType>
bool RedBlackTree<KeyType, ValueType>::exists(KeyType key) const
{
	if (find(key))
	{
		return true;
	}

	return false;
}

template <class KeyType, class ValueType>
typename RedBlackTree<KeyType, ValueType>::Node* RedBlackTree<KeyType, ValueType>::find(KeyType key) const
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

template <class KeyType, class ValueType>
typename RedBlackTree<KeyType, ValueType>::Node* RedBlackTree<KeyType, ValueType>::min(Node* node)
{
	Node* currentNode = node;

	while (currentNode->left != nullptr)
	{
		currentNode = currentNode->left;
	}

	return currentNode;
}

template <class KeyType, class ValueType>
typename RedBlackTree<KeyType, ValueType>::Node* RedBlackTree<KeyType, ValueType>::successor(Node* node)
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

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::remove(KeyType key)
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

template <class KeyType, class ValueType>
int RedBlackTree<KeyType, ValueType>::size() const
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

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::rotateLeft(Node* currentNode)
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

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::rotateRight(Node* currentNode)
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

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::rearrange(Node* currentNode)
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

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::fixStructure(Node* node)
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

template<class KeyType, class ValueType>
typename RedBlackTree<KeyType, ValueType>::Node * RedBlackTree<KeyType, ValueType>::getMinNode()
{
	return min(m_root);
}

template<class KeyType, class ValueType>
typename RedBlackTree<KeyType, ValueType>::Node * RedBlackTree<KeyType, ValueType>::getMaxNode()
{
	Node* currentNode = m_root;

	while (currentNode->right != nullptr)
	{
		currentNode = currentNode->right;
	}

	return currentNode;
}