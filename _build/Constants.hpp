#pragma once

#include <raylib.h>


namespace jothly::con
{
	static const Transform DefaultTransform =
	{ 
		{0, 0, 0},		// Pos
		{0, 0, 0, 1},	// Rot
		{1, 1, 1}		// Scale
	};

	static const Vector2 DefaultVector2 =
	{
		0, 0
	};
}