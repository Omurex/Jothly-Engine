#pragma once

#include "Vector4.h"
#include "include/Vector4.hpp"


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

		static Quaternion Quaternion2D(float angle, bool degrees = true);

		Vector4 GetComponents() { return components; }
		
		Quaternion& Normalize();
		bool IsNormalized(float& out_magnitudeSquared);
		Quaternion GetNormalized();

		void Invert();
		Quaternion GetInverse();


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

		static Vector4 Hamiltonian(Vector4 const& v1, Vector4 const& v2);

		Vector2 GetRotated(Vector2 vec);
		Vector3 GetRotated(Vector3 vec);
		Vector4 GetRotated(Vector4 vec);
		Quaternion GetRotated(Quaternion other);

		// STILL NEEDS TESTING
		Vector2 GetRotatedAroundPoint(Vector2 vecToRotate, Vector2 point);
		Vector3 GetRotatedAroundPoint(Vector3 vecToRotate, Vector3 point);
		Vector4 GetRotatedAroundPoint(Vector4 vecToRotate, Vector4 point);

		void Rotate(Quaternion other);

		Quaternion& operator=(const Quaternion& other) 
		{ 
			components = other.components;
			return *this;
		}

		Vector2 operator*(const Vector2& other);
		Vector3 operator*(const Vector3& other);
		Vector4 operator*(const Vector4& other);
		Quaternion operator*(const Quaternion& other) { return this->GetRotated(other); }

		operator raylib::Vector4() const { return { components.x, components.y, components.z, components.w }; }
	};
}