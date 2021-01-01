#ifndef GAMEITEMS_H
#define GAMEITEMS_H
#include "./game.h"
#include "./item.h"
#include "./inventory.h"

// Max items defined in game
#define MAX_ITEMS 12
// Item by id (0 to MAX_ITEMS-1)
#define ENGINE_KEY 0
#define MAGNET_CARD_BLUE 1
#define FLINT 2
#define FLINT_ACTIVE 3
#define NOTES 4
#define AMMONIUM_NITRATE 5
#define CELL_KEY 6
#define MAGNET_CARD_GREEN 7
#define MAGNET_CARD_RED 8
#define BOMB 9 
#define ROPE 10 

#define SOUND_COUNT 2

#define CRAFT_SOUND 0
#define BOMB_SOUND 1

typedef void (*useItem)(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]);

typedef struct GameItems {
	Item items[MAX_ITEMS];
	useItem use[MAX_ITEMS];
	Sound sounds[SOUND_COUNT];
} GameItems;


void usePrisonKey(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]);
void useMagnetCardBlue(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]);
void useMagnetCardGreen(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]);
void useMagnetCardRed(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]);
void useFlint(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]);
void useFlintActive(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]);
void useNotes(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]);
void craftBomb(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]);
void useBomb(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]);

GameItems * GameItems_new();

void GameItems_init(GameItems * gameItems);

void GameItems_control(Game * game, GameItems * gameItems);
#endif