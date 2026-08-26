#include <iostream>
#include <raylib.h>
#include "Player.h"
#include "Chunk.h"
#include "BlockLoader.h"

int main() {
    // Load block data
    BlockLoader::getInstance().loadData("assets");

    InitWindow(1600, 900, "Raylib mc");

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    DisableCursor();

    Player player;
    Chunk chunk({0, 0, 0});
    Chunk chunk2({2, 0, 0});
    Chunk chunk3({0, 2, 0});

    while(!WindowShouldClose()) {

        player.update(GetFrameTime());
        
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(player.get_cam());

                // DrawCube(Vector3{0.f, 0.f, 0.f}, 1.f, 1.f, 1.f, SKYBLUE);
                BeginBlendMode(BLEND_ALPHA);

                chunk.Draw();
                chunk2.Draw();
                chunk3.Draw();

                EndBlendMode();

            
            EndMode3D();
            
            DrawFPS(10, 10);

        EndDrawing();

    }

    CloseWindow();
}