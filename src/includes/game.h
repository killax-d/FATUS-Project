#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "stdlib.h"
#include "./player.h"
#include "./map.h"


typedef struct Game {
	int state;
	/*
	-1 = Main Menu
	0 = In game
	1 = ended
	*/
    int gameOver;
    int paused;
    GameMap * map;
    Player * player;
} Game;

void Game_init(Game * game);

#endif