#include "includes/door.h"
#include "includes/env.h"
#include <stdlib.h>

Door * Door_new(GameMap * map, Rectangle bounds, Rectangle useArea, Sound openSound, Sound closeSound, Texture2D doorCloseTexture, Texture2D doorOpenTexture, Texture2D doorUseAreaTexture) {
	Door * door = malloc(sizeof(Door));
	door->doorCloseTexture = doorCloseTexture;
	door->doorOpenTexture = doorOpenTexture;
	door->doorUseAreaTexture = doorUseAreaTexture;
	
	// Add useArea overlay to map (only DEBUG mode)
	if (DEBUG)
		for (int y = (int) useArea.y; y < (int) (useArea.y + useArea.height); y++) {
			for (int x = (int) useArea.x; x < (int) (useArea.x + useArea.width); x++) {
				map->sprite[y][x]->hasTexture = true;
				map->sprite[y][x]->texture = door->doorUseAreaTexture;
			}
		}

	// Add door to map
	for (int y = (int) bounds.y; y < (int) (bounds.y + bounds.height); y++) {
		for (int x = (int) bounds.x; x < (int) (bounds.x + bounds.width); x++) {
			map->sprite[y][x]->hasTexture = true;
			map->sprite[y][x]->texture = door->doorCloseTexture;
			map->sprite[y][x]->blocking = true;
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
	door->openSound = openSound;
	door->closeSound = closeSound;
	door->open = false;
	return door;
}

bool Door_open(GameMap * map, Door * door, Vector2 vector, bool needCheck) {
	if (door->open) return true;
	if (!needCheck | CheckCollisionPointRec(vector, door->useArea)) {
		for (int y = (int) door->bounds.y; y < (int) (door->bounds.y + door->bounds.height); y++) {
			for (int x = (int) door->bounds.x; x < (int) (door->bounds.x + door->bounds.width); x++) {
				map->sprite[y][x]->texture = door->doorOpenTexture;
				map->sprite[y][x]->blocking = false;
			}
		}
		door->open = true;
		PlaySound(door->openSound);
		return true;
	}
	return false;
}

void Door_close(GameMap * map, Door * door, Vector2 vector, bool needCheck) {
	if (!door->open) return;
	if (!needCheck | CheckCollisionPointRec(vector, door->useArea)) {
		for (int y = (int) door->bounds.y; y < (int) (door->bounds.y + door->bounds.height); y++) {
			for (int x = (int) door->bounds.x; x < (int) (door->bounds.x + door->bounds.width); x++) {
				map->sprite[y][x]->texture = door->doorCloseTexture;
				map->sprite[y][x]->blocking = true;
			}
		}
		door->open = false;
		PlaySound(door->closeSound);
	}
}