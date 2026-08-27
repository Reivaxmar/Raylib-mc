#ifndef CHUNK_MANAGER_CLASS_H
#define CHUNK_MANAGER_CLASS_H

#include <map>

#include "Utils.h"
#include "Chunk.h"

class ChunkManager {
private:
    std::map<Vector3i, Chunk> m_chunks;

public:

    ChunkManager();

    BlockID GetBlock(Vector3i pos);

    void LoadChunk(Vector3i chunk_pos);

    void Draw();

};

#endif // CHUNK_MANAGER_CLASS_H