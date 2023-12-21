#pragma once

#include "raylib.h"


namespace jothly
{
	struct Vector3;


	struct Vector4
	{
		union
		{
			struct 
			{
				float x;
				float y;
				float z;
				float w; 
			};

			float components[4];
		};


		Vector4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) : x(_x), y(_y), z(_z), w(_w) {}
		Vector4(const Vector4& vec4) : Vector4(vec4.x, vec4.y, vec4.z, vec4.w) {}
		Vector4(const Vector3& vec3);

		void Normalize();
		void Normalize(float precomputedMagnitudeSquared);
		Vector4 GetNormalized();
		Vector4 GetNormalized(float precomputedMagnitudeSquared);
		float GetMagnitude();
		float GetMagnitudeSquared();

		Vector4 operator+(Vector4 const& other);
		Vector4 operator-(Vector4 const& other);
		Vector4 operator*(float const& scale);
		Vector4 operator/(float const& scale);
		bool operator==(Vector4 const& other);

		operator Vector3() const;
		operator const float*() const;

		// Convert to RayLib version
		operator rlb_Vector3() const { return { x, y, z }; };
		operator rlb_Vector4() const { return { x, y, z, w }; };
	};
}