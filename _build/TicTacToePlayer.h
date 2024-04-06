#pragma once
#include "TicTacToeData.hpp"


namespace jothly
{
	class TicTacToeBoard;

	class TicTacToePlayer
	{
		public:
		virtual bool GetNextMove(const TicTacToeBoard& tttBoard, float dt, int& out_row, int& out_column) = 0;
	};
}