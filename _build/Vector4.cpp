#include "Vector4.h"
#include "Vector3.h"
#include "raymath.h"


namespace jothly
{
	Vector4::Vector4(const Vector3& vec3) : Vector4(vec3.x, vec3.y, vec3.z) {}


	Vector4& Vector4::Normalize()
    {
		float magnitude = sqrtf((x * x) + (y * y) + (z * z) + (w * w));

		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;

		return *this;
    }


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
