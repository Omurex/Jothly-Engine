#ifndef RAYLIB_CPP_INCLUDE_COLOR_HPP_
#define RAYLIB_CPP_INCLUDE_COLOR_HPP_

#include <string>

#include "./raylib.hpp"
#include "./Vector4.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Color type, RGBA (32bit)
 */
class rlb_Color : public ::rlb_Color {
 public:
    rlb_Color(const ::rlb_Color& color) : ::rlb_Color{color.r, color.g, color.b, color.a} {}

    rlb_Color(
            unsigned char red,
            unsigned char green,
            unsigned char blue,
            unsigned char alpha = 255) : ::rlb_Color{red, green, blue, alpha} {};

    /**
     * Black.
     */
    rlb_Color() : ::rlb_Color{0, 0, 0, 255} {};

    /**
     * Returns a Color from HSV values
     */
    rlb_Color(::rlb_Vector3 hsv) {
        set(::ColorFromHSV(hsv.x, hsv.y, hsv.z));
    }

    /**
     * Returns a Color from HSV values
     */
    static ::rlb_Color FromHSV(float hue, float saturation, float value) {
        return ::ColorFromHSV(hue, saturation, value);
    }

    /**
     * Get Color structure from hexadecimal value
     */
    rlb_Color(unsigned int hexValue) {
        set(::GetColor(hexValue));
    }

    rlb_Color(void *srcPtr, int format) {
        set(::GetPixelColor(srcPtr, format));
    }

    /**
     * Returns hexadecimal value for a Color
     */
    int ToInt() const {
        return ::ColorToInt(*this);
    }

    /**
     * Returns hexadecimal value for a Color
     */
    operator int() const {
        return ::ColorToInt(*this);
    }

    inline std::string ToString() const {
        return TextFormat("Color(%d, %d, %d, %d)", r, g, b, a);
    }

    inline operator std::string() const {
        return ToString();
    }

    /**
     * Returns color with alpha applied, alpha goes from 0.0f to 1.0f
     */
    rlb_Color Fade(float alpha) const {
        return ::Fade(*this, alpha);
    }

    /**
     * Returns Color normalized as float [0..1]
     */
    rlb_Vector4 Normalize() const {
        return ::ColorNormalize(*this);
    }

    /**
     * Returns Color from normalized values [0..1]
     */
    rlb_Color(::rlb_Vector4 normalized) {
        set(::ColorFromNormalized(normalized));
    }

    /**
     * Returns HSV values for a Color
     */
    rlb_Vector3 ToHSV() const {
        return ::ColorToHSV(*this);
    }

    GETTERSETTER(unsigned char, R, r)
    GETTERSETTER(unsigned char, G, g)
    GETTERSETTER(unsigned char, B, b)
    GETTERSETTER(unsigned char, A, a)

    rlb_Color& operator=(const ::rlb_Color& color) {
        set(color);
        return *this;
    }

    /**
     * Set background color (framebuffer clear color)
     */
    inline rlb_Color& ClearBackground() {
        ::ClearBackground(*this);
        return *this;
    }

    inline void DrawPixel(int x, int y) const {
        ::DrawPixel(x, y, *this);
    }

    /**
     * Draw a pixel
     */
    inline void DrawPixel(::rlb_Vector2 pos) const {
        ::DrawPixelV(pos, *this);
    }

