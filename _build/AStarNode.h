#pragma once
#include "Vector2.h"
#include "Color.h"
#include <vector>


namespace jothly
{
	struct AStarNode
	{
		private:
		AStarNode* pathParent = nullptr;
		float pathCost = 0;

		AStarNode* AddReverseConnection(AStarNode* node);
		
		public:
		std::vector<AStarNode*> connections;
		Vector2 pos;

		AStarNode(Vector2 _pos) : pos(_pos) {}

		AStarNode* GetPathParent() const { return pathParent; }
		float GetPathCost() const { return pathCost; }

		void SetPathParent(AStarNode* _pathParent) { pathParent = _pathParent; }

		AStarNode* Form2WayConnection(AStarNode* node);

		void Draw(Color nodeColor, float nodeRadius, Color connectionLineColor, float connectionLineThickness);

		float CalculateG(AStarNode* proposedPathParent) const; // Distance between current node and start node
		float CalculateH(AStarNode* end) const; // Estimated distance from current node to the end node
		float CalculateScore(AStarNode* start, AStarNode* end) const;

		bool UpdatePathDataIfShorter(AStarNode* proposedPathParent); // Returns true if path data changed, false if otherwise

		float CalculateHeuristic(AStarNode* other) const; // Heuristic we use is square of distance between nodes

		void ResetPathFindingVariables() { pathParent = nullptr; }
	};
}