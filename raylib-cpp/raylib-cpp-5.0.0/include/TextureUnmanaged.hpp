#ifndef RAYLIB_CPP_INCLUDE_TEXTUREUNMANAGED_HPP_
#define RAYLIB_CPP_INCLUDE_TEXTUREUNMANAGED_HPP_

#include <string>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./Vector2.hpp"
#include "./Material.hpp"
#include "./RaylibException.hpp"
#include "./Image.hpp"

namespace raylib {
/**
 * A Texture that is not managed by the C++ garbage collector.
 *
 * Make sure to Unload() this if needed, otherwise use raylib::Texture.
 *
 * @see raylib::Texture
 */
class TextureUnmanaged : public ::rlb_Texture {
 public:
    /**
     * Default texture constructor.
     */
    TextureUnmanaged() : ::rlb_Texture{0, 0, 0, 0, 0} {
        // Nothing.
    }

    /**
     * Move/Create a texture structure manually.
     */
    TextureUnmanaged(unsigned int id,
            int width, int height,
            int mipmaps = 1,
            int format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
            : ::rlb_Texture{id, width, height, mipmaps, format} {
        // Nothing.
    }

    /**
     * Creates a texture object based on the given Texture struct data.
     */
    TextureUnmanaged(const ::rlb_Texture& texture) :
            ::rlb_Texture{texture.id, texture.width, texture.height, texture.mipmaps, texture.format} {
        // Nothing.
    }

    /**
     * Creates a texture from the given Image.
     *
     * @throws raylib::RaylibException Throws if failed to create the texture from the given image.
     */
    TextureUnmanaged(const ::rlb_Image& image) {
        Load(image);
    }

    /**
     * Load cubemap from image, multiple image cubemap layouts supported.
     *
     * @throws raylib::RaylibException Throws if failed to create the texture from the given cubemap.
     *
     * @see LoadTextureCubemap()
     */
    TextureUnmanaged(const ::rlb_Image& image, int layout) {
        Load(image, layout);
    }

    /**
     * Load texture from file into GPU memory (VRAM)
     *
     * @throws raylib::RaylibException Throws if failed to create the texture from the given file.
     */
    TextureUnmanaged(const std::string& fileName) {
        Load(fileName);
    }

    TextureUnmanaged(::rlb_Texture&& other) :
            ::rlb_Texture{other.id, other.width, other.height, other.mipmaps, other.format} {
        // Nothing.
    }

    GETTERSETTER(unsigned int, Id, id)
    GETTERSETTER(int, Width, width)
    GETTERSETTER(int, Height, height)
    GETTERSETTER(int, Mipmaps, mipmaps)
    GETTERSETTER(int, Format, format)

    TextureUnmanaged& operator=(const ::rlb_Texture& texture) {
        set(texture);
        return *this;
    }

    /**
     * Retrieve the width and height of the texture.
     */
    inline ::rlb_Vector2 GetSize() const {
        return {static_cast<float>(width), static_cast<float>(height)};
    }

    /**
     * Load texture from image data
     */
    void Load(const ::rlb_Image& image) {
        set(::LoadTextureFromImage(image));
        if (!IsReady()) {
            throw RaylibException("Failed to load Texture from Image");
        }
    }

    /**
     * Load cubemap from image, multiple image cubemap layouts supported
     */
    void Load(const ::rlb_Image& image, int layoutType) {
        set(::LoadTextureCubemap(image, layoutType));
        if (!IsReady()) {
            throw RaylibException("Failed to load Texture from Cubemap");
        }
    }

    /**
     * Load texture from file into GPU memory (VRAM)
     */
    void Load(const std::string& fileName) {
        set(::LoadTexture(fileName.c_str()));
        if (!IsReady()) {
            throw RaylibException("Failed to load Texture from file: " + fileName);
        }
    }

    /**
     * Unload texture from GPU memory (VRAM)
     */
    inline void Unload() {
        // Protect against calling UnloadTexture() twice.
        if (id != 0) {
            ::UnloadTexture(*this);
            id = 0;
        }
    }

    /**
     * Update GPU texture with new data
     */
    inline TextureUnmanaged& Update(const void *pixels) {
        ::UpdateTexture(*this, pixels);
        return *this;
    }

    /**
     * Update GPU texture rectangle with new data
     */
    inline TextureUnmanaged& Update(::rlb_Rectangle rec, const void *pixels) {
        UpdateTextureRec(*this, rec, pixels);
        return *this;
    }

    /**
     * Get pixel data from GPU texture and return an Image
     */
    inline ::rlb_Image GetData() const {
        return ::LoadImageFromTexture(*this);
    }

    /**
     * Get pixel data from GPU texture and return an Image
     */
    inline operator rlb_Image() {
        return GetData();
    }

    /**
     * Generate GPU mipmaps for a texture
     */
    inline TextureUnmanaged& GenMipmaps() {
        ::GenTextureMipmaps(this);
        return *this;
    }

    /**
     * Set texture scaling filter mode
     */
    inline TextureUnmanaged& SetFilter(int filterMode) {
        ::SetTextureFilter(*this, filterMode);
        return *this;
    }

    /**
     * Set texture wrapping mode
     */
    inline TextureUnmanaged& SetWrap(int wrapMode) {
        ::SetTextureWrap(*this, wrapMode);
        return *this;
    }

    /**
     * Draw a Texture2D
     *
     * @see ::DrawTexture()
     */
    inline void Draw(int posX = 0, int posY = 0, ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawTexture(*this, posX, posY, tint);
    }

    /**
     * Draw a Texture2D with position defined as Vector2
     *
     * @see ::DrawTextureV()
     */
    inline void Draw(::rlb_Vector2 position, ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawTextureV(*this, position, tint);
    }

    /**
     * Draw a Texture2D with extended parameters
     *
     * @see ::DrawTextureEx()
     */
    inline void Draw(::rlb_Vector2 position, float rotation, float scale = 1.0f,
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawTextureEx(*this, position, rotation, scale, tint);
    }

    /**
     * Draw a part of a texture defined by a rectangle
     *
     * @see ::DrawTextureRec()
     */
    inline void Draw(::rlb_Rectangle sourceRec, ::rlb_Vector2 position = {0, 0},
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawTextureRec(*this, sourceRec, position, tint);
    }

    /**
     * Draw a part of a texture defined by a rectangle with 'pro' parameters
     *
     * @see ::DrawTexturePro()
     */
    inline void Draw(::rlb_Rectangle sourceRec, ::rlb_Rectangle destRec, ::rlb_Vector2 origin = {0, 0},
            float rotation = 0, ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawTexturePro(*this, sourceRec, destRec, origin, rotation, tint);
    }

    /**
     * Draws a texture (or part of it) that stretches or shrinks nicely
     *
     * @see ::DrawTextureNPatch()
     */
    inline void Draw(::rlb_NPatchInfo nPatchInfo, ::rlb_Rectangle destRec, ::rlb_Vector2 origin = {0, 0},
            float rotation = 0, ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawTextureNPatch(*this, nPatchInfo, destRec, origin, rotation, tint);
    }

    /**
     * Draw a billboard texture
     *
     * @see ::DrawBillboard()
     */
    inline void DrawBillboard(const ::rlb_Camera& camera,
            ::rlb_Vector3 position, float size,
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawBillboard(camera, *this, position, size, tint);
    }

    /**
     * Draw a billboard texture defined by source
     *
     * @see ::DrawBillboardRec()
     */
    inline void DrawBillboard(const ::rlb_Camera& camera,
            ::rlb_Rectangle source, ::rlb_Vector3 position, ::rlb_Vector2 size,
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        DrawBillboardRec(camera, *this, source, position, size, tint);
    }

    /**
     * Draw a billboard texture defined by source and rotation
     *
     * @see ::DrawBillboardPro()
     */
    inline void DrawBillboard(const ::rlb_Camera& camera,
            ::rlb_Rectangle source, rlb_Vector3 position,
            ::rlb_Vector3 up, rlb_Vector2 size, rlb_Vector2 origin, float rotation = 0.0f,
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        DrawBillboardPro(camera, *this, source, position, up, size, origin, rotation, tint);
    }

    /**
     * Set texture for a material map type (MAP_DIFFUSE, MAP_SPECULAR...)
     */
    inline TextureUnmanaged& SetMaterial(::rlb_Material *material, int mapType = MATERIAL_MAP_NORMAL) {
        ::SetMaterialTexture(material, mapType, *this);
        return *this;
    }

    inline TextureUnmanaged& SetMaterial(const ::rlb_Material& material, int mapType = MATERIAL_MAP_NORMAL) {
        ::SetMaterialTexture((::rlb_Material*)(&material), mapType, *this);
        return *this;
    }

    /**
     * Set texture and rectangle to be used on shapes drawing.
     */
    inline TextureUnmanaged& SetShapes(const ::rlb_Rectangle& source) {
        ::SetShapesTexture(*this, source);
        return *this;
    }

    /**
     * Set shader uniform value for texture (sampler2d)
     */
    inline TextureUnmanaged& SetShaderValue(const ::rlb_Shader& shader, int locIndex) {
        ::SetShaderValueTexture(shader, locIndex, *this);
        return *this;
    }

    /**
     * Determines whether or not the Texture has been loaded and is ready.
     *
     * @return True or false depending on whether the Texture has data.
     */
    bool IsReady() const {
        return id != 0;
    }

 protected:
    void set(const ::rlb_Texture& texture) {
        id = texture.id;
        width = texture.width;
        height = texture.height;
        mipmaps = texture.mipmaps;
        format = texture.format;
    }
};

// Create the TextureUnmanaged aliases.
typedef TextureUnmanaged Texture2DUnmanaged;
typedef TextureUnmanaged TextureCubemapUnmanaged;

}  // namespace raylib

using RTextureUnmanaged = raylib::TextureUnmanaged;
using RTexture2DUnmanaged = raylib::Texture2DUnmanaged;
using RTextureCubemapUnmanaged = raylib::TextureCubemapUnmanaged;

#endif  // RAYLIB_CPP_INCLUDE_TEXTUREUNMANAGED_HPP_
