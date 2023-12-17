#pragma once

#include "raylib.h"


namespace jothly
{
	struct Vector3;


	struct Vector4
	{
		float x;
		float y;
		float z;
		float w;


		Vector4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) : x(_x), y(_y), z(_z), w(_w) {}

		Vector4 operator+(Vector4 const& other);
		Vector4 operator-(Vector4 const& other);
		Vector4 operator*(float const& scale);
		Vector4 operator/(float const& scale);

		operator Vector3() const;

		// Convert to RayLib version
		operator rlb_Vector3() const { return { x, y, z }; };
		operator rlb_Vector4() const { return { x, y, z, w }; };
	};
}