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
    Vector2 collider;
    Color color;
    Inventory inventory;
    int sprinting;
    int direction;
    int walkSprite;
    Texture2D texture;
} Player;

Player* Player_new(Vector2 position, Vector2 speed, float acceleration, float rotation, Vector2 collider, Color color, Inventory inventory, int sprinting, Texture2D texture) {
    Player* p = malloc(sizeof(Player));
    p->position = position;
    p->speed = speed;
    p->acceleration = acceleration;
    p->rotation = rotation;
    p->collider = collider;
    p->color = color;
    p->inventory = inventory;
    p->sprinting = sprinting;
    p->direction = 0;
    p->walkSprite = -1;
    p->texture = texture;
    return p;
}

void Player_delete(Player p) {
    free(&p);
}

#endif