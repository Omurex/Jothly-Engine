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

		bool gameOver = false;


		void Draw() override;
		void Update(float dt) override;

		protected:

		TicTacToeBoard(GameObject* _owner);
		~TicTacToeBoard() {}

		public:

		TicTacToeBoard* Init(Texture* _xTexture = nullptr, Texture* _oTexture = nullptr, Texture* _emptyTexture = nullptr, 
			Vector2 _offset = Vector2(0), float _size = 300);

		void SetXPlayer(TicTacToePlayer* _xPlayer) { xPlayer = _xPlayer; }
		void SetYPlayer(TicTacToePlayer* _oPlayer) { oPlayer = _oPlayer; }
		void SetPlayers(TicTacToePlayer* _xPlayer, TicTacToePlayer* _oPlayer) { SetXPlayer(_xPlayer); SetYPlayer(_oPlayer); }

		ComponentID GetID() const override { return ComponentID::TIC_TAC_TOE_BOARD; }
		bool GetBoardCopy(TTTSquare out_board[TTT_NUM_SPACES]) const;

		bool PlaceSquare(int index, bool placingX, bool overwriteExisting = false);
		bool PlaceSquare(int row, int column, bool placingX, bool overwriteExisting = false);
		TTTResult CheckForEndOfGame() const; // 0 = Still playing, 1 = X win, 2 = O win, 3 = Draw

		Vector2 GetSquareWorldPos(int index) const;
		TTTSquare GetSquare(int row, int column) const;
		TTTSquare GetSquare(int index) const;

		static TTTResult CheckForEndOfGame(const TTTSquare sampleBoard[TTT_NUM_SPACES]);
		static int GetSquareIndex(int row, int column);
		static TTTSquare GetSquare(int row, int column, const TTTSquare sampleBoard[TTT_NUM_SPACES]);
		static TTTSquare GetSquare(int index, const TTTSquare sampleBoard[TTT_NUM_SPACES]);
		static TTTResult SquareToFinalGameResult(TTTSquare square);
		static TTTSquare FinalGameResultToSquare(TTTResult result);

		int GetIndexFromWorldPoint(Vector2 worldPoint) const; // Returns index if point valid in board, -1 otherwise

		void ResetBoard();
	};
}