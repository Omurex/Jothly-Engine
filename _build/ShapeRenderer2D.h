#pragma once


#include "Component.h"


namespace jothly
{
	class ShapeRenderer2D : Component
	{
		rlb_Vector2 offset;


		public:
		ShapeRenderer2D(GameObject* owner);
	
		ComponentID GetID() const override { return ComponentID::SHAPE_RENDERER; }

		rlb_Vector2 SetOffset(rlb_Vector2 _offset) { offset = _offset; return offset; }

		void Draw() override;
	};
}