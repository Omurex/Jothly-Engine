#ifndef RAYLIB_CPP_INCLUDE_FONT_HPP_
#define RAYLIB_CPP_INCLUDE_FONT_HPP_

#include <string>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./RaylibException.hpp"
#include "./TextureUnmanaged.hpp"

namespace raylib {
/**
 * Font type, includes texture and charSet array data
 */
class rlb_Font : public ::rlb_Font {
 public:
    rlb_Font(int baseSize,
            int glyphCount,
            int glyphPadding,
            ::rlb_Texture2D texture,
            ::rlb_Rectangle *recs = nullptr,
            ::rlb_GlyphInfo *glyphs = nullptr) : ::rlb_Font{baseSize, glyphCount, glyphPadding, texture, recs, glyphs} {
        // Nothing.
    }

    /**
     * Retrieves the default Font.
     */
    rlb_Font() {
        set(::GetFontDefault());
    }

    rlb_Font(const ::rlb_Font& font) {
        set(font);
    }

    /**
     * Loads a Font from the given file.
     *
     * @param fileName The file name of the font to load.
     *
     * @throws raylib::RaylibException Throws if the given font failed to initialize.
     */
    rlb_Font(const std::string& fileName) {
        Load(fileName);
    }

    /**
     * Loads a Font from the given file, with generation parameters.
     *
     * @param fileName The file name of the font to load.
     *
     * @throws raylib::RaylibException Throws if the given font failed to initialize.
     *
     * @see ::LoadFontEx
     */
    rlb_Font(const std::string& fileName, int fontSize, int* fontChars = 0, int charCount = 0)  {
        Load(fileName, fontSize, fontChars, charCount);
    }

    /**
     * Loads a Font from the given image with a color key.
     *
     * @param image The image to load the fond from.
     *
     * @throws raylib::RaylibException Throws if the given font failed to initialize.
     *
     * @see ::LoadFontFromImage()
     */
    rlb_Font(const ::rlb_Image& image, ::rlb_Color key, int firstChar) {
        Load(image, key, firstChar);
    }

    /**
     * Loads a font from memory, based on the given file type and file data.
     *
     * @throws raylib::RaylibException Throws if the given font failed to initialize.
     *
     * @see ::LoadFontFromMemory()
     */
    rlb_Font(const std::string& fileType, const unsigned char* fileData, int dataSize, int fontSize,
            int *fontChars, int charsCount)  {
        Load(fileType, fileData, dataSize, fontSize, fontChars, charsCount);
    }

    rlb_Font(const rlb_Font&) = delete;

    rlb_Font(rlb_Font&& other) {
        set(other);

        other.baseSize = 0;
        other.glyphCount = 0;
        other.glyphPadding = 0;
        other.texture = {};
        other.recs = nullptr;
        other.glyphs = nullptr;
    }

    ~rlb_Font() {
        Unload();
    }

    void Unload() {
        // Protect against calling UnloadFont() twice.
        if (baseSize != 0) {
            UnloadFont(*this);
            baseSize = 0;
        }
    }

    GETTERSETTER(int, BaseSize, baseSize)
    GETTERSETTER(int, GlyphCount, glyphCount)
    GETTERSETTER(int, GlyphPadding, glyphPadding)
    GETTERSETTER(::rlb_Rectangle*, Recs, recs)
    GETTERSETTER(::rlb_GlyphInfo*, Glyphs, glyphs)

    /**
     * Get the texture atlas containing the glyphs.
     */
    inline TextureUnmanaged GetTexture() {
        return texture;
    }

    /**
     * Set the texture atlas containing the glyphs.
     */
    inline void SetTexture(const ::rlb_Texture& newTexture) {
        texture = newTexture;
    }

    rlb_Font& operator=(const ::rlb_Font& font) {
        Unload();
        set(font);
        return *this;
    }

    rlb_Font& operator=(const rlb_Font&) = delete;

    rlb_Font& operator=(rlb_Font&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.baseSize = 0;
        other.glyphCount = 0;
        other.glyphPadding = 0;
        other.texture = {};
        other.recs = nullptr;
        other.glyphs = nullptr;

        return *this;
    }

    /**
     * Loads a font from a given file.
     *
     * @param fileName The filename of the font to load.
     *
     * @throws raylib::RaylibException Throws if the given font failed to initialize.
     *
     * @see ::LoadFont()
     */
    void Load(const std::string& fileName) {
        set(::LoadFont(fileName.c_str()));
        if (!IsReady()) {
            throw new RaylibException("Failed to load Font with from file: " + fileName);
        }
    }

