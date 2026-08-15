#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <array>
#include <vector>
#include "Utils.h"

// const int CHUNK_SIZE = 16;
// const int CHUNK_HEIGHT = 32;

const Vector3i CH_SIZE = { 16, 32, 16 };

enum class Block : unsigned short {
    AIR, GRASS, DIRT
};

class Chunk {
public:

    Chunk(Vector3i chunk_pos) {
        m_upd_mesh = true;
        m_data.fill(Block::AIR);
        m_chunk_pos = chunk_pos;
        GetRandomValue(0, 2);

        for(int i = 0; i < CH_SIZE.x * CH_SIZE.y * CH_SIZE.z; i++) {
            m_data[i] = (Block)GetRandomValue(0, 2);
        }
    }

    void Draw() {
        if(m_upd_mesh) {
            update_mesh();
        }


        for(int x = 0; x < CH_SIZE.x; x++) {
            for(int y = 0; y < CH_SIZE.y; y++) {
                for(int z = 0; z < CH_SIZE.z; z++) {
                    int idx = Vec3_to_idx({x, y, z}, CH_SIZE);
                    Block block = m_data[idx];

                    if(block == Block::AIR) continue;
                    else if(block == Block::GRASS) {
                        DrawCube((Vector3){x, y, z}, 1.f, 1.f, 1.f, GREEN);
                    } else if(block == Block::DIRT) {
                        DrawCube((Vector3){x, y, z}, 1.f, 1.f, 1.f, BROWN);
                    }
                }
            }
        }
    }

    void SetBlock(Vector3i pos, Block block) {
        // If outside
        if(pos.x < 0 || pos.y < 0 || pos.z < 0 ||
           pos.x >= CH_SIZE.x || pos.y >= CH_SIZE.y || pos.z >= CH_SIZE.z) {
            return;
        }

        m_upd_mesh = true;
        m_data[Vec3_to_idx(pos, CH_SIZE)] = block;
    }

    Block GetBlock(Vector3i pos) const {
        // If outside
        if(pos.x < 0 || pos.y < 0 || pos.z < 0 ||
           pos.x >= CH_SIZE.x || pos.y >= CH_SIZE.y || pos.z >= CH_SIZE.z) {
            return Block::AIR;
        }
        return m_data[Vec3_to_idx(pos, CH_SIZE)];
    }

private:

    std::array<Block, CH_SIZE.x * CH_SIZE.y * CH_SIZE.z> m_data;

    Vector3i m_chunk_pos;

    bool m_upd_mesh;

    Model m_model;
    Mesh m_mesh;

    void update_mesh() {

        std::vector<Vector3> verts, normals;
        std::vector<Vector2> uvs;

        for(int x = 0; x < CH_SIZE.x; x++) {
            for(int y = 0; y < CH_SIZE.y; y++) {
                for(int z = 0; z < CH_SIZE.z; z++) {
                    int idx = Vec3_to_idx({x, y, z}, CH_SIZE);
                    Block block = m_data[idx];
                    if(block == Block::AIR) continue;

                    Vector3 pos = (Vector3){ x, y, z };

                    // Faces:
                    // 2---1
                    // |   |
                    // 3---0

                    // Front face
                    verts.push_back(pos + (Vector3){ 0.5f, -0.5f, -0.5f});
                    verts.push_back(pos + (Vector3){ 0.5f,  0.5f, -0.5f});
                    verts.push_back(pos + (Vector3){-0.5f,  0.5f, -0.5f});
                    verts.push_back(pos + (Vector3){-0.5f, -0.5f, -0.5f});
                }
            }
        }
    }

};

#endif // CHUNK_CLASS_H