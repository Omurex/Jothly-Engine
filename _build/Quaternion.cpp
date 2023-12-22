#include "Quaternion.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Math.h"


namespace jothly
{
	Quaternion::Quaternion(Vector3 euler, bool degrees)
	{
		if (degrees) SetEulerDeg(euler); 
		else SetEulerRad(euler);
	}


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
		// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles



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


	void Quaternion::SetEulerDeg(Vector3 euler)
	{
		SetEulerRad(euler * DEG2RAD);
	}


	void Quaternion::SetEulerRad(Vector3 euler)
	{
		// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

		float sx = sinf(euler.x * .5f);
		float cx = cosf(euler.x * .5f);

		float sy = sinf(euler.y * .5f);
		float cy = cosf(euler.y * .5f);

		float sz = sinf(euler.z * .5f);
		float cz = cosf(euler.z * .5f);

		w = cx * cy * cz + sx * sy * sz;
		x = sx * cy * cz - cx * sy * sz;
		y = cx * sy * cz + sx * cy * sz;
		z = cx * cy * sz - sx * sy * cz;
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