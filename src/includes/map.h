#ifndef GAMEMAP_H
#define GAMEMAP_H
#define MAP_WIDTH 178
#define MAP_HEIGHT 102
#include "./sprite.h"

typedef struct GameMap {
    int size;
    Sprite sprite[MAP_HEIGHT][MAP_WIDTH];
    int width;
    int height;
} GameMap;

void IntArrayToSpriteMap(GameMap * map, int array[MAP_HEIGHT][MAP_WIDTH]) {
	Color color[] = {BLACK, LIGHTGRAY, GRAY};
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			map->sprite[y][x] = (Sprite) {(Rectangle) {32*x, 32*y, 32, 32}, array[y][x] >= 2, color[array[y][x]], false, {}};
		}
	}
}

#endif