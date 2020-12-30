#include "includes/gameentities.h"

void GameEntities_init(GameEntities * gameEntities, GameItems * gameItems) {
	gameEntities->itemsEntities[ITEM_PRISON_KEY_ENTITY] = *GameItemsEntities_new(ITEM_PRISON_KEY_ENTITY, (Vector2) {2900, 1500}, &gameItems->items[PRISON_KEY], 32.f, true);
	gameEntities->itemsEntities[ITEM_MAGNET_CARD_ENTITY] = *GameItemsEntities_new(ITEM_MAGNET_CARD_ENTITY, (Vector2) {2600, 1800}, &gameItems->items[MAGNET_CARD], 32.f, true);
}

void GameEntities_update(Game * game, GameEntities * gameEntities) {
	for (int i = 0; i < MAX_ENTITIES_ITEMS; i++) GameItemsEntities_update(game, &gameEntities->itemsEntities[i]);
}

void GameEntities_control(Game * game, GameEntities * gameEntities) {
	if (IsKeyDown(KEY_F))
		for (int i = 0; i < MAX_ENTITIES_ITEMS; i++) GameItemsEntities_control(game, &gameEntities->itemsEntities[i]);
}

void GameEntities_draw(GameEntities * gameEntities) {
	for (int i = 0; i < MAX_ENTITIES_ITEMS; i++) GameItemsEntities_draw(&gameEntities->itemsEntities[i]);
}
