#include "Vector2.h"
#include "Vector3.h"
#include <math.h>


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

		x /= mag;
		y /= mag;
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


    bool Vector2::operator==(Vector2 const& other)
    {
        return x == other.x && y == other.y;
    }


	Vector2::operator Vector3() const
	{
		return Vector3(x, y, 0);
	}


	Vector2::operator const float* () const
	{
		return components;
	}
}