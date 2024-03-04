#pragma once
#include "AStarNode.h"


namespace jothly
{
	class AStarGraph
	{
		std::vector<AStarNode*> nodes;


		public:
		Color nodeColor = Color::PURPLE;
		float nodeRadius = 5;

		Color nodeConnectionLineColor = Color::BLACK;
		float nodeConnectionLineThickness = 5;

		AStarGraph() {}
		~AStarGraph();
		
		AStarNode* CreateNode(Vector2 pos);

		void Clear();

		void Draw();
	};
}