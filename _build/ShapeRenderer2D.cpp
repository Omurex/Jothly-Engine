#include "ShapeRenderer2D.h"
#include "Constants.hpp"
#include "ShapeDrawing2D.h"


namespace jothly
{
	ShapeRenderer2D* ShapeRenderer2D::Init(float _radius, Color _color, Vector2 _offset)
	{
		SetRadius(_radius);
		SetColor(_color);
		SetOffset(_offset);

		return this;
	}


	void ShapeRenderer2D::Draw()
	{
		ShapeDrawing2D::DrawCircle((int) (owner->transform.pos.x + offset.x), (int) (owner->transform.pos.y + offset.y), radius, color);
	}
}
