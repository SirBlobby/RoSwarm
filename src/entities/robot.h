#ifndef ROBOT_H
#define ROBOT_H

#include "entity.h"
#include "../raylib/raylib.h"

typedef struct RobotData {
    float radius;
    Color bodyColor;
    Color centerColor;
    float heading;        // Direction robot is facing (in radians)
    float fovAngle;       // Field of view angle (in radians)
    float fovRange;       // How far the robot can see
    int showFOV;          // Toggle FOV visualization
} RobotData;

typedef struct Robot {
    Entity base;
    RobotData data;
} Robot;

Robot* robot_create(float x, float y, float radius, Color centerColor);
void robot_destroy(Robot* robot);
void robot_update(Entity* self);
void robot_render(Entity* self);
void robot_set_heading(Robot* robot, float heading);
void robot_toggle_fov(Robot* robot);
void robot_set_fov_visible(Robot* robot, int visible);

#endif // ROBOT_H
