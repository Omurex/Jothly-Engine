#ifndef RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_
#define RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_

#include "./raylib.hpp"
#include "./Vector2.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Camera2D type, defines a 2d camera
 */
class rlb_Camera2D : public ::rlb_Camera2D {
 public:
    rlb_Camera2D(const ::rlb_Camera2D& camera) {
        set(camera);
    }

    rlb_Camera2D() {}
    rlb_Camera2D(::rlb_Vector2 offset, ::rlb_Vector2 target,
            float rotation = 0.0f, float zoom = 1.0f) : ::rlb_Camera2D{offset, target, rotation, zoom} {}

    inline rlb_Camera2D& BeginMode() {
        ::BeginMode2D(*this);
        return *this;
    }

    inline rlb_Camera2D& EndMode() {
        ::EndMode2D();
        return *this;
    }

    GETTERSETTER(::rlb_Vector2, Offset, offset)
    GETTERSETTER(::rlb_Vector2, Target, target)
    GETTERSETTER(float, Rotation, rotation)
    GETTERSETTER(float, Zoom, zoom)

    rlb_Camera2D& operator=(const ::rlb_Camera2D& camera) {
        set(camera);
        return *this;
    }

    /**
     * Returns camera 2d transform matrix
     */
    inline rlb_Matrix GetMatrix() const {
        return ::GetCameraMatrix2D(*this);
    }

    /**
     * Returns the world space position for a 2d camera screen space position
     */
    inline rlb_Vector2 GetScreenToWorld(::rlb_Vector2 position) const {
        return ::GetScreenToWorld2D(position, *this);
    }

    /**
     * Returns the screen space position for a 3d world space position
     */
    inline rlb_Vector2 GetWorldToScreen(::rlb_Vector2 position) const {
        return ::GetWorldToScreen2D(position, *this);
    }

 protected:
    void set(const ::rlb_Camera2D& camera) {
        offset = camera.offset;
        target = camera.target;
        rotation = camera.rotation;
        zoom = camera.zoom;
    }
};
}  // namespace raylib

using RCamera2D = raylib::rlb_Camera2D;

#endif  // RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_
