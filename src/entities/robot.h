#ifndef ROBOT_H
#define ROBOT_H

#include "entity.h"
#include "../raylib/raylib.h"

typedef struct RobotData {
    float radius;
    Color bodyColor;
    Color centerColor;
} RobotData;

typedef struct Robot {
    Entity base;
    RobotData data;
} Robot;

Robot* robot_create(float x, float y, float radius, Color centerColor);
void robot_destroy(Robot* robot);
void robot_update(Entity* self);
void robot_render(Entity* self);

#endif // ROBOT_H
