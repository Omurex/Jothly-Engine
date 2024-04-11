#include "TicTacToeMiniMaxPlayer.h"
#include "TicTacToeBoard.h"


namespace jothly
{
	TTTSquare GetOppositeSquare(TTTSquare square)
	{
		if(square == TTTSquare::X) return TTTSquare::O;
		else return TTTSquare::X;
	}


	int TicTacToeMiniMaxPlayer::MiniMax(TTTSquare board[TTT_NUM_SPACES], TTTSquare square, bool maximizing, int depth)
	{
		TTTResult endOfGameResult = TicTacToeBoard::CheckForEndOfGame(board);
		if (endOfGameResult != TTTResult::STILL_PLAYING)
		{
			if(endOfGameResult == TTTResult::DRAW) return 0;

			// If X Win and X Square: 1
			// If X Win and O Square: -1
			int score = (2 * (square == TicTacToeBoard::FinalGameResultToSquare(endOfGameResult)) - 1);
			return score * (2 * maximizing - 1);
		}

		if(depth > maxDepth) return 0;

		int best = maximizing ? -INT16_MAX : INT16_MAX;
		for (int i = 0; i < TTT_NUM_SPACES; ++i)
		{
			if (board[i] == TTTSquare::EMPTY)
			{
				board[i] = square;
				int miniMaxResult = MiniMax(board, GetOppositeSquare(square), !maximizing, depth + 1);
				board[i] = TTTSquare::EMPTY;

				if((maximizing && miniMaxResult > best) || (!maximizing && miniMaxResult < best)) best = miniMaxResult;
			}
		}

		return best;
	}


	bool TicTacToeMiniMaxPlayer::GetNextMove(const TicTacToeBoard& tttBoard, TTTSquare playerSquare, float dt, int& out_index)
	{
		int best = -INT16_MAX;
		out_index = -1;

		for (int i = 0; i < TTT_NUM_SPACES; ++i)
		{
			if (tttBoard.GetSquare(i) == TTTSquare::EMPTY)
			{
				TTTSquare board[TTT_NUM_SPACES];
				tttBoard.GetBoardCopy(board);
				board[i] = playerSquare;

				int result = MiniMax(board, GetOppositeSquare(playerSquare), false);

				if(best < result) 
				{
					best = result;
					out_index = i;
				}
			}
		}

		return true;


	}
}
