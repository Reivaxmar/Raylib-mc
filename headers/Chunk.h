#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <array>
#include "Utils.h"

const int CHUNK_SIZE = 16;
const int CHUNK_HEIGHT = 32;

const Vector3i ch_sz = { CHUNK_SIZE, CHUNK_HEIGHT, CHUNK_SIZE };

enum Block : unsigned short {
    AIR, GRASS, DIRT
};

class Chunk {
public:

    Chunk(Vector3i chunk_pos) {
        m_data.fill(AIR);
        m_chunk_pos = chunk_pos;
        GetRandomValue(0, 2);

        for(int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT; i++) {
            m_data[i] = (Block)GetRandomValue(0, 2);
        }
    }

    void Draw() const {
        for(int x = 0; x < CHUNK_SIZE; x++) {
            for(int y = 0; y < CHUNK_HEIGHT; y++) {
                for(int z = 0; z < CHUNK_SIZE; z++) {
                    int idx = Vec3_to_idx({x, y, z}, ch_sz);
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

private:

    std::array<Block, CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT> m_data;

    Vector3i m_chunk_pos;

};

#endif // CHUNK_CLASS_H