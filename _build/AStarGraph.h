#pragma once
#include "AStarNode.h"


namespace jothly
{
	class AStarGraph
	{
		std::vector<AStarNode*> nodes;

		AStarNode* lastPathComputedDestination = nullptr;


		public:
		Color nodeColor = Color::PURPLE;
		float nodeRadius = 5;

		Color nodeConnectionLineColor = Color::RED;
		float nodeConnectionLineThickness = 2;

		Color pathLineColor = Color::GREEN;
		float pathLineThickness = 3;

		AStarGraph() {}
		~AStarGraph();
		
		AStarNode* CreateNode(Vector2 pos);
		std::vector<AStarNode*> GetNodes() const { return nodes; }

		void ReserveGraphSize(size_t size) { nodes.reserve(size); }

		std::vector<AStarNode*> CalculatePath(AStarNode* start, AStarNode* end);

		void Clear();

		void Draw(bool drawNodes = true, bool drawConnections = true, bool drawLastComputedPath = true);
	};
}