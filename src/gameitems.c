#include "includes/gameitems.h"

// Prison key function
void usePrisonKey(Game * game) {
    logger(LOG_INFO, "Using prison key!", "");
}

// Magnet card function
void useMagnetCard(Game * game) {
    logger(LOG_INFO, "Using magnet card!", "");
}


GameItems * GameItems_new() {
	GameItems * gi = malloc(sizeof(GameItems));
    return gi;
}

void GameItems_init(GameItems * gameItems) {
	// SIGNATURE :
    // Item_new(int id, char * name, bool hasTexture, Texture2D texture)
    gameItems->items[PRISON_KEY] = *Item_new(PRISON_KEY, "Prison Key", true, LoadTexture("assets/prison_key.png"));
    gameItems->use[PRISON_KEY] = usePrisonKey;

    gameItems->items[MAGNET_CARD] = *Item_new(MAGNET_CARD, "Magnet Card", true, LoadTexture("assets/magnet_card.png"));
    gameItems->use[MAGNET_CARD] = useMagnetCard;
}

void GameItems_control(Game * game, GameItems * gameItems) {
	Item item = game->player->inventory->items[game->player->inventory->selected];
	if (IsKeyPressed(KEY_E) && item.name != 0x0) gameItems->use[item.id](game);
}
