#include "Quaternion.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Math.hpp"


namespace jothly
{
	Quaternion& Quaternion::Normalize()
	{
		float magSquared;
		if (!IsNormalized(magSquared))
		{
			components.Normalize(magSquared);
		}

		return *this;
	}


	bool Quaternion::IsNormalized(float& out_magnitudeSquared)
	{
		out_magnitudeSquared = components.GetMagnitudeSquared();
		return Approx(out_magnitudeSquared, 1, MARGIN_OF_ERROR);
	}


	Quaternion Quaternion::GetInverse()
	{
		return Quaternion();
	}

	Vector3 Quaternion::GetEuler()
	{
		return Vector3();
	}

	Quaternion Quaternion::GetNormalized()
	{
		Quaternion quat = Quaternion(*this);
		int a = 0;
		a++;
		quat.Normalize();
		a++;
		return quat;
	}

	void Quaternion::SetEuler(Vector3 euler)
	{
	}

	Vector2 Quaternion::Rotate(Vector2 vec)
	{
		return Vector2();
	}

	Vector3 Quaternion::Rotate(Vector3 vec)
	{
		return Vector3();
	}

	Quaternion Quaternion::Rotate(Quaternion other)
	{
		return Quaternion();
	}
}