#ifndef SPRITE_H
#define SPRITE_H
#include "raylib.h"

typedef struct Sprite {
    Rectangle rect;
    bool blocking;
    bool hasTexture;
    Texture2D texture;
} Sprite;

#endif