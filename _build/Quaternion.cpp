#include "Quaternion.h"
#include "Vector2.h"
#include "Vector3.h"


namespace jothly
{
	Quaternion& Quaternion::Normalize()
	{
		components.Normalize();
		return *this;
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
		return Quaternion();
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