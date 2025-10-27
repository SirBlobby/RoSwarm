#include "../include/raylib.h"

void renderFrame() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Rendering Frame...", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
}


int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "ROSWARM - Swarm Robotics Simulator");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        renderFrame();
    }

    CloseWindow();
    return 0;
}
