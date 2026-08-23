#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <array>
#include <vector>
#include "Utils.h"

#include <raymath.h>

// const int CHUNK_SIZE = 16;
// const int CHUNK_HEIGHT = 32;

constexpr Vector3i CH_SIZE = { 16, 32, 16 };

enum class BlockID : unsigned short {
    AIR, GRASS, DIRT
};

class Chunk {
public:

    Chunk(Vector3i chunk_pos) {
        m_mat = LoadMaterialDefault();
        m_mat.maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/blocks.png");

        m_matrix = MatrixTranslate(chunk_pos.x * CH_SIZE.x, chunk_pos.y * CH_SIZE.y, chunk_pos.z * CH_SIZE.z);

        m_upd_mesh = true;
        m_data.fill(BlockID::AIR);
        m_chunk_pos = chunk_pos;
        
        m_mesh = {0};

        for(int i = 0; i < CH_SIZE.x * CH_SIZE.y * CH_SIZE.z; i++) {
            m_data[i] = (BlockID)GetRandomValue(0, 2);
        }
        for(int x = 0; x < CH_SIZE.x; x++) {
            for(int z = 0; z < CH_SIZE.z; z++) {
                m_data[Vec3_to_idx(Vector3i(x, 0, z), CH_SIZE)] = BlockID::DIRT;
                m_data[Vec3_to_idx(Vector3i(x, 1, z), CH_SIZE)] = BlockID::GRASS;
            }
        }
    }

    void Draw() {
        if(m_upd_mesh) {
            update_mesh();
        }

        DrawMesh(m_mesh, m_mat, m_matrix);


        // for(int x = 0; x < CH_SIZE.x; x++) {
        //     for(int y = 0; y < CH_SIZE.y; y++) {
        //         for(int z = 0; z < CH_SIZE.z; z++) {
        //             int idx = Vec3_to_idx({x, y, z}, CH_SIZE);
        //             BlockID block = m_data[idx];

        //             if(block == BlockID::AIR) continue;
        //             else if(block == BlockID::GRASS) {
        //                 DrawCube((Vector3){x, y, z}, 1.f, 1.f, 1.f, GREEN);
        //             } else if(block == BlockID::DIRT) {
        //                 DrawCube((Vector3){x, y, z}, 1.f, 1.f, 1.f, BROWN);
        //             }
        //         }
        //     }
        // }
    }

    void SetBlock(Vector3i pos, BlockID block) {
        // If outside
        if(pos.x < 0 || pos.y < 0 || pos.z < 0 ||
           pos.x >= CH_SIZE.x || pos.y >= CH_SIZE.y || pos.z >= CH_SIZE.z) {
            return;
        }

        m_upd_mesh = true;
        m_data[Vec3_to_idx(pos, CH_SIZE)] = block;
    }

    BlockID GetBlock(Vector3i pos) const {
        // If outside
        if(pos.x < 0 || pos.y < 0 || pos.z < 0 ||
           pos.x >= CH_SIZE.x || pos.y >= CH_SIZE.y || pos.z >= CH_SIZE.z) {
            return BlockID::AIR;
        }
        return m_data[Vec3_to_idx(pos, CH_SIZE)];
    }

private:

    std::array<BlockID, CH_SIZE.x * CH_SIZE.y * CH_SIZE.z> m_data;

    Vector3i m_chunk_pos;

    bool m_upd_mesh;

    Model m_model;
    Mesh m_mesh;
    Material m_mat;

    Matrix m_matrix;

