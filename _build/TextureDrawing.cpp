#include "TextureDrawing.h"
#include "include/Rectangle.hpp"


void jothly::TextureDrawing::DrawTexture(Texture& tex, Vector2 topLeftPos, Vector2 origin, float angleDegRot, Vector2 scale, Color tint)
{
	raylib::rlb_Texture* backingTexture = tex.GetBackingTexture();
	raylib::rlb_Rectangle source = raylib::rlb_Rectangle(0, 0, backingTexture->GetWidth(), backingTexture->GetHeight());
	raylib::rlb_Rectangle dest = raylib::rlb_Rectangle(topLeftPos, ((Vector2) backingTexture->GetSize()).MultiplyComponents(scale));

	backingTexture->Draw(source, dest, origin, angleDegRot, tint);
}
