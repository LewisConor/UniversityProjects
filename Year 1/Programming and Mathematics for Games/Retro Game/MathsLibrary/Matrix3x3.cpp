#include <cmath>
#include "Matrix3x3.h"
#include "Vector3D.h"

Matrix3x3::Matrix3x3()
{
	m_matrixValues[0] = 0.0f;
	m_matrixValues[1] = 0.0f;
	m_matrixValues[2] = 0.0f;

	m_matrixValues[3] = 0.0f;
	m_matrixValues[4] = 0.0f;
	m_matrixValues[5] = 0.0f;

	m_matrixValues[6] = 0.0f;
	m_matrixValues[7] = 0.0f;
	m_matrixValues[8] = 0.0f;
}
