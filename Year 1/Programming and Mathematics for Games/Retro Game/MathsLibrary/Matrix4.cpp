#include "MathLibrary.h"

#pragma region Operator Overload
const Matrix4 Matrix4::operator+(const Matrix4& a_other) const 
{
	Matrix4 newMatrix4;

	for (int i = 0; i < 16; i++) 
	{
		newMatrix4.m_matrixValues[i] = m_matrixValues[i] + a_other.m_matrixValues[i];
	}

	return newMatrix4;
}

void Matrix4::operator+=(const Matrix4& a_other)
{
	for (int i = 0; i < 16; i++) 
	{
		m_matrixValues[i] += a_other.m_matrixValues[i];
	}
}

const Matrix4 Matrix4::operator-(const Matrix4& a_other) const
{
	Matrix4 newMatrix4;

	for (int i = 0; i < 16; i++)
	{
		newMatrix4.m_matrixValues[i] = m_matrixValues[i] - a_other.m_matrixValues[i];
	}

	return newMatrix4;
}

void Matrix4::operator-=(const Matrix4& a_other)
{
	for (int i = 0; i < 16; i++)
	{
		m_matrixValues[i] -= a_other.m_matrixValues[i];
	}
}

const Matrix4 Matrix4::operator*(const Matrix4& a_other) const
{
	Matrix4 newMatrix4;

	for (int i = 0; i < 16; i++)
	{
		newMatrix4.m_matrixValues[i] = m_matrixValues[i] * a_other.m_matrixValues[i];
	}

	return newMatrix4;
}

void Matrix4::operator*=(const Matrix4& a_other)
{
	for (int i = 0; i < 16; i++)
	{
		m_matrixValues[i] *= a_other.m_matrixValues[i];
	}
}

const Matrix4 Matrix4::operator*(const float& a_other) const
{
	Matrix4 newMatrix4;

	for (int i = 0; i < 16; i++)
	{
		newMatrix4.m_matrixValues[i] = m_matrixValues[i] * a_other;
	}

	return newMatrix4;
}

void Matrix4::operator*=(const float& a_other)
{
	for (int i = 0; i < 16; i++)
	{
		m_matrixValues[i] *= a_other;
	}
}

const bool Matrix4::operator==(const Matrix4& a_other) const
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

const bool Matrix4::operator!=(const Matrix4& a_other) const
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

const float Matrix4::operator[](const int i) const
{
	return m_matrixValues[i];
}
#pragma endregion

#pragma region Functions
const Matrix4 Matrix4::Identity()
{
	Matrix4 newMatrix4;

	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 5 || i == 10 || i == 15)
		{
			newMatrix4.m_matrixValues[i] = 1;
		}
		else
		{
			newMatrix4.m_matrixValues[i] = 0;
		}
	}

	return newMatrix4;
}

// Getters / Setters
const Vector3 Matrix4::GetRow(const int a_irowNumber) const
{
	Vector3 newVector3;

	switch (a_irowNumber)
	{
		case 1:
		{
			newVector3.SetX(m_matrixValues[0]);
			newVector3.SetY(m_matrixValues[1]);
			newVector3.SetZ(m_matrixValues[2]);

			break;
		}
		case 2:
		{
			newVector3.SetX(m_matrixValues[4]);
			newVector3.SetY(m_matrixValues[5]);
			newVector3.SetZ(m_matrixValues[6]);

			break;
		}
		case 3:
		{
			newVector3.SetX(m_matrixValues[8]);
			newVector3.SetY(m_matrixValues[9]);
			newVector3.SetZ(m_matrixValues[10]);

			break;
		}
		case 4:
		{
			newVector3.SetX(m_matrixValues[12]);
			newVector3.SetY(m_matrixValues[13]);
			newVector3.SetZ(m_matrixValues[14]);

			break;
		}
	}

	return newVector3;
}

void Matrix4::SetRow(const int a_irowNumber, const Vector3& a_rowValues)
{
	switch (a_irowNumber)
	{
		case 1:
		{
			m_matrixValues[0] = a_rowValues.GetX();
			m_matrixValues[1] = a_rowValues.GetY();
			m_matrixValues[2] = a_rowValues.GetZ();

			break;
		}
		case 2:
		{
			m_matrixValues[4] = a_rowValues.GetX();
			m_matrixValues[5] = a_rowValues.GetY();
			m_matrixValues[6] = a_rowValues.GetZ();

			break;
		}
		case 3:
		{
			m_matrixValues[8] = a_rowValues.GetX();
			m_matrixValues[9] = a_rowValues.GetY();
			m_matrixValues[10] = a_rowValues.GetZ();

			break;
		}
		case 4:
		{
			m_matrixValues[12] = a_rowValues.GetX();
			m_matrixValues[13] = a_rowValues.GetY();
			m_matrixValues[14] = a_rowValues.GetZ();

			break;
		}
	}
}

// Rotations - No Longer Needed
//const Matrix4 Matrix4::RotateX(const float a_ftheta) const
//{
//	return Matrix4();
//}
//const Matrix4 Matrix4::RotateY(const float a_ftheta) const
//{
//	return Matrix4();
//}
//
//const Matrix4 Matrix4::RotateZ(const float a_ftheta) const 
//{
//	return Matrix4();
//}
#pragma endregion

#pragma region Constructors and Destructor
Matrix4::Matrix4() : m_matrixValues{ }
{
	for (int i = 0; i < 16; i++)
	{
		m_matrixValues[i] = 0;
	}
}

Matrix4::Matrix4(const float a_fm11, const float a_fm12, const float a_fm13, const float a_fm14, const float a_fm21, const float a_fm22, const float a_fm23, const float a_fm24, const float a_fm31, const float a_fm32, const float a_fm33, const float a_fm34, const float a_fm41, const float a_fm42, const float a_fm43, const float a_fm44) : m_matrixValues{ }
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
				m_matrixValues[3] = a_fm14;
				break;
			}
			case 4:
			{
				m_matrixValues[4] = a_fm21;
				break;
			}
			case 5:
			{
				m_matrixValues[5] = a_fm22;
				break;
			}
			case 6:
			{
				m_matrixValues[6] = a_fm23;
				break;
			}
			case 7:
			{
				m_matrixValues[7] = a_fm24;
				break;
			}
			case 8:
			{
				m_matrixValues[8] = a_fm31;
				break;
			}
			case 9:
			{
				m_matrixValues[9] = a_fm32;
				break;
			}
			case 10:
			{
				m_matrixValues[10] = a_fm33;
				break;
			}
			case 11:
			{
				m_matrixValues[11] = a_fm34;
				break;
			}
			case 12:
			{
				m_matrixValues[12] = a_fm41;
				break;
			}
			case 13:
			{
				m_matrixValues[13] = a_fm42;
				break;
			}
			case 14:
			{
				m_matrixValues[14] = a_fm43;
				break;
			}
			case 15:
			{
				m_matrixValues[15] = a_fm44;
				break;
			}
		}
	}
}

Matrix4::Matrix4(const float* a_fpm44Values) : m_matrixValues{ }
{
	for (int i = 0; i < 9; i++)
	{
		m_matrixValues[i] = a_fpm44Values[i];
	}
}
#pragma endregion