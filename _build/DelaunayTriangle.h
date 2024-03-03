#pragma once


#include "DelaunayPoint.h"
#include "Texture.h"
#include "Color.h"


namespace jothly
{
	struct DelaunayTriangle
	{
		DelaunayPoint points[3] = { DelaunayPoint(), DelaunayPoint(), DelaunayPoint() };

		DelaunayTriangle(DelaunayPoint p0 = DelaunayPoint(), DelaunayPoint p1 = DelaunayPoint(),
			DelaunayPoint p2 = DelaunayPoint()) : points { p0, p1, p2 } {}

		DelaunayTriangle(DelaunayPoint _points[3]) : 
			DelaunayTriangle(_points[0], _points[1], _points[2]) {}

		DelaunayTriangle(Vector2 p0, Vector2 p1, Vector2 p2) : 
			DelaunayTriangle(DelaunayPoint(p0), DelaunayPoint(p1), DelaunayPoint(p2)) {}

		void Draw(float thickness, Color lineColor = Color::WHITE, float pointRadius = 1, Color pointColor = Color::BLACK);

		float GetArea();
		float GetCircumradius();
		Vector2 GetCircumcenter();

		// -1 if doesn't share edge (outs won't be set), 0 if same triangle (outs won't be set), 1 if shares edge
		int SharesEdge(const DelaunayTriangle& other, DelaunayPoint& out_edgeP0, DelaunayPoint& out_edgeP1);
		bool HasPoint(const DelaunayPoint& point);
	};
}