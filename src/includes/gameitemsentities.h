#ifndef GAMEITEMSENTITIES_H
#define GAMEITEMSENTITIES_H
#include "./raylib.h"
#include "./game.h"
#include "./item.h"
#include "./gameitems.h"
#include "./inventory.h"

typedef struct GameItemsEntities {
	int id;
	Vector2 position;
	Item * item;
	float radiusPickup;
	bool canPickup;
	bool visible;
} GameItemsEntities;

GameItemsEntities * GameItemsEntities_new(int id, Vector2 position, Item * item, float radiusPickup, bool visible);

void GameItemsEntities_update(Game * game, GameItemsEntities * gameItemsEntity);

void GameItemsEntities_control(Game * game, GameItemsEntities * gameItemsEntity);

void GameItemsEntities_draw(GameItemsEntities * gameItemsEntity);

#endif