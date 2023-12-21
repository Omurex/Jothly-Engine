#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include <math.h>


namespace jothly
{
	Vector3::Vector3(const Vector2& vec2) : Vector3(vec2.x, vec2.y) {}
	Vector3::Vector3(const Vector4& vec4) : Vector3(vec4.x, vec4.y, vec4.z) {}


	void Vector3::Normalize()
    {
		float sqrMag = GetMagnitudeSquared();
		Normalize(sqrMag);
    }


	void Vector3::Normalize(float precomputedMagnitudeSquared)
	{
		float mag = sqrtf(precomputedMagnitudeSquared);

		x /= mag;
		y /= mag;
		z /= mag;
	}


	Vector3 Vector3::GetNormalized()
	{
		Vector3 vec = Vector3(*this);
		vec.Normalize();
		return vec;
	}


	Vector3 Vector3::GetNormalized(float precomputedMagnitudeSquared)
	{
		Vector3 vec = Vector3(*this);
		vec.Normalize(precomputedMagnitudeSquared);
		return vec;
	}


	float Vector3::GetMagnitude()
	{
		return sqrtf(GetMagnitudeSquared());
	}


	float Vector3::GetMagnitudeSquared()
	{
		return (x * x) + (y * y) + (z * z);
	}


    Vector3 Vector3::operator+(Vector3 const& other)
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}


	Vector3 Vector3::operator-(Vector3 const& other)
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}


	Vector3 Vector3::operator*(float const& scale)
	{
		return Vector3(x * scale, y * scale, z * scale);
	}


	Vector3 Vector3::operator/(float const& scale)
	{
		return Vector3(x / scale, y / scale, z / scale);
	}


	bool Vector3::operator==(Vector3 const& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}


	Vector3::operator Vector2() const
	{
		return Vector2(x, y);
	}


	Vector3::operator Vector4() const
	{
		return Vector4(x, y, z, 0);
	}
}