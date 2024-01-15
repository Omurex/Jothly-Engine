#include "ShapeRenderer2D.h"
#include "Constants.hpp"
#include "raylib.h"


namespace jothly
{
	ShapeRenderer2D::ShapeRenderer2D(GameObject* _owner) : Component(_owner), offset(Vector2())
	{
	}


	void ShapeRenderer2D::Draw()
	{
		DrawCircle(owner->transform.translation.x + offset.x, owner->transform.translation.y + offset.y, 
			20, {255, 0, 0, 255});
	}
}
