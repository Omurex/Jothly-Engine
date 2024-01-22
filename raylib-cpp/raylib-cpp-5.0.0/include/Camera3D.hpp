#ifndef RAYLIB_CPP_INCLUDE_CAMERA3D_HPP_
#define RAYLIB_CPP_INCLUDE_CAMERA3D_HPP_

#include "./raylib.hpp"
#include "./Vector3.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Camera type, defines a camera position/orientation in 3d space
 */
class rlb_Camera3D : public ::rlb_Camera3D {
 public:
    rlb_Camera3D(const ::rlb_Camera3D& camera) {
        set(camera);
    }

    /**
     * Create a new Camera3D.
     *
     * @param position Camera position
     * @param target Camera target it looks-at
     * @param up Camera up vector (rotation over its axis)
     * @param fovy Camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic
     * @param projection Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
     */
    rlb_Camera3D(::rlb_Vector3 position,
            ::rlb_Vector3 target = ::rlb_Vector3{0.0f, 0.0f, 0.0f},
            ::rlb_Vector3 up = ::rlb_Vector3{0.0f, 1.0f, 0.0f},
            float fovy = 0,
            int projection = CAMERA_PERSPECTIVE) : ::rlb_Camera3D{position, target, up, fovy, projection} {}

    rlb_Camera3D() {}

    GETTERSETTER(::rlb_Vector3, Position, position)
    GETTERSETTER(::rlb_Vector3, Target, target)
    GETTERSETTER(::rlb_Vector3, Up, up)
    GETTERSETTER(float, Fovy, fovy)
    GETTERSETTER(int, Projection, projection)

    rlb_Camera3D& operator=(const ::rlb_Camera3D& camera) {
        set(camera);
        return *this;
    }

    /**
     * Initializes 3D mode with custom camera (3D)
     */
    rlb_Camera3D& BeginMode() {
        ::BeginMode3D(*this);
        return *this;
    }

    /**
     * Ends 3D mode and returns to default 2D orthographic mode
     */
    rlb_Camera3D& EndMode() {
        ::EndMode3D();
        return *this;
    }

    /**
     * Get camera transform matrix (view matrix)
     */
    inline rlb_Matrix GetMatrix() const {
        return ::GetCameraMatrix(*this);
    }

    /**
     * Update camera position for selected mode
     */
    inline rlb_Camera3D& Update(int mode) {
        ::UpdateCamera(this, mode);
        return *this;
    }

    /**
     * Update camera movement/rotation
     */
    inline rlb_Camera3D& Update(::rlb_Vector3 movement, ::rlb_Vector3 rotation, float zoom = 1.0f) {
        ::UpdateCameraPro(this, movement, rotation, zoom);
        return *this;
    }

    /**
     * Returns a ray trace from mouse position
     */
    inline rlb_Ray GetMouseRay(::rlb_Vector2 mousePosition) const {
        return ::GetMouseRay(mousePosition, *this);
    }

    /**
     * Returns the screen space position for a 3d world space position
     */
    inline rlb_Vector2 GetWorldToScreen(::rlb_Vector3 position) const {
        return ::GetWorldToScreen(position, *this);
    }

    /**
     * Draw a billboard texture.
     */
    inline void DrawBillboard(
            const ::rlb_Texture2D& texture,
            ::rlb_Vector3 center,
            float size,
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawBillboard(*this, texture, center, size, tint);
    }

    /**
     * Draw a billboard texture defined by source.
     */
    inline void DrawBillboard(
            const ::rlb_Texture2D& texture,
            ::rlb_Rectangle sourceRec,
            ::rlb_Vector3 center,
            ::rlb_Vector2 size,
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawBillboardRec(*this, texture, sourceRec, center, size, tint);
    }

 protected:
    void set(const ::rlb_Camera3D& camera) {
        position = camera.position;
        target = camera.target;
        up = camera.up;
        fovy = camera.fovy;
        projection = camera.projection;
    }
};

typedef rlb_Camera3D rlb_Camera;

}  // namespace raylib

using RCamera = raylib::rlb_Camera;
using RCamera3D = raylib::rlb_Camera3D;

#endif  // RAYLIB_CPP_INCLUDE_CAMERA3D_HPP_
