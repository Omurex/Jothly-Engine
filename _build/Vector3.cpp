#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include "raymath.h"


namespace jothly
{
	Vector3::Vector3(const Vector2& vec2) : Vector3(vec2.x, vec2.y) {}
	Vector3::Vector3(const Vector4& vec4) : Vector3(vec4.x, vec4.y, vec4.z) {}


	Vector3& Vector3::Normalize()
    {
		float magnitude = sqrtf((x * x) + (y * y) + (z * z));

		x /= magnitude;
		y /= magnitude;
		z /= magnitude;

		return *this;
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


	Vector3::operator Vector2() const
	{
		return Vector2(x, y);
	}


	Vector3::operator Vector4() const
	{
		return Vector4(x, y, z, 0);
	}
}