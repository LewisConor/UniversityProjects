#include "MathLibrary.h"

#pragma region Operators Overload
const Matrix3 Matrix3::operator+(const Matrix3& a_other) const
{
	Matrix3 newMatrix3;

	for (int i = 0; i < 9; i++)
	{
		newMatrix3.m_matrixValues[i] = m_matrixValues[i] + a_other.m_matrixValues[i];
	}

	return newMatrix3;
}

void Matrix3::operator+=(const Matrix3& a_other)
{
	for (int i = 0; i < 9; i++)
	{
		m_matrixValues[i] += a_other.m_matrixValues[i];
	}
}

const Matrix3 Matrix3::operator-(const Matrix3& a_other) const
{
	Matrix3 newMatrix3;

	for (int i = 0; i < 9; i++)
	{
		newMatrix3.m_matrixValues[i] = m_matrixValues[i] - a_other.m_matrixValues[i];
	}

	return newMatrix3;
}

void Matrix3::operator-=(const Matrix3& a_other)
{
	for (int i = 0; i < 9; i++)
	{
		m_matrixValues[i] -= a_other.m_matrixValues[i];
	}
}

const Matrix3 Matrix3::operator*(const Matrix3& a_other) const
{
	Matrix3 newMatrix3;

	for (int i = 0; i < 9; i++)
	{
		newMatrix3.m_matrixValues[i] = m_matrixValues[i] * a_other.m_matrixValues[i];
	}

	return newMatrix3;
}

void Matrix3::operator*=(const Matrix3& a_other)
{
	for (int i = 0; i < 9; i++)
	{
		m_matrixValues[i] *= a_other.m_matrixValues[i];
	}
}

const Matrix3 Matrix3::operator*(const float& a_other) const
{
	Matrix3 newMatrix3;

	for (int i = 0; i < 9; i++)
	{
		newMatrix3.m_matrixValues[i] = m_matrixValues[i] * a_other;
	}

	return newMatrix3;
}

void Matrix3::operator*=(const float& a_other)
{
	for (int i = 0; i < 9; i++)
	{
		m_matrixValues[i] *= a_other;
	}
}

const bool Matrix3::operator==(const Matrix3& a_other) const
{
	int numOfCheck = 0;

	for (int i = 0; i < 9; i++)
	{
		if (m_matrixValues[i] == a_other.m_matrixValues[i])
		{
			numOfCheck++;
		}
	}

	if (numOfCheck == 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Matrix3::operator!=(const Matrix3& a_other) const
{
	int numOfCheck = 0;

	for (int i = 0; i < 9; i++)
	{
		if (m_matrixValues[i] == a_other.m_matrixValues[i])
		{
			numOfCheck++;
		}
	}

	if (numOfCheck == 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const float Matrix3::operator[](const int i) const
{
	return m_matrixValues[i];
}
#pragma endregion

const Matrix3 Matrix3::Identity()
{
	Matrix3 newMatrix3;

	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 4 || i == 8)
		{
			newMatrix3.m_matrixValues[i] = 1;
		}
		else
		{
			newMatrix3.m_matrixValues[i] = 0;
		}
	}

	return newMatrix3;
}

#pragma region Getters and Setters
const Vector3 Matrix3::GetRow(const int a_irowNumber) const
{
	Vector3 newVector3;

	if (a_irowNumber == 0)
	{
		return Vector3(m_matrixValues[0], m_matrixValues[1], m_matrixValues[2]);
	}
	else if (a_irowNumber == 1)
	{
		return Vector3(m_matrixValues[3], m_matrixValues[4], m_matrixValues[5]);
	}
	else if (a_irowNumber == 2)
	{
		return Vector3(m_matrixValues[6], m_matrixValues[7], m_matrixValues[8]);
	}
	else
	{
		return Vector3();
	}
}

void Matrix3::SetRow(const int a_irowNumber, const Vector3& a_rowValues)
{
	if (a_irowNumber == 0)
	{
		m_matrixValues[0] = a_rowValues[0];
		m_matrixValues[1] = a_rowValues[1];
		m_matrixValues[2] = a_rowValues[2];
	}
	else if (a_irowNumber == 1)
	{
		m_matrixValues[3] = a_rowValues[0];
		m_matrixValues[4] = a_rowValues[1];
		m_matrixValues[5] = a_rowValues[2];
	}
	else if (a_irowNumber == 2)
	{
		m_matrixValues[6] = a_rowValues[0];
		m_matrixValues[7] = a_rowValues[1];
		m_matrixValues[8] = a_rowValues[2];
	}
}
#pragma endregion

#pragma region Rotations - No Longer Required
//const Matrix3 Matrix3::RotateX(const float a_ftheta) const
//{
//	return Matrix3();
//}
//
//const Matrix3 Matrix3::RotateY(const float a_ftheta) const
//{
//	return Matrix3();
//}
//
//const Matrix3 Matrix3::RotateZ(const float a_ftheta) const
//{
//	return Matrix3();
//}
#pragma endregion

#pragma region Constructors/Destructors
Matrix3::Matrix3() : m_matrixValues{ }
{
	for (int i = 0; i < 9; i++)
	{
		m_matrixValues[i] = 0;
	}
}

Matrix3::Matrix3(const float a_fm11, const float a_fm12, const float a_fm13, const float a_fm21, const float a_fm22, const float a_fm23, const float a_fm31, const float a_fm32, const float a_fm33) : m_matrixValues{ }
{
	for (int i = 0; i < 9; i++)
	{
		switch (i)
		{
			case 0: 
			{
				m_matrixValues[0] = a_fm11;
				break;
			}
			case 1:
			{
				m_matrixValues[1] = a_fm12;
				break;
			}
			case 2:
			{
				m_matrixValues[2] = a_fm13;
				break;
			}
			case 3:
			{
				m_matrixValues[3] = a_fm21;
				break;
			}
			case 4:
			{
				m_matrixValues[4] = a_fm22;
				break;
			}
			case 5:
			{
				m_matrixValues[5] = a_fm23;
				break;
			}
			case 6:
			{
				m_matrixValues[6] = a_fm31;
				break;
			}
			case 7:
			{
				m_matrixValues[7] = a_fm32;
				break;
			}
			case 8:
			{
				m_matrixValues[8] = a_fm33;
				break;
			}
		}
	}
}

Matrix3::Matrix3(const float* a_fpm33Values) : m_matrixValues{ }
{
	for (int i = 0; i < 9; i++)
	{
		m_matrixValues[i] = a_fpm33Values[i];
	}
}
#pragma endregion