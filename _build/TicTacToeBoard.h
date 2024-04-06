#pragma once

#include "Component.h"
#include "Vector2.h"
#include "Texture.h"
#include "TicTacToeData.hpp"
#include <vector>
#include "TicTacToePlayer.h"


namespace jothly
{
	class TicTacToeBoard : public Component
	{	
		private:
		friend class GameObject;

		TTTSquare board[TTT_NUM_SPACES];
		std::vector<int> emptySpaceIndexes;

		TicTacToePlayer* xPlayer = nullptr;
		TicTacToePlayer* oPlayer = nullptr;
		bool xTurn;

		Texture* xTexture = nullptr;
		Texture* oTexture = nullptr;
		Texture* emptyTexture = nullptr;

		Vector2 offset = Vector2(0);
		float size = 300;

		void Draw() override;
		void Update(float dt) override;

		Vector2 GetSquareWorldPos(int index);
		int GetSquareIndex(int row, int column);
		TTTSquare GetSquare(int row, int column);

		protected:

		TicTacToeBoard(GameObject* _owner);
		~TicTacToeBoard() {}

		public:

		TicTacToeBoard* Init(Texture* _xTexture = nullptr, Texture* _oTexture = nullptr, Texture* _emptyTexture = nullptr, 
			Vector2 _offset = Vector2(0), float _size = 300);

		ComponentID GetID() const override { return ComponentID::TIC_TAC_TOE_BOARD; }
		bool GetBoardCopy(TTTSquare out_board[TTT_NUM_SPACES]);

		bool PlaceSquare(int row, int column, bool placingX, bool overwriteExisting = false);
		TTTResult CheckForEndOfGame(); // 0 = Still playing, 1 = X win, 2 = O win, 3 = Draw

		void ResetBoard();
	};
}