#pragma once

#include "Vector2.h"
#include "DelaunayPoint.h"
#include <vector>


namespace jothly
{
	class NavMeshObstacle
	{
		public:
		NavMeshObstacle(Vector2 _centerPos) : centerPos(_centerPos) {}

		Vector2 centerPos;
		Color color;

		virtual std::vector<DelaunayPoint> GetNavMeshPoints() = 0;
		virtual std::vector<DelaunayPoint> GetObstaclePoints() = 0;

		virtual bool IsPointInObstacle(Vector2 point) = 0;

		virtual void Draw() = 0;
	};
}