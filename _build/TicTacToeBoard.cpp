#include "TicTacToeBoard.h"
#include "ShapeDrawing2D.h"
#include "TextureDrawing.h"
#include "Color.h"


namespace jothly
{
	void TicTacToeBoard::Draw()
	{
		float halfSize = size / 2.0f;
		float thirdSize = size / 3.0f;
		float halfThirdSize = thirdSize / 2.0f;

		Vector2 pos = owner->transform.pos + offset;
		Vector2 topLeft = pos - Vector2(halfSize);

		for(int i = 0; i < NUM_SPACES; ++i)
		{
			Texture* tex = nullptr;

			if(board[i] == Square::X)
			{
				tex = xTexture;	
			}
			else if(board[i] == Square::O)
			{
				tex = oTexture;
			}
			else continue;

			Vector2 squarePos = GetBoardPos(i);

			TextureDrawing::DrawTexture(*tex, squarePos - Vector2(halfThirdSize), Vector2(0), Vector2(thirdSize));
		}

		// Vertical lines
		ShapeDrawing2D::DrawLine(topLeft + Vector2(thirdSize, 0), topLeft + Vector2(thirdSize, size), 10, Color::GREEN);
		ShapeDrawing2D::DrawLine(topLeft + Vector2(thirdSize * 2, 0), topLeft + Vector2(thirdSize * 2, size), 10, Color::GREEN);

		// Horizontal lines
		ShapeDrawing2D::DrawLine(topLeft + Vector2(0, thirdSize), topLeft + Vector2(size, thirdSize), 10, Color::GREEN);
		ShapeDrawing2D::DrawLine(topLeft + Vector2(0, thirdSize * 2), topLeft + Vector2(size, thirdSize * 2), 10, Color::GREEN);
	}


	void TicTacToeBoard::Update(float dt)
	{
	}


	Vector2 TicTacToeBoard::GetBoardPos(int index)
	{
		Vector2 topLeft = owner->transform.pos + offset - Vector2(size / 2.0f);
		float spacer = size / 3.0f;

		int row = index / 3;
		int column = index % 3;

		return topLeft + Vector2(spacer * column, spacer * row) + Vector2(size / 6.0f);
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
}