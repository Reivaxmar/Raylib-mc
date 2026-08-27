#include "ChunkManager.h"
#include <iostream>

ChunkManager::ChunkManager(siv::PerlinNoise::seed_type seed)
    : m_settings(seed), m_noise(seed) {}

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

int ChunkManager::GetTerrainHeight(Vector2i pos) {
    return static_cast<int>(m_noise.octave2D_01(
        pos.x * m_settings.frequency,
        pos.y * m_settings.frequency,
        m_settings.octaves
    ) * m_settings.amplitude);
}