#include "Vector4.h"
#include "Vector3.h"


namespace jothly
{
	Vector4 Vector4::operator+(Vector4 const& other)
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}


	Vector4 Vector4::operator-(Vector4 const& other)
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}


	Vector4 Vector4::operator*(float const& scale)
	{
		return Vector4(x * scale, y * scale, z * scale, w * scale);
	}


	Vector4 Vector4::operator/(float const& scale)
	{
		return Vector4(x / scale, y / scale, z / scale, w / scale);
	}


	Vector4::operator Vector3() const
	{
		return Vector3(x, y, z);
	}
}
