#include "robot.h"
#include <stdlib.h>

void robot_update(Entity* self) {
    if (self == NULL) return;
}

void robot_render(Entity* self) {
    if (self == NULL) return;
    
    Robot* robot = (Robot*)self;
    
    DrawCircle((int)self->x, (int)self->y, robot->data.radius, robot->data.bodyColor);
    
    float centerDotRadius = robot->data.radius * 0.3f;
    DrawCircle((int)self->x, (int)self->y, centerDotRadius, robot->data.centerColor);
}

Robot* robot_create(float x, float y, float radius, Color centerColor) {
    Robot* robot = (Robot*)malloc(sizeof(Robot));
    if (robot == NULL) return NULL;
    
    robot->base.x = x;
    robot->base.y = y;
    robot->base.active = 1;
    robot->base.update = robot_update;
    robot->base.render = robot_render;
    robot->base.data = &robot->data;
    
    robot->data.radius = radius;
    robot->data.bodyColor = DARKGRAY;
    robot->data.centerColor = centerColor;
    
    return robot;
}

void robot_destroy(Robot* robot) {
    if (robot != NULL) {
        free(robot);
    }
}
