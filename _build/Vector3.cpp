#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"


namespace jothly
{
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