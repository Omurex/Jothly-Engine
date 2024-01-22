#ifndef RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_
#define RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./RaylibException.hpp"
#include "./TextureUnmanaged.hpp"

namespace raylib {
/**
 * RenderTexture type, for texture rendering
 */
class rlb_RenderTexture : public ::rlb_RenderTexture {
 public:
    /**
     * Default constructor to build an empty RenderTexture.
     */
    rlb_RenderTexture() {
        id = 0;
    }

    rlb_RenderTexture(const ::rlb_RenderTexture& renderTexture) {
        set(renderTexture);
    }

    rlb_RenderTexture(unsigned int id, const ::rlb_Texture& texture, const ::rlb_Texture& depth) :
        ::rlb_RenderTexture{id, texture, depth} {}

    /**
     * Load texture for rendering (framebuffer)
     */
    rlb_RenderTexture(int width, int height) {
        set(::LoadRenderTexture(width, height));
    }

    rlb_RenderTexture(const rlb_RenderTexture&) = delete;

    rlb_RenderTexture(rlb_RenderTexture&& other) {
        set(other);

        other.id = 0;
        other.texture = {};
        other.depth = {};
    }

    GETTERSETTER(unsigned int, Id, id)

    /**
     * Get the color buffer attachment texture.
     */
    inline TextureUnmanaged GetTexture() {
        return texture;
    }

    inline void SetTexture(const ::rlb_Texture& newTexture) {
        texture = newTexture;
    }

    /**
     * Depth buffer attachment texture
     */
    inline TextureUnmanaged GetDepth() {
        return depth;
    }

    inline void SetDepth(const ::rlb_Texture& newDepth) {
        depth = newDepth;
    }

    rlb_RenderTexture& operator=(const ::rlb_RenderTexture& texture) {
        set(texture);
        return *this;
    }

    rlb_RenderTexture& operator=(const rlb_RenderTexture&) = delete;

    rlb_RenderTexture& operator=(rlb_RenderTexture&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.id = 0;
        other.texture = {};
        other.depth = {};

        return *this;
    }

    ~rlb_RenderTexture() {
        Unload();
    }

    inline void Unload() {
        UnloadRenderTexture(*this);
    }

    /**
     * Initializes render texture for drawing
     */
    inline rlb_RenderTexture& BeginMode() {
        ::BeginTextureMode(*this);
        return *this;
    }

    /**
     * Ends drawing to render texture
     */
    inline rlb_RenderTexture& EndMode() {
        ::EndTextureMode();
        return *this;
    }

    /**
     * Load texture for rendering (framebuffer)
     */
    static rlb_RenderTexture Load(int width, int height) {
        return ::LoadRenderTexture(width, height);
    }

    /**
     * Retrieves whether or not the render texture is ready.
     */
    inline bool IsReady() const {
        return ::IsRenderTextureReady(*this);
    }

 protected:
    void set(const ::rlb_RenderTexture& renderTexture) {
        id = renderTexture.id;
        texture = renderTexture.texture;
        depth = renderTexture.depth;
    }
};
typedef rlb_RenderTexture rlb_RenderTexture2D;
}  // namespace raylib

using RRenderTexture = raylib::rlb_RenderTexture;
using RRenderTexture2D = raylib::rlb_RenderTexture2D;

#endif  // RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_
