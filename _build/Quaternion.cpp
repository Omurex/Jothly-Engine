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

		Normalize();
	}


	Quaternion::Quaternion(float angle, Vector3 axis, bool degrees)
	{
		if(degrees) SetAngleAxisDeg(angle, axis);
		else SetAngleAxisRad(angle, axis);

		Normalize();
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


	Quaternion Quaternion::GetNormalized()
	{
		Quaternion quat = Quaternion(*this);
		quat.Normalize();
		return quat;
	}


	const void Quaternion::GetAngleAxisDeg(float& out_angle, Vector3& out_axis)
	{
		Normalize();

		out_angle = GetAngleDeg();
		out_axis = GetAxis();
	}


	const void Quaternion::GetAngleAxisRad(float& out_angle, Vector3& out_axis)
	{
		Normalize();

		out_angle = GetAngleRad();
		out_axis = GetAxis();
	}


	const float Quaternion::GetAngleDeg()
	{
		return GetAngleRad() * RAD2DEG;
	}


	const float Quaternion::GetAngleRad()
	{
		// https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/index.htm
		return 2 * acosf(w);
	}
	

	const Vector3 Quaternion::GetAxis()
	{
		// https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/index.htm

		// If at 0 singularity, axis doesn't matter. Replace with arbitrary normalized x axis
		if (Approx(w, 1, MARGIN_OF_ERROR))
		{
			return Vector3(1, 0, 0);
		}

		float mag = sqrtf(1 - (w * w));

		return Vector3(
			x / mag,
			y / mag,
			z / mag
		);
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


	void Quaternion::SetAngleAxisDeg(float angle, Vector3 axis)
	{
		SetAngleAxisRad(angle * DEG2RAD, axis);
	}


	void Quaternion::SetAngleAxisRad(float angle, Vector3 axis)
	{
		// https://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm

		axis.Normalize();

		float s = sinf(angle / 2.0f);

		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
		w = cosf(angle / 2.0f);
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