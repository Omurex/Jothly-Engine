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
		quat.Normalize();
		return quat;
	}


	Vector4 Quaternion::SetComponents(Vector4 _components)
	{
		components = _components;
		Normalize();
		return components;
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
		// https://www.cprogramming.com/tutorial/3d/quaternions.html
		Vector4 rotatedComponents = Vector4(
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w,
			w * other.w - x * other.x - y * other.y - z * other.z
		);

		return Quaternion(rotatedComponents);
	}
}