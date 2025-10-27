#include "../include/raylib.h"
#include "scene_manager.h"

#include "room.h"

SceneManager scene_manager;

const int screenWidth = 1200;
const int screenHeight = 720;

void renderFrame() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_current_scene(&scene_manager);
    EndDrawing();
}


int main(void) {

    InitWindow(screenWidth, screenHeight, "ROSWARM - Swarm Robotics Simulator");
    SetTargetFPS(60);

    init_scene_manager(&scene_manager);

    add_scene(&scene_manager, room_scene);
    switch_to_scene(&scene_manager, 0);

    while (!WindowShouldClose()) {
        update_current_scene(&scene_manager);
        renderFrame();
    }

    deinit_current_scene(&scene_manager);
    CloseWindow();
    return 0;
}
