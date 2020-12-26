#ifndef GAMEITEMS_H
#define GAMEITEMS_H
#include "./game.h"
#include "./item.h"

// Max items defined in game
#define MAX_ITEMS 10
// Item by id (0 to MAX_ITEMS-1)
#define PRISON_KEY 0
#define MAGNET_CARD 1
#define FLINT 2
#define FLINT_ACTIVE 3
#define NOTES 4
#define PAPER_ASH 5

typedef void (*useItem)(Game * game, Item items[MAX_ITEMS]);

typedef struct GameItems {
	Item items[MAX_ITEMS];
	useItem use[MAX_ITEMS];
} GameItems;


void usePrisonKey(Game * game, Item items[MAX_ITEMS]);
void useMagnetCard(Game * game, Item items[MAX_ITEMS]);
void useFlint(Game * game, Item items[MAX_ITEMS]);
void useFlintActive(Game * game, Item items[MAX_ITEMS]);
void useNotes(Game * game, Item items[MAX_ITEMS]);

GameItems * GameItems_new();

void GameItems_init(GameItems * gameItems);

void GameItems_control(Game * game, GameItems * gameItems);
#endif