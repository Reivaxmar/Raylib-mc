#include "Chunk.h"
#include "ChunkManager.h"
#include <iostream>

Chunk::Chunk(ChunkManager* _chman, Vector3i chunk_pos) : chman(_chman) {
    m_mat = LoadMaterialDefault();
    m_mat.maps[MATERIAL_MAP_DIFFUSE].texture = BlockLoader::getInstance().getAtlas();

    m_matrix = MatrixTranslate(chunk_pos.x * CH_SIZE.x, chunk_pos.y * CH_SIZE.y, chunk_pos.z * CH_SIZE.z);
    
    m_upd_mesh = true;
    m_data.fill(BlockID(0));
    m_chunk_pos = chunk_pos;
    
    m_opaque_mesh = {0};
    m_transparent_mesh = {0};
    m_cutout_mesh = {0};

}

void Chunk::Draw() {
    if(m_upd_mesh) {
        update_mesh();
    }

    DrawMesh(m_opaque_mesh, m_mat, m_matrix);
    DrawMesh(m_cutout_mesh, m_mat, m_matrix);
    DrawMesh(m_transparent_mesh, m_mat, m_matrix);
}

void Chunk::SetBlock(Vector3i pos, BlockID block) {
    // If outside
    if(pos.x < 0 || pos.y < 0 || pos.z < 0 ||
        pos.x >= CH_SIZE.x || pos.y >= CH_SIZE.y || pos.z >= CH_SIZE.z) {
        return;
    }

    m_upd_mesh = true;
    m_data[Vec3_to_idx(pos, CH_SIZE)] = block;
}

BlockID Chunk::GetBlock(Vector3i pos) const {
    // If outside
    if(pos.x < 0 || pos.y < 0 || pos.z < 0 ||
        pos.x >= CH_SIZE.x || pos.y >= CH_SIZE.y || pos.z >= CH_SIZE.z) {
        return chman->GetBlock(pos + m_chunk_pos * CH_SIZE);
    }
    return m_data[Vec3_to_idx(pos, CH_SIZE)];
}

void Chunk::GenerateTerrain(int seed) {

    m_data.fill(BlockID(0));

    for(int x = 0; x < CH_SIZE.x; x++) {
        for(int z = 0; z < CH_SIZE.z; z++) {
            Vector3i chunk_world = m_chunk_pos * CH_SIZE;
            Vector2i xzworld = Vector2i(chunk_world.x + x, chunk_world.z + z);
            int height = chman->GetTerrainHeight(xzworld);
            for(int y = 0; y < CH_SIZE.y; y++) {
                if(height - y - chunk_world.y > 0) m_data[Vec3_to_idx(Vector3i(x, y, z), CH_SIZE)] = BlockID(1);
                else if(height - y == 0) m_data[Vec3_to_idx(Vector3i(x, y, z), CH_SIZE)] = BlockID(3);
                else break;
            }
        }
    }
}

void Chunk::update_mesh() {
    MeshData opaque, transparent, cutout;

    for(int x = 0; x < CH_SIZE.x; x++) {
        for(int y = 0; y < CH_SIZE.y; y++) {
            for(int z = 0; z < CH_SIZE.z; z++) {
                int idx = Vec3_to_idx({x, y, z}, CH_SIZE);
                BlockID block = m_data[idx];
                BlockData bData = getBlockData(block);
                if(!bData.drawn) continue;

                Vector3i pos = (Vector3i){ x, y, z };

                MeshData* data = &opaque;
                if(bData.transparent) data = &transparent;

                // Faces:
                // 2---1
                // |   |
                // 3---0

                if(getBlockData(GetBlock(pos + (Vector3i){0, 1, 0})).transparent && GetBlock(pos + (Vector3i){0, 1, 0}) != block) {
                    add_face(0, Vector3(pos), bData.faceIDs[0], *data);
                }
                if(getBlockData(GetBlock(pos + (Vector3i){0, -1, 0})).transparent && GetBlock(pos + (Vector3i){0, -1, 0}) != block) {
                    add_face(1, Vector3(pos), bData.faceIDs[1], *data);
                }
                
                if(getBlockData(GetBlock(pos + (Vector3i){1, 0, 0})).transparent && GetBlock(pos + (Vector3i){1, 0, 0}) != block) {
                    add_face(2, Vector3(pos), bData.faceIDs[2], *data);
                }
                if(getBlockData(GetBlock(pos + (Vector3i){-1, 0, 0})).transparent && GetBlock(pos + (Vector3i){-1, 0, 0}) != block) {
                    add_face(3, Vector3(pos), bData.faceIDs[3], *data);
                }

                if(getBlockData(GetBlock(pos + (Vector3i){0, 0, 1})).transparent && GetBlock(pos + (Vector3i){0, 0, 1}) != block) {
                    add_face(4, Vector3(pos), bData.faceIDs[4], *data);
                }
                if(getBlockData(GetBlock(pos + (Vector3i){0, 0, -1})).transparent && GetBlock(pos + (Vector3i){0, 0, -1}) != block) {
                    add_face(5, Vector3(pos), bData.faceIDs[5], *data);
                }
            }
        }
    }

    if(m_opaque_mesh.vaoId != 0) UnloadMesh(m_opaque_mesh);
    if(m_transparent_mesh.vaoId != 0) UnloadMesh(m_transparent_mesh);
    if(m_cutout_mesh.vaoId != 0) UnloadMesh(m_cutout_mesh);
        

    m_opaque_mesh = {0};
    m_transparent_mesh = {0};
    m_cutout_mesh = {0};

    opaque.UploadData(m_opaque_mesh);
    transparent.UploadData(m_transparent_mesh);
    cutout.UploadData(m_cutout_mesh);

    UploadMesh(&m_opaque_mesh, false);
    UploadMesh(&m_transparent_mesh, false);
    UploadMesh(&m_cutout_mesh, false);

    m_upd_mesh = false;
}

void Chunk::add_face(int face, Vector3 pos, unsigned int faceID, MeshData& data) {

    int vert_idx = data.verts.size();

    data.indices.push_back(vert_idx + 2);
    data.indices.push_back(vert_idx + 1);
    data.indices.push_back(vert_idx + 0);

    data.indices.push_back(vert_idx + 2);
    data.indices.push_back(vert_idx + 3);
    data.indices.push_back(vert_idx + 1);


    Vector3 n;
    Vector3 v[4];
    Vector2 uv[4];

    int tile_x = (int)(faceID) % 16;
    int tile_y = (int)(faceID) / 16;
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
        data.verts.push_back(v[i] + pos);
        data.uvs.push_back(uv[i]);
        data.normals.push_back(n);
    }
}