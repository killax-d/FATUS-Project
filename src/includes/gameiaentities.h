/**
 * @file gameiaentities.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief GameIAEntities are the monsters with pathfinding implementation, they attack player if he's close enough
 *
 * This file contains all declarations and function regarding GameIAEntities
 *
 */

#ifndef GAMEIAENTITIES_H
#define GAMEIAENTITIES_H
#include "raylib.h"
#include "game.h"
#include "map.h"
#include "pathfinding.h"

#define PATH_BUFFER_LENGTH 20 /**< The MAX Path length of the Entity pathfinding.h */
#define CLOCK_MAX 60 /**< The Clock to search a new Path with pathfinding.h */
#define ENITTY_TEXTURE_SCALE 64 /**< The Entity texture scale */

typedef struct GameIAEntities {
	int id; /**< The ID of the Entity */
	Texture2D texture; /**< The ID of the Entity */
	Vector2 position; /**< The current position in 2D of the Entity */
	Vector2 speed; /**< The speed in 2D of the Entity */
	float radiusZone; /**< The radius Zone where the Entity become active if Player is inside */
	bool active; /**< The ID of the Entity */
	int path[PATH_BUFFER_LENGTH][2]; /**< The current Entity Path filled by pathfinding.h */
	int pathIndex; /**< The current position in Path where the Entity is navigating */
	int clock; /**< The Clock to make a cooldown on IA Path Searching */
	bool visible; /**< Is the Entity currently visible in game ? */
} GameIAEntities;

/**
 * Return a pointer to a GameIAEntities and intialize some variables
 * @param id The ID of the Entity
 * @param texture The texture of the Entity
 * @param position The 2D position of the Entity
 * @param speed The 2D speed of the Entity
 * @param radiusZone The Radius where the entity start to chase Player
 * @param visible The Visibility of the Entity in the game
 * @return A pointer to the GameIAEntities
 */
GameIAEntities * GameIAEntities_new(int id, Texture2D texture, Vector2 position, Vector2 speed, float radiusZone, bool visible);

/**
 * Reset the path of the Entity by setting all nodes to [-1, -1]
 * @param gameIAEntity The GameItemsEntities to reset
 */
void GameIAEntities_resetPath(GameIAEntities * gameIAEntity);

/**
 * Update the Game IA Entity
 * @param game The Game to retrieve data
 * @param gameIAEntity The GameItemsEntities currently updating
 * @param delta The delta time between the previous frame and the current
 */
void GameIAEntities_update(Game * game, GameIAEntities * gameIAEntity, float delta);

/**
 * Control the Game IA Entity
 * @param game The Game to retrieve data
 * @param gameIAEntity The GameItemsEntities currently controling
 */
void GameIAEntities_control(Game * game, GameIAEntities * gameIAEntity);

/**
 * Draw a GameItemsEntities with Raylib
 * @param gameIAEntity The GameIAEntities to draw
 */
void GameIAEntities_draw(GameIAEntities * gameIAEntity);

#endif