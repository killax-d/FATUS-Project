#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "stdlib.h"
#include "./player.h"
#include "./map.h"
#include "./door.h"
#define COORDS_BUFFER_LENGTH 50
#define DOORS_COUNT 2

typedef struct Game {
	int state;
	/*
	-1 = Main Menu
	0 = In game
	1 = ended
	*/
    bool gameOver;
    bool paused;
    GameMap * map;
    Player * player;
    Door doors[DOORS_COUNT];
    char coordsText[COORDS_BUFFER_LENGTH];
} Game;

void Game_init(Game * game);

void Game_draw(Camera2D * camera, Game * game);

#endif