    /**
     * Draw a line
     */
    inline void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY) const {
        ::DrawLine(startPosX, startPosY, endPosX, endPosY, *this);
    }

    /**
     * Draw a line using Vector points
     */
    inline void DrawLine(::rlb_Vector2 startPos, ::rlb_Vector2 endPos) const {
        ::DrawLineV(startPos, endPos, *this);
    }

    /**
     * Draw a line using Vector points, with a given thickness
     */
    inline void DrawLine(::rlb_Vector2 startPos, ::rlb_Vector2 endPos, float thick) const {
        ::DrawLineEx(startPos, endPos, thick, *this);
    }

    inline void DrawLineBezier(::rlb_Vector2 startPos, ::rlb_Vector2 endPos, float thick = 1.0f) const {
        ::DrawLineBezier(startPos, endPos, thick, *this);
    }

    inline void DrawLineStrip(::rlb_Vector2 *points, int numPoints) const {
        ::DrawLineStrip(points, numPoints, *this);
    }

    inline void DrawText(const std::string& text, int posX = 0, int posY = 0, int fontSize = 10.0f) const {
        ::DrawText(text.c_str(), posX, posY, fontSize, *this);
    }

    inline void DrawText(const ::rlb_Font& font, const std::string& text, ::rlb_Vector2 position,
            float fontSize, float spacing) const {
        ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, *this);
    }

    inline void DrawText(
            const ::rlb_Font& font,
            const std::string& text,
            ::rlb_Vector2 position,
            ::rlb_Vector2 origin,
            float rotation,
            float fontSize,
            float spacing) const {
        ::DrawTextPro(font, text.c_str(), position, origin, rotation, fontSize, spacing, *this);
    }

    inline void DrawRectangle(int posX, int posY, int width, int height) const {
        ::DrawRectangle(posX, posY, width, height, *this);
    }

    inline void DrawRectangle(::rlb_Vector2 position, ::rlb_Vector2 size) const {
        ::DrawRectangleV(position, size, *this);
    }

    inline void DrawRectangle(::rlb_Rectangle rec) const {
        ::DrawRectangleRec(rec, *this);
    }

    inline void DrawRectangle(::rlb_Rectangle rec, ::rlb_Vector2 origin, float rotation) const {
        ::DrawRectanglePro(rec, origin, rotation, *this);
    }

    inline void DrawRectangleLines(int posX, int posY, int width, int height) const {
        ::DrawRectangleLines(posX, posY, width, height, *this);
    }

    inline void DrawRectangleLines(::rlb_Rectangle rec, float lineThick) const {
        ::DrawRectangleLinesEx(rec, lineThick, *this);
    }

    /**
     * Get color multiplied with another color
     */
    inline rlb_Color Tint(::rlb_Color tint) {
        return ::ColorTint(*this, tint);
    }

    /**
     * Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
     */
    inline rlb_Color Brightness(float factor) {
        return ::ColorBrightness(*this, factor);
    }

    /**
     * Get color with contrast correction, contrast values between -1.0f and 1.0f
     */
    inline rlb_Color Contrast(float contrast) {
        return ::ColorContrast(*this, contrast);
    }

    /**
     * Returns color with alpha applied, alpha goes from 0.0f to 1.0f
     */
    rlb_Color Alpha(float alpha) const {
        return ::ColorAlpha(*this, alpha);
    }

    /**
     * Returns src alpha-blended into dst color with tint
     */
    rlb_Color AlphaBlend(::rlb_Color dst, ::rlb_Color tint) const {
        return ::ColorAlphaBlend(dst, *this, tint);
    }

    inline static rlb_Color LightGray() { return LIGHTGRAY; }
    inline static rlb_Color Gray() { return GRAY; }
    inline static rlb_Color DarkGray() { return DARKGRAY; }
    inline static rlb_Color Yellow() { return YELLOW; }
    inline static rlb_Color Gold() { return GOLD; }
    inline static rlb_Color Orange() { return ORANGE; }
    inline static rlb_Color Pink() { return PINK; }
    inline static rlb_Color Red() { return RED; }
    inline static rlb_Color Maroon() { return MAROON; }
    inline static rlb_Color Green() { return GREEN; }
    inline static rlb_Color Lime() { return LIME; }
    inline static rlb_Color DarkGreen() { return DARKGREEN; }
    inline static rlb_Color SkyBlue() { return SKYBLUE; }
    inline static rlb_Color Blue() { return BLUE; }
    inline static rlb_Color DarkBlue() { return DARKBLUE; }
    inline static rlb_Color Purple() { return PURPLE; }
    inline static rlb_Color Violet() { return VIOLET; }
    inline static rlb_Color DarkPurple() { return DARKPURPLE; }
    inline static rlb_Color Beige() { return BEIGE; }
    inline static rlb_Color Brown() { return BROWN; }
    inline static rlb_Color DarkBrown() { return DARKBROWN; }
    inline static rlb_Color White() { return WHITE; }
    inline static rlb_Color Black() { return BLACK; }
    inline static rlb_Color Blank() { return BLANK; }
    inline static rlb_Color Magenta() { return MAGENTA; }
    inline static rlb_Color RayWhite() { return RAYWHITE; }

 protected:
    void set(const ::rlb_Color& color) {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }
};

}  // namespace raylib

using RColor = raylib::rlb_Color;

#endif  // RAYLIB_CPP_INCLUDE_COLOR_HPP_
