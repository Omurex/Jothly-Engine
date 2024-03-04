#pragma once

#include "NavMeshObstacle.h"


namespace jothly
{
	class SquareNavMeshObstacle : public NavMeshObstacle
	{
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
	};
}