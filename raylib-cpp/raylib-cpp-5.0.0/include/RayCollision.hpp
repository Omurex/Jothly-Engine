#ifndef RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_
#define RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Raycast hit information
 */
class rlb_RayCollision : public ::rlb_RayCollision {
 public:
    rlb_RayCollision(const ::rlb_RayCollision& ray) {
        set(ray);
    }

    rlb_RayCollision(bool hit, float distance,
        ::rlb_Vector3 point, ::rlb_Vector3 normal) : ::rlb_RayCollision{hit, distance, point, normal} {
        // Nothing.
    }

    /**
     * Get collision info between ray and bounding box
     */
    rlb_RayCollision(const ::rlb_Ray& ray, const ::rlb_BoundingBox& box) {
        set(::GetRayCollisionBox(ray, box));
    }

    /**
     * Get collision info between ray and mesh
     */
    rlb_RayCollision(const ::rlb_Ray& ray, const ::rlb_Mesh& mesh, const ::rlb_Matrix& transform) {
        set(::GetRayCollisionMesh(ray, mesh, transform));
    }

    /**
     * Get collision info between ray and quad
     */
    rlb_RayCollision(const ::rlb_Ray& ray, ::rlb_Vector3 p1, ::rlb_Vector3 p2, ::rlb_Vector3 p3, ::rlb_Vector3 p4) {
        set(::GetRayCollisionQuad(ray, p1, p2, p3, p4));
    }

    /**
     * Get collision info between ray and sphere
     */
    rlb_RayCollision(const ::rlb_Ray& ray, ::rlb_Vector3 center, float radius) {
        set(::GetRayCollisionSphere(ray, center, radius));
    }

    /**
     * Get collision info between ray and triangle
     */
    rlb_RayCollision(const ::rlb_Ray& ray, ::rlb_Vector3 p1, ::rlb_Vector3 p2, ::rlb_Vector3 p3) {
        set(::GetRayCollisionTriangle(ray, p1, p2, p3));
    }

    rlb_RayCollision& operator=(const ::rlb_RayCollision& ray) {
        set(ray);
        return *this;
    }

    GETTERSETTER(bool, Hit, hit)
    GETTERSETTER(float, Distance, distance)
    GETTERSETTER(::rlb_Vector3, Position, point)
    GETTERSETTER(::rlb_Vector3, Normal, normal)

 protected:
    void set(const ::rlb_RayCollision& ray) {
        hit = ray.hit;
        distance = ray.distance;
        point = ray.point;
        normal = ray.normal;
    }
};
}  // namespace raylib

using RRayCollision = raylib::rlb_RayCollision;

#endif  // RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_
