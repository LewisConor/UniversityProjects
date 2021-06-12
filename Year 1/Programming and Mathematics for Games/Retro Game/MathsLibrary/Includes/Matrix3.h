#ifndef MATRIX_3_H
#define MATRIX_3_H

class Vector3;

class Matrix3
{
#pragma region Public
public:
	#pragma region Constructors and Destructor
	Matrix3();
	Matrix3(const float a_fm11, const float a_fm12, const float a_fm13, const float a_fm21, const float a_fm22, const float a_fm23, const float a_fm31, const float a_fm32, const float a_fm33);
	Matrix3(const float* a_fpm33Values);
	~Matrix3() {};
	#pragma endregion

	#pragma region Functions
	static const Matrix3 Identity();

	// Getters / Setters
	const Vector3 GetRow(const int a_irowNumber) const;
	void SetRow(const int a_irowNumber, const Vector3 &a_rowValues);

	// Rotations
	//const Matrix3 RotateX(const float a_ftheta) const;
	//const Matrix3 RotateY(const float a_ftheta) const;
	//const Matrix3 RotateZ(const float a_ftheta) const;
	#pragma endregion

	#pragma region Operator Overload
	const Matrix3 operator+(const Matrix3 &a_other) const;
	void operator+=(const Matrix3 &a_other);

	const Matrix3 operator-(const Matrix3 &a_other) const;
	void operator-=(const Matrix3 &a_other);

	const Matrix3 operator*(const Matrix3 &a_other) const;
	void operator*=(const Matrix3 &a_other);

	const Matrix3 operator*(const float &a_other) const;
	void operator*=(const float &a_other);

	const bool operator==(const Matrix3 &a_other) const;
	const bool operator!=(const Matrix3 &a_other) const;

	const float operator[](const int i) const;
	#pragma endregion

private:
	#pragma region Variables
	static const int cols = 3;
	static const int rows = 3;
	float m_matrixValues[9];
	#pragma endregion
};

#endif //!MATRIX_3_H
