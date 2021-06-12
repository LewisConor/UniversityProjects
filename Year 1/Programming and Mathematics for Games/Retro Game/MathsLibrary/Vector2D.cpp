#include "Vector2D.h"

#include <cmath>

Vector2D::Vector2D()
{
	m_coordinates[0] = 0.f;
	m_coordinates[1] = 0.f;
}

Vector2D::Vector2D(float a_x, float a_y)
{
	m_coordinates[0] = a_x;
	m_coordinates[1] = a_y;
}
