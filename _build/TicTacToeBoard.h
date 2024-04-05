#pragma once

#include "Component.h"
#include "Vector2.h"
#include "Texture.h"


namespace jothly
{
	class TicTacToeBoard : public Component
	{
		enum Square : char
		{
			EMPTY,
			X,
			O
		};

		static const int NUM_SPACES = 9;

		friend class GameObject;

		Square board[NUM_SPACES];

		Texture* xTexture = nullptr;
		Texture* oTexture = nullptr;
		Texture* emptyTexture = nullptr;

		Vector2 offset = Vector2(0);
		float size = 300;

		void Draw() override;
		void Update(float dt) override;

		Vector2 GetBoardPos(int index);

		protected:

		TicTacToeBoard(GameObject* _owner) : Component(_owner) { Init(); std::fill_n(board, NUM_SPACES, Square::EMPTY); }
		~TicTacToeBoard() {}

		public:

		TicTacToeBoard* Init(Texture* _xTexture = nullptr, Texture* _oTexture = nullptr, Texture* _emptyTexture = nullptr, 
			Vector2 _offset = Vector2(0), float _size = 300);

		ComponentID GetID() const override { return ComponentID::TIC_TAC_TOE_BOARD; }
	};
}