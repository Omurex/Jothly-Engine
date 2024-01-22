#pragma once

#include <raylib.h>


namespace jothly::con
{
	// Will be deprecated and replaced with Jothly version
	static const Transform rlb_DefaultTransform =
	{ 
		{0, 0, 0},		// Pos
		{0, 0, 0, 1},	// Rot
		{1, 1, 1}		// Scale
	};

	// Will be deprecated and replaced with Jothly version
	static const Vector2 rlb_DefaultVector2 =
	{
		0, 0
	};


	static const float VECTOR_MARGIN_OF_ERROR = .00001f;
}