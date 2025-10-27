#include "room.h"
#include "../raylib/raylib.h"
#include "../entities/robot.h"
#include <stddef.h>
#include <math.h>

Scene room_scene = {
    .id = 0,
    .init = room_scene_init,
    .update = room_scene_update,
    .draw = room_scene_draw,
    .deinit = room_scene_deinit
};

#define WALL_THICKNESS 10 // in pixels
#define MAX_ROBOTS 100

// Room size in meters (defaults)
static int s_room_width_m = 35;
static int s_room_height_m = 20;

// Robot management
static Robot* s_robots[MAX_ROBOTS];
static int s_robot_count = 0;

void room_set_size(int width_meters, int height_meters) {
    if (width_meters > 0) s_room_width_m = width_meters;
    if (height_meters > 0) s_room_height_m = height_meters;
}

int room_get_width_meters(void) { return s_room_width_m; }

int room_get_height_meters(void) { return s_room_height_m; }

void room_add_robot(Robot* robot) {
    if (s_robot_count < MAX_ROBOTS && robot != NULL) {
        s_robots[s_robot_count++] = robot;
    }
}

void room_remove_robot(Robot* robot) {
    for (int i = 0; i < s_robot_count; i++) {
        if (s_robots[i] == robot) {
            for (int j = i; j < s_robot_count - 1; j++) {
                s_robots[j] = s_robots[j + 1];
            }
            s_robot_count--;
            break;
        }
    }
}

void room_scene_init(void) {
    s_robot_count = 0;
    
    Robot* robot1 = robot_create(200, 200, 15, RED);
    Robot* robot2 = robot_create(400, 300, 15, RED);
    Robot* robot3 = robot_create(600, 400, 15, RED);
    
    room_add_robot(robot1);
    room_add_robot(robot2);
    room_add_robot(robot3);
}

void room_scene_update(void) {
    for (int i = 0; i < s_robot_count; i++) {
        entity_update((Entity*)s_robots[i]);
    }
}

static void draw_Walls(int innerX, int innerY, int innerW, int innerH) {
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    
    // Draw walls flush to screen edges
    // Top wall - full width of screen
    DrawRectangle(0, 0, screenW, WALL_THICKNESS, GRAY);
    
    // Bottom wall - full width of screen
    DrawRectangle(0, screenH - WALL_THICKNESS, screenW, WALL_THICKNESS, GRAY);
    
    // Left wall - full height of screen
    DrawRectangle(0, 0, WALL_THICKNESS, screenH, GRAY);
    
    // Right wall - full height of screen
    DrawRectangle(screenW - WALL_THICKNESS, 0, WALL_THICKNESS, screenH, GRAY);
}

static void draw_Grid(int innerX, int innerY, int innerW, int innerH, float meterSizePx) {
    // Draw vertical grid lines for each meter
    for (int i = 0; i <= s_room_width_m; i++) {
        int px = innerX + (int)roundf(i * meterSizePx);
        DrawLine(px, innerY, px, innerY + innerH, LIGHTGRAY);
    }
    
    // Draw horizontal grid lines for each meter
    for (int i = 0; i <= s_room_height_m; i++) {
        int py = innerY + (int)roundf(i * meterSizePx);
        DrawLine(innerX, py, innerX + innerW, py, LIGHTGRAY);
    }
}

void room_scene_draw(void) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Calculate available space inside walls
    int innerW = screenWidth - 2 * WALL_THICKNESS;
    int innerH = screenHeight - 2 * WALL_THICKNESS;
    
    // Calculate meter size in pixels to fit the room dimensions exactly
    float meterSizeX = (float)innerW / (float)s_room_width_m;
    float meterSizeY = (float)innerH / (float)s_room_height_m;
    float meterSizePx = (meterSizeX < meterSizeY) ? meterSizeX : meterSizeY;
    
    if (meterSizePx < 1.0f) meterSizePx = 1.0f;
    
    // Grid starts right after the wall thickness (flush with walls)
    int innerX = WALL_THICKNESS;
    int innerY = WALL_THICKNESS;
    
    // Grid dimensions fill the available space
    int roomPixelW = innerW;
    int roomPixelH = innerH;
    
    // Draw walls flush to screen edges
    draw_Walls(innerX, innerY, roomPixelW, roomPixelH);
    
    // Draw grid with exact meter markings
    draw_Grid(innerX, innerY, roomPixelW, roomPixelH, meterSizePx);
    
    // Render all robots
    for (int i = 0; i < s_robot_count; i++) {
        entity_render((Entity*)s_robots[i]);
    }
}

void room_scene_deinit(void) {
    for (int i = 0; i < s_robot_count; i++) {
        robot_destroy(s_robots[i]);
    }
    s_robot_count = 0;
}
