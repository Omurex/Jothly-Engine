#include "SquareNavMeshObstacle.h"


namespace jothly
{
	std::vector<DelaunayPoint> SquareNavMeshObstacle::GetNavMeshPoints()
	{
		float halfLength = sideLength / 2.0f;

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
		float halfLength = sideLength / 2.0f;

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
		float halfLength = sideLength / 2.0f;
		Vector2 bottomLeft = centerPos - Vector2(halfLength);
		Vector2 topRight = centerPos + Vector2(halfLength);

		return point.x < topRight.x && point.y < topRight.y && point.x > bottomLeft.x && point.y > bottomLeft.y;
	}
}