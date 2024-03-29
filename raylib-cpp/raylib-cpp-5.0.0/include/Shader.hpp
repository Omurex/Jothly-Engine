#ifndef RAYLIB_CPP_INCLUDE_SHADER_HPP_
#define RAYLIB_CPP_INCLUDE_SHADER_HPP_

#include <string>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "Texture.hpp"

namespace raylib {
/**
 * Shader type (generic)
 */
class rlb_Shader : public ::rlb_Shader {
 public:
    rlb_Shader(const ::rlb_Shader& shader) {
        set(shader);
    }

    rlb_Shader(unsigned int id, int* locs = nullptr) : ::rlb_Shader{id, locs} {}

    rlb_Shader(const std::string& vsFileName, const std::string& fsFileName) {
        set(::LoadShader(vsFileName.c_str(), fsFileName.c_str()));
    }

    rlb_Shader(const char* vsFileName, const char* fsFileName) {
        set(::LoadShader(vsFileName, fsFileName));
    }

    rlb_Shader(const rlb_Shader&) = delete;

    rlb_Shader(rlb_Shader&& other) {
        set(other);

        other.id = 0;
        other.locs = nullptr;
    }

    /**
     * Load shader from files and bind default locations.
     *
     * @see ::LoadShader
     */
    static ::rlb_Shader Load(const std::string& vsFileName, const std::string& fsFileName) {
        return ::LoadShader(vsFileName.c_str(), fsFileName.c_str());
    }

    static ::rlb_Shader Load(const char* vsFileName, const char* fsFileName) {
        return ::LoadShader(vsFileName, fsFileName);
    }

    /**
     * Load a shader from memory.
     *
     * @see ::LoadShaderFromMemory
     */
    static ::rlb_Shader LoadFromMemory(const std::string& vsCode, const std::string& fsCode) {
        return ::LoadShaderFromMemory(vsCode.c_str(), fsCode.c_str());
    }

    static ::rlb_Shader LoadFromMemory(const char* vsCode, const char* fsCode) {
        return ::LoadShaderFromMemory(vsCode, fsCode);
    }

    GETTERSETTER(unsigned int, Id, id)
    GETTERSETTER(int*, Locs, locs)

    rlb_Shader& operator=(const ::rlb_Shader& shader) {
        set(shader);
        return *this;
    }

    rlb_Shader& operator=(const rlb_Shader&) = delete;

    rlb_Shader& operator=(rlb_Shader&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.id = 0;
        other.locs = nullptr;

        return *this;
    }

    /**
     * Unload shader from GPU memory (VRAM)
     */
    ~rlb_Shader() {
        Unload();
    }

    /**
     * Unload shader from GPU memory (VRAM)
     */
    void Unload() {
        if (locs != nullptr) {
            ::UnloadShader(*this);
        }
    }

    /**
     * Begin custom shader drawing.
     */
    inline rlb_Shader& BeginMode() {
        ::BeginShaderMode(*this);
        return *this;
    }

    /**
     * End custom shader drawing (use default shader).
     */
    inline rlb_Shader& EndMode() {
        ::EndShaderMode();
        return *this;
    }

    /**
     * Get shader uniform location
     *
     * @see GetShaderLocation()
     */
    inline int GetLocation(const std::string& uniformName) const {
        return ::GetShaderLocation(*this, uniformName.c_str());
    }

    /**
     * Get shader attribute location
     *
     * @see GetShaderLocationAttrib()
     */
    inline int GetLocationAttrib(const std::string& attribName) const {
        return ::GetShaderLocationAttrib(*this, attribName.c_str());
    }

    /**
     * Set shader uniform value
     *
     * @see SetShaderValue()
     */
    inline rlb_Shader& SetValue(int uniformLoc, const void* value, int uniformType) {
        ::SetShaderValue(*this, uniformLoc, value, uniformType);
        return *this;
    }

    /**
     * Set shader uniform value vector
     *
     * @see SetShaderValueV()
     */
    inline rlb_Shader& SetValue(int uniformLoc, const void* value, int uniformType, int count) {
        ::SetShaderValueV(*this, uniformLoc, value, uniformType, count);
        return *this;
    }

    /**
     * Set shader uniform value (matrix 4x4)
     *
     * @see SetShaderValueMatrix()
     */
    inline rlb_Shader& SetValue(int uniformLoc, const ::rlb_Matrix& mat) {
        ::SetShaderValueMatrix(*this, uniformLoc, mat);
        return *this;
    }

    /**
     * Set shader uniform value for texture
     *
     * @see SetShaderValueTexture()
     */
    inline rlb_Shader& SetValue(int uniformLoc, const ::rlb_Texture2D& texture) {
        ::SetShaderValueTexture(*this, uniformLoc, texture);
        return *this;
    }

    /**
     * Retrieves whether or not the shader is ready.
     */
    bool IsReady() const {
        return id != 0 && locs != nullptr;
    }

 protected:
    void set(const ::rlb_Shader& shader) {
        id = shader.id;
        locs = shader.locs;
    }
};
}  // namespace raylib

using RShader = raylib::rlb_Shader;

#endif  // RAYLIB_CPP_INCLUDE_SHADER_HPP_
