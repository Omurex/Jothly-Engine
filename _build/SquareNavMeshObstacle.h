#pragma once

#include "NavMeshObstacle.h"


namespace jothly
{
	class SquareNavMeshObstacle : public NavMeshObstacle
	{
		const float NAVMESH_OFFSET_MAGNITUDE = 2.f;

		public:
		SquareNavMeshObstacle(Vector2 _centerPos = Vector2(0, 0), float _sideLength = 50) : 
			NavMeshObstacle(_centerPos), sideLength(_sideLength) {}

		float sideLength;
		Color color;

		// Inherited via NavMeshObstacle
		std::vector<DelaunayPoint> GetNavMeshPoints() override;
		std::vector<DelaunayPoint> GetObstaclePoints() override;

		// Inherited via NavMeshObstacle
		bool IsPointInObstacle(Vector2 point) override;

		// Inherited via NavMeshObstacle
		void Draw() override;

		// Inherited via NavMeshObstacle
		bool DoesLineSegmentIntersectObstacle(Vector2 p0, Vector2 p1) override;

		void operator=(const SquareNavMeshObstacle& other)
		{
			centerPos = other.centerPos;
			sideLength = other.sideLength;
			color = other.color;
		}
	};
}