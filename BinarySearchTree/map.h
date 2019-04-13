#pragma once
#include "RedBlackTree.h"
#include <string>

namespace kb
{
	template <class KeyType, class ValueType>
	class map
	{
	public:
		void insert(KeyType key, ValueType value);
		ValueType& operator[](KeyType key);
		bool exists(KeyType key) const;
		void remove(KeyType key);
		int size() const;

	private:
		RedBlackTree<KeyType, ValueType> m_tree;
	};

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
	bool kb::map<KeyType, ValueType>::exists(KeyType key) const
	{
		return m_tree.exists(key);
	}

	template<class KeyType, class ValueType>
	void kb::map<KeyType, ValueType>::remove(KeyType key)
	{
		m_tree.remove(key);
	}

	template<class KeyType, class ValueType>
	int kb::map<KeyType, ValueType>::size() const
	{
		return m_tree.size();
	}
}