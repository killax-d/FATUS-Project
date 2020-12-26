#ifndef COLLIDER_H
#define COLLIDER_H
#include "raylib.h"

typedef struct Collider {
    bool UP;
    bool RIGHT;
    bool DOWN;
    bool LEFT;
} Collider;

Collider * Collider_new();

void Collider_reset(Collider * collider);

#endif