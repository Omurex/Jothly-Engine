#pragma once
#include "TicTacToePlayer.h"


namespace jothly
{
	class TicTacToeHumanPlayer : public TicTacToePlayer
	{
		// Inherited via TicTacToePlayer
		bool GetNextMove(const TicTacToeBoard& tttBoard, float dt, int& out_index) override;
	};
}