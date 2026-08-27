#ifndef BLOCK_DEFINITIONS_H
#define BLOCK_DEFINITIONS_H

#include "BlockLoader.h"


struct BlockData {
    BlockID ID = 0;
    bool transparent = false;
    bool drawn = false;
    // [0, 1, 2, 3, 4, 5] => [Top, Bottom, Right, Left, Front, Back]
    unsigned int faceIDs[6] = {};
};

inline BlockData getBlockData(const BlockID& id) {
    // Load block loader
    auto& bl = BlockLoader::getInstance();

    BlockData ret;

    // Get block data
    json data = bl.getData();
    json block = data.at(bl.getName(id));

    // Check for type
    std::string type = block.at("type").get<std::string>();
    if(type == "air") {
        // pass
    } else if(type == "cube_all") {
        int fid = block["textures"]["all"].get<int>();
        for(int i = 0; i < 6; i++) ret.faceIDs[i] = fid;
    } else if(type == "cube_top_bottom") {
        int top = block["textures"]["top"].get<int>();
        int bottom = block["textures"]["bottom"].get<int>();
        int side = block["textures"]["side"].get<int>();

        ret.faceIDs[0] = top;
        ret.faceIDs[1] = bottom;
        for(int i = 2; i < 6; i++) ret.faceIDs[i] = side;
    } else if(type == "cube_column") {
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

#endif // BLOCK_DEFINITIONS_H