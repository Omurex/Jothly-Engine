#pragma once
#include "TicTacToeData.hpp"


namespace jothly
{
	class TicTacToeBoard;

	class TicTacToePlayer
	{
		public:
		virtual bool GetNextMove(const TicTacToeBoard& tttBoard, TTTSquare playerSquare, float dt, int& out_index) = 0;
	};
}