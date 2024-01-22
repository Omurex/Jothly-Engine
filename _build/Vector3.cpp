#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Math.h"
#include "Constants.hpp"


namespace jothly
{
	rlb_Vector3::rlb_Vector3(const rlb_Vector2& vec2) : rlb_Vector3(vec2.x, vec2.y, 0) {}
	rlb_Vector3::rlb_Vector3(const rlb_Vector4& vec4) : rlb_Vector3(vec4.x, vec4.y, vec4.z) {}


	void rlb_Vector3::Normalize()
    {
		float sqrMag = GetMagnitudeSquared();

		Normalize(sqrMag);
    }


	void rlb_Vector3::Normalize(float precomputedMagnitudeSquared)
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


	rlb_Vector3 rlb_Vector3::GetNormalized()
	{
		rlb_Vector3 vec = rlb_Vector3(*this);
		vec.Normalize();
		return vec;
	}


	rlb_Vector3 rlb_Vector3::GetNormalized(float precomputedMagnitudeSquared)
	{
		rlb_Vector3 vec = rlb_Vector3(*this);
		vec.Normalize(precomputedMagnitudeSquared);
		return vec;
	}


	float rlb_Vector3::GetMagnitude()
	{
		return sqrtf(GetMagnitudeSquared());
	}


	float rlb_Vector3::GetMagnitudeSquared()
	{
		return (x * x) + (y * y) + (z * z);
	}


	void rlb_Vector3::Scale(float const& scale)
	{
		x *= scale; y *= scale; z *= scale;
	}


    rlb_Vector3 rlb_Vector3::operator+(rlb_Vector3 const& other)
	{
		return rlb_Vector3(x + other.x, y + other.y, z + other.z);
	}


    rlb_Vector3 rlb_Vector3::operator+(rlb_Vector2 const& other)
    {
        return rlb_Vector3(x + other.x, y + other.y, z);
    }

	rlb_Vector3& rlb_Vector3::operator+=(rlb_Vector3 const& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	rlb_Vector3& rlb_Vector3::operator+=(rlb_Vector2 const& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}


	rlb_Vector3 rlb_Vector3::operator-(rlb_Vector3 const& other)
	{
		return rlb_Vector3(x - other.x, y - other.y, z - other.z);
	}


	rlb_Vector3 rlb_Vector3::operator-(rlb_Vector2 const& other)
	{
		return rlb_Vector3(x - other.x, y - other.y, z);
	}


	rlb_Vector3& rlb_Vector3::operator-=(rlb_Vector3 const& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}


	rlb_Vector3& rlb_Vector3::operator-=(rlb_Vector2 const& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}


	rlb_Vector3 rlb_Vector3::operator*(float const& scale)
	{
		return rlb_Vector3(x * scale, y * scale, z * scale);
	}


	rlb_Vector3 rlb_Vector3::operator/(float const& scale)
	{
		return rlb_Vector3(x / scale, y / scale, z / scale);
	}


	bool rlb_Vector3::operator==(rlb_Vector3 const& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}


	rlb_Vector3::operator rlb_Vector2() const
	{
		return rlb_Vector2(x, y);
	}


	rlb_Vector3::operator rlb_Vector4() const
	{
		return rlb_Vector4(x, y, z, 0);
	}


    /*Vector3::operator const float* () const
    {
		return components;
    }*/
}