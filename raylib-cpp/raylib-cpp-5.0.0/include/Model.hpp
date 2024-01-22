#ifndef RAYLIB_CPP_INCLUDE_MODEL_HPP_
#define RAYLIB_CPP_INCLUDE_MODEL_HPP_

#include <string>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./RaylibException.hpp"

namespace raylib {
class rlb_Mesh;
/**
 * Model type
 */
class rlb_Model : public ::rlb_Model {
 public:
    rlb_Model() {
        // Nothing.
    }

    /*
     * Copy a model from another model.
     */
    rlb_Model(const ::rlb_Model& model) {
        set(model);
    }

    /*
     * Load a model from a file.
     *
     * @throws raylib::RaylibException Throws if failed to load the Modal.
     */
    rlb_Model(const std::string& fileName) {
        Load(fileName);
    }

    /*
     * Load a model from a mesh.
     *
     * @throws raylib::RaylibException Throws if failed to load the Modal.
     */
    rlb_Model(const ::rlb_Mesh& mesh) {
        Load(mesh);
    }

    ~rlb_Model() {
        Unload();
    }

    rlb_Model(const rlb_Model&) = delete;

    rlb_Model(rlb_Model&& other) {
        set(other);

        other.meshCount = 0;
        other.materialCount = 0;
        other.meshes = nullptr;
        other.materials = nullptr;
        other.meshMaterial = nullptr;
        other.boneCount = 0;
        other.bones = nullptr;
        other.bindPose = nullptr;
    }

    GETTERSETTER(::rlb_Matrix, rlb_Transform, transform)
    GETTERSETTER(int, MeshCount, meshCount)
    GETTERSETTER(int, MaterialCount, materialCount)
    GETTERSETTER(::rlb_Mesh*, Meshes, meshes)
    GETTERSETTER(::rlb_Material*, Materials, materials)
    GETTERSETTER(int*, MeshMaterial, meshMaterial)
    GETTERSETTER(int, BoneCount, boneCount)
    GETTERSETTER(::rlb_BoneInfo*, Bones, bones)
    GETTERSETTER(::rlb_Transform*, BindPose, bindPose)

    rlb_Model& operator=(const ::rlb_Model& model) {
        set(model);
        return *this;
    }

    rlb_Model& operator=(const rlb_Model&) = delete;

    rlb_Model& operator=(rlb_Model&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.meshCount = 0;
        other.materialCount = 0;
        other.meshes = nullptr;
        other.materials = nullptr;
        other.meshMaterial = nullptr;
        other.boneCount = 0;
        other.bones = nullptr;
        other.bindPose = nullptr;

        return *this;
    }

    /**
     * Unload model (including meshes) from memory (RAM and/or VRAM)
     */
    inline void Unload() {
        if (meshes != nullptr || materials != nullptr) {
            ::UnloadModel(*this);
            meshes = nullptr;
            materials = nullptr;
        }
    }

    /**
     * Set material for a mesh
     */
    inline rlb_Model& SetMeshMaterial(int meshId, int materialId) {
        ::SetModelMeshMaterial(this, meshId, materialId);
        return *this;
    }

    /**
     * Update model animation pose
     */
    inline rlb_Model& UpdateAnimation(const ::rlb_ModelAnimation& anim, int frame) {
        ::UpdateModelAnimation(*this, anim, frame);
        return *this;
    }

    /**
     * Check model animation skeleton match
     */
    inline bool IsModelAnimationValid(const ::rlb_ModelAnimation& anim) const {
        return ::IsModelAnimationValid(*this, anim);
    }

    /**
     * Draw a model (with texture if set)
     */
    inline void Draw(::rlb_Vector3 position,
            float scale = 1.0f,
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawModel(*this, position, scale, tint);
    }

    /**
     * Draw a model with extended parameters
     */
    inline void Draw(
            ::rlb_Vector3 position,
            ::rlb_Vector3 rotationAxis,
            float rotationAngle = 0.0f,
            ::rlb_Vector3 scale = {1.0f, 1.0f, 1.0f},
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawModelEx(*this, position, rotationAxis, rotationAngle, scale, tint);
    }

    /**
     * Draw a model wires (with texture if set)
     */
    inline void DrawWires(::rlb_Vector3 position,
            float scale = 1.0f,
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawModelWires(*this, position, scale, tint);
    }

    /**
     * Draw a model wires (with texture if set) with extended parameters
     */
    inline void DrawWires(
            ::rlb_Vector3 position,
            ::rlb_Vector3 rotationAxis,
            float rotationAngle = 0.0f,
            ::rlb_Vector3 scale = {1.0f, 1.0f, 1.0f},
            ::rlb_Color tint = {255, 255, 255, 255}) const {
        ::DrawModelWiresEx(*this, position, rotationAxis, rotationAngle, scale, tint);
    }

    /**
     * Compute model bounding box limits (considers all meshes)
     */
    inline rlb_BoundingBox GetBoundingBox() const {
        return ::GetModelBoundingBox(*this);
    }

    /**
     * Compute model bounding box limits (considers all meshes)
     */
    operator rlb_BoundingBox() const {
        return ::GetModelBoundingBox(*this);
    }

    /**
     * Determines whether or not the Model has data in it.
     */
    bool IsReady() const {
        return ::IsModelReady(*this);
    }

    /**
     * Loads a Model from the given file.
     *
     * @throws raylib::RaylibException Throws if failed to load the Modal.
     */
    void Load(const std::string& fileName) {
        set(::LoadModel(fileName.c_str()));
        if (!IsReady()) {
            throw RaylibException("Failed to load Model from " + fileName);
        }
    }

    /**
     * Loads a Model from the given Mesh.
     *
     * @throws raylib::RaylibException Throws if failed to load the Modal.
     */
    void Load(const ::rlb_Mesh& mesh) {
        set(::LoadModelFromMesh(mesh));
        if (!IsReady()) {
            throw RaylibException("Failed to load Model from Mesh");
        }
    }

 protected:
    void set(const ::rlb_Model& model) {
        transform = model.transform;

        meshCount = model.meshCount;
        materialCount = model.materialCount;
        meshes = model.meshes;
        materials = model.materials;
        meshMaterial = model.meshMaterial;

        boneCount = model.boneCount;
        bones = model.bones;
        bindPose = model.bindPose;
    }
};

}  // namespace raylib

using RModel = raylib::rlb_Model;

#endif  // RAYLIB_CPP_INCLUDE_MODEL_HPP_
