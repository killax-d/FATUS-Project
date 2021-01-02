#ifndef DOOR_H
#define DOOR_H
#include "raylib.h"
#include "map.h"

#define MAGNET_DOOR 0
#define MOTOR1_DOOR 1
#define CELL_DOOR 2
#define MAGNET_DOOR1 3
#define MAGNET_DOOR2 4
#define MAGNET_DOOR3 5
#define MOTOR2_DOOR 6

typedef struct Door {
	Rectangle bounds;
	Rectangle useArea;
	Sound openSound;
	Sound closeSound;
	Texture2D doorCloseTexture;
	Texture2D doorOpenTexture;
	Texture2D doorUseAreaTexture;
	bool open;
} Door;

Door * Door_new(GameMap * map, Rectangle bounds, Rectangle useArea, Sound openSound, Sound closeSound, Texture2D doorCloseTexture, Texture2D doorOpenTexture, Texture2D doorUseAreaTexture);

bool Door_open(GameMap * map, Door * door, Vector2 vector, bool needCheck);

void Door_close(GameMap * map, Door * door, Vector2 vector, bool needCheck);

#endif