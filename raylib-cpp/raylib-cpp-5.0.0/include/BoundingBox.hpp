#ifndef RAYLIB_CPP_INCLUDE_BOUNDINGBOX_HPP_
#define RAYLIB_CPP_INCLUDE_BOUNDINGBOX_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Bounding box type
 */
class rlb_BoundingBox : public ::rlb_BoundingBox {
 public:
    /*
     * Copy a bounding box from another bounding box.
     */
    rlb_BoundingBox(const ::rlb_BoundingBox& box) : ::rlb_BoundingBox{box.min, box.max} {
        // Nothing.
    }

    /**
     * Compute mesh bounding box limits
     */
    rlb_BoundingBox(const ::rlb_Mesh& mesh) {
        set(::GetMeshBoundingBox(mesh));
    }

    rlb_BoundingBox(::rlb_Vector3 minMax = ::rlb_Vector3{0.0f, 0.0f, 0.0f}) : ::rlb_BoundingBox{minMax, minMax} {}
    rlb_BoundingBox(::rlb_Vector3 min, ::rlb_Vector3 max) : ::rlb_BoundingBox{min, max} {}

    GETTERSETTER(::rlb_Vector3, Min, min)
    GETTERSETTER(::rlb_Vector3, Max, max)

    rlb_BoundingBox& operator=(const ::rlb_BoundingBox& box) {
        set(box);
        return *this;
    }

    /**
     * Draw a bounding box with wires
     */
    inline void Draw(::rlb_Color color = {255, 255, 255, 255}) const {
        ::DrawBoundingBox(*this, color);
    }

    /**
     * Detect collision between two boxes
     */
    inline bool CheckCollision(const ::rlb_BoundingBox& box2) const {
        return CheckCollisionBoxes(*this, box2);
    }

    /**
     * Detect collision between box and sphere
     */
    inline bool CheckCollision(::rlb_Vector3 center, float radius) const {
        return CheckCollisionBoxSphere(*this, center, radius);
    }

    /**
     * Detect collision between ray and bounding box
     */
    inline bool CheckCollision(const ::rlb_Ray& ray) const {
        return GetRayCollisionBox(ray, *this).hit;
    }

    /**
     * Get collision information between ray and bounding box
     */
    inline rlb_RayCollision GetCollision(const ::rlb_Ray& ray) const {
        return GetRayCollisionBox(ray, *this);
    }

 protected:
    void set(const ::rlb_BoundingBox& box) {
        min = box.min;
        max = box.max;
    }
    void set(const ::rlb_Vector3& _min, const ::rlb_Vector3& _max) {
        min = _min;
        max = _max;
    }
};
}  // namespace raylib

using RBoundingBox = raylib::rlb_BoundingBox;

#endif  // RAYLIB_CPP_INCLUDE_BOUNDINGBOX_HPP_
