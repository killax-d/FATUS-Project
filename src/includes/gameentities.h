/**
 * @file gameentities.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief GameEntities contains all the entities defined in game (Items Entities & IA Entities)
 *
 * This file contains all declarations and function regarding GameEntities
 *
 */

#ifndef GAMEENTITIES_H
#define GAMEENTITIES_H
#include "gameitemsentities.h"
#include "gameiaentities.h"
#include "gameitems.h"
#include "assets.h"

#define MAX_ENTITIES_ITEMS 10 /**< The number of GameItemsEntities present in game */
// ITEM ENTITY ID
#define ITEM_ENGINE_KEY_ENTITY 0
#define ITEM_MAGNET_CARD_BLUE_ENTITY 1
#define ITEM_MAGNET_CARD_GREEN_ENTITY 2
#define ITEM_MAGNET_CARD_RED_ENTITY 3
#define ITEM_CELL_KEY_ENTITY 4
#define ITEM_BOMB_ENTITY 5
#define ITEM_ROPE_ENTITY 6
#define ITEM_AMMONIUM_NITRATE_ENTITY 7
#define ITEM_USB_KEY_ENTITY 8
#define ITEM_MAGNET_CARD_YELLOW_ENTITY 9


#define MAX_ENTITIES_IA 11 /**< The number of GameIAEntities present in game */


typedef struct GameEntities {
	GameItemsEntities * itemsEntities[MAX_ENTITIES_ITEMS]; /**< The GameItemsEntities List */
	GameIAEntities * iaEntities[MAX_ENTITIES_IA]; /**< The GameIAEntities List */
} GameEntities;

/**
 * Initialize some variables of a GameEntities
 * @param gameEntities The GameEntities to initialize
 * @param gameItems All the Item present in Game
 * @param assets The Assets manager to retrieve required assets
 */
void GameEntities_init(GameEntities * gameEntities, GameItems * gameItems, Assets * assets);

/**
 * Update all the entities present in the Game
 * @param game The Game to retrieve data
 * @param gameEntities The GameEntities to update
 * @param delta The delta time between the previous frame and the current
 */
void GameEntities_update(Game * game, GameEntities * gameEntities, float delta);

/**
 * Control all the entities present in the Game
 * @param game The Game to retrieve data
 * @param gameEntities The GameEntities to update
 */
void GameEntities_control(Game * game, GameEntities * gameEntities);

/**
 * Draw all GameEntities with Raylib
 * @param gameEntities The GameEntities to draw
 */
void GameEntities_draw(GameEntities * gameEntities);

#endif