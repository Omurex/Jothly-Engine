#include "AStarNode.h"
#include "ShapeDrawing2D.h"


namespace jothly
{
	void AStarNode::Draw(Color nodeColor, float nodeRadius, Color connectionLineColor, float connectionLineThickness)
	{
		ShapeDrawing2D::DrawCircle(pos, nodeRadius, nodeColor);

		for (int i = 0; i < connections.size(); i++)
		{
			ShapeDrawing2D::DrawLine(pos, connections[i]->pos, connectionLineThickness, connectionLineColor);
		}
	}
}