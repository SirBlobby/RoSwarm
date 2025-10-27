#ifndef ENTITY_H
#define ENTITY_H

typedef struct Entity Entity;

struct Entity {
    float x;
    float y;
    int active;
    void (*update)(Entity* self);
    void (*render)(Entity* self);
    void* data;
};

void entity_update(Entity* entity);
void entity_render(Entity* entity);

#endif // ENTITY_H
