#include "includes/map.h"

void IntArrayToSpriteMap(GameMap * map, int array[MAP_HEIGHT][MAP_WIDTH], Assets * assets) {
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			map->sprite[y][x] = Sprite_new((Rectangle) {MAP_TEXTURE_SCALE*x, MAP_TEXTURE_SCALE*y, MAP_TEXTURE_SCALE, MAP_TEXTURE_SCALE}, array[y][x] >= 2, assets->mapTextures[array[y][x]].id != 0, assets->mapTextures[array[y][x]]);
		}
	}
}

void Map_draw(GameMap * map, int position[2]) {
	// Calcul for the height
	int sideBlocsHeight = (GetScreenHeight())/MAP_TEXTURE_SCALE;

	int startY = position[1] - sideBlocsHeight-2;
	int endY = position[1] + sideBlocsHeight+2;
	startY = startY < 0 ? 0 : startY;
	endY = endY >= MAP_HEIGHT ? MAP_HEIGHT : endY;

	// Calcul for the width
	int sideBlocsWidth = (GetScreenWidth())/MAP_TEXTURE_SCALE;

	int startX = position[0] - sideBlocsWidth-2;
	int endX = position[0] + sideBlocsWidth+2;
	startX = startX < 0 ? 0 : startX;
	endX = endX >= MAP_WIDTH ? MAP_WIDTH : endX;

	for (int y = startY; y < endY; y++) 
        for (int x = startX; x < endX; x++)
        	if (map->sprite[y][x] && map->sprite[y][x]->hasTexture) {
        		DrawRectangleRec(map->sprite[y][x]->rect, LIGHTGRAY);
        		DrawTexture(map->sprite[y][x]->texture, map->sprite[y][x]->rect.x, map->sprite[y][x]->rect.y, WHITE);
        	}
}