    void update_mesh() {

        std::vector<Vector3> verts, normals;
        std::vector<Vector2> uvs;
        std::vector<unsigned short> indices;

        for(int x = 0; x < CH_SIZE.x; x++) {
            for(int y = 0; y < CH_SIZE.y; y++) {
                for(int z = 0; z < CH_SIZE.z; z++) {
                    int idx = Vec3_to_idx({x, y, z}, CH_SIZE);
                    BlockID block = m_data[idx];
                    if(block == BlockID::AIR) continue;

                    Vector3i pos = (Vector3i){ x, y, z };

                    // if()

                    // Faces:
                    // 2---1
                    // |   |
                    // 3---0

                    if(GetBlock(pos + (Vector3i){0, 1, 0}) == BlockID::AIR) {
                        add_face(0, Vector3(pos), block, verts, normals, uvs, indices);
                    }
                    if(GetBlock(pos + (Vector3i){0, -1, 0}) == BlockID::AIR) {
                        add_face(1, Vector3(pos), block, verts, normals, uvs, indices);
                    }
                    
                    if(GetBlock(pos + (Vector3i){1, 0, 0}) == BlockID::AIR) {
                        add_face(2, Vector3(pos), block, verts, normals, uvs, indices);
                    }
                    if(GetBlock(pos + (Vector3i){-1, 0, 0}) == BlockID::AIR) {
                        add_face(3, Vector3(pos), block, verts, normals, uvs, indices);
                    }

                    if(GetBlock(pos + (Vector3i){0, 0, 1}) == BlockID::AIR) {
                        add_face(4, Vector3(pos), block, verts, normals, uvs, indices);
                    }
                    if(GetBlock(pos + (Vector3i){0, 0, -1}) == BlockID::AIR) {
                        add_face(5, Vector3(pos), block, verts, normals, uvs, indices);
                    }

                    // // Front face
                    // verts.push_back(pos + (Vector3){ 0.5f, -0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){ 0.5f,  0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f,  0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f, -0.5f, -0.5f});

                    // // Back face
                    // verts.push_back(pos + (Vector3){-0.5f, -0.5f, 0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f,  0.5f, 0.5f});
                    // verts.push_back(pos + (Vector3){ 0.5f,  0.5f, 0.5f});
                    // verts.push_back(pos + (Vector3){ 0.5f, -0.5f, 0.5f});
                    
                    // // Left face
                    // verts.push_back(pos + (Vector3){ 0.5f, -0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){ 0.5f,  0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f,  0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f, -0.5f, -0.5f});

                    // // Right face
                    // verts.push_back(pos + (Vector3){ 0.5f, -0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){ 0.5f,  0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f,  0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f, -0.5f, -0.5f});

                    // // Top face
                    // verts.push_back(pos + (Vector3){ 0.5f, -0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){ 0.5f,  0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f,  0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f, -0.5f, -0.5f});

                    // // Bottom face
                    // verts.push_back(pos + (Vector3){ 0.5f, -0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){ 0.5f,  0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f,  0.5f, -0.5f});
                    // verts.push_back(pos + (Vector3){-0.5f, -0.5f, -0.5f});
                }
            }
        }

        if (m_mesh.vaoId != 0) {
            UnloadMesh(m_mesh);
        }

        m_mesh = {0};

        m_mesh.vertexCount = verts.size();
        m_mesh.triangleCount = indices.size() / 3;
        m_mesh.vertices = reinterpret_cast<float*>(verts.data());
        m_mesh.indices = indices.data();
        m_mesh.normals = reinterpret_cast<float*>(normals.data());
        m_mesh.texcoords = reinterpret_cast<float*>(uvs.data());

        UploadMesh(&m_mesh, false);

        m_upd_mesh = false;
    }

    // [0, 1, 2, 3, 4, 5] => [Top, Bottom, Right, Left, Front, Back]
    void add_face(int face, Vector3 pos, BlockID block,
        std::vector<Vector3>& verts,
        std::vector<Vector3>& normals,
        std::vector<Vector2>& uvs,
        std::vector<unsigned short>& indices
    ) {

        // if(face >= 2) return;
        int vert_idx = verts.size();

        indices.push_back(vert_idx + 2);
        indices.push_back(vert_idx + 1);
        indices.push_back(vert_idx + 0);

        indices.push_back(vert_idx + 2);
        indices.push_back(vert_idx + 3);
        indices.push_back(vert_idx + 1);


        Vector3 n;
        Vector3 v[4];
        Vector2 uv[4];

        int tile_x = (int)(block) % 16;
        int tile_y = (int)(block) / 16;
        constexpr float tile_size = 1.0f / 16.0f;

        float u0 = tile_x * tile_size;
        float v0 = tile_y * tile_size;
        float u1 = (tile_x + 1) * tile_size;
        float v1 = (tile_y + 1) * tile_size;

        uv[0] = {u0, v0};
        uv[1] = {u1, v0};
        uv[2] = {u0, v1};
        uv[3] = {u1, v1};

        if(face == 0) { // Top face
            n = {0, 1, 0};
            v[0] = {0, 1, 0};
            v[1] = {1, 1, 0};
            v[2] = {0, 1, 1};
            v[3] = {1, 1, 1};
        } else if(face == 1) { // Bottom face
            n = {0, -1, 0};
            v[0] = {0, 0, 0};
            v[1] = {0, 0, 1};
            v[2] = {1, 0, 0};
            v[3] = {1, 0, 1};
        } else if(face == 2) { // Right face
            n = {1, 0, 0};
            v[3] = {1, 0, 0};
            v[2] = {1, 0, 1};
            v[1] = {1, 1, 0};
            v[0] = {1, 1, 1};
        } else if(face == 3) { // Left face
            n = {-1, 0, 0};
            v[2] = {0, 0, 0};
            v[0] = {0, 1, 0};
            v[3] = {0, 0, 1};
            v[1] = {0, 1, 1};
        } else if(face == 4) { // Front face
            n = {0, 0, 1};
            v[2] = {0, 0, 1};
            v[0] = {0, 1, 1};
            v[3] = {1, 0, 1};
            v[1] = {1, 1, 1};
        } else if(face == 5) { // Back face
            n = {0, 0, -1};
            v[3] = {0, 0, 0};
            v[2] = {1, 0, 0};
            v[1] = {0, 1, 0};
            v[0] = {1, 1, 0};
        }

        for(int i = 0; i < 4; i++) {
            verts.push_back(v[i] + pos);
            uvs.push_back(uv[i]);
            normals.push_back(n);
        }
    }

};

#endif // CHUNK_CLASS_H