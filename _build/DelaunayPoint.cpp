#include "DelaunayPoint.h"
#include "TextureDrawing.h"


namespace jothly
{
	void DelaunayPoint::Draw(Texture* tex, Vector2 size)
	{
		TextureDrawing::DrawTexture(*tex, pos - (size / 2.0f), Vector2(0), size);
	}
}
