#include "DelaunayTriangle.h"
#include "ShapeDrawing2D.h"
#include "Color.h"


namespace jothly
{
	void DelaunayTriangle::Draw()
	{
		ShapeDrawing2D::DrawLine(Vector2(100, 100), Vector2(200, 300), 1, Color::WHITE);
	}


	DelaunayTriangle* DelaunayTriangle::Init(DelaunayPoint p0, DelaunayPoint p1, DelaunayPoint p2, Texture* _pointTexture)
	{
		points[0] = p0;
		points[1] = p1;
		points[2] = p2;

		pointTexture = _pointTexture;
		return this;
	}


	ComponentID DelaunayTriangle::GetID() const
	{
		return ComponentID::DELAUNAY_TRIANGLE;
	}
}