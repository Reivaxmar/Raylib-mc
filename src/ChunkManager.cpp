#include "ChunkManager.h"
#include <iostream>

ChunkManager::ChunkManager(siv::PerlinNoise::seed_type seed)
    : m_settings(seed), m_noise(seed), m_gen_thread(&ChunkManager::chunkWorker, this), m_stop(false) {}

ChunkManager::~ChunkManager() {
    m_stop = true;
    m_cv.notify_one();
    m_gen_thread.join();
}

BlockID ChunkManager::GetBlock(Vector3i pos) const {
    return 0;
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
        m_chunk_queue.push(&it->second);
        m_cv.notify_one();
    }
}

void ChunkManager::Draw() {
    for(auto& it : m_chunks) {
        // it.second.Draw();
        // auto state = it.second.GetState();
        // if(it.second.GetState() == Chunk::State::MESHED) it.second.TryUploadMesh();
        // if(it.second.GetState() == Chunk::State::UPLOADED) it.second.Draw();
        if(it.second.GetState() < Chunk::State::MESHED) continue;
        it.second.Draw();
        // std::cout << (it.second.GetState() == Chunk::State::MESHED) << std::endl;
        // std::cout << int(it.second.GetState()) << ", " << int(Chunk::State::MESHED) << std::endl;
    }
}

int ChunkManager::GetTerrainHeight(Vector2i pos) {
    return static_cast<int>(m_noise.octave2D_01(
        pos.x * m_settings.frequency,
        pos.y * m_settings.frequency,
        m_settings.octaves
    ) * m_settings.amplitude);
}


void ChunkManager::chunkWorker() {
    while(!m_stop) {
        Chunk* chunk;

        {
            std::unique_lock<std::mutex> lock(m_mutex);

            m_cv.wait(lock, [this] {
                return !m_chunk_queue.empty() || m_stop;
            });
            if(m_stop) return;

            chunk = m_chunk_queue.front();
            m_chunk_queue.pop();

        }
        processChunk(chunk);

    }
}

void ChunkManager::processChunk(Chunk* chunk) {

    chunk->GenerateTerrain();
    chunk->GenerateMesh();

    // auto [it, inserted] = m_chunks.try_emplace(pos, this, pos);

    // if(inserted) {
    //     it->second.GenerateTerrain();
    //     it->second.GenerateMesh();
    // }
}