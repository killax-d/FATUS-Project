#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "stdlib.h"
#include "./collider.h"
#include "./inventory.h"
#include "./map.h"
#include <math.h>
#define FRAME_RATE 8 //How many frames before switching animations
#define PLAYER_SIZE 40

typedef struct Player {
    Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    float size;
    Collider * collider;
    Color color;
    Inventory * inventory;
    bool sprinting;
    int direction;
    int walkSprite;
    Texture2D texture;
} Player;

Player * Player_new();

void Player_init(Player * player);

void Player_draw(Player * player);

void Player_control(Camera2D * camera, Player * player);

void Player_switchItem(Player * player, int selected);

void Player_move(GameMap * map, Player * player, float delta);

void Player_collisions(GameMap * map, Player * player, Vector2 speed);

#endif