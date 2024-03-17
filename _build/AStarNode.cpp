#include "AStarNode.h"
#include "ShapeDrawing2D.h"


namespace jothly
{	
	AStarNode* AStarNode::Form2WayConnection(AStarNode* node)
    {
        Form1WayConnection(node);
		node->Form1WayConnection(this);
		return this;
    }


	AStarNode* AStarNode::Form1WayConnection(AStarNode* node)
	{
		connections.insert(node);
		return this;
	}


    AStarNode* AStarNode::Remove2WayConnection(AStarNode* node)
    {
        Remove1WayConnection(node);
		node->Remove1WayConnection(this);
		return this;
    }


	AStarNode* AStarNode::Remove1WayConnection(AStarNode* node)
	{
		connections.erase(node);
		return this;
	}


    void AStarNode::Draw(Color nodeColor, float nodeRadius, Color connectionLineColor, float connectionLineThickness)
	{
		ShapeDrawing2D::DrawCircle(pos, nodeRadius, nodeColor);

		for(auto it = connections.begin(); it != connections.end(); ++it)
		{
			DrawConnection(*it, connectionLineColor, connectionLineThickness);
		}
	}


	void AStarNode::DrawConnection(AStarNode* other, Color connectionLineColor, float connectionLineThickness)
	{
		ShapeDrawing2D::DrawLine(pos, other->pos, connectionLineThickness, connectionLineColor);
	}


	float AStarNode::CalculateG(AStarNode* proposedPathParent) const
	{
		return CalculateHeuristic(proposedPathParent) + proposedPathParent->pathCost;
	}


	float AStarNode::CalculateH(AStarNode* other) const
	{
		return CalculateHeuristic(other);
	}


	float AStarNode::GetScore() const
	{
		return pathCost + heuristicFromEnd;
	}


	void AStarNode::UpdateHeuristicFromEnd(AStarNode* end)
	{
		heuristicFromEnd = CalculateH(end);
	}


	bool AStarNode::UpdatePathDataWithLowerScore(AStarNode* proposedPathParent)
	{
		float g = CalculateG(proposedPathParent);

		if(g < pathCost)
		{
			pathCost = g;
			pathParent = proposedPathParent;
			return true;
		}

		return false;
	}


	float AStarNode::CalculateHeuristic(AStarNode* other) const
	{
		return (pos - other->pos).GetMagnitude();
	}
}