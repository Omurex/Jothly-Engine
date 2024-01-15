#pragma once


#include "Component.h"
#include "Vector2.h"


namespace jothly
{
	class ShapeRenderer2D : Component
	{
		Vector2 offset;


		public:
		ShapeRenderer2D(GameObject* owner);
	
		ComponentID GetID() const override { return ComponentID::SHAPE_RENDERER; }

		Vector2 SetOffset(Vector2 _offset) { offset = _offset; return offset; }

		void Draw() override;
	};
}