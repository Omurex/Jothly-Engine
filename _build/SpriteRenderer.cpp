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
        if(sprite != nullptr) // Can't draw if there's no sprite! 
            TextureDrawing::DrawTexture(*sprite, (Vector2) owner->transform.pos + offset, tint);
    }
}
