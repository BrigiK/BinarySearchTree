#include "CSquare.h"

CSquare::CSquare(std::string name, double width)
{
	m_name = name;
	m_width = width;
}

double CSquare::GetSurfaceArea() const
{
	return m_width * m_width;
}
