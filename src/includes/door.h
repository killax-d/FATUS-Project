#ifndef DOOR_H
#define DOOR_H
#include "raylib.h"
#include "map.h"

#define MAGNET_DOOR 0
#define PRISON_DOOR 1

typedef struct Door {
	Rectangle bounds;
	Rectangle useArea;
	Sound openSound;
	Sound closeSound;
	bool open;
} Door;

Door * Door_new(GameMap * map, Rectangle bounds, Rectangle useArea, Sound openSound, Sound closeSound);

bool Door_open(GameMap * map, Door * door, Vector2 vector, bool needCheck);

void Door_close(GameMap * map, Door * door, Vector2 vector, bool needCheck);

#endif