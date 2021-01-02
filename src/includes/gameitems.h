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
#define USB_KEY 11 

typedef void (*useItem)(Game * game, Item items[MAX_ITEMS], Assets * assets);

typedef struct GameItems {
	Item items[MAX_ITEMS];
	useItem use[MAX_ITEMS];
} GameItems;


void useEngineKey(Game * game, Item items[MAX_ITEMS], Assets * assets);
void useMagnetCardBlue(Game * game, Item items[MAX_ITEMS], Assets * assets);
void useMagnetCardGreen(Game * game, Item items[MAX_ITEMS], Assets * assets);
void useMagnetCardRed(Game * game, Item items[MAX_ITEMS], Assets * assets);
void useFlint(Game * game, Item items[MAX_ITEMS], Assets * assets);
void useFlintActive(Game * game, Item items[MAX_ITEMS], Assets * assets);
void useNotes(Game * game, Item items[MAX_ITEMS], Assets * assets);
void craftBomb(Game * game, Item items[MAX_ITEMS], Assets * assets);
void useBomb(Game * game, Item items[MAX_ITEMS], Assets * assets);
void useUSBKey(Game * game, Item items[MAX_ITEMS], Assets * assets);

GameItems * GameItems_new();

void GameItems_init(GameItems * gameItems, Assets * assets);

void GameItems_control(Game * game, GameItems * gameItems, Assets * assets);
#endif