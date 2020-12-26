#include "includes/door.h"
#include <stdlib.h>

Door * Door_new(GameMap * map, Rectangle bounds, Rectangle useArea) {
	Door * door = malloc(sizeof(Door));
	// Add door to map
	for (int y = (int) bounds.y; y < (int) (bounds.y + bounds.height); y++) {
		for (int x = (int) bounds.x; x < (int) (bounds.x + bounds.width); x++) {
			map->sprite[y][x].color = RED;
			map->sprite[y][x].blocking = true;
		}
	}

	// REMOVE THAT FOR THE RELEASE
	// Add useArea overlay to map
	for (int y = (int) useArea.y; y < (int) (useArea.y + useArea.height); y++) {
		for (int x = (int) useArea.x; x < (int) (useArea.x + useArea.width); x++) {
			map->sprite[y][x].color = GREEN;
		}
	}

	door->bounds = bounds;
	door->useArea = (Rectangle) 
		{
			useArea.x * MAP_TEXTURE_SCALE, 
			useArea.y * MAP_TEXTURE_SCALE,
			useArea.width * MAP_TEXTURE_SCALE,
			useArea.height * MAP_TEXTURE_SCALE
		};
	door->open = false;
	return door;
}

bool Door_open(GameMap * map, Door * door, Vector2 vector) {
	if (CheckCollisionPointRec(vector, door->useArea)) {
		for (int y = (int) door->bounds.y; y < (int) (door->bounds.y + door->bounds.height); y++) {
			for (int x = (int) door->bounds.x; x < (int) (door->bounds.x + door->bounds.width); x++) {
				map->sprite[y][x].color = YELLOW;
				map->sprite[y][x].blocking = false;
			}
		}
		door->open = true;
		return true;
	}
	return false;
}