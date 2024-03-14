#pragma once
#include "Vector2.h"
#include "Color.h"
#include <vector>
#include <limits>


namespace jothly
{
	struct AStarNode
	{
		private:
		AStarNode* pathParent = nullptr;
		float pathCost = 0;
		float heuristicFromEnd = 0;

		AStarNode* AddReverseConnection(AStarNode* node);
		
		public:
		std::vector<AStarNode*> connections;
		Vector2 pos;

		AStarNode(Vector2 _pos) : pos(_pos) {}

		AStarNode* GetPathParent() const { return pathParent; }
		float GetPathCost() const { return pathCost; }

		void SetPathParent(AStarNode* _pathParent) { pathParent = _pathParent; }
		void SetPathCost(float _pathCost) { pathCost = _pathCost; }

		AStarNode* Form2WayConnection(AStarNode* node);

		void Draw(Color nodeColor, float nodeRadius, Color connectionLineColor, float connectionLineThickness);
		void DrawConnection(AStarNode* other, Color connectionLineColor, float connectionLineThickness);

		float CalculateG(AStarNode* proposedPathParent) const; // Distance between current node and start node
		float CalculateH(AStarNode* end) const; // Estimated distance from current node to the end node

		float GetScore() const;

		void UpdateHeuristicFromEnd(AStarNode* end);
		bool UpdatePathDataWithLowerScore(AStarNode* proposedPathParent); // Returns true if path data changed, false if otherwise

		float CalculateHeuristic(AStarNode* other) const; // Heuristic we use is square of distance between nodes

		void ResetPathFindingVariables() { pathParent = nullptr; pathCost = std::numeric_limits<float>::max(); }
	};
}