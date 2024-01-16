#include "ShapeRenderer2D.h"
#include "Constants.hpp"
#include "ShapeDrawing2D.h"


namespace jothly
{
	void ShapeRenderer2D::Draw()
	{
		DrawCircle(owner->transform.pos.x + offset.x, owner->transform.pos.y + offset.y, 
			20, {255, 0, 0, 255});
	}
}
