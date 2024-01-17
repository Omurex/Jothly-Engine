#pragma once


#include "Component.h"
#include "Vector2.h"
#include "Color.h"


namespace jothly
{
	class ShapeRenderer2D : Component
	{
		friend class GameObject;

		float radius;
		Color color;
		Vector2 offset;

		ShapeRenderer2D(GameObject* _owner) : Component(_owner) { Init(); }

		public:

		ShapeRenderer2D* Init(float _radius = 100, Color _color = Color::WHITE, Vector2 _offset = Vector2(0));
	
		ComponentID GetID() const override { return ComponentID::SHAPE_RENDERER; }

		float GetRadius() { return radius; }
		Color GetColor() { return color; }
		Vector2 GetOffset() { return offset; }

		void SetRadius(float _radius) { radius = _radius; }
		void SetColor(Color _color) { color = _color; }
		void SetOffset(Vector2 _offset) { offset = _offset; }

		void Draw() override;
	};
}