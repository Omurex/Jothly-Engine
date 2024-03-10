#include "AStarNode.h"
#include "ShapeDrawing2D.h"


namespace jothly
{
	AStarNode* AStarNode::AddReverseConnection(AStarNode* node)
	{
		connections.push_back(node);
		return this;
	}

	
	AStarNode* AStarNode::Form2WayConnection(AStarNode* node)
    {
        connections.push_back(node);
		node->AddReverseConnection(this);
		return this;
    }


    void AStarNode::Draw(Color nodeColor, float nodeRadius, Color connectionLineColor, float connectionLineThickness)
	{
		ShapeDrawing2D::DrawCircle(pos, nodeRadius, nodeColor);

		for (int i = 0; i < connections.size(); i++)
		{
			ShapeDrawing2D::DrawLine(pos, connections[i]->pos, connectionLineThickness, connectionLineColor);
		}
	}

	float AStarNode::CalculateG(AStarNode* proposedPathParent) const
	{
		return 0.0f;
	}


	float AStarNode::CalculateH(AStarNode* end) const
	{
		return 0.0f;
	}


	float AStarNode::CalculateScore(AStarNode* start, AStarNode* end)
	{
		return 0.0f;
	}


	float AStarNode::CalculateHeuristic(AStarNode* other)
	{
		return (pos - other->pos).GetMagnitudeSquared();
	}
}