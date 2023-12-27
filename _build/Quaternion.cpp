#include "Quaternion.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Math.h"
#include <raymath.h>


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


	Vector3 Quaternion::GetEulerDeg()
	{
		return GetEulerRad() * R2D;
	}


	Vector3 Quaternion::GetEulerRad()
	{
		// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

		/*float innerFirstSqrt = 1 + 2 * (w * y - x * z);
		float innerSecondSqrt = 1 - 2 * (w * y - x * z);

		float firstSqrt = sqrtf(innerFirstSqrt);
		float secondSqrt = sqrtf(innerSecondSqrt);
		float yTan = atan2f(firstSqrt, secondSqrt);

		float eulerY = (-PI / 2) + (2 * yTan);

		Vector3 euler = Vector3
		(
			atan2f(2 * (w * x + eulerY * z), 1 - 2 * (x * x + eulerY * eulerY)),
			eulerY,
			atan2f(2 * (w * z + x * eulerY), 1 - 2 * (eulerY * eulerY + z * z))
		);

		return euler;*/
		
		//Vector3 euler = QuaternionToEuler(*this);

		// https://stackoverflow.com/questions/70462758/c-sharp-how-to-convert-quaternions-to-euler-angles-xyz

		Vector3 angles = Vector3(0);

		// roll / x
		double sinr_cosp = 2 * (w * x + y * z);
		double cosr_cosp = 1 - 2 * (x * x + y * y);
		angles.x = (float)atan2f(sinr_cosp, cosr_cosp);

		// pitch / y
		double sinp = 2 * (w * y - z * x);
		if (abs(sinp) >= 1)
		{
			angles.y = sinp > 0 ? 1 : -1 * (PI / 2); //(float)Math.CopySign(Math.PI / 2, sinp);
		}
		else
		{
			angles.y = (float)asinf(sinp);
		}

		// yaw / z
		double siny_cosp = 2 * (w * z + x * y);
		double cosy_cosp = 1 - 2 * (y * y + z * z);
		angles.z = atan2f(siny_cosp, cosy_cosp);

		return angles;
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


	Vector2 Quaternion::GetRotated(Vector2 vec)
	{
		return Vector2();
	}


	Vector3 Quaternion::GetRotated(Vector3 vec)
	{
		return Vector3();
	}


	Quaternion Quaternion::GetRotated(Quaternion other)
	{
		Quaternion q = Quaternion(this->components);
		q.Rotate(other);

		return q;
	}


	void Quaternion::Rotate(Quaternion other)
	{
		// https://www.cprogramming.com/tutorial/3d/quaternions.html

		components = Vector4(
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w,
			w * other.w - x * other.x - y * other.y - z * other.z
		);
	}
}