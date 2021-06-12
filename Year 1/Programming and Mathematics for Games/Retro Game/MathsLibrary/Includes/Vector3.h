#ifndef VECTOR_3_H
#define VECTOR_3_H

class Vector2;
class Matrix3;

class Vector3
{
public:
	#pragma region Constructors & Destructor
	Vector3(float a_x, float a_y, float a_z);
	Vector3(Vector2 a_other);
	Vector3();
	~Vector3() {};
	#pragma endregion

	#pragma region Functions
	//Magnitude
	const float Magnitude() const;
	const float MagnitudeSq() const;

	//Distance
	const float Distance(const Vector3& a_other) const;
	const float DistanceSq(const Vector3& a_other) const;

	//Product Functionality
	const float DotProduct(const Vector3& a_other) const;
	const Vector3 CrossProduct(const Vector3& a_rv3a) const;

	//Normalise and Normalised
	void Normalise();
	const Vector3 Normalised() const;

	// Getters / Setters
	const float GetX() const { return m_coordinates[0]; }
	const float GetY() const { return m_coordinates[1]; }
	const float GetZ() const { return m_coordinates[2]; }
	void SetX(const float a_x) { m_coordinates[0] = a_x; }
	void SetY(const float a_y) { m_coordinates[1] = a_y; }
	void SetZ(const float a_z) { m_coordinates[2] = a_z; }
	#pragma endregion

	#pragma region Operator Overload
	const float operator[](const int a_i) const;

	const Vector3 operator*(const float a_other) const;
	void operator*=(const float a_other);

	const Vector3 operator*(const Vector3 &a_other) const;
	void operator*=(const Vector3 &a_other);

	const Vector3 operator/(const Vector3 &a_other) const;
	void operator/=(const Vector3 &a_other);

	const Vector3 operator/(const float a_other) const;
	void operator/=(const float a_other);

	const Vector3 operator+(const Vector3 &a_other) const;
	void operator+=(const Vector3 &a_other);

	const Vector3 operator-(const Vector3 &a_other) const;
	void operator-=(const Vector3 &a_other);
	#pragma endregion
private:
	#pragma region Variables
	float m_coordinates[3];
	#pragma endregion
};

#endif //!VECTOR_3_H
