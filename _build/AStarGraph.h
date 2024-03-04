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

		Color nodeConnectionLineColor = Color::RED;
		float nodeConnectionLineThickness = 2;

		AStarGraph() {}
		~AStarGraph();
		
		AStarNode* CreateNode(Vector2 pos);
		std::vector<AStarNode*> GetNodes() const { return nodes; }

		void ReserveGraphSize(size_t size) { nodes.reserve(size); }

		void Clear();

		void Draw();
	};
}