#pragma once

#include "Vector4.h"



namespace jothly
{
	struct Vector2;
	struct Vector3;

	class Quaternion
	{
		const float MARGIN_OF_ERROR = .001f;

		Vector4 components;

		public:

		const static Quaternion Identity() { return Quaternion(); }
		const static Vector4 IdentityComponents() { return Vector4(0, 0, 0, 1); }
		
		
		Quaternion(Vector4 _components = Quaternion::IdentityComponents()) : components(_components) {}
		Quaternion(const Quaternion& quat) { components = quat.components; }

		Quaternion& Normalize();
		bool IsNormalized(float& out_magnitudeSquared);

		Vector4 GetComponents() { return components; }
		Quaternion GetInverse();
		Vector3 GetEuler();
		Quaternion GetNormalized();

		void SetEuler(Vector3 euler);

		Vector2 Rotate(Vector2 vec);
		Vector3 Rotate(Vector3 vec);
		Quaternion Rotate(Quaternion other);

		Quaternion operator=(const Quaternion& other) const {
		int a = 0;
		a++;
		return Quaternion(other.components); }

		operator rlb_Quaternion() const { return { components.x, components.y, components.z, components.w }; }
	};
}