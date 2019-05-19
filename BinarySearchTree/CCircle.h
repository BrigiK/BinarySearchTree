#pragma once
#include "CShape.h"
#include <string>

class CCircle : public CShape
{
public:
	CCircle(std::string name, double radius);
	double GetSurfaceArea() const;

private:
	double m_radius;
};
