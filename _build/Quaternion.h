#pragma once

#include "Vector4.h"

// https://www.cprogramming.com/tutorial/3d/quaternions.html
// Quaternion rotation uses ZYX for euler rotation

namespace jothly
{
	struct Vector2;
	struct Vector3;

	class Quaternion
	{
		const float MARGIN_OF_ERROR = .00001f;

		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};

			Vector4 components;
		};

		public:

		const static Quaternion Identity() { return Quaternion(); }
		const static Vector4 IdentityComponents() { return Vector4(0, 0, 0, 1); }
		
		
		Quaternion(Vector4 _components = Quaternion::IdentityComponents()) { SetComponents(_components); }
		Quaternion(float _x, float _y, float _z, float _w) : Quaternion(Vector4(_x, _y, _z, _w)) {}
		Quaternion(float angle, Vector3 axis, bool degrees = true);
		Quaternion(Vector3 euler, bool degrees = true);
		Quaternion(const Quaternion& quat) { components = quat.components; }

		Quaternion& Normalize();
		bool IsNormalized(float& out_magnitudeSquared);

		Vector4 GetComponents() { return components; }
		Quaternion GetInverse();
		Quaternion GetNormalized();


		const void GetAngleAxisDeg(float &out_angle, Vector3 &out_axis);
		const void GetAngleAxisRad(float &out_angle, Vector3 &out_axis);
		const float GetAngleDeg();
		const float GetAngleRad();
		const Vector3 GetAxis();

		Vector4 SetComponents(Vector4 _components);
		void SetEulerDeg(Vector3 euler);
		void SetEulerRad(Vector3 euler);
		void SetAngleAxisDeg(float angle, Vector3 axis);
		void SetAngleAxisRad(float angle, Vector3 axis);

		Vector2 GetRotated(Vector2 vec);
		Vector3 GetRotated(Vector3 vec);
		Quaternion GetRotated(Quaternion other);

		void Rotate(Quaternion other);

		Quaternion& operator=(const Quaternion& other) 
		{ 
			components = other.components;
			return *this;
		}

		Quaternion operator*(const Quaternion& other) { return this->GetRotated(other); }

		operator rlb_Quaternion() const { return { components.x, components.y, components.z, components.w }; }
	};
}