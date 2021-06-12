#ifndef _MATRIX_4_H_
#define _MATRIX_4_H_

class Vector3;

class Matrix4 
{
public:
	#pragma region Operator Overload
	const Matrix4 operator+(const Matrix4& a_other) const;
	void operator+=(const Matrix4& a_other);

	const Matrix4 operator-(const Matrix4& a_other) const;
	void operator-=(const Matrix4& a_other);

	const Matrix4 operator*(const Matrix4& a_other) const;
	void operator*=(const Matrix4& a_other);

	const Matrix4 operator*(const float& a_other) const;
	void operator*=(const float& a_other);

	const bool operator==(const Matrix4& a_other) const;
	const bool operator!=(const Matrix4& a_other) const;

	const float operator[](const int i) const;
	#pragma endregion

	#pragma region Functions
	static const Matrix4 Identity();

	// Getters / Setters
	const Vector3 GetRow(const int a_irowNumber) const;
	void SetRow(const int a_irowNumber, const Vector3& a_rowValues);

	// Rotations
	//const Matrix4 RotateX(const float a_ftheta) const;
	//const Matrix4 RotateY(const float a_ftheta) const;
	//const Matrix4 RotateZ(const float a_ftheta) const;
	#pragma endregion

	#pragma region Constructors and Destructor
	Matrix4();
	Matrix4(const float a_fm11, const float a_fm12, const float a_fm13, const float a_fm14, const float a_fm21, const float a_fm22, const float a_fm23, const float a_fm24, const float a_fm31, const float a_fm32, const float a_fm33, const float a_fm34, const float a_fm41, const float a_fm42, const float a_fm43, const float a_fm44);
	Matrix4(const float* a_fpm44Values);
	~Matrix4() {};
	#pragma endregion
private:
	static const int m_columns = 4, m_rows = 4;
	float m_matrixValues[16];
};

#endif //_MATRIX_4_H_