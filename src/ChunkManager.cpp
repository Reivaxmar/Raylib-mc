#include "ChunkManager.h"
#include <iostream>

ChunkManager::ChunkManager() {

}

BlockID ChunkManager::GetBlock(Vector3i pos) const {
    // return BlockID(0);
    Vector3i ch_pos = getChunk(pos);

    auto it = m_chunks.find(ch_pos);
    
    if(it != m_chunks.end()) {
        return it->second.GetBlock(worldToChunk(pos));
    }
    return 0;
}

void ChunkManager::LoadChunk(Vector3i chunk_pos) {
    auto [it, inserted] = m_chunks.try_emplace(chunk_pos, this, chunk_pos);

    if(inserted) {
        it->second.GenerateTerrain(67);
    }
}

void ChunkManager::Draw() {
    for(auto& it : m_chunks) {
        it.second.Draw();
    }
}