#pragma once
#include "Vector2.h"
#include "Component.h"


namespace jothly
{
	class Snake : public Component
	{
		Vector2 vel = Vector2(0);
		float radius = 0;

		
		Snake(GameObject* _owner) : Component(_owner) {}

		Snake* Init(float _radius = 30) { radius = _radius; }


		bool CheckIfDead();

		// Inherited via Component
		ComponentID GetID() const override;
	};
}