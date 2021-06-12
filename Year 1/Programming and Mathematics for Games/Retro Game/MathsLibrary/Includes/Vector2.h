#ifndef VECTOR_2_H
#define VECTOR_2_H

class Vector2
{
public:
	#pragma region Constructors & Destructor
	Vector2(float a_x, float a_y);
	Vector2(const Vector2& other);
	Vector2();
	~Vector2() {};
	#pragma endregion

	#pragma region Functions
	const float Magnitude() const;
	const float MagnitudeSq() const;

	const float Distance(const Vector2& a_other) const;
	const float DistanceSq(const Vector2& a_other) const;

	const Vector2 CrossProduct() const;
	const float DotProduct(const Vector2& a_other) const;

	void Normalise();
	const Vector2 Normalised() const;

	// Getters / Setters
	const float GetX() const { return m_coordinates[0]; }
	const float GetY() const { return m_coordinates[1]; }
	void SetX(const float a_x) { m_coordinates[0] = a_x; }
	void SetY(const float a_y) { m_coordinates[1] = a_y; }
	#pragma endregion

	#pragma region Operator Overload
	const float operator[](const int a_i) const;

	const Vector2 operator*(const float a_other) const;
	void operator*=(const float a_other);

	const Vector2 operator*(const Vector2& a_other) const;
	void operator*=(const Vector2& a_other);

	const Vector2 operator/(const Vector2& a_other) const;
	void operator/=(const Vector2& a_other);

	const Vector2 operator/(const float a_other) const;
	void operator/=(const float a_other);

	const Vector2 operator+(const Vector2& a_other) const;
	void operator+=(const Vector2& a_other);

	const Vector2 operator-(const Vector2& a_other) const;
	void operator-=(const Vector2& a_other);

	const bool operator==(const Vector2& a_other) const;
	#pragma endregion
private:
	#pragma region Variables
	float m_coordinates[2];
	#pragma endregion
};

#endif //!VECTOR_2D
