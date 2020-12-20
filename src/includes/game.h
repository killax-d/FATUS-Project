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
    GameMap map;
    Player player;
} Game;

Game* Game_new(Player player) {
    Game* g = malloc(sizeof(Game));
    g->state = -1;
    g->gameOver = -1;
    g->paused = -1;
    g->player = player;
    return g;
}

void Game_delete(Game g) {
    free(&g);
}

#endif