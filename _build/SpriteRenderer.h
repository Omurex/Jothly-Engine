#pragma once


#include "Component.h"
#include "Texture.h"
#include "Color.h"
#include "Vector2.h"


namespace jothly
{
	class SpriteRenderer : Component
	{
		friend class GameObject;

		protected:
		Texture* sprite;
		Color tint;
		Vector2 offset;

		SpriteRenderer(GameObject* _owner) : Component(_owner) { Init(); }
		~SpriteRenderer() {}

		public:
		SpriteRenderer* Init(Texture* _sprite = nullptr, Color _tint = Color::WHITE, Vector2 _offset = Vector2(0));

		ComponentID GetID() const override { return ComponentID::SPRITE_RENDERER; }

		Texture* GetSprite() { return sprite; }
		Color GetTint() { return tint; }
		Vector2 GetOffset() { return offset; }
	
		void SetSprite(Texture* _sprite) { sprite = _sprite; }
		void SetTint(Color _tint) { tint = _tint; }
		void SetOffset(Vector2 _offset) { offset = _offset; }

		void Draw() override;
	};
}