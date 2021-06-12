#include "MathLibrary.h"
#include <cmath>

#pragma region Operator Overload
const float Vector2::operator[](const int a_i) const
{
	return m_coordinates[a_i];
}

const Vector2 Vector2::operator+(const Vector2& a_other) const
{
	Vector2 newVector2;

	newVector2.m_coordinates[0] = m_coordinates[0] + a_other.m_coordinates[0];
	newVector2.m_coordinates[1] = m_coordinates[1] + a_other.m_coordinates[1];

	return newVector2;
}

void Vector2::operator+=(const Vector2& a_other)
{
	m_coordinates[0] += a_other.m_coordinates[0];
	m_coordinates[1] += a_other.m_coordinates[1];
}

const Vector2 Vector2::operator-(const Vector2& a_other) const
{
	Vector2 newVector2;

	newVector2.m_coordinates[0] = m_coordinates[0] - a_other.m_coordinates[0];
	newVector2.m_coordinates[1] = m_coordinates[1] - a_other.m_coordinates[1];

	return newVector2;
}

void Vector2::operator-=(const Vector2& a_other)
{
	m_coordinates[0] -= a_other.m_coordinates[0];
	m_coordinates[1] -= a_other.m_coordinates[1];
}

const Vector2 Vector2::operator*(const Vector2& a_other) const
{
	Vector2 newVector2;

	newVector2.m_coordinates[0] = m_coordinates[0] * a_other.m_coordinates[0];
	newVector2.m_coordinates[1] = m_coordinates[1] * a_other.m_coordinates[1];

	return newVector2;
}

void Vector2::operator*=(const Vector2& a_other)
{
	m_coordinates[0] *= a_other.m_coordinates[0];
	m_coordinates[1] *= a_other.m_coordinates[1];
}

const Vector2 Vector2::operator/(const Vector2& a_other) const
{
	Vector2 newVector2;

	newVector2.m_coordinates[0] = m_coordinates[0] / a_other.m_coordinates[0];
	newVector2.m_coordinates[1] = m_coordinates[1] / a_other.m_coordinates[1];

	return newVector2;
}

void Vector2::operator/=(const Vector2& a_other)
{
	m_coordinates[0] /= a_other.m_coordinates[0];
	m_coordinates[1] /= a_other.m_coordinates[1];
}

const Vector2 Vector2::operator*(const float a_other) const
{
	Vector2 newVector2;

	newVector2.m_coordinates[0] = m_coordinates[0] * a_other;
	newVector2.m_coordinates[1] = m_coordinates[1] * a_other;

	return newVector2;
}

void Vector2::operator*=(const float a_other)
{
	m_coordinates[0] *= a_other;
	m_coordinates[1] *= a_other;
}

const Vector2 Vector2::operator/(const float a_other) const
{
	Vector2 newVector2;

	newVector2.m_coordinates[0] = m_coordinates[0] / a_other;
	newVector2.m_coordinates[1] = m_coordinates[1] / a_other;

	return newVector2;
}

void Vector2::operator/=(const float a_other)
{
	m_coordinates[0] /= a_other;
	m_coordinates[1] /= a_other;
}

const bool Vector2::operator==(const Vector2& a_other) const
{
	if (m_coordinates[0] == a_other.m_coordinates[0] && m_coordinates[1] == a_other.m_coordinates[1])
	{
		return true;
	}
	else
	{
		return false;
	}
}
#pragma endregion

#pragma region Magnitude Functions
const float Vector2::Magnitude() const
{
	return sqrtf(MagnitudeSq());
}

const float Vector2::MagnitudeSq() const
{
	return powf(m_coordinates[0], 2) + powf(m_coordinates[1], 2);
}
#pragma endregion

#pragma region Distance Functions
const float Vector2::Distance(const Vector2& a_other) const
{
	return sqrtf(DistanceSq(a_other));
}

const float Vector2::DistanceSq(const Vector2& a_other) const
{
	return (powf((m_coordinates[0] - a_other.m_coordinates[0]), 2) + powf((m_coordinates[1] - a_other.m_coordinates[1]), 2));
}
#pragma endregion

#pragma region Product Functions
const float Vector2::DotProduct(const Vector2& a_other) const
{
	return (m_coordinates[0] * a_other.m_coordinates[0]) + (m_coordinates[1] * a_other.m_coordinates[1]);
}

const Vector2 Vector2::CrossProduct() const
{
	return Vector2();
}
#pragma endregion

#pragma region Normalise Function
void Vector2::Normalise()
{
	float magnitude = Magnitude();
	m_coordinates[0] = m_coordinates[0] / magnitude;
	m_coordinates[1] = m_coordinates[1] / magnitude;
}

const Vector2 Vector2::Normalised() const
{
	Vector2 newVector2;

	float magnitude = Magnitude();
	newVector2.m_coordinates[0] = m_coordinates[0] / magnitude;
	newVector2.m_coordinates[1] = m_coordinates[1] / magnitude;

	return newVector2;
}
#pragma endregion

#pragma region Constructors & Deconstructor
Vector2::Vector2(float a_x, float a_y)
{
	m_coordinates[0] = a_x;
	m_coordinates[1] = a_y;
}

Vector2::Vector2(const Vector2& other)
{
	m_coordinates[0] = other.m_coordinates[0];
	m_coordinates[1] = other.m_coordinates[1];
}

Vector2::Vector2()
{
	m_coordinates[0] = 0;
	m_coordinates[1] = 0;
}
#pragma endregion