#ifndef BLOCK_LOADER_H
#define BLOCK_LOADER_H

#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

#include <raylib.h>

namespace fs = std::filesystem;
using json = nlohmann::json;

typedef unsigned short BlockID;

struct BlockData {
    BlockID ID = 0;
    bool transparent = false;
    bool drawn = false;
    // [0, 1, 2, 3, 4, 5] => [Top, Bottom, Right, Left, Front, Back]
    unsigned int faceIDs[6] = {};
};

class BlockLoader {
private:
    BlockLoader() = default;

    json m_data;
    std::vector<std::string> m_blockNames;
    Texture2D m_blockAtlas;
    std::vector<BlockData> m_blockData;

public:
    BlockLoader(const BlockLoader&) = delete;
    BlockLoader(const BlockLoader&&) = delete;
    BlockLoader& operator=(const BlockLoader&) = delete;
    BlockLoader& operator=(const BlockLoader&&) = delete;

    static BlockLoader& getInstance() {
        static BlockLoader instance;
        return instance;
    }

    // Expects `blocks.json` and `blocks.png` to be in the directory
    void loadData(const fs::path& path) {
        // Clear everything
        m_data.clear();
        m_blockNames.clear();
        m_blockData.clear();
        
        // Load json
        std::ifstream file(path / "blocks.json");
        file >> m_data;

        m_blockNames.reserve(m_data.size());
        m_blockData.reserve(m_data.size());

        // Load block names
        for (const auto& [name, block] : m_data.items()) {
            m_blockNames.push_back(name);
            m_blockData.push_back(getBlockFromJSON(block));
        }
        
        // Load atlas map
        m_blockAtlas = LoadTexture((path / "blocks.png").c_str());
    }

    const json& getData() const {
        return m_data;
    }

    const std::string getName(const BlockID& id) const {
        if(id > m_blockNames.size()) return "";
        return m_blockNames[id];
    }

    const BlockData getBlockData(const BlockID& id) const {
        if(id > m_blockData.size()) return m_blockData[0];
        return m_blockData[id];
    }

    const Texture2D& getAtlas() const {
        return m_blockAtlas;
    }

    BlockData getBlockFromJSON(const json& block) {
        // Data to return
        BlockData ret;

        // Check for type
        std::string type = block.at("type").get<std::string>();
        if(type == "air") {
            // pass
        } else if(type == "cube_all") {
            // All faces equal
            int fid = block["textures"]["all"].get<int>();
            for(int i = 0; i < 6; i++) ret.faceIDs[i] = fid;
        } else if(type == "cube_top_bottom") {
            // Sides equal, top and bottom different
            int top = block["textures"]["top"].get<int>();
            int bottom = block["textures"]["bottom"].get<int>();
            int side = block["textures"]["side"].get<int>();

            ret.faceIDs[0] = top;
            ret.faceIDs[1] = bottom;
            for(int i = 2; i < 6; i++) ret.faceIDs[i] = side;
        } else if(type == "cube_column") {
            // Sides equal, top and bottom equal
            int end = block["textures"]["end"].get<int>();
            int side = block["textures"]["side"].get<int>();

            ret.faceIDs[0] = end;
            ret.faceIDs[1] = end;
            for(int i = 2; i < 6; i++) ret.faceIDs[i] = side;
        }

        // Set other properties
        ret.transparent = block.value("transparent", false);
        ret.drawn = block.value("drawn", true);

        return ret;

    }
};

#endif // BLOCK_LOADER_H