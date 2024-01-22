#ifndef RAYLIB_CPP_INCLUDE_VECTOR4_HPP_
#define RAYLIB_CPP_INCLUDE_VECTOR4_HPP_

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#include <utility>
#endif

#include <string>

#include "./raylib.hpp"
#include "./raymath.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Vector4 type
 */
class rlb_Vector4 : public ::rlb_Vector4 {
 public:
    rlb_Vector4(const ::rlb_Vector4& vec) : ::rlb_Vector4{vec.x, vec.y, vec.z, vec.w} {}

    rlb_Vector4(float x, float y, float z, float w) : ::rlb_Vector4{x, y, z, w} {}
    rlb_Vector4(float x, float y, float z) : ::rlb_Vector4{x, y, z, 0} {}
    rlb_Vector4(float x, float y) : ::rlb_Vector4{x, y, 0, 0} {}
    rlb_Vector4(float x) : ::rlb_Vector4{x, 0, 0, 0} {}
    rlb_Vector4() : ::rlb_Vector4{0, 0, 0, 0} {}
    rlb_Vector4(::rlb_Rectangle rectangle) : ::rlb_Vector4{rectangle.x, rectangle.y, rectangle.width, rectangle.height} {}

    rlb_Vector4(::rlb_Color color) {
        set(ColorNormalize(color));
    }

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Z, z)
    GETTERSETTER(float, W, w)

    rlb_Vector4& operator=(const ::rlb_Vector4& vector4) {
        set(vector4);
        return *this;
    }

    bool operator==(const ::rlb_Vector4& other) const {
        return x == other.x
            && y == other.y
            && z == other.z
            && w == other.w;
    }

    bool operator!=(const ::rlb_Vector4& other) const {
        return !(*this == other);
    }

    inline ::rlb_Rectangle ToRectangle() const {
        return {x, y, z, w};
    }

    operator ::rlb_Rectangle() const {
        return {x, y, z, w};
    }

    inline std::string ToString() const {
        return TextFormat("Vector4(%f, %f, %f, %f)", x, y, z, w);
    }

    inline operator std::string() const {
        return ToString();
    }

#ifndef RAYLIB_CPP_NO_MATH
    inline rlb_Vector4 Multiply(const ::rlb_Vector4& vector4) const {
        return QuaternionMultiply(*this, vector4);
    }

    inline rlb_Vector4 operator*(const ::rlb_Vector4& vector4) const {
        return QuaternionMultiply(*this, vector4);
    }

    inline rlb_Vector4 Lerp(const ::rlb_Vector4& vector4, float amount) const {
        return QuaternionLerp(*this, vector4, amount);
    }

    inline rlb_Vector4 Nlerp(const ::rlb_Vector4& vector4, float amount) const {
        return QuaternionNlerp(*this, vector4, amount);
    }

    inline rlb_Vector4 Slerp(const ::rlb_Vector4& vector4, float amount) const {
        return QuaternionSlerp(*this, vector4, amount);
    }

    inline rlb_Matrix ToMatrix() const {
        return QuaternionToMatrix(*this);
    }

    inline float Length() const {
        return QuaternionLength(*this);
    }

    inline rlb_Vector4 Normalize() const {
        return QuaternionNormalize(*this);
    }

    inline rlb_Vector4 Invert() const {
        return QuaternionInvert(*this);
    }

    inline void ToAxisAngle(::rlb_Vector3 *outAxis, float *outAngle) const {
        QuaternionToAxisAngle(*this, outAxis, outAngle);
    }

    /**
     * Get the rotation angle and axis for a given quaternion
     */
    std::pair<rlb_Vector3, float> ToAxisAngle() const {
        rlb_Vector3 outAxis;
        float outAngle;
        QuaternionToAxisAngle(*this, &outAxis, &outAngle);

        return std::pair<rlb_Vector3, float>(outAxis, outAngle);
    }

    inline rlb_Vector4 rlb_Transform(const ::rlb_Matrix& matrix) const {
        return ::QuaternionTransform(*this, matrix);
    }

    static inline rlb_Vector4 Identity() {
        return ::QuaternionIdentity();
    }

    static inline rlb_Vector4 FromVector3ToVector3(const ::rlb_Vector3& from , const ::rlb_Vector3& to) {
        return ::QuaternionFromVector3ToVector3(from , to);
    }

    static inline rlb_Vector4 FromMatrix(const ::rlb_Matrix& matrix) {
        return ::QuaternionFromMatrix(matrix);
    }

    static inline rlb_Vector4 FromAxisAngle(const ::rlb_Vector3& axis, const float angle) {
        return ::QuaternionFromAxisAngle(axis, angle);
    }

    static inline rlb_Vector4 FromEuler(const float pitch, const float yaw, const float roll) {
        return ::QuaternionFromEuler(pitch, yaw, roll);
    }

    static inline rlb_Vector4 FromEuler(const ::rlb_Vector3& vector3) {
        return ::QuaternionFromEuler(vector3.x, vector3.y, vector3.z);
    }

    inline rlb_Vector3 ToEuler() const {
        return ::QuaternionToEuler(*this);
    }
#endif

    inline rlb_Color ColorFromNormalized() const {
        return ::ColorFromNormalized(*this);
    }

    operator rlb_Color() const {
        return ColorFromNormalized();
    }

 protected:
    void set(const ::rlb_Vector4& vec4) {
        x = vec4.x;
        y = vec4.y;
        z = vec4.z;
        w = vec4.w;
    }
};

// Alias the Vector4 as Quaternion.
typedef rlb_Vector4 rlb_Quaternion;
}  // namespace raylib

using RVector4 = raylib::rlb_Vector4;
using RQuaternion = raylib::rlb_Quaternion;

#endif  // RAYLIB_CPP_INCLUDE_VECTOR4_HPP_
