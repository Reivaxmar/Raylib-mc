#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <array>
#include <vector>
#include "Utils.h"
#include "Block.h"

#include <raymath.h>

constexpr Vector3i CH_SIZE = { 16, 32, 16 };

inline Vector3i getChunk(Vector3i world) {
    return Vector3i(world.x / CH_SIZE.x, world.y / CH_SIZE.y, world.z / CH_SIZE.z);
}

inline Vector3i worldToChunk(Vector3i world) {
    return world - getChunk(world);
}

class Chunk {
public:

    Chunk(Vector3i chunk_pos);

    void Draw();

    void SetBlock(Vector3i pos, BlockID block);

    BlockID GetBlock(Vector3i pos) const;

    void GenerateTerrain(int seed);

private:

    std::array<BlockID, CH_SIZE.x * CH_SIZE.y * CH_SIZE.z> m_data;

    Vector3i m_chunk_pos;

    bool m_upd_mesh;

    Mesh m_opaque_mesh, m_cutout_mesh, m_transparent_mesh;
    Material m_mat;

    Matrix m_matrix;

    void update_mesh();

    // [0, 1, 2, 3, 4, 5] => [Top, Bottom, Right, Left, Front, Back]
    void add_face(int face, Vector3 pos, unsigned int faceID, MeshData& data);

};

#endif // CHUNK_CLASS_H