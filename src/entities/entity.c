#include "entity.h"
#include <stddef.h>

void entity_update(Entity* entity) {
    if (entity != NULL && entity->active && entity->update != NULL) {
        entity->update(entity);
    }
}

void entity_render(Entity* entity) {
    if (entity != NULL && entity->active && entity->render != NULL) {
        entity->render(entity);
    }
}
