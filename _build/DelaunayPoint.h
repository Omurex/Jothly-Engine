#pragma once

#include "Vector2.h"
#include "Texture.h"


namespace jothly
{
	struct DelaunayPoint
	{
		Vector2 pos;


		DelaunayPoint() : pos(Vector2(0)) {}
		DelaunayPoint(Vector2 _pos) : pos(_pos) {}

		void Draw(Texture* tex, Vector2 size);
	};
}