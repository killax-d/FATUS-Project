#ifndef MINIMAP_H
#define MINIMAP_H
#include "raylib.h"
#include "game.h"

#define ZOOM_COUNT 3

typedef struct Minimap {
	int x;
	int y;
	int size;
	int scale;
	int zoom;
	int zooms_availables[ZOOM_COUNT];
} Minimap;

void Minimap_init(Minimap * minimap);
void Minimap_control(Minimap * minimap);
void Minimap_draw(Minimap * minimap, Game * game);

#endif