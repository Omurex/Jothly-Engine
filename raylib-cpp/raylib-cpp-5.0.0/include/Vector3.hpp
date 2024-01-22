#ifndef RAYLIB_CPP_INCLUDE_VECTOR3_HPP_
#define RAYLIB_CPP_INCLUDE_VECTOR3_HPP_

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#endif

#include <string>

#include "./raylib.hpp"
#include "./raymath.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Vector3 type
 */
class rlb_Vector3 : public ::rlb_Vector3 {
 public:
    rlb_Vector3(const ::rlb_Vector3& vec) : ::rlb_Vector3{vec.x, vec.y, vec.z} {}

    rlb_Vector3(float x, float y, float z) : ::rlb_Vector3{x, y, z} {}
    rlb_Vector3(float x, float y) : ::rlb_Vector3{x, y, 0} {}
    rlb_Vector3(float x) : ::rlb_Vector3{x, 0, 0} {}
    rlb_Vector3() {}

    rlb_Vector3(::rlb_Color color) {
        set(ColorToHSV(color));
    }

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Z, z)

    rlb_Vector3& operator=(const ::rlb_Vector3& vector3) {
        set(vector3);
        return *this;
    }

    bool operator==(const ::rlb_Vector3& other) const {
        return x == other.x
            && y == other.y
            && z == other.z;
    }

    bool operator!=(const ::rlb_Vector3& other) const {
        return !(*this == other);
    }

    inline std::string ToString() const {
        return TextFormat("Vector3(%f, %f, %f)", x, y, z);
    }

    inline operator std::string() const {
        return ToString();
    }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * Add two vectors
     */
    inline rlb_Vector3 Add(const ::rlb_Vector3& vector3) const {
        return Vector3Add(*this, vector3);
    }

    /**
     * Add two vectors
     */
    inline rlb_Vector3 operator+(const ::rlb_Vector3& vector3) const {
        return Vector3Add(*this, vector3);
    }

    rlb_Vector3& operator+=(const ::rlb_Vector3& vector3) {
        set(Vector3Add(*this, vector3));

        return *this;
    }

    /**
     * Subtract two vectors.
     */
    inline rlb_Vector3 Subtract(const ::rlb_Vector3& vector3) const {
        return Vector3Subtract(*this, vector3);
    }

    /**
     * Subtract two vectors.
     */
    inline rlb_Vector3 operator-(const ::rlb_Vector3& vector3) const {
        return Vector3Subtract(*this, vector3);
    }

    rlb_Vector3& operator-=(const ::rlb_Vector3& vector3) {
        set(Vector3Subtract(*this, vector3));

        return *this;
    }

    /**
     * Negate provided vector (invert direction)
     */
    inline rlb_Vector3 Negate() const {
        return Vector3Negate(*this);
    }

    /**
     * Negate provided vector (invert direction)
     */
    inline rlb_Vector3 operator-() const {
        return Vector3Negate(*this);
    }

    /**
     * Multiply vector by vector
     */
    inline rlb_Vector3 Multiply(const ::rlb_Vector3& vector3) const {
        return Vector3Multiply(*this, vector3);
    }

    /**
     * Multiply vector by vector
     */
    inline rlb_Vector3 operator*(const ::rlb_Vector3& vector3) const {
        return Vector3Multiply(*this, vector3);
    }

    /**
     * Multiply vector by vector
     */
    rlb_Vector3& operator*=(const ::rlb_Vector3& vector3) {
        set(Vector3Multiply(*this, vector3));

        return *this;
    }

    /**
     * Multiply vector by scalar
     */
    inline rlb_Vector3 Scale(const float scaler) const {
        return Vector3Scale(*this, scaler);
    }

    /**
     * Multiply vector by scalar
     */
    inline rlb_Vector3 operator*(const float scaler) const {
        return Vector3Scale(*this, scaler);
    }

    /**
     * Multiply vector by scalar
     */
    rlb_Vector3& operator*=(const float scaler) {
        set(Vector3Scale(*this, scaler));

        return *this;
    }

    /**
     * Divide vector by vector
     */
    inline rlb_Vector3 Divide(const ::rlb_Vector3& vector3) const {
        return Vector3Divide(*this, vector3);
    }

    /**
     * Divide vector by vector
     */
    inline rlb_Vector3 operator/(const ::rlb_Vector3& vector3) const {
        return Vector3Divide(*this, vector3);
    }

    /**
     * Divide vector by vector
     */
    rlb_Vector3& operator/=(const ::rlb_Vector3& vector3) {
        x /= vector3.x;
        y /= vector3.y;
        z /= vector3.z;

        return *this;
    }

    /**
     * Divide a vector by a value.
     */
    inline rlb_Vector3 Divide(const float div) const {
        return ::rlb_Vector3{x / div, y / div, z / div};
    }

    /**
     * Divide a vector by a value.
     */
    inline rlb_Vector3 operator/(const float div) const {
        return Divide(div);
    }

    /**
     * Divide a vector by a value.
     */
    rlb_Vector3& operator/=(const float div) {
        x /= div;
        y /= div;
        z /= div;

        return *this;
    }

    /**
     * Calculate vector length
     */
    inline float Length() const {
        return Vector3Length(*this);
    }

    inline rlb_Vector3 Normalize() const {
        return Vector3Normalize(*this);
    }

    inline float DotProduct(const ::rlb_Vector3& vector3) const {
        return Vector3DotProduct(*this, vector3);
    }

    inline float Distance(const ::rlb_Vector3& vector3) const {
        return Vector3Distance(*this, vector3);
    }

    inline rlb_Vector3 Lerp(const ::rlb_Vector3& vector3, const float amount) const {
        return Vector3Lerp(*this, vector3, amount);
    }

    inline rlb_Vector3 CrossProduct(const ::rlb_Vector3& vector3) const {
        return Vector3CrossProduct(*this, vector3);
    }

    inline rlb_Vector3 Perpendicular() const {
        return Vector3Perpendicular(*this);
    }

    inline void OrthoNormalize(::rlb_Vector3* vector3) {
        Vector3OrthoNormalize(this, vector3);
    }

    inline rlb_Vector3 rlb_Transform(const ::rlb_Matrix& matrix) const {
        return Vector3Transform(*this, matrix);
    }

    inline rlb_Vector3 RotateByQuaternion(const ::rlb_Quaternion& quaternion) const {
        return Vector3RotateByQuaternion(*this, quaternion);
    }

    inline rlb_Vector3 Reflect(const ::rlb_Vector3& normal) const {
        return Vector3Reflect(*this, normal);
    }

    inline rlb_Vector3 Min(const ::rlb_Vector3& vector3) const {
        return Vector3Min(*this, vector3);
    }

    inline rlb_Vector3 Max(const ::rlb_Vector3& vector3) const {
        return Vector3Max(*this, vector3);
    }

    inline rlb_Vector3 Barycenter(const ::rlb_Vector3& a, const ::rlb_Vector3& b, const ::rlb_Vector3& c) const {
        return Vector3Barycenter(*this, a, b, c);
    }

    static inline rlb_Vector3 Zero() {
        return Vector3Zero();
    }

    static inline rlb_Vector3 One() {
        return Vector3One();
    }
