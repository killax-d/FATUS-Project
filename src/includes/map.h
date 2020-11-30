#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "./sprite.h"

typedef struct GameMap {
    int size;
    Sprite sprite[];
} GameMap;

#endif