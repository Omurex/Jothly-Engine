#ifndef RAYLIB_CPP_INCLUDE_MESH_HPP_
#define RAYLIB_CPP_INCLUDE_MESH_HPP_

#include <string>
#include <vector>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./BoundingBox.hpp"
#include "./Model.hpp"

namespace raylib {
/**
 * Vertex data definning a mesh
 */
class rlb_Mesh : public ::rlb_Mesh {
 public:
    rlb_Mesh(const ::rlb_Mesh& mesh) {
        set(mesh);
    }

    /**
     * Load meshes from model file
     */
    // static std::vector<Mesh> Load(const std::string& fileName) {
    //    int count = 0;
    //    ::Mesh* meshes = LoadMeshes(fileName.c_str(), &count);
    //    return std::vector<Mesh>(meshes, meshes + count);
    // }

    rlb_Mesh(const rlb_Mesh&) = delete;

    rlb_Mesh(rlb_Mesh&& other) {
        set(other);

        other.vertexCount = 0;
        other.triangleCount = 0;
        other.vertices = nullptr;
        other.texcoords = nullptr;
        other.texcoords2 = nullptr;
        other.normals = nullptr;
        other.tangents = nullptr;
        other.colors = nullptr;
        other.indices = nullptr;
        other.animVertices = nullptr;
        other.animNormals = nullptr;
        other.boneIds = nullptr;
        other.boneWeights = nullptr;
        other.vaoId = 0;
        other.vboId = nullptr;
    }

    /**
     * Generate polygonal mesh
     */
    static ::rlb_Mesh Poly(int sides, float radius) {
        return ::GenMeshPoly(sides, radius);
    }

    /**
     * Generate plane mesh (with subdivisions)
     */
    static ::rlb_Mesh Plane(float width, float length, int resX, int resZ) {
        return ::GenMeshPlane(width, length, resX, resZ);
    }

    /**
     * Generate cuboid mesh
     */
    static ::rlb_Mesh Cube(float width, float height, float length) {
        return ::GenMeshCube(width, height, length);
    }

    /**
     * Generate sphere mesh (standard sphere)
     */
    static ::rlb_Mesh Sphere(float radius, int rings, int slices) {
        return ::GenMeshSphere(radius, rings, slices);
    }

    /**
     * Generate half-sphere mesh (no bottom cap)
     */
    static ::rlb_Mesh HemiSphere(float radius, int rings, int slices) {
        return ::GenMeshHemiSphere(radius, rings, slices);
    }

    /**
     * Generate cylinder mesh
     */
    static ::rlb_Mesh Cylinder(float radius, float height, int slices) {
        return ::GenMeshCylinder(radius, height, slices);
    }

    /**
     * Generate cone/pyramid mesh
     */
    static ::rlb_Mesh Cone(float radius, float height, int slices) {
        return ::GenMeshCone(radius, height, slices);
    }

    /**
     * Generate torus mesh
     */
    static ::rlb_Mesh Torus(float radius, float size, int radSeg, int sides) {
        return ::GenMeshTorus(radius, size, radSeg, sides);
    }

    /**
     * Generate trefoil knot mesh
     */
    static ::rlb_Mesh Knot(float radius, float size, int radSeg, int sides) {
        return ::GenMeshKnot(radius, size, radSeg, sides);
    }

    /**
     * Generate heightmap mesh from image data
     */
    static ::rlb_Mesh Heightmap(const ::rlb_Image& heightmap, ::rlb_Vector3 size) {
        return ::GenMeshHeightmap(heightmap, size);
    }

    /**
     * Generate cubes-based map mesh from image data
     */
    static ::rlb_Mesh Cubicmap(const ::rlb_Image& cubicmap, ::rlb_Vector3 cubeSize) {
        return ::GenMeshCubicmap(cubicmap, cubeSize);
    }

    GETTERSETTER(int, VertexCount, vertexCount)
    GETTERSETTER(int, TriangleCount, triangleCount)
    GETTERSETTER(float*, Vertices, vertices)
    GETTERSETTER(float *, TexCoords, texcoords)
    GETTERSETTER(float *, TexCoords2, texcoords2)
    GETTERSETTER(float *, Normals, normals)
    GETTERSETTER(float *, Tangents, tangents)
    GETTERSETTER(unsigned char *, Colors, colors)
    GETTERSETTER(unsigned short *, Indices, indices) // NOLINT
    GETTERSETTER(float *, AnimVertices, animVertices)
    GETTERSETTER(float *, AnimNormals, animNormals)
    GETTERSETTER(unsigned char *, BoneIds, boneIds)
    GETTERSETTER(float *, BoneWeights, boneWeights)
    GETTERSETTER(unsigned int, VaoId, vaoId)
    GETTERSETTER(unsigned int *, VboId, vboId)

