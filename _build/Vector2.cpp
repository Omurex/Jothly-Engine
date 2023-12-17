#include "Vector2.h"
#include "Vector3.h"
#include "raymath.h"


namespace jothly
{
	Vector2::Vector2(const Vector3& vec3) : Vector2(vec3.x, vec3.y) {}


	void Vector2::Normalize()
	{
		float magnitude = GetMagnitude();

		x /= magnitude;
		y /= magnitude;
	}

	Vector2 Vector2::GetNormalized()
	{
		Vector2 vec = Vector2(*this);
		vec.Normalize();
		return vec;
	}

	float Vector2::GetMagnitude()
	{
		return sqrtf(GetMagnitudeSquared());
	}

	float Vector2::GetMagnitudeSquared()
	{
		return (x * x) + (y * y);
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