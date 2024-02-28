#include "DelaunayTriangle.h"
#include "ShapeDrawing2D.h"


namespace jothly
{
	void DelaunayTriangle::Draw(float thickness, Color lineColor, Texture* pointTexture, Vector2 pointSize)
	{
		if (pointTexture != nullptr)
		{
			points[0].Draw(pointTexture, pointSize);
			points[1].Draw(pointTexture, pointSize);
			points[2].Draw(pointTexture, pointSize);
		}

		ShapeDrawing2D::DrawLine(points[0].pos, points[1].pos, thickness, lineColor);
		ShapeDrawing2D::DrawLine(points[1].pos, points[2].pos, thickness, lineColor);
		ShapeDrawing2D::DrawLine(points[2].pos, points[0].pos, thickness, lineColor);
	}
}