#include "TextureDrawing.h"


void jothly::TextureDrawing::DrawTexture(Texture& tex, Vector2 pos, Color tint)
{
	raylib::rlb_Texture* backingTexture = tex.GetBackingTexture();
	backingTexture->Draw(pos, tint);
}
