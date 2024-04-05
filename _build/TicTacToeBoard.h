#pragma once
#include "Component.h"
#include "Vector2.h"


namespace jothly
{
	class TicTacToeBoard : public Component
	{
		friend class GameObject;

		Vector2 offset = Vector2(0);
		float size = 300;

		void Draw() override;
		void Update(float dt) override;

		protected:

		TicTacToeBoard(GameObject* _owner) : Component(_owner) { Init(); }
		~TicTacToeBoard() {}

		public:

		TicTacToeBoard* Init(Vector2 _offset = Vector2(0), float _size = 300);

		ComponentID GetID() const override { return ComponentID::TIC_TAC_TOE_BOARD; }
	};
}