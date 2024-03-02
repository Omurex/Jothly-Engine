#pragma once

#include <vector>
#include "Component.h"
#include "ComponentID.hpp"
#include "Color.h"
#include "DelaunayTriangle.h"
#include "DelaunayPoint.h"


namespace jothly
{
	class NavMesh : public Component
	{
		friend class GameObject;

		std::vector<DelaunayPoint> points;
		std::vector<DelaunayTriangle> triangles;

		float pointRadius = 1;
		Color pointColor = Color::BLACK;

		float lineThickness = 1;
		Color lineColor = Color::WHITE;

		bool drawPoints = true;
		bool drawTriangles = true;


		NavMesh(GameObject* _owner) : Component(_owner) {}
		void Draw() override;


		public:

		NavMesh* Init(float _pointRadius = 1, Color _pointColor = Color::BLACK, bool _drawPoints = true, float _lineThickness = 1, 
			Color _lineColor = Color::WHITE, bool _drawTriangles = true);

		ComponentID GetID() const override;

		void LoadPoints(std::vector<Vector2> _points);
		bool GenerateDelaunayTriangles();

		bool GetPointBounds(Vector2& out_lb, Vector2& out_ub); // Returns lowerbound and upperbound
		DelaunayTriangle GetSuperTriangle();

		void GenerateRandomPoints(int numPoints, Vector2 lowerbound, Vector2 upperbound);
	};
}