#ifndef BLOCK_LOADER_H
#define BLOCK_LOADER_H

#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

typedef unsigned short BlockID;

class BlockLoader {
private:
    BlockLoader() = default;

    json m_data;
    std::vector<std::string> m_blockNames;

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
        
        // Load json
        std::ifstream file(path / "blocks.json");
        file >> m_data;

        m_blockNames.reserve(m_data.size());

        // Load block names
        for (const auto& [name, block] : m_data.items()) {
            m_blockNames.push_back(name);
        }
        // std::cout << m_data.dump() << std::endl;
    }

    const json& getData() const {
        return m_data;
    }

    const std::string& getName(const BlockID& id) const {
        if(id > m_blockNames.size()) return "";
        return m_blockNames[id];
    }
};

#endif // BLOCK_LOADER_H