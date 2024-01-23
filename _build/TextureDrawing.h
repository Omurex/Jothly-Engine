#pragma once

#include "Texture.h"
#include "Vector2.h"
#include "Color.h"


namespace jothly
{
	class TextureDrawing
	{
		public:
		static void DrawTexture(Texture& tex, Vector2 pos, Vector2 origin, float angleDegRot = 0, Vector2 scale = Vector2(1), Color tint = Color::WHITE);
	};
}