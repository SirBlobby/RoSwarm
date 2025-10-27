#include "room.h"
#include "../include/raylib.h"
#include <stddef.h>

Scene room_scene = {
    .id = 0,
    .init = room_scene_init,
    .update = room_scene_update,
    .draw = room_scene_draw,
    .deinit = room_scene_deinit
};

#define METER_SCALE 20 // 20 pixels per meter
#define WALL_THICKNESS 10 // in pixels

void room_scene_init(void) {
    // Initialization logic for the room scene
}

void room_scene_update(void) {
    // Update logic for the room scene
}

void room_scene_draw(void) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Draw walls
    DrawRectangle(0, 0, screenWidth, WALL_THICKNESS, GRAY); // Top wall
    DrawRectangle(0, screenHeight - WALL_THICKNESS, screenWidth, WALL_THICKNESS, GRAY); // Bottom wall
    DrawRectangle(0, 0, WALL_THICKNESS, screenHeight, GRAY); // Left wall
    DrawRectangle(screenWidth - WALL_THICKNESS, 0, WALL_THICKNESS, screenHeight, GRAY); // Right wall

    // Draw grid
    for (int x = WALL_THICKNESS; x < screenWidth - WALL_THICKNESS; x += METER_SCALE) {
        DrawLine(x, WALL_THICKNESS, x, screenHeight - WALL_THICKNESS, LIGHTGRAY);
    }
    for (int y = WALL_THICKNESS; y < screenHeight - WALL_THICKNESS; y += METER_SCALE) {
        DrawLine(WALL_THICKNESS, y, screenWidth - WALL_THICKNESS, y, LIGHTGRAY);
    }
}

void room_scene_deinit(void) {
    // Deinitialization logic for the room scene
}
