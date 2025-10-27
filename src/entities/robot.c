#include "robot.h"
#include <stdlib.h>
#include <math.h>

void robot_update(Entity* self) {
    if (self == NULL) return;
}

void robot_render(Entity* self) {
    if (self == NULL) return;
    
    Robot* robot = (Robot*)self;
    
    // Draw FOV triangle if enabled
    if (robot->data.showFOV) {
        float halfFOV = robot->data.fovAngle / 2.0f;
        
        // Calculate the three points of the FOV triangle
        Vector2 p1 = { self->x, self->y }; // Center of robot
        
        // Left edge of FOV
        float leftAngle = robot->data.heading - halfFOV;
        Vector2 p2 = { 
            self->x + cosf(leftAngle) * robot->data.fovRange,
            self->y + sinf(leftAngle) * robot->data.fovRange
        };
        
        // Right edge of FOV
        float rightAngle = robot->data.heading + halfFOV;
        Vector2 p3 = { 
            self->x + cosf(rightAngle) * robot->data.fovRange,
            self->y + sinf(rightAngle) * robot->data.fovRange
        };
        
        // Draw the FOV triangle with transparency
        DrawTriangle(p1, p2, p3, Fade(SKYBLUE, 0.3f));
        DrawTriangle(p1, p3, p2, Fade(SKYBLUE, 0.3f)); // Draw both sides for visibility
        
        // Draw curved arc at the end of the FOV
        DrawCircleSector(
            (Vector2){self->x, self->y},
            robot->data.fovRange,
            (robot->data.heading - halfFOV) * RAD2DEG,
            (robot->data.heading + halfFOV) * RAD2DEG,
            36,
            Fade(SKYBLUE, 0.3f)
        );
        
        // Draw FOV outline edges
        DrawLineV(p1, p2, Fade(SKYBLUE, 0.6f));
        DrawLineV(p1, p3, Fade(SKYBLUE, 0.6f));
        
        // Draw curved arc outline at the end
        DrawCircleSectorLines(
            (Vector2){self->x, self->y},
            robot->data.fovRange,
            (robot->data.heading - halfFOV) * RAD2DEG,
            (robot->data.heading + halfFOV) * RAD2DEG,
            36,
            Fade(SKYBLUE, 0.6f)
        );
    }
    
    // Draw robot body
    DrawCircle((int)self->x, (int)self->y, robot->data.radius, robot->data.bodyColor);
    
    // Draw center dot
    float centerDotRadius = robot->data.radius * 0.3f;
    DrawCircle((int)self->x, (int)self->y, centerDotRadius, robot->data.centerColor);
    
    // Draw heading indicator (small line showing direction)
    float indicatorLength = robot->data.radius * 0.8f;
    float endX = self->x + cosf(robot->data.heading) * indicatorLength;
    float endY = self->y + sinf(robot->data.heading) * indicatorLength;
    DrawLineEx((Vector2){self->x, self->y}, (Vector2){endX, endY}, 2.0f, WHITE);
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
    robot->data.heading = 0.0f;              // Facing right (0 radians)
    robot->data.fovAngle = 1.0472f;          // 60 degrees in radians (PI/3)
    robot->data.fovRange = 100.0f;           // Can see 100 pixels ahead
    robot->data.showFOV = 1;                 // FOV visible by default
    
    return robot;
}

void robot_destroy(Robot* robot) {
    if (robot != NULL) {
        free(robot);
    }
}

void robot_set_heading(Robot* robot, float heading) {
    if (robot != NULL) {
        robot->data.heading = heading;
    }
}

void robot_toggle_fov(Robot* robot) {
    if (robot != NULL) {
        robot->data.showFOV = !robot->data.showFOV;
    }
}

void robot_set_fov_visible(Robot* robot, int visible) {
    if (robot != NULL) {
        robot->data.showFOV = visible;
    }
}
