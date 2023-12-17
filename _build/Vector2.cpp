#include "Vector2.h"
#include "Vector3.h"
#include "raymath.h"


namespace jothly
{
	Vector2::Vector2(const Vector3& vec3) : Vector2(vec3.x, vec3.y) {}


	Vector2& Vector2::Normalize()
	{
		float magnitude = sqrtf((x * x) + (y * y));

		x /= magnitude;
		y /= magnitude;

		return *this;
	}


	Vector2 Vector2::operator+(Vector2 const& other)
	{
		return Vector2(x + other.x, y + other.y);
	}


	Vector2 Vector2::operator-(Vector2 const& other)
	{
		return Vector2(x - other.x, y - other.y);
	}


	Vector2 Vector2::operator*(float const& scale)
	{
		return Vector2(x * scale, y * scale);
	}


	Vector2 Vector2::operator/(float const& scale)
	{
		return Vector2(x / scale, y / scale);
	}


	Vector2::operator Vector3() const
	{
		return Vector3(x, y, 0);
	}
}