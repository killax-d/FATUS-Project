#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "stdlib.h"
#include "./player.h"

typedef struct Game {
    int gameOver;
    int paused;
    Player player;
} Game;

Game* Game_new(Player player) {
    Game* g = malloc(sizeof(Game));
    g->gameOver = -1;
    g->paused = -1;
    g->player = player;
    return g;
}

void Game_delete(Game g) {
    free(&g);
}

#endif