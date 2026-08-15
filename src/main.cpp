#include <iostream>
#include <raylib.h>
#include "header.h"

int main() {
    InitWindow(1600, 900, "Raylib-mc");

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    while(!WindowShouldClose()) {
        
    }
}