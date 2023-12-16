#pragma once

#include "raylib.h"

namespace jothly
{
	struct Vector2
	{
		float x;
		float y;


		Vector2(float _x, float _y) : x(_x), y(_y) {}
	
		Vector2 operator+(Vector2 const& other);
		Vector2 operator-(Vector2 const& other);
		Vector2 operator*(float const& scale);
		Vector2 operator/(float const& scale);
	};
}