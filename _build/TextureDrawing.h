#pragma once

#include "Texture.h"
#include "Vector2.h"
#include "Color.h"


namespace jothly
{
	class TextureDrawing
	{
		public:
		static void DrawTexture(Texture& tex, Vector2 pos, float angleDeg = 0, float scale = 1, Color tint = Color::WHITE);
	};
}