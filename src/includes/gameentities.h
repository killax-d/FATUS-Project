#ifndef GAMEENTITIES_H
#define GAMEENTITIES_H
#include "./gameitemsentities.h"
#include "./gameitems.h"

#define MAX_ENTITIES_ITEMS 2
// ITEM ENTITY ID
#define ITEM_PRISON_KEY_ENTITY 0
#define ITEM_MAGNET_CARD_ENTITY 1

typedef struct GameEntities {
	GameItemsEntities itemsEntities[MAX_ENTITIES_ITEMS];
} GameEntities;

void GameEntities_init(GameEntities * gameEntities, GameItems * gameItems);

void GameEntities_update(Game * game, GameEntities * gameEntities);

void GameEntities_control(Game * game, GameEntities * gameEntities);

void GameEntities_draw(GameEntities * gameEntities);

#endif