#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "./sprite.h"
#define MAP_TEXTURE_SCALE 32
#define MAP_WIDTH 178
#define MAP_HEIGHT 102

typedef struct GameMap {
    int size;
    Sprite sprite[MAP_HEIGHT][MAP_WIDTH];
    int width;
    int height;
} GameMap;

void IntArrayToSpriteMap(GameMap * map, int array[MAP_HEIGHT][MAP_WIDTH]);

void Map_draw(GameMap * map);

#endif