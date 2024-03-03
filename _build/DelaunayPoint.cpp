#include "DelaunayPoint.h"
#include "ShapeDrawing2D.h"
#include "Math.h"


namespace jothly
{
	void DelaunayPoint::Draw(float radius, Color color)
	{
		ShapeDrawing2D::DrawCircle(pos, radius, color);
	}


    bool DelaunayPoint::operator==(const DelaunayPoint& rhs)
    {
		return Approx(pos, rhs.pos) == 1;
    }
}
