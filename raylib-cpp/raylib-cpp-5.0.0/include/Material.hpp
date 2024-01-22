#ifndef RAYLIB_CPP_INCLUDE_MATERIAL_HPP_
#define RAYLIB_CPP_INCLUDE_MATERIAL_HPP_

#include <string>
#include <vector>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Material type (generic)
 */
class rlb_Material : public ::rlb_Material {
 public:
    rlb_Material(const ::rlb_Material& material) {
        set(material);
    }

    /**
     * Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
     */
    rlb_Material() {
        set(LoadMaterialDefault());
    }

    rlb_Material(const rlb_Material&) = delete;

    rlb_Material(rlb_Material&& other) {
        set(other);

        other.maps = nullptr;
        other.shader = {};
        other.params[0] = 0.0f;
        other.params[1] = 0.0f;
        other.params[2] = 0.0f;
        other.params[3] = 0.0f;
    }

    ~rlb_Material() {
        Unload();
    }

    /**
     * Load materials from model file
     */
    static std::vector<rlb_Material> Load(const std::string& fileName) {
        int count = 0;
        // TODO(RobLoach): Material::Load() possibly leaks the materials array.
        ::rlb_Material* materials = ::LoadMaterials(fileName.c_str(), &count);
        return std::vector<rlb_Material>(materials, materials + count);
    }

    GETTERSETTER(::rlb_Shader, rlb_Shader, shader)
    GETTERSETTER(::rlb_MaterialMap*, Maps, maps)
    // TODO(RobLoach): Resolve the Material params being a float[4].
    // GETTERSETTER(float[4], Params, params)

    rlb_Material& operator=(const ::rlb_Material& material) {
        set(material);
        return *this;
    }

    rlb_Material& operator=(const rlb_Material&) = delete;

    rlb_Material& operator=(rlb_Material&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.maps = nullptr;
        other.shader = {};

        return *this;
    }

    /**
     * Unload material from memory
     */
    inline void Unload() {
        if (maps != nullptr) {
            ::UnloadMaterial(*this);
            maps = nullptr;
        }
    }

    /**
     * Set texture for a material map type (MAP_DIFFUSE, MAP_SPECULAR...)
     */
    inline rlb_Material& SetTexture(int mapType, const ::rlb_Texture2D& texture) {
        ::SetMaterialTexture(this, mapType, texture);
        return *this;
    }

    /**
     * Draw a 3d mesh with material and transform
     */
    inline void DrawMesh(const ::rlb_Mesh& mesh, ::rlb_Matrix transform) const {
        ::DrawMesh(mesh, *this, transform);
    }

    /**
     * Draw multiple mesh instances with material and different transforms
     */
    inline void DrawMesh(const ::rlb_Mesh& mesh, ::rlb_Matrix* transforms, int instances) const {
        ::DrawMeshInstanced(mesh, *this, transforms, instances);
    }

    /**
     * Check if material is ready
     */
    inline bool IsReady() const {
        return ::IsMaterialReady(*this);
    }

 protected:
    void set(const ::rlb_Material& material) {
        shader = material.shader;
        maps = material.maps;
        params[0] = material.params[0];
        params[1] = material.params[1];
        params[2] = material.params[2];
        params[3] = material.params[3];
    }
};
}  // namespace raylib

using RMaterial = raylib::rlb_Material;

#endif  // RAYLIB_CPP_INCLUDE_MATERIAL_HPP_
