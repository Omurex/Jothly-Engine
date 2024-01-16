#pragma once


#include "Component.h"
#include "Vector2.h"
#include "Color.h"


namespace jothly
{
	class ShapeRenderer2D : Component
	{
		Vector2 offset;
		float radius;
		Color color;


		public:
		ShapeRenderer2D(GameObject* _owner) : ShapeRenderer2D(_owner, Vector2(0)) {}
		ShapeRenderer2D(GameObject* _owner, Vector2 _offset) : Component(_owner), offset(_offset) {}
	
		ComponentID GetID() const override { return ComponentID::SHAPE_RENDERER; }

		Vector2 SetOffset(Vector2 _offset) { offset = _offset; return offset; }

		void Draw() override;
	};
}