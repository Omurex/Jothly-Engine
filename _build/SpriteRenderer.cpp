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
            Vector2 halfSize = (sprite->GetSize().MultiplyComponents(owner->transform.scale)) / 2.0f;

            TextureDrawing::DrawTexture(*sprite, (Vector2)owner->transform.pos + offset, halfSize,
                -owner->transform.rot.GetAngleDeg(), owner->transform.scale, tint);

            // Alternative drawing method
            //TextureDrawing::DrawTexture(*sprite, (Vector2)owner->transform.pos + offset, halfSize, halfSize * 2, -owner->transform.rot.GetAngleDeg());
        }
    }
}
