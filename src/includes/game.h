#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "stdlib.h"
#include "./player.h"
#include "./map.h"
#define COORDS_BUFFER_LENGTH 30

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
} Game;

void Game_init(Game * game);

void Game_draw(Camera2D * camera, Game * game, char coords[COORDS_BUFFER_LENGTH]);

#endif