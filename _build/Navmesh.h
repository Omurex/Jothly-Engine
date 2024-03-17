#pragma once

#include <vector>
#include "Component.h"
#include "ComponentID.hpp"
#include "Color.h"
#include "DelaunayTriangle.h"
#include "DelaunayPoint.h"
#include "NavMeshObstacle.h"
#include "AStarGraph.h"


namespace jothly
{
	class NavMesh : public Component
	{
		friend class GameObject;

		std::vector<NavMeshObstacle*> obstacles;

		std::vector<DelaunayPoint> points;
		std::vector<DelaunayTriangle> triangles;

		std::vector<DelaunayPoint> obstaclePoints;

		std::vector<std::vector<AStarNode*>> triangleToAStarPoints;

		AStarGraph graph;

		float pointRadius = 5;
		Color pointColor = Color::BLACK;

		float lineThickness = 1;
		Color lineColor = Color::WHITE;

		float obstaclePointRadius = 5;
		Color obstaclePointColor = Color::RED;

		bool drawPoints = true;
		bool drawTriangles = true;
		bool drawObstaclePoints = true;
		bool drawObstacles = true;
		bool drawAStar = true;


		NavMesh(GameObject* _owner) : Component(_owner) {}
		void Draw() override;

		int FindTriangleIndexContainingPoint(Vector2 point);

		public:

		NavMesh* Init(float _pointRadius = 5, Color _pointColor = Color::BLACK, bool _drawPoints = true, float _lineThickness = 1,
			Color _lineColor = Color::WHITE, bool _drawTriangles = true, float _obstaclePointRadius = 5,
			Color _obstaclePointColor = Color::RED, bool _drawObstaclePoints = true, bool _drawObstacles = true,
			bool _drawAStar = true);

		ComponentID GetID() const override;

		AStarGraph* GetAStarGraph() { return &graph; }

		void AddObstacle(NavMeshObstacle* obstacle);
		void AddObstacles(std::vector<NavMeshObstacle>& newObstacles);

		void LoadPoints(std::vector<Vector2> _points);
		void LoadObstaclePoints(std::vector<Vector2> _obstaclePoints);

		bool GenerateDelaunayTriangles();

		void AddPoints(std::vector<Vector2> _points);

		bool CalculatePointBounds(Vector2& out_lb, Vector2& out_ub); // Returns lowerbound and upperbound
		DelaunayTriangle CalculateSuperTriangle();

		void GenerateRandomPoints(int numPoints, Vector2 lowerbound, Vector2 upperbound);

		AStarGraph& GenerateAStarGraph();

		bool FindTriangleContainingPoint(Vector2 point, DelaunayTriangle& out_triangle); // True if successful
		std::vector<Vector2> CalculatePath(Vector2 start, Vector2 end);
	};
}