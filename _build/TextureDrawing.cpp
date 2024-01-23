#include "TextureDrawing.h"


void jothly::TextureDrawing::DrawTexture(Texture& tex, Vector2 pos)
{
	raylib::rlb_Texture* backingTexture = tex.GetBackingTexture();
	backingTexture->Draw(pos);
}
