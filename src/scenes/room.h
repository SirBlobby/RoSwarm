#include "scene.h"

// Forward declaration
typedef struct Robot Robot;

// Function declarations for the room scene
void room_scene_init(void);
void room_scene_update(void);
void room_scene_draw(void);
void room_scene_deinit(void);

// Configure room size (in meters)
void room_set_size(int width_meters, int height_meters);
int room_get_width_meters(void);
int room_get_height_meters(void);

// Robot management
void room_add_robot(Robot* robot);
void room_remove_robot(Robot* robot);
void room_toggle_all_fov(void);

// The room scene definition
extern Scene room_scene;
