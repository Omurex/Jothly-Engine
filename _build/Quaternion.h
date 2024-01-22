#pragma once

#include "Vector4.h"
#include "include/Vector4.hpp"


// https://www.cprogramming.com/tutorial/3d/quaternions.html
// Quaternion rotation uses ZYX for euler rotation

namespace jothly
{
	struct rlb_Vector2;
	struct rlb_Vector3;

	class rlb_Quaternion
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

			rlb_Vector4 components;
		};

		public:

		const static rlb_Quaternion Identity() { return rlb_Quaternion(); }
		const static rlb_Vector4 IdentityComponents() { return rlb_Vector4(0, 0, 0, 1); }
		
		
		rlb_Quaternion(rlb_Vector4 _components = rlb_Quaternion::IdentityComponents()) { SetComponents(_components); }
		rlb_Quaternion(float _x, float _y, float _z, float _w) : rlb_Quaternion(rlb_Vector4(_x, _y, _z, _w)) {}
		rlb_Quaternion(float angle, rlb_Vector3 axis, bool degrees = true);
		rlb_Quaternion(rlb_Vector3 euler, bool degrees = true);
		rlb_Quaternion(const rlb_Quaternion& quat) { components = quat.components; }

		static rlb_Quaternion Quaternion2D(float angle, bool degrees = true);

		rlb_Vector4 GetComponents() { return components; }
		
		rlb_Quaternion& Normalize();
		bool IsNormalized(float& out_magnitudeSquared);
		rlb_Quaternion GetNormalized();

		void Invert();
		rlb_Quaternion GetInverse();


		const void GetAngleAxisDeg(float &out_angle, rlb_Vector3 &out_axis);
		const void GetAngleAxisRad(float &out_angle, rlb_Vector3 &out_axis);
		const float GetAngleDeg();
		const float GetAngleRad();
		const rlb_Vector3 GetAxis();

		rlb_Vector4 SetComponents(rlb_Vector4 _components);
		void SetEulerDeg(rlb_Vector3 euler);
		void SetEulerRad(rlb_Vector3 euler);
		void SetAngleAxisDeg(float angle, rlb_Vector3 axis);
		void SetAngleAxisRad(float angle, rlb_Vector3 axis);

		static rlb_Vector4 Hamiltonian(rlb_Vector4 const& v1, rlb_Vector4 const& v2);

		rlb_Vector2 GetRotated(rlb_Vector2 vec);
		rlb_Vector3 GetRotated(rlb_Vector3 vec);
		rlb_Vector4 GetRotated(rlb_Vector4 vec);
		rlb_Quaternion GetRotated(rlb_Quaternion other);

		// STILL NEEDS TESTING
		rlb_Vector2 GetRotatedAroundPoint(rlb_Vector2 vecToRotate, rlb_Vector2 point);
		rlb_Vector3 GetRotatedAroundPoint(rlb_Vector3 vecToRotate, rlb_Vector3 point);
		rlb_Vector4 GetRotatedAroundPoint(rlb_Vector4 vecToRotate, rlb_Vector4 point);

		void Rotate(rlb_Quaternion other);

		rlb_Quaternion& operator=(const rlb_Quaternion& other) 
		{ 
			components = other.components;
			return *this;
		}

		rlb_Vector2 operator*(const rlb_Vector2& other);
		rlb_Vector3 operator*(const rlb_Vector3& other);
		rlb_Vector4 operator*(const rlb_Vector4& other);
		rlb_Quaternion operator*(const rlb_Quaternion& other) { return this->GetRotated(other); }

		operator raylib::rlb_Vector4() const { return { components.x, components.y, components.z, components.w }; }
	};
}