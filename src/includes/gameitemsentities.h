/**
 * @file gameitemsentities.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief GameItemsEntities is an entity that contain an item, player are able to pick them up in their inventory
 *
 * This file contains all declarations and function regarding GameItemsEntities
 *
 */

#ifndef GAMEITEMSENTITIES_H
#define GAMEITEMSENTITIES_H
#include "raylib.h"
#include "game.h"
#include "map.h"
#include "item.h"
#include "gameitems.h"
#include "inventory.h"

typedef struct GameItemsEntities {
	int id; /**< The ID of the Entity */
	Vector2 position; /**< The 2D position of the Entity */
	Item * item; /**< The Item that the Entity hold & give when pickup */
	float radiusPickup; /**< The Radius where the player are able to pickup the item */
	bool canPickup; /**< Player can pickup that Item ? */
	bool visible; /**< Is The Entity currently visible */
} GameItemsEntities;

/**
 * Return a pointer to a GameItemsEntities and intialize some variables
 * @param id The ID of the Entity
 * @param position The 2D position of the Entity
 * @param item The Item that the Entity hold & give when pickup
 * @param radiusPickup The Radius where the Player are able to pickup the item
 * @param visible The Visibility of the Entity in the game
 * @return A pointer to the GameItemsEntities
 */
GameItemsEntities * GameItemsEntities_new(int id, Vector2 position, Item * item, float radiusPickup, bool visible);

/**
 * Update Items entities
 * @param game The Game to retrieve data
 * @param gameItemsEntity The GameItemsEntities currently updating
 */
void GameItemsEntities_update(Game * game, GameItemsEntities * gameItemsEntity);

/**
 * Control Items entities (pressing key)
 * @param game The Game to retrieve data
 * @param gameItemsEntity The GameItemsEntities currently controling
 */
void GameItemsEntities_control(Game * game, GameItemsEntities * gameItemsEntity);

/**
 * Draw a GameItemsEntities with Raylib
 * @param gameItemsEntity The GameItemsEntities to draw
 */
void GameItemsEntities_draw(GameItemsEntities * gameItemsEntity);

#endif