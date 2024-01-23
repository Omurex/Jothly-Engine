#include "SpriteRenderer.h"
#include "TextureDrawing.h"


namespace jothly
{
    SpriteRenderer* SpriteRenderer::Init(Texture* _sprite, Color _tint, Vector2 _offset)
    {
        SetSprite(_sprite); SetTint(_tint); SetOffset(_offset);
        return this; 
    }


    void SpriteRenderer::Draw()
    {
        if (sprite != nullptr) // Can't draw if there's no sprite! 
        {
            // Doesn't seem to be a way to scale independently in directions, for now just use x scale

            Vector2 halfSize = (sprite->GetSize() * owner->transform.scale.x) / 2.0f;

            TextureDrawing::DrawTexture(*sprite, (Vector2) owner->transform.pos - halfSize + offset,
                -owner->transform.rot.GetAngleDeg(), owner->transform.scale.x, tint);
        }
    }
}
