#ifndef RAYLIB_CPP_INCLUDE_TEXTURE_HPP_
#define RAYLIB_CPP_INCLUDE_TEXTURE_HPP_

#include "./TextureUnmanaged.hpp"

namespace raylib {
/**
 * Texture type
 *
 * The texture will be unloaded on object destruction. Use raylib::TextureUnmanaged if you're looking to not unload.
 *
 * @see raylib::TextureUnmanaged
 */
class rlb_Texture : public TextureUnmanaged {
 public:
    using TextureUnmanaged::TextureUnmanaged;

    /**
     * Explicitly forbid the copy constructor.
     */
    rlb_Texture(const rlb_Texture&) = delete;

    /**
     * Explicitly forbid copy assignment.
     */
    rlb_Texture& operator=(const rlb_Texture&) = delete;

    /**
     * Move constructor.
     */
    rlb_Texture(rlb_Texture&& other) {
        set(other);

        other.id = 0;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;
    }

    /**
     * On destruction, unload the Texture.
     */
    ~rlb_Texture() {
        Unload();
    }

    /**
     * Move assignment.
     */
    rlb_Texture& operator=(rlb_Texture&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.id = 0;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;

        return *this;
    }
};

// Create the Texture aliases.
typedef rlb_Texture rlb_Texture2D;
typedef rlb_Texture rlb_TextureCubemap;

}  // namespace raylib

using RTexture = raylib::rlb_Texture;
using RTexture2D = raylib::rlb_Texture2D;
using RTextureCubemap = raylib::rlb_TextureCubemap;

#endif  // RAYLIB_CPP_INCLUDE_TEXTURE_HPP_