    rlb_Mesh& operator=(const ::rlb_Mesh& mesh) {
        set(mesh);
        return *this;
    }

    rlb_Mesh& operator=(const rlb_Mesh&) = delete;

    rlb_Mesh& operator=(rlb_Mesh&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.vertexCount = 0;
        other.triangleCount = 0;
        other.vertices = nullptr;
        other.texcoords = nullptr;
        other.texcoords2 = nullptr;
        other.normals = nullptr;
        other.tangents = nullptr;
        other.colors = nullptr;
        other.indices = nullptr;
        other.animVertices = nullptr;
        other.animNormals = nullptr;
        other.boneIds = nullptr;
        other.boneWeights = nullptr;
        other.vaoId = 0;
        other.vboId = nullptr;

        return *this;
    }

    ~rlb_Mesh() {
        Unload();
    }

    /**
     * Upload mesh vertex data to GPU (VRAM)
     */
    inline void Upload(bool dynamic = false) {
        ::UploadMesh(this, dynamic);
    }

    /**
     * Upload mesh vertex data to GPU (VRAM)
     */
    inline void UpdateBuffer(int index, void *data, int dataSize, int offset = 0) {
        ::UpdateMeshBuffer(*this, index, data, dataSize, offset);
    }

    /**
     * Draw a 3d mesh with material and transform
     */
    inline void Draw(const ::rlb_Material& material, const ::rlb_Matrix& transform) const {
        ::DrawMesh(*this, material, transform);
    }

    /**
     * Draw multiple mesh instances with material and different transforms
     */
    inline void Draw(const ::rlb_Material& material, ::rlb_Matrix* transforms, int instances) const {
        ::DrawMeshInstanced(*this, material, transforms, instances);
    }

    /**
     * Export mesh data to file
     *
     * @throws raylib::RaylibException Throws if failed to export the Mesh.
     */
    inline void Export(const std::string& fileName) {
        if (!::ExportMesh(*this, fileName.c_str())) {
            throw new RaylibException("Failed to export the Mesh");
        }
    }

    /**
     * Unload mesh from memory (RAM and/or VRAM)
     */
    inline void Unload() {
        if (vboId != nullptr) {
            ::UnloadMesh(*this);
            vboId = nullptr;
        }
    }

    /**
     * Compute mesh bounding box limits
     */
    inline raylib::rlb_BoundingBox rlb_BoundingBox() const {
        return ::GetMeshBoundingBox(*this);
    }

    /**
     * Compute mesh bounding box limits
     */
    operator raylib::rlb_BoundingBox() {
        return rlb_BoundingBox();
    }

    /**
     * Compute mesh tangents
     */
    inline rlb_Mesh& GenTangents() {
        ::GenMeshTangents(this);
        return *this;
    }

    /**
     * Load model from generated mesh
     */
    inline raylib::rlb_Model LoadModelFrom() const {
        return ::LoadModelFromMesh(*this);
    }

    /**
     * Load model from generated mesh
     */
    operator raylib::rlb_Model() {
        return ::LoadModelFromMesh(*this);
    }

 protected:
    void set(const ::rlb_Mesh& mesh) {
        vertexCount = mesh.vertexCount;
        triangleCount = mesh.triangleCount;
        vertices = mesh.vertices;
        texcoords = mesh.texcoords;
        texcoords2 = mesh.texcoords2;
        normals = mesh.normals;
        tangents = mesh.tangents;
        colors = mesh.colors;
        indices = mesh.indices;
        animVertices = mesh.animVertices;
        animNormals = mesh.animNormals;
        boneIds = mesh.boneIds;
        boneWeights = mesh.boneWeights;
        vaoId = mesh.vaoId;
        vboId = mesh.vboId;
    }
};
}  // namespace raylib

using RMesh = raylib::rlb_Mesh;

#endif  // RAYLIB_CPP_INCLUDE_MESH_HPP_
