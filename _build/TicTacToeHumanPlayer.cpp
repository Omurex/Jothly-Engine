#include "TicTacToeHumanPlayer.h"
#include "TicTacToeBoard.h"
#include "Input.h"

namespace jothly
{
	bool TicTacToeHumanPlayer::GetNextMove(const TicTacToeBoard& tttBoard, float dt, int& out_row, int& out_column)
	{
		if(Input::GetKeyJustPressed(KeyCode::SPACE))
		{
		}

		return false;
	}
}