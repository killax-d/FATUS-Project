#ifndef GAMEITEMS_H
#define GAMEITEMS_H
#include "./game.h"
#include "./item.h"

// Max items defined in game
#define MAX_ITEMS 10
// Item by id (0 to MAX_ITEMS-1)
#define PRISON_KEY 0
#define MAGNET_CARD 1

typedef void (*useItem)(Game * game);

typedef struct GameItems {
	Item items[MAX_ITEMS];
	useItem use[MAX_ITEMS];
} GameItems;


void usePrisonKey(Game * game);
void useMagnetCard(Game * game);

GameItems * GameItems_new();

void GameItems_init(GameItems * gameItems);

void GameItems_control(Game * game, GameItems * gameItems);
#endif