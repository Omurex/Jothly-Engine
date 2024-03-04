#pragma once
#include "Vector2.h"
#include "Color.h"
#include <vector>


namespace jothly
{
	struct AStarNode
	{
		std::vector<AStarNode*> connections;
		Vector2 pos;

		AStarNode(Vector2 _pos) : pos(_pos) {}

		void Draw(Color nodeColor, float nodeRadius, Color connectionLineColor, float connectionLineThickness);
	};
}