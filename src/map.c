#include "includes/map.h"

void IntArrayToSpriteMap(GameMap * map, int array[MAP_HEIGHT][MAP_WIDTH]) {
	Color color[] = {BLACK, LIGHTGRAY, GREEN, GRAY, RED};
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			map->sprite[y][x] = (Sprite) {(Rectangle) {MAP_TEXTURE_SCALE*x, MAP_TEXTURE_SCALE*y, MAP_TEXTURE_SCALE, MAP_TEXTURE_SCALE}, array[y][x] >= 3, color[array[y][x]], false, {}};
		}
	}
}

void Map_draw(GameMap * map) {
	for (int y = 0; y < MAP_HEIGHT; y++) 
        for (int x = 0; x < MAP_WIDTH; x++)
            DrawRectangleRec(map->sprite[y][x].rect, map->sprite[y][x].color);
}