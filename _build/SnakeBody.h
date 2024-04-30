#pragma once
#include "Component.h"
#include "Vector2.h"


namespace jothly
{
	class SnakeBody : public Component
	{
		public:

		SnakeBody* parent = nullptr;
		SnakeBody* child = nullptr;

		Vector2 prevFramePosition = Vector2(0);

		void UpdateLocation();
		virtual void DrawObject();

		virtual void AddChild(SnakeBody* _child);

		public:
		SnakeBody(GameObject* _owner) : Component(_owner) {}
		void Init(SnakeBody* _parent, SnakeBody* _child = nullptr) { parent = _parent; child = _child; prevFramePosition = owner->transform.pos; }

		// Inherited via Component
		ComponentID GetID() const override;
	};
}