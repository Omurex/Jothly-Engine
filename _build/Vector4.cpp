#include "Vector4.h"
#include "Vector3.h"
#include "Math.h"
#include "Constants.hpp"


namespace jothly
{
	rlb_Vector4::rlb_Vector4(const rlb_Vector3& vec3) : rlb_Vector4(vec3.x, vec3.y, vec3.z, 0) {}


	void rlb_Vector4::Normalize()
    {
		float sqrMag = GetMagnitudeSquared();
		Normalize(sqrMag);
    }


	void rlb_Vector4::Normalize(float precomputedMagnitudeSquared)
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


	rlb_Vector4 rlb_Vector4::GetNormalized()
	{
		rlb_Vector4 vec = rlb_Vector4(*this);
		vec.Normalize();
		return vec;
	}


	rlb_Vector4 rlb_Vector4::GetNormalized(float precomputedMagnitudeSquared)
	{
		rlb_Vector4 vec = rlb_Vector4(*this);
		vec.Normalize(precomputedMagnitudeSquared);
		return vec;
	}


	float rlb_Vector4::GetMagnitude()
	{
		return sqrtf(GetMagnitudeSquared());
	}


	float rlb_Vector4::GetMagnitudeSquared()
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}


	void rlb_Vector4::Scale(float const& scale)
	{
		x *= scale; y *= scale; z *= scale; w *= scale;
	}


    rlb_Vector4 rlb_Vector4::operator+(rlb_Vector4 const& other)
	{
		return rlb_Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}


	rlb_Vector4 rlb_Vector4::operator-(rlb_Vector4 const& other)
	{
		return rlb_Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}


	rlb_Vector4 rlb_Vector4::operator*(float const& scale)
	{
		return rlb_Vector4(x * scale, y * scale, z * scale, w * scale);
	}


	rlb_Vector4 rlb_Vector4::operator/(float const& scale)
	{
		return rlb_Vector4(x / scale, y / scale, z / scale, w / scale);
	}


    bool rlb_Vector4::operator==(rlb_Vector4 const& other)
    {
		return x == other.x && y == other.y && z == other.z && w == other.w;
    }


	rlb_Vector4::operator rlb_Vector3() const
	{
		return rlb_Vector3(x, y, z);
	}


	/*Vector4::operator const float* () const
	{
		return components;
	}*/
}
