#include "DelaunayTriangle.h"
#include "ShapeDrawing2D.h"
#include "Math.h"


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
}