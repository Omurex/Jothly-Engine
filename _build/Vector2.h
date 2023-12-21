#pragma once

#include "raylib.h"


namespace jothly
{
	struct Vector3;
	
	
	struct Vector2
	{
		union
		{
			struct
			{
				float x;
				float y;
			};

			float components[2];
		};


		Vector2(float _x = 0, float _y = 0) : x(_x), y(_y) {}
		Vector2(const Vector2& vec2) : Vector2(vec2.x, vec2.y) {}
		Vector2(const Vector3& vec3);

		void Normalize();
		void Normalize(float precomputedMagnitudeSquared);
		Vector2 GetNormalized();
		Vector2 GetNormalized(float precomputedMagnitudeSquared);
		float GetMagnitude();
		float GetMagnitudeSquared();
	
		Vector2 operator+(Vector2 const& other);
		Vector2 operator-(Vector2 const& other);
		Vector2 operator*(float const& scale);
		Vector2 operator/(float const& scale);
		bool operator==(Vector2 const& other);

		operator Vector3() const;

		operator rlb_Vector2() { return {x, y}; }; // Convert to RayLib version
	};
}