#include "Vector2.h"
#include "Vector3.h"
#include "Math.h"
#include "Constants.hpp"


namespace jothly
{
	rlb_Vector2::rlb_Vector2(const rlb_Vector3& vec3) : rlb_Vector2(vec3.x, vec3.y) {}


	void rlb_Vector2::Normalize()
	{
		float sqrMag = GetMagnitudeSquared();
		Normalize(sqrMag);
	}


	void rlb_Vector2::Normalize(float precomputedMagnitudeSquared)
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


	rlb_Vector2 rlb_Vector2::GetNormalized()
	{
		rlb_Vector2 vec = rlb_Vector2(*this);
		vec.Normalize();
		return vec;
	}


	rlb_Vector2 rlb_Vector2::GetNormalized(float precomputedMagnitudeSquared)
	{
		rlb_Vector2 vec = rlb_Vector2(*this);
		vec.Normalize(precomputedMagnitudeSquared);
		return vec;
	}


	float rlb_Vector2::GetMagnitude()
	{
		return sqrtf(GetMagnitudeSquared());
	}


	float rlb_Vector2::GetMagnitudeSquared()
	{
		return (x * x) + (y * y);
	}


	void rlb_Vector2::Scale(float const& scale)
	{
		x *= scale; y *= scale;
	}


	rlb_Vector2 rlb_Vector2::operator+(rlb_Vector2 const& other)
	{
		return rlb_Vector2(x + other.x, y + other.y);
	}


    rlb_Vector3 rlb_Vector2::operator+(rlb_Vector3 const& other)
    {
        return rlb_Vector3(other.x + x, other.y + y, other.z);
    }


	rlb_Vector2& rlb_Vector2::operator+=(rlb_Vector2 const& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}


	rlb_Vector2& rlb_Vector2::operator+=(rlb_Vector3 const& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}


	rlb_Vector2 rlb_Vector2::operator-(rlb_Vector2 const& other)
	{
		return rlb_Vector2(x - other.x, y - other.y);
	}


	rlb_Vector3 rlb_Vector2::operator-(rlb_Vector3 const& other)
	{
		return rlb_Vector3(x - other.x, y - other.y, 0 - other.z);
	}


	rlb_Vector2& rlb_Vector2::operator-=(rlb_Vector2 const& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}


	rlb_Vector2& rlb_Vector2::operator-=(rlb_Vector3 const& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}


	rlb_Vector2 rlb_Vector2::operator*(float const& scale)
	{
		return rlb_Vector2(x * scale, y * scale);
	}


	rlb_Vector2 rlb_Vector2::operator/(float const& scale)
	{
		return rlb_Vector2(x / scale, y / scale);
	}


    bool rlb_Vector2::operator==(rlb_Vector2 const& other)
    {
        return x == other.x && y == other.y;
    }


	rlb_Vector2::operator rlb_Vector3() const
	{
		return rlb_Vector3(x, y, 0);
	}
}