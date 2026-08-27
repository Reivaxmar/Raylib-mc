#include <iostream>
#include <raylib.h>
#include "Player.h"
#include "Chunk.h"
#include "BlockLoader.h"
#include "ChunkManager.h"

int main() {
    InitWindow(1600, 900, "Raylib mc");
    
    // Load block data
    BlockLoader::getInstance().loadData("assets");
    
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    DisableCursor();

    Player player;
    ChunkManager chman;

    while(!WindowShouldClose()) {

        player.update(GetFrameTime());

        chman.LoadChunk(getChunk(Vector3i(player.get_cam().position)));
        
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(player.get_cam());

                BeginBlendMode(BLEND_ALPHA);

                chman.Draw();

                EndBlendMode();
            
            EndMode3D();
            
            DrawFPS(10, 10);

        EndDrawing();

    }

    CloseWindow();
}