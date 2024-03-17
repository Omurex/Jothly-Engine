#include "SquareNavMeshObstacle.h"
#include "ShapeDrawing2D.h"
#include "Math.h"


namespace jothly
{
	std::vector<DelaunayPoint> SquareNavMeshObstacle::GetNavMeshPoints()
	{
		float halfLength = sideLength * NAVMESH_OFFSET_MAGNITUDE / 2.0f;

		return std::vector<DelaunayPoint>
		{
			centerPos + Vector2(-halfLength, -halfLength),
			centerPos + Vector2(halfLength, -halfLength),
			centerPos + Vector2(-halfLength, halfLength),
			centerPos + Vector2(halfLength, halfLength),
			centerPos + Vector2(0, -halfLength),
			centerPos + Vector2(0, halfLength),
			centerPos + Vector2(-halfLength, 0),
			centerPos + Vector2(halfLength, 0),
		};
	}


	std::vector<DelaunayPoint> SquareNavMeshObstacle::GetObstaclePoints()
	{
		float halfLength = sideLength * NAVMESH_OFFSET_MAGNITUDE / 2.0f;

		return std::vector<DelaunayPoint>
		{
			centerPos + (Vector2(-halfLength, -halfLength) / 4.0f),
			centerPos + (Vector2(halfLength, -halfLength) / 4.0f),
			centerPos + (Vector2(-halfLength, halfLength) / 4.0f),
			centerPos + (Vector2(halfLength, halfLength) / 4.0f)
		};
	}


	bool SquareNavMeshObstacle::IsPointInObstacle(Vector2 point)
	{
		float halfLength = sideLength * NAVMESH_OFFSET_MAGNITUDE / 2.0f;
		Vector2 bottomLeft = centerPos - Vector2(halfLength);
		Vector2 topRight = centerPos + Vector2(halfLength);

		return point.x < topRight.x && point.y < topRight.y && point.x > bottomLeft.x && point.y > bottomLeft.y;
	}


	void SquareNavMeshObstacle::Draw()
	{
		ShapeDrawing2D::DrawSquare(centerPos - (Vector2(sideLength) / 2.0f), sideLength, color);
	}


	// https://stackoverflow.com/questions/4977491/determining-if-two-line-segments-intersect/4977569#4977569
	bool DoLineSegmentsIntersect(Vector2 p0, Vector2 p1, Vector2 k0, Vector2 k1)
	{
		Vector2 vP = p1 - p0;
		Vector2 vK = k1 - k0;

		float det = (vK.x * vP.y) - (vP.x * vK.y);

		if(Approx(det, 0)) return false; // Basically parallel

		float detRecip = 1 / det;

		float s = detRecip * ((p0.x - k0.x) * vP.y - (p0.y - k0.y) * vP.x);
		float t = detRecip * -(-(p0.x - k0.x) * vK.y + (p0.y - k0.y) * vK.x);

		return (s >= 0 && s <= 1) && (t >= 0 && t <= 1);
	}


	// https://stackoverflow.com/questions/4977491/determining-if-two-line-segments-intersect/4977569#4977569
    bool SquareNavMeshObstacle::DoesLineSegmentIntersectObstacle(Vector2 p0, Vector2 p1)
    {
		/*Vector2 topLeft, topRight, rightTop, rightBottom, 
		bottomLeft, bottomRight, leftTop, leftBottom = centerPos;*/

		float halfLength = sideLength * (NAVMESH_OFFSET_MAGNITUDE * .99f) / 2.0f;

		Vector2 corners[] { 
			Vector2(-halfLength, -halfLength),
			Vector2(halfLength, -halfLength),
			Vector2(halfLength, halfLength),
			Vector2(-halfLength, halfLength)
		};

		int prevIndex = 3; // Do this so we don't have to use modulus in for loop

		for(int i = 0; i < 4; ++i)
		{
			if(DoLineSegmentsIntersect(p0, p1, centerPos + corners[prevIndex], centerPos + corners[i]))
			{
				return true;
			}

			prevIndex = i;
		}

		return false;
    }
}