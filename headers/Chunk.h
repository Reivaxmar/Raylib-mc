#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <array>
#include <vector>
#include <atomic>
#include "Utils.h"
#include "BlockLoader.h"

#include <raymath.h>

constexpr Vector3i CH_SIZE = { 16, 32, 16 };

inline Vector3i getChunk(Vector3 world) {
    return {
        floorDiv(world.x, CH_SIZE.x),
        floorDiv(world.y, CH_SIZE.y),
        floorDiv(world.z, CH_SIZE.z)
    };
}

inline Vector3i worldToChunk(Vector3i world) {
    return world - getChunk(world)*CH_SIZE;
}

class ChunkManager;

class Chunk {
public:

    Chunk(ChunkManager* _chman, Vector3i chunk_pos);
    ~Chunk();

    void Draw();

    void SetBlock(Vector3i pos, BlockID block);

    BlockID GetBlock(Vector3i pos) const;

    void GenerateTerrain();

    enum class State : int8_t { EMPTY, GENERATED, MESHED, UPLOADED };
    State GetState() const;

    // void TryUpdateMesh();
    void GenerateMesh();
    void TryUploadMesh();

private:

    std::array<BlockID, CH_SIZE.x * CH_SIZE.y * CH_SIZE.z> m_data;

    Vector3i m_chunk_pos;

    bool m_upd_mesh;

    MeshData m_opaque_data, m_transparent_data, m_cutout_data;
    Mesh m_opaque_mesh, m_cutout_mesh, m_transparent_mesh;
    Material m_mat;

    std::atomic<State> m_state;

    Matrix m_matrix;

    void generate_mesh();
    void upload_mesh();

    ChunkManager* chman;

    // [0, 1, 2, 3, 4, 5] => [Top, Bottom, Right, Left, Front, Back]
    void add_face(int face, Vector3 pos, unsigned int faceID, MeshData& data);

};

#endif // CHUNK_CLASS_H