    /**
     * Loads a font from a given file with generation parameters.
     *
     * @param fileName The filename of the font to load.
     * @param fontSize The desired size of the font.
     *
     * @throws raylib::RaylibException Throws if the given font failed to initialize.
     *
     * @see ::LoadFontEx()
     */
    void Load(const std::string& fileName, int fontSize, int* fontChars, int charCount)  {
        set(::LoadFontEx(fileName.c_str(), fontSize, fontChars, charCount));
        if (!IsReady()) {
            throw new RaylibException("Failed to load Font with from file with font size: " + fileName);
        }
    }

    void Load(const ::rlb_Image& image, ::rlb_Color key, int firstChar) {
        set(::LoadFontFromImage(image, key, firstChar));
        if (!IsReady()) {
            throw new RaylibException("Failed to load Font with from image");
        }
    }

    void Load(const std::string& fileType, const unsigned char* fileData, int dataSize, int fontSize,
            int *fontChars, int charsCount)  {
        set(::LoadFontFromMemory(fileType.c_str(), fileData, dataSize, fontSize, fontChars,
            charsCount));
        if (!IsReady()) {
            throw new RaylibException("Failed to load Font " + fileType + " with from file data");
        }
    }

    /**
     * Returns if the font is ready to be used.
     */
    bool IsReady() const {
        return ::IsFontReady(*this);
    }

    /**
     * Draw text using font and additional parameters.
     */
    inline void DrawText(const std::string& text, ::rlb_Vector2 position, float fontSize,
            float spacing, ::rlb_Color tint = RLB_WHITE) const {
        ::DrawTextEx(*this, text.c_str(), position,  fontSize,  spacing,  tint);
    }

    /**
     * Draw text using font and additional parameters.
     */
    inline void DrawText(const std::string& text, int posX, int posY, float fontSize,
            float spacing, ::rlb_Color tint = RLB_WHITE) const {
        ::DrawTextEx(*this, text.c_str(),
            { static_cast<float>(posX), static_cast<float>(posY) },
            fontSize, spacing, tint);
    }

    inline void DrawText(
            const std::string& text,
            ::rlb_Vector2 position,
            ::rlb_Vector2 origin,
            float rotation,
            float fontSize,
            float spacing,
            ::rlb_Color tint = RLB_WHITE) const {
        ::DrawTextPro(*this, text.c_str(),
            position, origin,
            rotation, fontSize,
            spacing, tint);
    }

    /**
     * Draw one character (codepoint)
     */
    inline void DrawText(int codepoint,
            ::rlb_Vector2 position,
            float fontSize,
            ::rlb_Color tint = { 255, 255, 255, 255 }) const {
        ::DrawTextCodepoint(*this, codepoint, position, fontSize, tint);
    }

    /**
     * Draw multiple character (codepoint)
     */
    inline void DrawText(const int *codepoints,
            int count, ::rlb_Vector2 position,
            float fontSize, float spacing,
            ::rlb_Color tint = { 255, 255, 255, 255 }) const {
        ::DrawTextCodepoints(*this,
            codepoints, count,
            position, fontSize,
            spacing, tint);
    }

    /**
     * Measure string size for Font
     */
    inline rlb_Vector2 MeasureText(const std::string& text, float fontSize, float spacing) const {
        return ::MeasureTextEx(*this, text.c_str(), fontSize, spacing);
    }

    /**
     * Get index position for a unicode character on font
     */
    inline int GetGlyphIndex(int character) const {
        return ::GetGlyphIndex(*this, character);
    }

    /**
     * Create an image from text (custom sprite font)
     */
    inline ::rlb_Image ImageText(const std::string& text, float fontSize,
            float spacing, ::rlb_Color tint) const {
        return ::ImageTextEx(*this, text.c_str(), fontSize, spacing, tint);
    }

 protected:
    void set(const ::rlb_Font& font) {
        baseSize = font.baseSize;
        glyphCount = font.glyphCount;
        glyphPadding = font.glyphPadding;
        texture = font.texture;
        recs = font.recs;
        glyphs = font.glyphs;
    }
};
}  // namespace raylib

using RFont = raylib::rlb_Font;

#endif  // RAYLIB_CPP_INCLUDE_FONT_HPP_
