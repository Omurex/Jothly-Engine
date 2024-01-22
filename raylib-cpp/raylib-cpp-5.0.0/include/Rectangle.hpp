#ifndef RAYLIB_CPP_INCLUDE_RECTANGLE_HPP_
#define RAYLIB_CPP_INCLUDE_RECTANGLE_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./Vector2.hpp"

namespace raylib {
/**
 * Rectangle type
 */
class rlb_Rectangle : public ::rlb_Rectangle {
 public:
    rlb_Rectangle(const ::rlb_Rectangle& rect) : ::rlb_Rectangle{rect.x, rect.y, rect.width, rect.height} {}

    rlb_Rectangle(float x, float y, float width, float height) : ::rlb_Rectangle{x, y, width, height} {}
    rlb_Rectangle(float x, float y, float width) : ::rlb_Rectangle{x, y, width, 0} {}
    rlb_Rectangle(float x, float y) : ::rlb_Rectangle{x, y, 0, 0} {}
    rlb_Rectangle(float x) : ::rlb_Rectangle{x, 0, 0, 0} {}
    rlb_Rectangle() : ::rlb_Rectangle{0, 0, 0, 0} {}

    rlb_Rectangle(::rlb_Vector2 position, ::rlb_Vector2 size)
            : ::rlb_Rectangle{position.x, position.y, size.x, size.y} {}
    rlb_Rectangle(::rlb_Vector2 size) : ::rlb_Rectangle{0, 0, size.x, size.y} {}
    rlb_Rectangle(::rlb_Vector4 rect) : ::rlb_Rectangle{rect.x, rect.y, rect.z, rect.w} {}

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Width, width)
    GETTERSETTER(float, Height, height)

    rlb_Rectangle& operator=(const ::rlb_Rectangle& rect) {
        set(rect);
        return *this;
    }

    inline ::rlb_Vector4 ToVector4() {
        return {x, y, width, height};
    }

    operator ::rlb_Vector4() const {
        return {x, y, width, height};
    }

    /**
     * Draw a color-filled rectangle
     */
    inline void Draw(::rlb_Color color) const {
        ::DrawRectangleRec(*this, color);
    }

    inline void Draw(::rlb_Vector2 origin, float rotation, ::rlb_Color color) const {
        ::DrawRectanglePro(*this, origin, rotation, color);
    }

    inline void DrawGradientV(::rlb_Color color1, ::rlb_Color color2) const {
        ::DrawRectangleGradientV(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width),
            static_cast<int>(height), color1, color2);
    }

    inline void DrawGradientH(::rlb_Color color1, ::rlb_Color color2) const {
        ::DrawRectangleGradientH(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width),
            static_cast<int>(height), color1, color2);
    }

    inline void DrawGradient(::rlb_Color col1, ::rlb_Color col2, ::rlb_Color col3, ::rlb_Color col4) const {
        ::DrawRectangleGradientEx(*this, col1, col2, col3, col4);
    }

    inline void DrawLines(::rlb_Color color) const {
        ::DrawRectangleLines(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width),
            static_cast<int>(height), color);
    }

    inline void DrawLines(::rlb_Color color, float lineThick) const {
        ::DrawRectangleLinesEx(*this, lineThick, color);
    }

    inline void DrawRounded(float roundness, int segments, ::rlb_Color color) const {
        ::DrawRectangleRounded(*this, roundness, segments, color);
    }

    inline void DrawRoundedLines(float roundness, int segments,
            float lineThick, ::rlb_Color color) const {
        ::DrawRectangleRoundedLines(*this, roundness, segments, lineThick, color);
    }

    /**
     * Check collision between two rectangles
     */
    inline bool CheckCollision(::rlb_Rectangle rec2) const {
        return ::CheckCollisionRecs(*this, rec2);
    }

    /**
     * Get collision rectangle for two rectangles collision
     */
    inline ::rlb_Rectangle GetCollision(::rlb_Rectangle rec2) const {
        return ::GetCollisionRec(*this, rec2);
    }

    /**
     * Check if point is inside rectangle
     */
    inline bool CheckCollision(::rlb_Vector2 point) const {
        return ::CheckCollisionPointRec(point, *this);
    }

    /**
     * Check collision between circle and rectangle
     */
    inline bool CheckCollision(::rlb_Vector2 center, float radius) const {
        return ::CheckCollisionCircleRec(center, radius, *this);
    }

    inline rlb_Vector2 GetSize() const {
        return {width, height};
    }

    inline rlb_Rectangle& SetSize(float newWidth, float newHeight) {
        width = newWidth;
        height = newHeight;
        return *this;
    }

    inline rlb_Rectangle& SetSize(const ::rlb_Vector2& size) {
        return SetSize(size.x, size.y);
    }

    inline rlb_Rectangle& SetShapesTexture(const ::rlb_Texture2D& texture) {
        ::SetShapesTexture(texture, *this);
        return *this;
    }

    inline rlb_Vector2 GetPosition() const {
        return {x, y};
    }

    inline rlb_Rectangle& SetPosition(float newX, float newY) {
        x = newX;
        y = newY;
        return *this;
    }

    inline rlb_Rectangle& SetPosition(const ::rlb_Vector2& position) {
        return SetPosition(position.x, position.y);
    }

 protected:
    void set(const ::rlb_Rectangle& rect) {
        x = rect.x;
        y = rect.y;
        width = rect.width;
        height = rect.height;
    }
};
}  // namespace raylib

using RRectangle = raylib::rlb_Rectangle;

#endif  // RAYLIB_CPP_INCLUDE_RECTANGLE_HPP_
