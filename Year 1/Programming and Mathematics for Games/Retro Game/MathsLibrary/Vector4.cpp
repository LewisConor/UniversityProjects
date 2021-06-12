#include "MathLibrary.h"
#include <cmath>

#pragma region Operator Overload
const float Vector4::operator[](const int a_i) const
{
	return m_coordinates[a_i];
}

const Vector4 Vector4::operator+(const Vector3& a_other) const
{
	Vector4 newVector4;

	newVector4.m_coordinates[0] = m_coordinates[0] + a_other.GetX();
	newVector4.m_coordinates[1] = m_coordinates[1] + a_other.GetY();
	newVector4.m_coordinates[2] = m_coordinates[2] + a_other.GetZ();

	return newVector4;
}

void Vector4::operator+=(const Vector3& a_other)
{
	m_coordinates[0] += a_other.GetX();
	m_coordinates[1] += a_other.GetY();
	m_coordinates[2] += a_other.GetZ();
}

const Vector4 Vector4::operator-(const Vector3& a_other) const
{
	Vector4 newVector4;

	newVector4.m_coordinates[0] = m_coordinates[0] - a_other.GetX();
	newVector4.m_coordinates[1] = m_coordinates[1] - a_other.GetY();
	newVector4.m_coordinates[2] = m_coordinates[2] - a_other.GetZ();

	return newVector4;
}

void Vector4::operator-=(const Vector3& a_other)
{
	m_coordinates[0] -= a_other.GetX();
	m_coordinates[1] -= a_other.GetY();
	m_coordinates[2] -= a_other.GetZ();
}

const Vector4 Vector4::operator*(const Vector3& a_other) const
{
	Vector4 newVector4;

	newVector4.m_coordinates[0] = m_coordinates[0] * a_other.GetX();
	newVector4.m_coordinates[1] = m_coordinates[1] * a_other.GetY();
	newVector4.m_coordinates[2] = m_coordinates[2] * a_other.GetZ();

	return newVector4;
}

void Vector4::operator*=(const Vector3& a_other)
{
	m_coordinates[0] *= a_other.GetX();
	m_coordinates[1] *= a_other.GetY();
	m_coordinates[2] *= a_other.GetZ();
}

const Vector4 Vector4::operator/(const Vector3& a_other) const
{
	Vector4 newVector4;

	newVector4.m_coordinates[0] = m_coordinates[0] / a_other.GetX();
	newVector4.m_coordinates[1] = m_coordinates[1] / a_other.GetY();
	newVector4.m_coordinates[2] = m_coordinates[2] / a_other.GetZ();

	return newVector4;
}

void Vector4::operator/=(const Vector3& a_other)
{
	m_coordinates[0] /= a_other.GetX();
	m_coordinates[1] /= a_other.GetY();
	m_coordinates[2] /= a_other.GetZ();
}

const Vector4 Vector4::operator*(const float a_other) const
{
	Vector4 newVector4;

	newVector4.m_coordinates[0] = m_coordinates[0] * a_other;
	newVector4.m_coordinates[1] = m_coordinates[1] * a_other;
	newVector4.m_coordinates[2] = m_coordinates[2] * a_other;

	return newVector4;
}

void Vector4::operator*=(const float a_other)
{
	m_coordinates[0] *= a_other;
	m_coordinates[1] *= a_other;
	m_coordinates[2] *= a_other;
}

const Vector4 Vector4::operator/(const float a_other) const
{
	Vector4 newVector4;

	newVector4.m_coordinates[0] = m_coordinates[0] / a_other;
	newVector4.m_coordinates[1] = m_coordinates[1] / a_other;
	newVector4.m_coordinates[2] = m_coordinates[2] / a_other;

	return newVector4;
}

void Vector4::operator/=(const float a_other)
{
	m_coordinates[0] /= a_other;
	m_coordinates[1] /= a_other;
	m_coordinates[2] /= a_other;
}

#pragma endregion

#pragma region Magnitude Functions
const float Vector4::Magnitude() const
{
	return sqrtf(MagnitudeSq());
}

const float Vector4::MagnitudeSq() const
{
	return powf(m_coordinates[0], 2) + powf(m_coordinates[1], 2) + powf(m_coordinates[2], 2);
}
#pragma endregion

#pragma region Distance Functions
const float Vector4::Distance(const Vector3& a_other) const
{
	return sqrtf(DistanceSq(a_other));
}

const float Vector4::DistanceSq(const Vector3& a_other) const
{
	return (powf((m_coordinates[0] - a_other.GetX()), 2) + powf((m_coordinates[1] - a_other.GetY()), 2) + powf((m_coordinates[2] - a_other.GetZ()), 2));
}
#pragma endregion

#pragma region Product Functions
const float Vector4::DotProduct(const Vector3& a_other) const
{
	return (m_coordinates[0] * a_other.GetX()) + (m_coordinates[1] * a_other.GetY()) + (m_coordinates[2] * a_other.GetZ());
}

const Vector4 Vector4::CrossProduct(const Vector3& a_rv3a) const
{
	Vector4 newVector4;

	newVector4.m_coordinates[0] = (m_coordinates[1] * a_rv3a.GetZ()) - (m_coordinates[2] * a_rv3a.GetY());
	newVector4.m_coordinates[1] = (m_coordinates[2] * a_rv3a.GetX()) - (m_coordinates[0] * a_rv3a.GetZ());
	newVector4.m_coordinates[2] = (m_coordinates[0] * a_rv3a.GetY()) - (m_coordinates[1] * a_rv3a.GetX());

	return newVector4;
}
#pragma endregion

#pragma region Normalise and Normalised Function
void Vector4::Normalise()
{
	float magnitudeValue = Magnitude();
	m_coordinates[0] = m_coordinates[0] / magnitudeValue;
	m_coordinates[1] = m_coordinates[1] / magnitudeValue;
	m_coordinates[2] = m_coordinates[2] / magnitudeValue;
}

const Vector4 Vector4::Normalised() const
{
	Vector4 newVector4;
	float magnitudeValue = Magnitude();

	newVector4.m_coordinates[0] = m_coordinates[0] / magnitudeValue;
	newVector4.m_coordinates[1] = m_coordinates[1] / magnitudeValue;
	newVector4.m_coordinates[2] = m_coordinates[2] / magnitudeValue;

	return newVector4;
}
#pragma endregion

#pragma region Constructors/Destructors
Vector4::Vector4(float a_x, float a_y, float a_z)
{
	m_coordinates[0] = a_x;
	m_coordinates[1] = a_y;
	m_coordinates[2] = a_z;
	m_coordinates[3] = 0;
}

Vector4::Vector4(const Vector2 a_other)
{
	m_coordinates[0] = a_other.GetX();
	m_coordinates[1] = a_other.GetY();
	m_coordinates[2] = 0;
	m_coordinates[3] = 0;
}

Vector4::Vector4()
{
	m_coordinates[0] = 0;
	m_coordinates[1] = 0;
	m_coordinates[2] = 0;
	m_coordinates[3] = 0;
}
#pragma endregion