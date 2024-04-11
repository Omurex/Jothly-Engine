#include "TicTacToeHumanPlayer.h"
#include "TicTacToeBoard.h"
#include "Input.h"
#include <iostream>


namespace jothly
{
	bool TicTacToeHumanPlayer::GetNextMove(const TicTacToeBoard& tttBoard, TTTSquare playerSquare, float dt, int& out_index)
	{
		if(Input::GetMouseJustPressed(MouseCode::MB_LEFT))
		{
			out_index = tttBoard.GetIndexFromWorldPoint(Input::GetMousePosition());
			if(out_index == -1) return false;

			return true;
		}

		return false;
	}
}