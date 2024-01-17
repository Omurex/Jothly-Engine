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
		DrawCircle(owner->transform.pos.x + offset.x, owner->transform.pos.y + offset.y, radius, color);
	}
}
