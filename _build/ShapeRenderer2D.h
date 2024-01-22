#pragma once


#include "Component.h"
#include "Vector2.h"
#include "Color.h"


namespace jothly
{
	class ShapeRenderer2D : Component
	{
		friend class GameObject;

		protected:

		float radius;
		rlb_Color color;
		rlb_Vector2 offset;

		ShapeRenderer2D(GameObject* _owner) : Component(_owner) { Init(); }
		~ShapeRenderer2D() {}

		public:

		ShapeRenderer2D* Init(float _radius = 100, rlb_Color _color = rlb_Color::WHITE, rlb_Vector2 _offset = rlb_Vector2(0));
	
		ComponentID GetID() const override { return ComponentID::SHAPE_RENDERER; }

		float GetRadius() { return radius; }
		rlb_Color GetColor() { return color; }
		rlb_Vector2 GetOffset() { return offset; }

		void SetRadius(float _radius) { radius = _radius; }
		void SetColor(rlb_Color _color) { color = _color; }
		void SetOffset(rlb_Vector2 _offset) { offset = _offset; }

		void Draw() override;
	};
}