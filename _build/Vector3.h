#pragma once

#include "raylib.h"


namespace jothly
{
	struct Vector2;
	struct Vector4;


	struct Vector3
	{
		float x;
		float y;
		float z;


		Vector3(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

		Vector3 operator+(Vector3 const& other);
		Vector3 operator-(Vector3 const& other);
		Vector3 operator*(float const& scale);
		Vector3 operator/(float const& scale);

		operator Vector2() const;
		operator Vector4() const;

		// Convert to RayLib version
		operator rlb_Vector2() const { return { x, y }; }
		operator rlb_Vector3() const { return { x, y, z }; }
		operator rlb_Vector4() const { return {x, y, z, 0 }; }
	};
}