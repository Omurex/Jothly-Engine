#include "DelaunayTriangle.h"
#include "ShapeDrawing2D.h"
#include "Math.h"
#include "Vector3.h"


namespace jothly
{
	void DelaunayTriangle::Draw(float thickness, Color lineColor, float pointRadius, Color pointColor)
	{
		if (pointRadius >= .01)
		{
			points[0].Draw(pointRadius, pointColor);
			points[1].Draw(pointRadius, pointColor);
			points[2].Draw(pointRadius, pointColor);
		}
		
		if (thickness >= .01)
		{
			ShapeDrawing2D::DrawLine(points[0].pos, points[1].pos, thickness, lineColor);
			ShapeDrawing2D::DrawLine(points[1].pos, points[2].pos, thickness, lineColor);
			ShapeDrawing2D::DrawLine(points[2].pos, points[0].pos, thickness, lineColor);
		}
	}


    float DelaunayTriangle::GetArea()
    {
		return .5f * (points[1].pos - points[0].pos).GetMagnitude() * (points[2].pos - points[1].pos).GetMagnitude();
    }


	// https://artofproblemsolving.com/wiki/index.php/Circumradius
	float DelaunayTriangle::GetCircumradius()
	{
		float a = (points[1].pos - points[0].pos).GetMagnitude();
		float b = (points[2].pos - points[1].pos).GetMagnitude();
		float c = (points[0].pos - points[2].pos).GetMagnitude();

		return (a * b * c) / sqrtf((a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c));
	}


	// https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
	// https://stackoverflow.com/questions/50762948/calculating-the-intersection-point-of-two-lines-with-eigen
	Vector2 DelaunayTriangle::GetCircumcenter()
	{
		Vector2 a = points[0].pos;
		Vector2 b = points[1].pos;
		Vector2 c = points[2].pos;

		Vector2 abMid = (a + b) / 2.0f;
		Vector2 bcMid = (b + c) / 2.0f;

		// Negative reciprocal, so y goes in x spot and vice versa, then multiply by -1
		Vector2 abPerpSlope = Vector2(b.y - a.y, a.x - b.x);
		Vector2 bcPerpSlope = Vector2(c.y - b.y, b.x - c.x);



		/*float abPerpSlope = -(points[1].pos.x - points[0].pos.x) / (points[1].pos.y - points[0].pos.y);
		float bcPerpSlope = -(points[2].pos.x - points[1].pos.x) / (points[2].pos.y - points[1].pos.y);*/

		Vector2 solution = SolveSystemOfEquations(
			Vector3(abPerpSlope.x, -bcPerpSlope.x, bcMid.x - abMid.x),
			Vector3(abPerpSlope.y, -bcPerpSlope.y, bcMid.y - abMid.y)
		);

		return abMid + (abPerpSlope * solution.x);
	}
}