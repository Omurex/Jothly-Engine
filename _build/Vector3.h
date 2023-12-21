#pragma once

#include "raylib.h"


namespace jothly
{
	struct Vector2;
	struct Vector4;


	struct Vector3
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


		Vector3(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}
		Vector3(const Vector3& vec3) : Vector3(vec3.x, vec3.y, vec3.z) {}
		Vector3(const Vector2& vec2);
		Vector3(const Vector4& vec4);

		void Normalize();
		void Normalize(float precomputedMagnitudeSquared);
		Vector3 GetNormalized();
		Vector3 GetNormalized(float precomputedMagnitudeSquared);
		float GetMagnitude();
		float GetMagnitudeSquared();

		Vector3 operator+(Vector3 const& other);
		Vector3 operator-(Vector3 const& other);
		Vector3 operator*(float const& scale);
		Vector3 operator/(float const& scale);
		bool operator==(Vector3 const& other);

		operator Vector2() const;
		operator Vector4() const;

		// Convert to RayLib version
		operator rlb_Vector2() const { return { x, y }; }
		operator rlb_Vector3() const { return { x, y, z }; }
		operator rlb_Vector4() const { return {x, y, z, 0 }; }
	};
}