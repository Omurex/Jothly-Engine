#include "Quaternion.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Math.h"


namespace jothly
{
	rlb_Quaternion::rlb_Quaternion(rlb_Vector3 euler, bool degrees)
	{
		if (degrees) SetEulerDeg(euler); 
		else SetEulerRad(euler);

		Normalize();
	}


	rlb_Quaternion rlb_Quaternion::Quaternion2D(float angle, bool degrees)
	{
		return rlb_Quaternion(angle, rlb_Vector3(0, 0, 1), degrees);
	}


	rlb_Quaternion::rlb_Quaternion(float angle, rlb_Vector3 axis, bool degrees)
	{
		if(degrees) SetAngleAxisDeg(angle, axis);
		else SetAngleAxisRad(angle, axis);

		Normalize();
	}


	rlb_Quaternion& rlb_Quaternion::Normalize()
	{
		float magSquared;
		if (!IsNormalized(magSquared))
		{
			components.Normalize(magSquared);
		}

		return *this;
	}


	bool rlb_Quaternion::IsNormalized(float& out_magnitudeSquared)
	{
		out_magnitudeSquared = components.GetMagnitudeSquared();
		return Approx(out_magnitudeSquared, 1, MARGIN_OF_ERROR);
	}


	void rlb_Quaternion::Invert()
	{
		x = -x; 
		y = -y;
		z = -z;
	}


	rlb_Quaternion rlb_Quaternion::GetInverse()
	{
		rlb_Quaternion q = rlb_Quaternion(x, y, z, w);
		q.Invert();
		return q;
	}


	rlb_Quaternion rlb_Quaternion::GetNormalized()
	{
		rlb_Quaternion quat = rlb_Quaternion(*this);
		quat.Normalize();
		return quat;
	}


	const void rlb_Quaternion::GetAngleAxisDeg(float& out_angle, rlb_Vector3& out_axis)
	{
		Normalize();

		out_angle = GetAngleDeg();
		out_axis = GetAxis();
	}


	const void rlb_Quaternion::GetAngleAxisRad(float& out_angle, rlb_Vector3& out_axis)
	{
		Normalize();

		out_angle = GetAngleRad();
		out_axis = GetAxis();
	}


	const float rlb_Quaternion::GetAngleDeg()
	{
		return GetAngleRad() * RAD2DEG;
	}


	const float rlb_Quaternion::GetAngleRad()
	{
		// https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/index.htm
		return 2 * acosf(w);
	}
	

	const rlb_Vector3 rlb_Quaternion::GetAxis()
	{
		// https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/index.htm

		// If at 0 singularity, axis doesn't matter. Replace with arbitrary normalized x axis
		if (Approx(w, 1, MARGIN_OF_ERROR))
		{
			return rlb_Vector3(1, 0, 0);
		}

		float mag = sqrtf(1 - (w * w));

		return rlb_Vector3(
			x / mag,
			y / mag,
			z / mag
		);
	}


	rlb_Vector4 rlb_Quaternion::SetComponents(rlb_Vector4 _components)
	{
		components = _components;
		Normalize();
		return components;
	}


	void rlb_Quaternion::SetEulerDeg(rlb_Vector3 euler)
	{
		SetEulerRad(euler * DEG2RAD);
	}


	void rlb_Quaternion::SetEulerRad(rlb_Vector3 euler)
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


	void rlb_Quaternion::SetAngleAxisDeg(float angle, rlb_Vector3 axis)
	{
		SetAngleAxisRad(angle * DEG2RAD, axis);
	}


	void rlb_Quaternion::SetAngleAxisRad(float angle, rlb_Vector3 axis)
	{
		// https://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm

		axis.Normalize();

		float s = sinf(angle / 2.0f);

		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
		w = cosf(angle / 2.0f);
	}


	rlb_Vector4 rlb_Quaternion::Hamiltonian(rlb_Vector4 const& v1, rlb_Vector4 const& v2)
	{
		return rlb_Vector4(
			v1.w * v2.x + v1.x * v2.w + v1.y * v2.z - v1.z * v2.y,
			v1.w * v2.y - v1.x * v2.z + v1.y * v2.w + v1.z * v2.x,
			v1.w * v2.z + v1.x * v2.y - v1.y * v2.x + v1.z * v2.w,
			v1.w * v2.w - v1.x * v2.x - v1.y * v2.y - v1.z * v2.z
		);
	}


	rlb_Vector2 rlb_Quaternion::GetRotated(rlb_Vector2 vec)
	{
		return (rlb_Vector2) GetRotated((rlb_Vector3) vec);
	}


	rlb_Vector3 rlb_Quaternion::GetRotated(rlb_Vector3 vec)
	{
		return (rlb_Vector3) GetRotated((rlb_Vector4) vec);
	}


	rlb_Vector4 rlb_Quaternion::GetRotated(rlb_Vector4 v)
	{
		// https://math.stackexchange.com/questions/40164/how-do-you-rotate-a-vector-by-a-unit-quaternion
		rlb_Quaternion inverse = GetInverse();
		return Hamiltonian(Hamiltonian(this->components, v), inverse.components);
	}


	rlb_Quaternion rlb_Quaternion::GetRotated(rlb_Quaternion other)
	{
		rlb_Quaternion q = rlb_Quaternion(this->components);
		q.Rotate(other);

		return q;
	}


	rlb_Vector2 rlb_Quaternion::GetRotatedAroundPoint(rlb_Vector2 vecToRotate, rlb_Vector2 point)
	{
		return (rlb_Vector2) GetRotatedAroundPoint((rlb_Vector3) vecToRotate, (rlb_Vector3) point);
	}


	rlb_Vector3 rlb_Quaternion::GetRotatedAroundPoint(rlb_Vector3 vecToRotate, rlb_Vector3 point)
	{
		return (rlb_Vector3) GetRotatedAroundPoint((rlb_Vector4) vecToRotate, (rlb_Vector4) point);
	}


	rlb_Vector4 rlb_Quaternion::GetRotatedAroundPoint(rlb_Vector4 vecToRotate, rlb_Vector4 point)
	{
		return GetRotated(vecToRotate - point) + point;
	}


	void rlb_Quaternion::Rotate(rlb_Quaternion other)
	{
		// https://www.cprogramming.com/tutorial/3d/quaternions.html

		components = rlb_Vector4(
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w,
			w * other.w - x * other.x - y * other.y - z * other.z
		);

		Normalize();
	}


	rlb_Vector2 rlb_Quaternion::operator*(const rlb_Vector2& other)
	{
		return this->GetRotated(other);
	}


	rlb_Vector3 rlb_Quaternion::operator*(const rlb_Vector3& other)
	{
		return this->GetRotated(other);
	}


	rlb_Vector4 rlb_Quaternion::operator*(const rlb_Vector4& other)
	{
		return this->GetRotated(other);
	}
}