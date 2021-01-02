#include "includes/map.h"

void IntArrayToSpriteMap(GameMap * map, int array[MAP_HEIGHT][MAP_WIDTH], Assets * assets) {
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			map->sprite[y][x] = (Sprite) {(Rectangle) {MAP_TEXTURE_SCALE*x, MAP_TEXTURE_SCALE*y, MAP_TEXTURE_SCALE, MAP_TEXTURE_SCALE}, array[y][x] >= 2, assets->mapTextures[array[y][x]].id != 0, assets->mapTextures[array[y][x]]};
		}
	}
}

void Map_draw(GameMap * map) {
	for (int y = 0; y < MAP_HEIGHT; y++) 
        for (int x = 0; x < MAP_WIDTH; x++) {
        	if (map->sprite[y][x].hasTexture) {
        		DrawRectangleRec(map->sprite[y][x].rect, LIGHTGRAY);
        		DrawTexture(map->sprite[y][x].texture, map->sprite[y][x].rect.x, map->sprite[y][x].rect.y, WHITE);
        	}
        }
}