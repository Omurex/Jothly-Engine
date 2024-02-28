#pragma once

#include <vector>
#include "Component.h"
#include "ComponentID.hpp"
#include "DelaunayTriangle.h"


namespace jothly
{
	class NavMesh : public Component
	{
		friend class GameObject;

		std::vector<Vector2> points;
		std::vector<DelaunayTriangle> triangles;

		float pointRadius = 1;
		Color pointColor = Color::BLACK;

		float lineThickness = 1;
		Color lineColor = Color::WHITE;


		NavMesh(GameObject* _owner) : Component(_owner) {}
		void Draw() override;


		public:

		NavMesh* Init(float _pointRadius = 1, Color _pointColor = Color::BLACK, float _lineThickness = 1, 
			Color _lineColor = Color::WHITE);

		ComponentID GetID() const override;

		void LoadPoints(std::vector<Vector2> _points);
		bool GenerateDelaunayTriangles();
	};
}