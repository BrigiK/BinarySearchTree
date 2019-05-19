#pragma once
#include "CShape.h"
#include <string>

class CSquare : public CShape
{
public:
	CSquare(std::string name, double width);
	double GetSurfaceArea() const;

private:
	double m_width;
};