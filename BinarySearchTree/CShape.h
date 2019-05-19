#pragma once
#include <string>

class CShape
{
public:
	virtual std::string Name() const;
	virtual double GetSurfaceArea() const = 0;

protected:
	std::string m_name;
};