#ifndef SCENE_H
#define SCENE_H

typedef struct Scene {
    int id;
    void (*init)(void);
    void (*update)(void);
    void (*draw)(void);
    void (*deinit)(void);
} Scene;

#endif // SCENE_H
