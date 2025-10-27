#include "scene_manager.h"
#include <stddef.h>

void init_scene_manager(SceneManager* sm) {
    sm->scene_count = 0;
    sm->current_scene = NULL;
}

void add_scene(SceneManager* sm, Scene scene) {
    if (sm->scene_count < MAX_SCENES) {
        sm->scenes[sm->scene_count++] = scene;
    }
}

void switch_to_scene(SceneManager* sm, int scene_id) {
    if (sm->current_scene != NULL && sm->current_scene->deinit != NULL) {
        sm->current_scene->deinit();
    }

    for (int i = 0; i < sm->scene_count; i++) {
        if (sm->scenes[i].id == scene_id) {
            sm->current_scene = &sm->scenes[i];
            if (sm->current_scene->init != NULL) {
                sm->current_scene->init();
            }
            return;
        }
    }
}

void update_current_scene(SceneManager* sm) {
    if (sm->current_scene != NULL && sm->current_scene->update != NULL) {
        sm->current_scene->update();
    }
}

void draw_current_scene(SceneManager* sm) {
    if (sm->current_scene != NULL && sm->current_scene->draw != NULL) {
        sm->current_scene->draw();
    }
}

void deinit_current_scene(SceneManager* sm) {
    if (sm->current_scene != NULL && sm->current_scene->deinit != NULL) {
        sm->current_scene->deinit();
    }
}
