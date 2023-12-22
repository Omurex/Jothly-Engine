#pragma once

#include "Vector4.h"

// https://www.cprogramming.com/tutorial/3d/quaternions.html

namespace jothly
{
	struct Vector2;
	struct Vector3;

	class Quaternion
	{
		const float MARGIN_OF_ERROR = .001f;

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
		Quaternion(Vector3 euler, bool degrees = true);
		Quaternion(const Quaternion& quat) { components = quat.components; }

		Quaternion& Normalize();
		bool IsNormalized(float& out_magnitudeSquared);

		Vector4 GetComponents() { return components; }
		Quaternion GetInverse();
		Vector3 GetEuler();
		Quaternion GetNormalized();

		Vector4 SetComponents(Vector4 _components);
		void SetEulerDeg(Vector3 euler);
		void SetEulerRad(Vector3 euler);

		Vector2 Rotate(Vector2 vec);
		Vector3 Rotate(Vector3 vec);
		Quaternion Rotate(Quaternion other);

		Quaternion& operator=(const Quaternion& other) 
		{ 
			components = other.components;
			return *this;
		}

		Quaternion operator*(const Quaternion& other) { return this->Rotate(other); }

		operator rlb_Quaternion() const { return { components.x, components.y, components.z, components.w }; }
	};
}