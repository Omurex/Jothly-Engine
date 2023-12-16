#pragma once

#include "raylib.h"


namespace jothly
{
	struct Vector3;
	
	
	struct Vector2
	{
		float x;
		float y;


		Vector2(float _x = 0, float _y = 0) : x(_x), y(_y) {}
	
		Vector2 operator+(Vector2 const& other);
		Vector2 operator-(Vector2 const& other);
		Vector2 operator*(float const& scale);
		Vector2 operator/(float const& scale);

		operator Vector3() const;

		operator rlb_Vector2() { return {x, y}; }; // Convert to RayLib version
	};
}