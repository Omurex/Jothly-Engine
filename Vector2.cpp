#include "Vector2.h"
#include "Vector3.h"
#include "Math.h"
#include "Constants.hpp"


namespace jothly
{
	Vector2::Vector2(const Vector3& vec3) : Vector2(vec3.x, vec3.y) {}


	void Vector2::Normalize()
	{
		float sqrMag = GetMagnitudeSquared();
		Normalize(sqrMag);
	}


	void Vector2::Normalize(float precomputedMagnitudeSquared)
	{
		float mag = sqrtf(precomputedMagnitudeSquared);

		if (Approx(mag, 0, con::VECTOR_MARGIN_OF_ERROR))
		{
			Scale(0);
		}
		else
		{
			Scale(1.0f / mag);
		}
	}


	Vector2 Vector2::GetNormalized()
	{
		Vector2 vec = Vector2(*this);
		vec.Normalize();
		return vec;
	}


	Vector2 Vector2::GetNormalized(float precomputedMagnitudeSquared)
	{
		Vector2 vec = Vector2(*this);
		vec.Normalize(precomputedMagnitudeSquared);
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


	void Vector2::Scale(float const& scale)
	{
		x *= scale; y *= scale;
	}


	Vector2 Vector2::operator+(Vector2 const& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}


	Vector3 Vector2::operator+(Vector3 const& other) const
	{
		return Vector3(other.x + x, other.y + y, other.z);
	}


	Vector2& Vector2::operator+=(Vector2 const& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}


	Vector2& Vector2::operator+=(Vector3 const& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}


	Vector2 Vector2::operator-(Vector2 const& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}


	Vector2& Vector2::operator-=(Vector2 const& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}


	Vector2& Vector2::operator-=(Vector3 const& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}


	Vector2 Vector2::operator*(float const& scale) const
	{
		return Vector2(x * scale, y * scale);
	}


	Vector2 Vector2::operator/(float const& scale) const
	{
		return Vector2(x / scale, y / scale);
	}


	bool Vector2::operator==(Vector2 const& other)
	{
		return x == other.x && y == other.y;
	}
}