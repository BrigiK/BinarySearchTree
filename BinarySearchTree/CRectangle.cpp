#include "CRectangle.h"

CRectangle::CRectangle(std::string name, double l1, double l2)
{
	m_name = name;
	m_l1 = l1;
	m_l2 = l2;
}

double CRectangle::GetSurfaceArea() const
{
	return m_l1 * m_l2;
}
