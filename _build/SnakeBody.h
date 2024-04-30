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

		float radius = 8;

		Vector2 prevFramePosition = Vector2(0);

		void UpdateLocation();
		virtual void DrawObject();

		bool IsOverlappingBody(Vector2 pos, float radius);

		virtual void AddChild(SnakeBody* _child);

		public:
		SnakeBody(GameObject* _owner) : Component(_owner) {}
		~SnakeBody() { if (child != nullptr) delete child->GetOwner(); }

		SnakeBody* Init(float _radius, SnakeBody* _parent, SnakeBody* _child = nullptr) { radius = _radius;  parent = _parent; child = _child; prevFramePosition = owner->transform.pos; return this; }

		// Inherited via Component
		ComponentID GetID() const override;
	};
}