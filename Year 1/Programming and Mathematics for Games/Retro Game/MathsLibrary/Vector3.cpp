#include "MathLibrary.h"
#include <cmath>

#pragma region Operator Overload
const float Vector3::operator[](const int a_i) const 
{
	return m_coordinates[a_i];
}

const Vector3 Vector3::operator+(const Vector3& a_other) const
{
	Vector3 newVector3;

	newVector3.m_coordinates[0] = m_coordinates[0] + a_other.m_coordinates[0];
	newVector3.m_coordinates[1] = m_coordinates[1] + a_other.m_coordinates[1];
	newVector3.m_coordinates[2] = m_coordinates[2] + a_other.m_coordinates[2];

	return newVector3;
}

void Vector3::operator+=(const Vector3& a_other)
{
	m_coordinates[0] += a_other.m_coordinates[0];
	m_coordinates[1] += a_other.m_coordinates[1];
	m_coordinates[2] += a_other.m_coordinates[2];
}

const Vector3 Vector3::operator-(const Vector3& a_other) const
{
	Vector3 newVector3;

	newVector3.m_coordinates[0] = m_coordinates[0] - a_other.m_coordinates[0];
	newVector3.m_coordinates[1] = m_coordinates[1] - a_other.m_coordinates[1];
	newVector3.m_coordinates[2] = m_coordinates[2] - a_other.m_coordinates[2];

	return newVector3;
}

void Vector3::operator-=(const Vector3& a_other)
{
	m_coordinates[0] -= a_other.m_coordinates[0];
	m_coordinates[1] -= a_other.m_coordinates[1];
	m_coordinates[2] -= a_other.m_coordinates[2];
}

const Vector3 Vector3::operator*(const Vector3& a_other) const
{
	Vector3 newVector3;

	newVector3.m_coordinates[0] = m_coordinates[0] * a_other.m_coordinates[0];
	newVector3.m_coordinates[1] = m_coordinates[1] * a_other.m_coordinates[1];
	newVector3.m_coordinates[2] = m_coordinates[2] * a_other.m_coordinates[2];

	return newVector3;
}

void Vector3::operator*=(const Vector3& a_other)
{
	m_coordinates[0] *= a_other.m_coordinates[0];
	m_coordinates[1] *= a_other.m_coordinates[1];
	m_coordinates[2] *= a_other.m_coordinates[2];
}

const Vector3 Vector3::operator/(const Vector3& a_other) const
{
	Vector3 newVector3;

	newVector3.m_coordinates[0] = m_coordinates[0] / a_other.m_coordinates[0];
	newVector3.m_coordinates[1] = m_coordinates[1] / a_other.m_coordinates[1];
	newVector3.m_coordinates[2] = m_coordinates[2] / a_other.m_coordinates[2];

	return newVector3;
}

void Vector3::operator/=(const Vector3& a_other)
{
	m_coordinates[0] /= a_other.m_coordinates[0];
	m_coordinates[1] /= a_other.m_coordinates[1];
	m_coordinates[2] /= a_other.m_coordinates[2];
}

const Vector3 Vector3::operator*(const float a_other) const
{
	Vector3 newVector3;

	newVector3.m_coordinates[0] = m_coordinates[0] * a_other;
	newVector3.m_coordinates[1] = m_coordinates[1] * a_other;
	newVector3.m_coordinates[2] = m_coordinates[2] * a_other;

	return newVector3;
}

void Vector3::operator*=(const float a_other)
{
	m_coordinates[0] *= a_other;
	m_coordinates[1] *= a_other;
	m_coordinates[2] *= a_other;
}

const Vector3 Vector3::operator/(const float a_other) const
{
	Vector3 newVector3;

	newVector3.m_coordinates[0] = m_coordinates[0] / a_other;
	newVector3.m_coordinates[1] = m_coordinates[1] / a_other;
	newVector3.m_coordinates[2] = m_coordinates[2] / a_other;

	return newVector3;
}

void Vector3::operator/=(const float a_other)
{
	m_coordinates[0] /= a_other;
	m_coordinates[1] /= a_other;
	m_coordinates[2] /= a_other;
}
#pragma endregion

#pragma region Magnitude Functions
const float Vector3::Magnitude() const
{
	return sqrtf(MagnitudeSq());
}

const float Vector3::MagnitudeSq() const
{
	return powf(m_coordinates[0], 2) + powf(m_coordinates[1], 2) + powf(m_coordinates[2], 2);
}
#pragma endregion

#pragma region Distance Functions
const float Vector3::Distance(const Vector3& a_other) const
{
	return sqrtf(DistanceSq(a_other));
}

const float Vector3::DistanceSq(const Vector3& a_other) const
{
	return (powf((m_coordinates[0] - a_other.m_coordinates[0]), 2) + powf((m_coordinates[1] - a_other.m_coordinates[1]), 2) + powf((m_coordinates[2] - a_other.m_coordinates[2]), 2));
}
#pragma endregion

#pragma region Product Functions
const float Vector3::DotProduct(const Vector3& a_other) const
{
	return (m_coordinates[0] * a_other.m_coordinates[0]) + (m_coordinates[1] * a_other.m_coordinates[1]) + (m_coordinates[2] * a_other.m_coordinates[2]);
}

const Vector3 Vector3::CrossProduct(const Vector3& a_rv3a) const
{
	Vector3 newVector3;

	newVector3.m_coordinates[0] = (m_coordinates[1] * a_rv3a.m_coordinates[2]) - (m_coordinates[2] * a_rv3a[1]);
	newVector3.m_coordinates[1] = (m_coordinates[2] * a_rv3a.m_coordinates[0]) - (m_coordinates[0] * a_rv3a[2]);
	newVector3.m_coordinates[2] = (m_coordinates[0] * a_rv3a.m_coordinates[1]) - (m_coordinates[1] * a_rv3a[0]);

	return newVector3;
}
#pragma endregion

#pragma region Normalise and Normalised Function
void Vector3::Normalise()
{
	float magnitudeValue = Magnitude();
	m_coordinates[0] = m_coordinates[0] / magnitudeValue;
	m_coordinates[1] = m_coordinates[1] / magnitudeValue;
	m_coordinates[2] = m_coordinates[2] / magnitudeValue;
}

const Vector3 Vector3::Normalised() const
{
	Vector3 newVector3;
	float magnitudeValue = Magnitude();

	newVector3.m_coordinates[0] = m_coordinates[0] / magnitudeValue;
	newVector3.m_coordinates[1] = m_coordinates[1] / magnitudeValue;
	newVector3.m_coordinates[2] = m_coordinates[2] / magnitudeValue;

	return newVector3;
}
#pragma endregion

#pragma region Constructors/Destructors
Vector3::Vector3(float a_x, float a_y, float a_z)
{
	m_coordinates[0] = a_x;
	m_coordinates[1] = a_y;
	m_coordinates[2] = a_z;
}

Vector3::Vector3(const Vector2 a_other)
{
	m_coordinates[0] = a_other.GetX();
	m_coordinates[1] = a_other.GetY();
	m_coordinates[2] = 0;
}

Vector3::Vector3()
{
	m_coordinates[0] = 0;
	m_coordinates[1] = 0;
	m_coordinates[2] = 0;
}
#pragma endregion