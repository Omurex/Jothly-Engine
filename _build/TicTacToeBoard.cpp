#include "TicTacToeBoard.h"
#include "ShapeDrawing2D.h"
#include "TextureDrawing.h"
#include "Color.h"
#include <iostream>


namespace jothly
{
	void TicTacToeBoard::Draw()
	{
		float halfSize = size / 2.0f;
		float thirdSize = size / 3.0f;
		float halfThirdSize = thirdSize / 2.0f;

		Vector2 pos = owner->transform.pos + offset;
		Vector2 topLeft = pos - Vector2(halfSize);

		for(int i = 0; i < TTT_NUM_SPACES; ++i)
		{
			Texture* tex = nullptr;

			if(board[i] == TTTSquare::X)
			{
				tex = xTexture;	
			}
			else if(board[i] == TTTSquare::O)
			{
				tex = oTexture;
			}
			else continue;

			Vector2 squarePos = GetSquareWorldPos(i);

			TextureDrawing::DrawTexture(*tex, squarePos - Vector2(halfThirdSize), Vector2(0), Vector2(thirdSize));
		}

		// Vertical lines
		ShapeDrawing2D::DrawLine(topLeft + Vector2(thirdSize, 0), topLeft + Vector2(thirdSize, size), 10, Color::GREEN);
		ShapeDrawing2D::DrawLine(topLeft + Vector2(thirdSize * 2, 0), topLeft + Vector2(thirdSize * 2, size), 10, Color::GREEN);

		// Horizontal lines
		ShapeDrawing2D::DrawLine(topLeft + Vector2(0, thirdSize), topLeft + Vector2(size, thirdSize), 10, Color::GREEN);
		ShapeDrawing2D::DrawLine(topLeft + Vector2(0, thirdSize * 2), topLeft + Vector2(size, thirdSize * 2), 10, Color::GREEN);
	}


	#define INVALID_PLAYER_CHECK

	void TicTacToeBoard::Update(float dt)
	{
		if(gameOver) return;

		TicTacToePlayer* player = nullptr;

		if(xTurn)
		{
			player = xPlayer;
		}
		else
		{
			player = oPlayer;
		}

		if (player == nullptr) // Player invalid!
		{
			std::cout << "No " << (xTurn ? "X" : "O") << " player set!" << std::endl; 
			xTurn = !xTurn; 
			return; 
		}

		int index; // Index at which to place move
		if (!player->GetNextMove(*this, dt, index)) return; // No move given
		if(!PlaceSquare(index, xTurn)) return; // Invalid move

		TTTResult result = CheckForEndOfGame();

		if (result != TTTResult::STILL_PLAYING) // Do end of game actions
		{
			gameOver = true;

			if(result == TTTResult::DRAW) { std::cout << "DRAW!" << std::endl; return; }

			std::string winner = 
				result == TTTResult::X_WIN ? "X" : "O";

			std::cout << winner << " WINS!" << std::endl;

			return;
		}

		xTurn = !xTurn;
	}


	Vector2 TicTacToeBoard::GetSquareWorldPos(int index) const
	{
		Vector2 topLeft = owner->transform.pos + offset - Vector2(size / 2.0f);
		float spacer = size / 3.0f;

		int row = index / 3;
		int column = index % 3;

		return topLeft + Vector2(spacer * column, spacer * row) + Vector2(size / 6.0f);
	}


	int TicTacToeBoard::GetSquareIndex(int row, int column) const
	{
		return row * 3 + column;
	}


	TTTSquare TicTacToeBoard::GetSquare(int row, int column) const
	{
		return board[GetSquareIndex(row, column)];
	}


	TicTacToeBoard::TicTacToeBoard(GameObject* _owner) : Component(_owner)
	{
		Init(); 
		ResetBoard();
	}


	bool TicTacToeBoard::GetBoardCopy(TTTSquare out_board[TTT_NUM_SPACES]) const
	{
		for (int i = 0; i < TTT_NUM_SPACES; ++i)
		{
			out_board[i] = board[i];
		}

		return true;
	}


	TicTacToeBoard* TicTacToeBoard::Init(Texture* _xTexture, Texture* _oTexture, Texture* _emptyTexture, Vector2 _offset, float _size)
	{
		xTexture = _xTexture;
		oTexture = _oTexture;
		emptyTexture = _emptyTexture;

		offset = _offset;
		size = _size;

		return this;
	}


	bool TicTacToeBoard::PlaceSquare(int index, bool placingX, bool overwriteExisting)
	{
		if (index < 0 || index > TTT_NUM_SPACES) return false;
		if (board[index] != TTTSquare::EMPTY && !overwriteExisting) return false;

		board[index] = placingX ? TTTSquare::X : TTTSquare::O;

		emptySpaceIndexes.erase(std::find(emptySpaceIndexes.begin(), emptySpaceIndexes.end(), index));

		return true;
	}


	bool TicTacToeBoard::PlaceSquare(int row, int column, bool placingX, bool overwriteExisting)
	{
		int index = GetSquareIndex(row, column);
		return PlaceSquare(index, placingX, overwriteExisting);
	}


	// Note: Never pass empty into this function, it will return O_Win
	TTTResult SquareToFinalGameResult(TTTSquare square)
	{
		if (square == TTTSquare::X) return X_WIN;
		else return O_WIN;
	}


	#define CALCULATE_END_OF_GAME if(s0 == s1 && s1 == s2 && s0 != TTTSquare::EMPTY) { return SquareToFinalGameResult(s0); }
	TTTResult TicTacToeBoard::CheckForEndOfGame() const
	{
		TTTSquare s0, s1, s2;

		// Check columns for win
		for(int c = 0; c < 3; ++c)
		{
			s0 = GetSquare(0, c);
			s1 = GetSquare(1, c);
			s2 = GetSquare(2, c);
			CALCULATE_END_OF_GAME
		}

		// Check columns for win
		for (int r = 0; r < 3; ++r)
		{
			s0 = GetSquare(r, 0);
			s1 = GetSquare(r, 1);
			s2 = GetSquare(r, 2);
			CALCULATE_END_OF_GAME
		}

		// Check top left -> bottom right diagonal
		s0 = GetSquare(0, 0);
		s1 = GetSquare(1, 1);
		s2 = GetSquare(2, 2);
		CALCULATE_END_OF_GAME

		// Check top right -> bottom left diagonal
		s0 = GetSquare(2, 0);
		s1 = GetSquare(1, 1);
		s2 = GetSquare(0, 2);
		CALCULATE_END_OF_GAME

		// No winners and no more spaces to play
		if(emptySpaceIndexes.size() == 0) return TTTResult::DRAW;

		return TTTResult::STILL_PLAYING;
	}


	void TicTacToeBoard::ResetBoard()
	{
		emptySpaceIndexes = std::vector<int>(TTT_NUM_SPACES);

		for(int i = 0; i < TTT_NUM_SPACES; ++i)
		{
			board[i] = TTTSquare::EMPTY;
			emptySpaceIndexes[i] = i;
		}

		xTurn = true;
		gameOver = false;
	}


	int TicTacToeBoard::GetIndexFromWorldPoint(Vector2 worldPoint) const
	{
		float halfSize = size / 2.0f;
		float thirdSize = size / 3.0f;

		Vector2 pos = owner->transform.pos + offset;
		Vector2 topLeft = pos - Vector2(halfSize);

		Vector2 offset = worldPoint - topLeft;
		int row = offset.y / thirdSize;
		int column = offset.x / thirdSize;

		int index = GetSquareIndex(row, column);
		if(index < 0 || index >= TTT_NUM_SPACES) return -1;

		return index;
	}
}