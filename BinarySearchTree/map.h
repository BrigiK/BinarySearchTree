#pragma once
#include "RedBlackTree.h"
#include <string>

namespace kb
{
	template <class KeyType, class ValueType>
	class map
	{
	public:
		class iterator
		{
		public:
			iterator(typename RedBlackTree<KeyType, ValueType>::Node* node) : m_node(node)
			{
				if (node)
				{
					m_currentValue = std::make_pair(node->key, node->value);
				}
			}
			const std::pair<KeyType, ValueType>& operator*();
			const std::pair<KeyType, ValueType>* operator->();
			bool operator!=(const iterator& other);
			iterator& operator++();

		private:
			typename RedBlackTree<KeyType, ValueType>::Node* m_node;
			std::pair<KeyType, ValueType> m_currentValue;
		};

		void insert(KeyType key, ValueType value);
		ValueType& operator[](KeyType key);
		bool exists(KeyType key) const;
		void remove(KeyType key);
		int size() const;
		iterator begin();
		iterator end();

	private:
		RedBlackTree<KeyType, ValueType> m_tree;
	};

	template<class KeyType, class ValueType>
	const std::pair<KeyType, ValueType>& map<KeyType, ValueType>::iterator::operator*()
	{
		return m_currentValue;
	}

	template<class KeyType, class ValueType>
	const std::pair<KeyType, ValueType>* map<KeyType, ValueType>::iterator::operator->()
	{
		return &m_currentValue;
	}

	template<class KeyType, class ValueType>
	bool map<KeyType, ValueType>::iterator::operator!=(const iterator & other)
	{
		return m_node != other.m_node;
	}

	template<class KeyType, class ValueType>
	typename map<KeyType, ValueType>::iterator& map<KeyType, ValueType>::iterator::operator++()
	{
		m_node = RedBlackTree<KeyType, ValueType>::successor(m_node);

		if (m_node)
		{
			m_currentValue = std::make_pair(m_node->key, m_node->value);
		}

		return *this;
	}

	template<class KeyType, class ValueType>
	void map<KeyType, ValueType>::insert(KeyType key, ValueType value)
	{
		m_tree.insert(key, value);
	}

	template<class KeyType, class ValueType>
	ValueType& map<KeyType, ValueType>::operator[](KeyType key)
	{
		auto nodeFound = m_tree.find(key);
		if(nodeFound != nullptr)
		{
			return nodeFound->value;
		}
		else
		{
			auto newNode = m_tree.insert(key);
			return newNode->value;
		}
	}

	template<class KeyType, class ValueType>
	bool map<KeyType, ValueType>::exists(KeyType key) const
	{
		return m_tree.exists(key);
	}

	template<class KeyType, class ValueType>
	void map<KeyType, ValueType>::remove(KeyType key)
	{
		m_tree.remove(key);
	}

	template<class KeyType, class ValueType>
	int map<KeyType, ValueType>::size() const
	{
		return m_tree.size();
	}

	template<class KeyType, class ValueType>
	typename map<KeyType, ValueType>::iterator map<KeyType, ValueType>::begin()
	{
		return iterator(m_tree.getMinNode());
	}

	template<class KeyType, class ValueType>
	typename map<KeyType, ValueType>::iterator map<KeyType, ValueType>::end()
	{
		return iterator(nullptr);
	}
}