#ifndef GAMEENTITIES_H
#define GAMEENTITIES_H
#include "./gameitemsentities.h"
#include "./gameitems.h"

#define MAX_ENTITIES_ITEMS 10
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
#define ITEM_MAGNET_CARD_GREEN_ENTITY_2 9


typedef struct GameEntities {
	GameItemsEntities itemsEntities[MAX_ENTITIES_ITEMS];
} GameEntities;

void GameEntities_init(GameEntities * gameEntities, GameItems * gameItems);

void GameEntities_update(Game * game, GameEntities * gameEntities);

void GameEntities_control(Game * game, GameEntities * gameEntities);

void GameEntities_draw(GameEntities * gameEntities);

#endif