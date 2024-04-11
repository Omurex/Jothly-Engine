#pragma once
#include "TicTacToePlayer.h"


namespace jothly
{
	class TicTacToeMiniMaxPlayer : public TicTacToePlayer
	{
		int maxDepth = 100;


		int MiniMax(TTTSquare board[TTT_NUM_SPACES], TTTSquare square, bool maximizing, int depth = 0);


		public:
		// Inherited via TicTacToePlayer
		bool GetNextMove(const TicTacToeBoard& tttBoard, TTTSquare playerSquare, float dt, int& out_index) override;

		int GetMaxDepth() { return maxDepth; }
		void SetMaxDepth(int _maxDepth) { maxDepth = _maxDepth; }
	};
}