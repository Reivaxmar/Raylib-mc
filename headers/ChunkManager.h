#ifndef CHUNK_MANAGER_CLASS_H
#define CHUNK_MANAGER_CLASS_H

#include <map>
#include <PerlinNoise.hpp>

#include "Utils.h"
#include "Chunk.h"

struct GenerationSettings {
    const siv::PerlinNoise::seed_type seed;
    const int octaves;
    const double frequency;
    const double amplitude;

    GenerationSettings(
        siv::PerlinNoise::seed_type seed,
        double amplitude = 10.0,
        int octaves = 3,
        double frequency = 0.025
    ) : seed(seed), octaves(octaves), frequency(frequency), amplitude(amplitude) {}
};

class ChunkManager {
private:
    std::map<Vector3i, Chunk> m_chunks;
    const siv::PerlinNoise m_noise;
    GenerationSettings m_settings;

    
public:
    
    ChunkManager(siv::PerlinNoise::seed_type seed);
    
    BlockID GetBlock(Vector3i pos) const;
    
    void LoadChunk(Vector3i chunk_pos);
    
    void Draw();
    
    int GetTerrainHeight(Vector2i pos);

};

#endif // CHUNK_MANAGER_CLASS_H