#endif

    inline void DrawLine3D(const ::rlb_Vector3& endPos, ::rlb_Color color) const {
        ::DrawLine3D(*this, endPos, color);
    }

    inline void DrawPoint3D(::rlb_Color color) const {
        ::DrawPoint3D(*this, color);
    }

    inline void DrawCircle3D(
            float radius,
            const ::rlb_Vector3& rotationAxis,
            float rotationAngle,
            rlb_Color color) const {
        ::DrawCircle3D(*this, radius, rotationAxis, rotationAngle, color);
    }

    inline void DrawCube(float width, float height, float length, ::rlb_Color color) const {
        ::DrawCube(*this, width, height, length, color);
    }

    inline void DrawCube(const ::rlb_Vector3& size, ::rlb_Color color) const {
        ::DrawCubeV(*this, size, color);
    }

    inline void DrawCubeWires(float width, float height, float length, ::rlb_Color color) const {
        ::DrawCubeWires(*this, width, height, length, color);
    }

    inline void DrawCubeWires(const ::rlb_Vector3& size, ::rlb_Color color) const {
        ::DrawCubeWiresV(*this, size, color);
    }

    inline void DrawSphere(float radius, ::rlb_Color color) const {
        ::DrawSphere(*this, radius, color);
    }

    inline void DrawSphere(float radius, int rings, int slices, ::rlb_Color color) const {
        ::DrawSphereEx(*this, radius, rings, slices, color);
    }

    inline void DrawSphereWires(float radius, int rings, int slices, ::rlb_Color color) const {
        ::DrawSphereWires(*this, radius, rings, slices, color);
    }

    inline void DrawCylinder(float radiusTop, float radiusBottom, float height,
            int slices, ::rlb_Color color) const {
        ::DrawCylinder(*this, radiusTop, radiusBottom, height, slices, color);
    }

    inline void DrawCylinderWires(float radiusTop, float radiusBottom, float height,
            int slices, ::rlb_Color color) const {
        ::DrawCylinderWires(*this, radiusTop, radiusBottom, height, slices, color);
    }

    inline void DrawPlane(const ::rlb_Vector2& size, ::rlb_Color color) const {
        ::DrawPlane(*this, size, color);
    }

    /**
     * Detect collision between two spheres
     */
    inline bool CheckCollision(float radius1, const ::rlb_Vector3& center2, float radius2) const {
        return CheckCollisionSpheres(*this, radius1, center2, radius2);
    }

 protected:
    void set(const ::rlb_Vector3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
};
}  // namespace raylib

using RVector3 = raylib::rlb_Vector3;

#endif  // RAYLIB_CPP_INCLUDE_VECTOR3_HPP_
