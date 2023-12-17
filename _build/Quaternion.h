#pragma once

#include "Vector4.h"
#include "raylib.h"



namespace jothly
{
	struct Vector2;
	struct Vector3;

	class Quaternion
	{
		Vector4 components;

		public:

		const static Quaternion Identity() { return Quaternion(); }
		const static Vector4 IdentityComponents() { return Vector4(0, 0, 0, 1); }
		
		
		Quaternion(Vector4 _components = Quaternion::IdentityComponents()) : components(_components) {}
		Quaternion(const Quaternion& quat) { components = quat.components; }

		Quaternion& Normalize();

		Quaternion GetInverse();
		Vector3 GetEuler();
		Quaternion GetNormalized();

		void SetEuler(Vector3 euler);

		Vector2 Rotate(Vector2 vec);
		Vector3 Rotate(Vector3 vec);
		Quaternion Rotate(Quaternion other);

		operator rlb_Quaternion() const { return { components.x, components.y, components.z, components.w }; }
	};
}