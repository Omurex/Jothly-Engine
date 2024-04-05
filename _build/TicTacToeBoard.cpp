#include "TicTacToeBoard.h"
#include "ShapeDrawing2D.h"
#include "Color.h"


namespace jothly
{
	void TicTacToeBoard::Draw()
	{
		float halfSize = size / 2.0f;
		float thirdSize = size / 3.0f;
		float halfThirdSize = thirdSize / 2.0f;

		Vector2 pos = owner->transform.pos + offset;
		Vector2 topLeft = pos - halfSize;

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


	TicTacToeBoard* TicTacToeBoard::Init(Vector2 _offset, float _size)
	{
		offset = _offset;
		size = _size;

		return this;
	}
}