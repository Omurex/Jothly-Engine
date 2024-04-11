#pragma once
#include "TicTacToePlayer.h"


namespace jothly
{
	class TicTacToeMiniMaxPlayer : public TicTacToePlayer
	{
		int MiniMax(TTTSquare board[TTT_NUM_SPACES], TTTSquare square, bool maximizing);


		public:
		// Inherited via TicTacToePlayer
		bool GetNextMove(const TicTacToeBoard& tttBoard, TTTSquare playerSquare, float dt, int& out_index) override;
	};
}