#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "stdlib.h"
#include "./inventory.h"
#include <math.h>
#define FRAME_RATE 8 //How many frames before switching animations

typedef struct Player {
    Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    Vector2 collider;
    Color color;
    Inventory * inventory;
    bool sprinting;
    int direction;
    int walkSprite;
    Texture2D texture;
} Player;

void Player_init(Player * player);

void Player_draw(Player * player);

#endif