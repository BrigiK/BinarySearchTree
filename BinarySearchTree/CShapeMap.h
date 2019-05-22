#pragma once
#include "CShape.h"
#include "map.h"

class CShapeMap
{
	// implement an iterator whose * operator returns a shape
public:
	class iterator
	{
	public:
		iterator(kb::map<std::string, CShape*>::iterator& iterator) : m_iterator(iterator)
		{
		}

		const CShape* operator*()
		{
			return m_iterator->second;
		}

		const CShape* operator->()
		{
			return m_iterator->second;
		}

		bool operator!=(const iterator& other)
		{
			return m_iterator != other.m_iterator;
		}

		iterator& operator++()
		{
			++m_iterator;
			return *this;
		}

	private:
		kb::map<std::string, CShape*>::iterator m_iterator;
	};

	void insert(CShape* shape);
	CShape*& operator[](std::string name); 
	iterator begin();
	iterator end();

private:
	kb::map<std::string, CShape*> m_map;
};

void CShapeMap::insert(CShape* shape)
{
	if (!m_map.exists(shape->Name()))
	{
		m_map.insert(shape->Name(), shape);
	}
	else
	{
		auto name = shape->Name();
		delete shape;
		throw std::invalid_argument(std::string("Cannot add duplicate entry: ") + name);
	}
}

CShape*& CShapeMap::operator[](std::string name)
{
	if (m_map.exists(name))
	{
		return m_map[name];
	}
	else
	{
		return m_map[name];
	}
}

typename CShapeMap::iterator CShapeMap::begin()
{
	auto it = m_map.begin();
	return iterator(it);
}

typename CShapeMap::iterator CShapeMap::end()
{
	auto it = m_map.end();
	return iterator(it);
}