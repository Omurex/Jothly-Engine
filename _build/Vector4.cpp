#include "Vector4.h"
#include "Vector3.h"
#include "Math.h"
#include "Constants.hpp"


namespace jothly
{
	Vector4::Vector4(const Vector3& vec3) : Vector4(vec3.x, vec3.y, vec3.z, 0) {}


	void Vector4::Normalize()
    {
		float sqrMag = GetMagnitudeSquared();
		Normalize(sqrMag);
    }


	void Vector4::Normalize(float precomputedMagnitudeSquared)
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


	Vector4 Vector4::GetNormalized()
	{
		Vector4 vec = Vector4(*this);
		vec.Normalize();
		return vec;
	}


	Vector4 Vector4::GetNormalized(float precomputedMagnitudeSquared)
	{
		Vector4 vec = Vector4(*this);
		vec.Normalize(precomputedMagnitudeSquared);
		return vec;
	}


	float Vector4::GetMagnitude()
	{
		return sqrtf(GetMagnitudeSquared());
	}


	float Vector4::GetMagnitudeSquared()
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}


	void Vector4::Scale(float const& scale)
	{
		x *= scale; y *= scale; z *= scale; w *= scale;
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


    bool Vector4::operator==(Vector4 const& other)
    {
		return x == other.x && y == other.y && z == other.z && w == other.w;
    }


	Vector4::operator Vector3() const
	{
		return Vector3(x, y, z);
	}


	/*Vector4::operator const float* () const
	{
		return components;
	}*/
}
