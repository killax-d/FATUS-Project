#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "stdlib.h"
#include "./inventory.h"

typedef struct Player {
    Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    Vector3 collider;
    Color color;
    Inventory inventory;
    int sprinting;
} Player;

Player* Player_new(Vector2 position, Vector2 speed, float acceleration, float rotation, Vector3 collider, Color color) {
    Player* p = malloc(sizeof(Player));
    p->position = position;
    p->speed = speed;
    p->acceleration = acceleration;
    p->rotation = rotation;
    p->collider = collider;
    p->color = color;
    Inventory inv;
    p->inventory = inv;
    p->sprinting = -1;
    return p;
}

void Player_delete(Player p) {
    free(&p);
}

#endif