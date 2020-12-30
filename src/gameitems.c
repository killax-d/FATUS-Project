#include "includes/gameitems.h"
#include "includes/env.h"

// Prison key function
void usePrisonKey(Game * game, Item items[MAX_ITEMS]) {
    logger(LOG_DEBUG, "Using prison key!", "");
    if (Door_open(game->map, &game->doors[PRISON_DOOR], game->player->position))
        logger(LOG_DEBUG, "Prison door is open!", "");
        //game->player->inventory->items[game->player->inventory->selected] = (Item) {0};
    else
        Door_close(game->map, &game->doors[PRISON_DOOR]);
}

// Magnet card function
void useMagnetCard(Game * game, Item items[MAX_ITEMS]) {
    logger(LOG_DEBUG, "Using magnet card!", "");
    if (Door_open(game->map, &game->doors[MAGNET_DOOR], game->player->position))
        Inventory_removeItem(game->player->inventory, MAGNET_CARD);
}

// Flint inactive function
void useFlint(Game * game, Item items[MAX_ITEMS]) {
    logger(LOG_DEBUG, "Using inactive flint!", "");
    game->player->inventory->items[game->player->inventory->selected] = items[FLINT_ACTIVE];
}

// Flint inactive function
void useFlintActive(Game * game, Item items[MAX_ITEMS]) {
    logger(LOG_DEBUG, "Using active flint!", "");
    game->player->inventory->items[game->player->inventory->selected] = items[FLINT];
}

// Notes function
void useNotes(Game * game, Item items[MAX_ITEMS]) {
    logger(LOG_DEBUG, "Using Notes!", "");
    if (Inventory_contain(game->player->inventory, FLINT_ACTIVE))
    	game->player->inventory->items[game->player->inventory->selected] = items[PAPER_ASH];
    else
    	logger(LOG_DEBUG, "You can't do that: Flint is not active!", "");
}

// Paper ash function
void usePaperAsh(Game * game, Item items[MAX_ITEMS]) {
    logger(LOG_DEBUG, "Using Paper Ash!", "");
}



GameItems * GameItems_new() {
	GameItems * gi = malloc(sizeof(GameItems));
    return gi;
}

void GameItems_init(GameItems * gameItems) {
    Sound item_pickup_sound = LoadSound("assets/item_pickup.mp3");
    Sound key_pickup_sound = LoadSound("assets/key_pickup.mp3");

	// SIGNATURE :
    // Item_new(int id, char * name, bool hasTexture, Texture2D texture)
    gameItems->items[PRISON_KEY] = *Item_new(PRISON_KEY, "Prison Key", true, LoadTexture("assets/prison_key.png"), key_pickup_sound);
    gameItems->use[PRISON_KEY] = usePrisonKey;

    gameItems->items[MAGNET_CARD] = *Item_new(MAGNET_CARD, "Magnet Card", true, LoadTexture("assets/magnet_card.png"), item_pickup_sound);
    gameItems->use[MAGNET_CARD] = useMagnetCard;

    gameItems->items[FLINT] = *Item_new(FLINT, "Flint", true, LoadTexture("assets/flint.png"), item_pickup_sound);
    gameItems->use[FLINT] = useFlint;

    gameItems->items[FLINT_ACTIVE] = *Item_new(FLINT_ACTIVE, "Flint", true, LoadTexture("assets/flint_active.png"), item_pickup_sound);
    gameItems->use[FLINT_ACTIVE] = useFlintActive;

    gameItems->items[NOTES] = *Item_new(NOTES, "Notes", true, LoadTexture("assets/instructions.png"), item_pickup_sound);
    gameItems->use[NOTES] = useNotes;

    gameItems->items[PAPER_ASH] = *Item_new(PAPER_ASH, "Paper Ash", true, LoadTexture("assets/paper_ash.png"), item_pickup_sound);
    gameItems->use[PAPER_ASH] = usePaperAsh;
}

void GameItems_control(Game * game, GameItems * gameItems) {
	Item item = game->player->inventory->items[game->player->inventory->selected];
	if (IsKeyPressed(KEY_E) && item.name != 0x0) gameItems->use[item.id](game, gameItems->items);
}
