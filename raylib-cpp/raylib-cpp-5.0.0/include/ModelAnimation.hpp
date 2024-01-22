#ifndef RAYLIB_CPP_INCLUDE_MODELANIMATION_HPP_
#define RAYLIB_CPP_INCLUDE_MODELANIMATION_HPP_

#include <vector>
#include <string>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./Mesh.hpp"

namespace raylib {
/**
 * Model animation
 */
class rlb_ModelAnimation : public ::rlb_ModelAnimation {
 public:
    rlb_ModelAnimation(const ::rlb_ModelAnimation& model) {
        set(model);
    }

    rlb_ModelAnimation(const rlb_ModelAnimation&) = delete;

    rlb_ModelAnimation(rlb_ModelAnimation&& other) {
        set(other);

        other.boneCount = 0;
        other.frameCount = 0;
        other.bones = nullptr;
        other.framePoses = nullptr;
    }

    ~rlb_ModelAnimation() {
        Unload();
    }

    /**
     * Load model animations from file
     */
    static std::vector<rlb_ModelAnimation> Load(const std::string& fileName) {
        int count = 0;
        ::rlb_ModelAnimation* modelAnimations = ::LoadModelAnimations(fileName.c_str(), &count);
        std::vector<rlb_ModelAnimation> mats(modelAnimations, modelAnimations + count);

        RL_FREE(modelAnimations);

        return mats;
    }

    GETTERSETTER(int, BoneCount, boneCount)
    GETTERSETTER(::rlb_BoneInfo*, Bones, bones)
    GETTERSETTER(int, FrameCount, frameCount)
    GETTERSETTER(::rlb_Transform**, FramePoses, framePoses)

    rlb_ModelAnimation& operator=(const ::rlb_ModelAnimation& model) {
        set(model);
        return *this;
    }

    rlb_ModelAnimation& operator=(const rlb_ModelAnimation&) = delete;

    rlb_ModelAnimation& operator=(rlb_ModelAnimation&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.boneCount = 0;
        other.frameCount = 0;
        other.bones = nullptr;
        other.framePoses = nullptr;

        return *this;
    }

    /**
     * Unload animation data
     */
    inline void Unload() {
        ::UnloadModelAnimation(*this);
    }

    /**
     * Update model animation pose
     */
    inline rlb_ModelAnimation& Update(const ::rlb_Model& model, int frame) {
        ::UpdateModelAnimation(model, *this, frame);
        return *this;
    }

    /**
     * Check model animation skeleton match
     */
    inline bool IsValid(const ::rlb_Model& model) const {
        return ::IsModelAnimationValid(model, *this);
    }

 protected:
    void set(const ::rlb_ModelAnimation& model) {
        boneCount = model.boneCount;
        frameCount = model.frameCount;
        bones = model.bones;
        framePoses = model.framePoses;
    }
};
}  // namespace raylib

using RModelAnimation = raylib::rlb_ModelAnimation;

#endif  // RAYLIB_CPP_INCLUDE_MODELANIMATION_HPP_
