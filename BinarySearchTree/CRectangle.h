#pragma once
#include "CShape.h"
#include <string>

class CRectangle : public CShape
{
public:
	CRectangle(std::string name, double l1, double l2);
	double GetSurfaceArea() const;

private:
	double m_l1;
	double m_l2;
};