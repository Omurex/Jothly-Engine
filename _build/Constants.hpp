#pragma once

#include <raylib.h>


namespace jothly::con
{
	static const rlb_Transform rlb_DefaultTransform =
	{ 
		{0, 0, 0},		// Pos
		{0, 0, 0, 1},	// Rot
		{1, 1, 1}		// Scale
	};

	static const rlb_Vector2 rlb_DefaultVector2 =
	{
		0, 0
	};
}