#include <iostream>
#include <raylib.h>
#include "Player.h"
#include "Chunk.h"

int main() {
    InitWindow(1600, 900, "Raylib mc");

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    DisableCursor();

    Player player;
    Chunk chunk({0, 0, 0});

    while(!WindowShouldClose()) {

        player.update(GetFrameTime());
        
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(player.get_cam());

                // DrawCube(Vector3{0.f, 0.f, 0.f}, 1.f, 1.f, 1.f, SKYBLUE);

                chunk.Draw();


            
            EndMode3D();

        EndDrawing();

    }

    CloseWindow();
}