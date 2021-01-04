/**
 * @file game.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Game representation
 *
 * This file contains all declarations and function regarding Game
 *
 */

#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "stdlib.h"
#include "player.h"
#include "map.h"
#include "door.h"
#include "assets.h"

#define COORDS_BUFFER_LENGTH 50 /**< Size of the char for coordinates in DEBUG mode */
#define DOORS_COUNT 7 /**< Number of Doors in game */

/**
 * Struct to represent a Game
 */
typedef struct Game {
	int state;/**< The State (-1 is MainMenu, 0 is InGame, 1 is Ended) */
    bool gameOver;/**< The game is over ? check if the player win or loose */
    bool paused;/**< The game is paused ? */
    GameMap * map;/**< The map of the game */
    Player * player;/**< The player of the game */
    Door * doors[DOORS_COUNT];/**< The doors availables in game */
    char coordsText[COORDS_BUFFER_LENGTH];/**< The coordinates of player in a string (used in DEBUG mode) */
} Game;

/**
 * Initialize some variables of a Game
 * @param game The Game to intialize
 * @param assets The Assets manager to retrieve required assets
 */
void Game_init(Game * game, Assets * assets);

/**
 * Draw a Game with Raylib
 * @param game The Game to draw
 */
void Game_draw(Game * game);

/**
 * End a Game (if player life left is 0, it's GameOver)
 * @param game The Game to draw
 */
void Game_end(Game * game);

#endif