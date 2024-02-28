#include "DelaunayPoint.h"
#include "ShapeDrawing2D.h"


namespace jothly
{
	void DelaunayPoint::Draw(float radius, Color color)
	{
		ShapeDrawing2D::DrawCircle(pos, radius, color);
	}
}
