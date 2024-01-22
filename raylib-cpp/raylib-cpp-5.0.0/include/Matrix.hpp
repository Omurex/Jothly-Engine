#ifndef RAYLIB_CPP_INCLUDE_MATRIX_HPP_
#define RAYLIB_CPP_INCLUDE_MATRIX_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raymath.hpp"

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#endif

namespace raylib {
/**
 * Matrix type (OpenGL style 4x4 - right handed, column major)
 */
class rlb_Matrix : public ::rlb_Matrix {
 public:
    rlb_Matrix(const ::rlb_Matrix& mat) : ::rlb_Matrix{
            mat.m0, mat.m4, mat.m8, mat.m12,
            mat.m1, mat.m5, mat.m9, mat.m13,
            mat.m2, mat.m6, mat.m10, mat.m14,
            mat.m3, mat.m7, mat.m11, mat.m15} {
        // Nothing.
    }

    rlb_Matrix(
            float m0 = 0, float m4 = 0, float m8 = 0, float m12 = 0,
            float m1 = 0, float m5 = 0, float m9 = 0, float m13 = 0,
            float m2 = 0, float m6 = 0, float m10 = 0, float m14 = 0,
            float m3 = 0, float m7 = 0, float m11 = 0, float m15 = 0) :
        ::rlb_Matrix{
            m0, m4, m8, m12,
            m1, m5, m9, m13,
            m2, m6, m10, m14,
            m3, m7, m11, m15} {
        // Nothing.
    }

    GETTERSETTER(float, M0, m0)
    GETTERSETTER(float, M1, m1)
    GETTERSETTER(float, M2, m2)
    GETTERSETTER(float, M3, m3)
    GETTERSETTER(float, M4, m4)
    GETTERSETTER(float, M5, m5)
    GETTERSETTER(float, M6, m6)
    GETTERSETTER(float, M7, m7)
    GETTERSETTER(float, M8, m8)
    GETTERSETTER(float, M9, m9)
    GETTERSETTER(float, M10, m10)
    GETTERSETTER(float, M11, m11)
    GETTERSETTER(float, M12, m12)
    GETTERSETTER(float, M13, m13)
    GETTERSETTER(float, M14, m14)
    GETTERSETTER(float, M15, m15)

    rlb_Matrix& operator=(const ::rlb_Matrix& matrix) {
        set(matrix);
        return *this;
    }

    rlb_Matrix& operator=(const rlb_Matrix& matrix) {
        set(matrix);
        return *this;
    }

    bool operator==(const ::rlb_Matrix& other) {
        return m0 == other.m0
            && m1 == other.m1
            && m2 == other.m2
            && m3 == other.m3
            && m4 == other.m4
            && m5 == other.m5
            && m6 == other.m6
            && m7 == other.m7
            && m8 == other.m8
            && m9 == other.m9
            && m10 == other.m10
            && m11 == other.m11
            && m12 == other.m12
            && m13 == other.m13
            && m14 == other.m14
            && m15 == other.m15;
    }

    bool operator!=(const ::rlb_Matrix& other) {
        return !(*this == other);
    }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * Returns the trace of the matrix (sum of the values along the diagonal)
     */
    inline float Trace() const {
        return ::MatrixTrace(*this);
    }

    /**
     * Transposes provided matrix
     */
    inline rlb_Matrix Transpose() const {
        return ::MatrixTranspose(*this);
    }

    inline rlb_Matrix Invert() const {
        return ::MatrixInvert(*this);
    }

    static rlb_Matrix Identity() {
        return ::MatrixIdentity();
    }

    rlb_Matrix Add(const ::rlb_Matrix& right) {
        return ::MatrixAdd(*this, right);
    }

    rlb_Matrix operator+(const ::rlb_Matrix& matrix) {
            return ::MatrixAdd(*this, matrix);
    }

    rlb_Matrix Subtract(const ::rlb_Matrix& right) {
        return ::MatrixSubtract(*this, right);
    }

    rlb_Matrix operator-(const ::rlb_Matrix& matrix) {
        return ::MatrixSubtract(*this, matrix);
    }

    static rlb_Matrix Translate(float x, float y, float z) {
        return ::MatrixTranslate(x, y, z);
    }

    static rlb_Matrix Rotate(rlb_Vector3 axis, float angle) {
        return ::MatrixRotate(axis, angle);
    }

    static rlb_Matrix RotateXYZ(rlb_Vector3 angle) {
        return ::MatrixRotateXYZ(angle);
    }

    static rlb_Matrix RotateX(float angle) {
        return ::MatrixRotateX(angle);
    }

    static rlb_Matrix RotateY(float angle) {
        return ::MatrixRotateY(angle);
    }

    static rlb_Matrix RotateZ(float angle) {
        return ::MatrixRotateZ(angle);
    }

    static rlb_Matrix Scale(float x, float y, float z) {
        return ::MatrixScale(x, y, z);
    }

    rlb_Matrix Multiply(const ::rlb_Matrix& right) const {
        return ::MatrixMultiply(*this, right);
    }

    rlb_Matrix operator*(const ::rlb_Matrix& matrix) {
        return ::MatrixMultiply(*this, matrix);
    }

    static rlb_Matrix Frustum(double left, double right, double bottom, double top,
            double near, double far) {
        return ::MatrixFrustum(left, right, bottom, top, near, far);
    }

    static rlb_Matrix Perspective(double fovy, double aspect, double near, double far) {
        return ::MatrixPerspective(fovy, aspect, near, far);
    }

    static rlb_Matrix Ortho(double left, double right, double bottom, double top,
            double near, double far) {
        return ::MatrixOrtho(left, right, bottom, top, near, far);
    }

    static rlb_Matrix LookAt(rlb_Vector3 eye, rlb_Vector3 target, rlb_Vector3 up) {
        return ::MatrixLookAt(eye, target, up);
    }

    inline float16 ToFloatV() const {
        return ::MatrixToFloatV(*this);
    }

    operator float16() {
        return ToFloatV();
    }

    /**
     * Set shader uniform value (matrix 4x4)
     */
    inline rlb_Matrix& SetShaderValue(const ::rlb_Shader& shader, int uniformLoc) {
        ::SetShaderValueMatrix(shader, uniformLoc, *this);
        return *this;
    }

    inline static rlb_Matrix GetCamera(const ::rlb_Camera& camera) {
        return ::GetCameraMatrix(camera);
    }

    inline static rlb_Matrix GetCamera(const ::rlb_Camera2D& camera) {
        return ::GetCameraMatrix2D(camera);
    }

#endif

 protected:
    void set(const ::rlb_Matrix& mat) {
        m0 = mat.m0;
        m1 = mat.m1;
        m2 = mat.m2;
        m3 = mat.m3;
        m4 = mat.m4;
        m5 = mat.m5;
        m6 = mat.m6;
        m7 = mat.m7;
        m8 = mat.m8;
        m9 = mat.m9;
        m10 = mat.m10;
        m11 = mat.m11;
        m12 = mat.m12;
        m13 = mat.m13;
        m14 = mat.m14;
        m15 = mat.m15;
    }
};
}  // namespace raylib

using RMatrix = raylib::rlb_Matrix;

#endif  // RAYLIB_CPP_INCLUDE_MATRIX_HPP_
