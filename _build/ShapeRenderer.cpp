#include "ShapeRenderer.h"


ShapeRenderer::ShapeRenderer(GameObject* _owner) : Component(_owner, GetID())
{
}


void ShapeRenderer::Draw()
{
	DrawCircle(5, 5, 20, {255, 0, 0, 255});
}
