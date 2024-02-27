#pragma once


#include "Component.h"
#include "DelaunayPoint.h"
#include "Texture.h"


namespace jothly
{
	class DelaunayTriangle : public Component
	{
		friend class GameObject;

		DelaunayPoint points[3] = { DelaunayPoint(), DelaunayPoint(), DelaunayPoint() };

		Texture* pointTexture = nullptr;


		DelaunayTriangle(GameObject* _owner) : Component(_owner) {}


		public:
		DelaunayTriangle* Init(DelaunayPoint p0 = DelaunayPoint(), DelaunayPoint p1 = DelaunayPoint(), 
			DelaunayPoint p2 = DelaunayPoint(), Texture* _pointTexture = nullptr);

		DelaunayTriangle* Init(DelaunayPoint _points[3], Texture* _pointTexture = nullptr) 
			{ return Init(_points[0], _points[1], _points[2], _pointTexture); }

		// Inherited via Component
		ComponentID GetID() const override;
	};
}