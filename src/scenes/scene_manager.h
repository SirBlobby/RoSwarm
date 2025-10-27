#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene.h"

#define MAX_SCENES 10

typedef struct SceneManager {
    Scene scenes[MAX_SCENES];
    int scene_count;
    Scene* current_scene;
} SceneManager;

void init_scene_manager(SceneManager* sm);
void add_scene(SceneManager* sm, Scene scene);
void switch_to_scene(SceneManager* sm, int scene_id);
void update_current_scene(SceneManager* sm);
void draw_current_scene(SceneManager* sm);
void deinit_current_scene(SceneManager* sm);

#endif // SCENE_MANAGER_H
