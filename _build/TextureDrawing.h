#pragma once

#include "Texture.h"
#include "Vector2.h"
#include "Color.h"


namespace jothly
{
	class TextureDrawing
	{
		public:
		static void DrawTexture(Texture& tex, Vector2 pos, Color tint = Color::WHITE);
	};
}