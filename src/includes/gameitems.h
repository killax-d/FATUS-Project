#ifndef GAMEITEMS_H
#define GAMEITEMS_H
#include "game.h"
#include "item.h"
#include "inventory.h"
#include "Objectivesnotes.h"

// Max items defined in game
#define MAX_ITEMS 12 /**< Defines the maximum amount of Item in the game */
// Item by id (0 to MAX_ITEMS-1)
#define ENGINE_KEY 0
#define MAGNET_CARD_BLUE 1
#define FLINT 2
#define FLINT_ACTIVE 3
#define NOTES 4
#define AMMONIUM_NITRATE 5
#define MAGNET_CARD_GREEN 6
#define MAGNET_CARD_YELLOW 7
#define MAGNET_CARD_RED 8
#define BOMB 9
#define ROPE 10 
#define USB_KEY 11 

/**
 * Define an Item action
 * @param game The Game to retrieve data
 * @param items The game Item List
 * @param assets The Assets manager to retrieve required assets
 * @param objectives The Objectives list
 */
typedef void (*useItem)(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);

typedef struct GameItems {
	Item * items[MAX_ITEMS]; /**< The Item List */
	useItem use[MAX_ITEMS]; /**< The Item useItem (action) List */
} GameItems;


/**
 * See useItem in gameitems.h
 */
void useEngineKey(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);
/**
 * See useItem in gameitems.h
 */
void useMagnetCardBlue(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);
/**
 * See useItem in gameitems.h
 */
void useMagnetCardGreen(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);
/**
 * See useItem in gameitems.h
 */
void useMagnetCardRed(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);
/**
 * See useItem in gameitems.h
 */
void useFlint(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);
/**
 * See useItem in gameitems.h
 */
void useFlintActive(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);
/**
 * See useItem in gameitems.h
 */
void useNotes(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);
/**
 * See useItem in gameitems.h
 */
void craftBomb(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);
/**
 * See useItem in gameitems.h
 */
void useBomb(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);
/**
 * See useItem in gameitems.h
 */
void useUSBKey(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives);


/**
 * Return a pointer to a GameItems
 * @return A pointer to a GameItems
 */
GameItems * GameItems_new();

/**
 * Initializes a GameItems structure
 * @param gameItems The gameItems to initalize
 * @param assets The Assets manager to retrieve required assets
 */
void GameItems_init(GameItems * gameItems, Assets * assets);

/**
 * Execute the action related to the GameItem
 * @param game The Game to retrieve data
 * @param gameItems The GameItems to control
 * @param assets The Assets manager to retrieve required assets
 * @param objectives The ObjectivesNotes to mark objectives as ended
 */
void GameItems_control(Game * game, GameItems * gameItems, Assets * assets, ObjectivesNotes * objectives);
#endif