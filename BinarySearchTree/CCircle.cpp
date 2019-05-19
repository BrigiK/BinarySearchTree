#include "CCircle.h"
#define _USE_MATH_DEFINES
#include <math.h>

CCircle::CCircle(std::string name, double radius)
{
	m_name = name;
	m_radius = radius;
}

double CCircle::GetSurfaceArea() const
{
	return M_PI * m_radius * m_radius;
}
