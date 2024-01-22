#ifndef RAYLIB_CPP_INCLUDE_RAY_HPP_
#define RAYLIB_CPP_INCLUDE_RAY_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./RayCollision.hpp"

namespace raylib {
/**
 * Ray type (useful for raycast)
 */
class rlb_Ray : public ::rlb_Ray {
 public:
    rlb_Ray(const ::rlb_Ray& ray) {
        set(ray);
    }

    rlb_Ray(::rlb_Vector3 position = {0.0f, 0.0f, 0.0f}, ::rlb_Vector3 direction = {0.0f, 0.0f, 0.0f}) :
            ::rlb_Ray{position, direction} {
        // Nothing.
    }

    rlb_Ray(::rlb_Vector2 mousePosition, const ::rlb_Camera& camera) {
        set(::GetMouseRay(mousePosition, camera));
    }

    rlb_Ray& operator=(const ::rlb_Ray& ray) {
        set(ray);
        return *this;
    }

    GETTERSETTER(::rlb_Vector3, Position, position)
    GETTERSETTER(::rlb_Vector3, Direction, direction)

    /**
     * Draw a ray line
     */
    inline void Draw(::rlb_Color color) const {
        DrawRay(*this, color);
    }

    /**
     * Get collision information between ray and sphere
     */
    inline rlb_RayCollision GetCollision(::rlb_Vector3 center, float radius) const {
        return ::GetRayCollisionSphere(*this, center, radius);
    }

    /**
     * Detect collision between ray and box
     */
    inline rlb_RayCollision GetCollision(const ::rlb_BoundingBox& box) const {
        return ::GetRayCollisionBox(*this, box);
    }

    /**
     * Get collision information between ray and mesh
     */
    inline rlb_RayCollision GetCollision(const ::rlb_Mesh& mesh, const ::rlb_Matrix& transform) const {
        return ::GetRayCollisionMesh(*this, mesh, transform);
    }

    /**
     * Get collision info between ray and triangle
     */
    inline rlb_RayCollision GetCollision(::rlb_Vector3 p1, ::rlb_Vector3 p2, ::rlb_Vector3 p3) const {
        return ::GetRayCollisionTriangle(*this, p1, p2, p3);
    }

    /**
     * Get collision info between ray and quad
     */
    inline rlb_RayCollision GetCollision(::rlb_Vector3 p1, ::rlb_Vector3 p2, ::rlb_Vector3 p3, ::rlb_Vector3 p4) const {
        return ::GetRayCollisionQuad(*this, p1, p2, p3, p4);
    }

    /**
     * Get a ray trace from mouse position
     */
    inline static rlb_Ray GetMouse(::rlb_Vector2 mousePosition, const ::rlb_Camera& camera) {
        return ::GetMouseRay(mousePosition, camera);
    }

    /**
     * Get a ray trace from mouse position
     */
    inline static rlb_Ray GetMouse(const ::rlb_Camera& camera) {
        return ::GetMouseRay(::GetMousePosition(), camera);
    }

 protected:
    inline void set(const ::rlb_Ray& ray) {
        position = ray.position;
        direction = ray.direction;
    }
};
}  // namespace raylib

using RRay = raylib::rlb_Ray;

#endif  // RAYLIB_CPP_INCLUDE_RAY_HPP_
