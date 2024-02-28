#pragma once

#include "Vector2.h"
#include "Texture.h"
#include "Color.h"


namespace jothly
{
	struct DelaunayPoint
	{
		Vector2 pos;


		DelaunayPoint() : pos(Vector2(0)) {}
		DelaunayPoint(Vector2 _pos) : pos(_pos) {}

		void Draw(float radius, Color color);
	};
}