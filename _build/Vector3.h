#pragma once


#include "include/Vector2.hpp"
#include "include/Vector3.hpp"
#include "include/Vector4.hpp"


namespace jothly
{
	struct rlb_Vector2;
	struct rlb_Vector4;


	struct rlb_Vector3
	{
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};

			float components[3];
		};


		rlb_Vector3() : x(0), y(0), z(0) {}
		rlb_Vector3(float val) : x(val), y(val), z(val) {}
		rlb_Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		rlb_Vector3(const rlb_Vector3& vec3) : rlb_Vector3(vec3.x, vec3.y, vec3.z) {}
		rlb_Vector3(const raylib::rlb_Vector3& vec3) : rlb_Vector3(vec3.x, vec3.y, vec3.z) {}
		rlb_Vector3(const rlb_Vector2& vec2);
		rlb_Vector3(const rlb_Vector4& vec4);

		void Normalize();
		void Normalize(float precomputedMagnitudeSquared);
		rlb_Vector3 GetNormalized();
		rlb_Vector3 GetNormalized(float precomputedMagnitudeSquared);
		float GetMagnitude();
		float GetMagnitudeSquared();

		void Scale(float const& scale);

		rlb_Vector3 operator+(rlb_Vector3 const& other);
		rlb_Vector3 operator+(rlb_Vector2 const& other);
		rlb_Vector3& operator+=(rlb_Vector3 const& other);
		rlb_Vector3& operator+=(rlb_Vector2 const& other);
		rlb_Vector3 operator-(rlb_Vector3 const& other);
		rlb_Vector3 operator-(rlb_Vector2 const& other);
		rlb_Vector3& operator-=(rlb_Vector3 const& other);
		rlb_Vector3& operator-=(rlb_Vector2 const& other);
		rlb_Vector3 operator*(float const& scale);
		rlb_Vector3 operator/(float const& scale);
		bool operator==(rlb_Vector3 const& other);

		operator rlb_Vector2() const;
		operator rlb_Vector4() const;
		//operator const float* () const;

		// Convert to RayLib version
		operator raylib::rlb_Vector2() const { return { x, y }; }
		operator raylib::rlb_Vector3() const { return { x, y, z }; }
		operator raylib::rlb_Vector4() const { return {x, y, z, 0 }; }
	};
}