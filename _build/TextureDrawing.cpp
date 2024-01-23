#include "TextureDrawing.h"


void jothly::TextureDrawing::DrawTexture(Texture& tex, Vector2 pos, float angleDeg, float scale, Color tint)
{
	raylib::rlb_Texture* backingTexture = tex.GetBackingTexture();
	backingTexture->Draw(pos, angleDeg, scale, tint);
}
