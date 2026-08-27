#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <array>
#include <vector>
#include "Utils.h"
#include "Block.h"

#include <raymath.h>

// const int CHUNK_SIZE = 16;
// const int CHUNK_HEIGHT = 32;

constexpr Vector3i CH_SIZE = { 16, 32, 16 };

// enum class BlockID : unsigned short {
//     AIR, GRASS, DIRT
// };

class Chunk {
public:

    Chunk(Vector3i chunk_pos);

    void Draw();

    void SetBlock(Vector3i pos, BlockID block);

    BlockID GetBlock(Vector3i pos) const;

private:

    std::array<BlockID, CH_SIZE.x * CH_SIZE.y * CH_SIZE.z> m_data;

    Vector3i m_chunk_pos;

    bool m_upd_mesh;

    Model m_model;
    Mesh m_mesh;
    Material m_mat;

    Matrix m_matrix;

    void update_mesh();

    // [0, 1, 2, 3, 4, 5] => [Top, Bottom, Right, Left, Front, Back]
    void add_face(int face, Vector3 pos, unsigned int faceID,
        std::vector<Vector3>& verts,
        std::vector<Vector3>& normals,
        std::vector<Vector2>& uvs,
        std::vector<unsigned short>& indices
    );

};

#endif // CHUNK_CLASS_H