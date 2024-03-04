#pragma once
#include "Vector2.h"
#include "Color.h"
#include <vector>


namespace jothly
{
	struct AStarNode
	{
		private:
		AStarNode* AddReverseConnection(AStarNode* node);
		
		public:
		std::vector<AStarNode*> connections;
		Vector2 pos;

		AStarNode(Vector2 _pos) : pos(_pos) {}

		AStarNode* Form2WayConnection(AStarNode* node);

		void Draw(Color nodeColor, float nodeRadius, Color connectionLineColor, float connectionLineThickness);

	};
}