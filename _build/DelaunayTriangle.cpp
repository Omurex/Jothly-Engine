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


	DelaunayTriangle* DelaunayTriangle::Init(DelaunayPoint _points[3], Texture* _pointTexture)
	{
		return Init(_points[0], _points[1], _points[2], _pointTexture);
	}


	DelaunayTriangle* DelaunayTriangle::Init(Vector2 p0, Vector2 p1, Vector2 p2, Texture* _pointTexture)
	{
		return Init(DelaunayPoint(p0), DelaunayPoint(p1), DelaunayPoint(p2), _pointTexture);
	}


	ComponentID DelaunayTriangle::GetID() const
	{
		return ComponentID::DELAUNAY_TRIANGLE;
	}
}