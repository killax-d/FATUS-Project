#include "includes/gameentities.h"

void GameEntities_init(GameEntities * gameEntities, GameItems * gameItems) {
	for (int i = 0; i < MAX_ENTITIES_ITEMS; i++) {
		gameEntities->itemsEntities[i].visible = false;
	}

	int r = rand() % 2; // rendre aléatoire le placement de la magnet card blue
	
	if (r == 1)
		gameEntities->itemsEntities[ITEM_MAGNET_CARD_BLUE_ENTITY] = *GameItemsEntities_new(ITEM_MAGNET_CARD_BLUE_ENTITY, (Vector2) {374, 2110}, &gameItems->items[MAGNET_CARD_BLUE], 32.f, true);
	else
		gameEntities->itemsEntities[ITEM_MAGNET_CARD_BLUE_ENTITY] = *GameItemsEntities_new(ITEM_MAGNET_CARD_BLUE_ENTITY, (Vector2) {408, 1068}, &gameItems->items[MAGNET_CARD_BLUE], 32.f, true);

	gameEntities->itemsEntities[ITEM_ENGINE_KEY_ENTITY] = *GameItemsEntities_new(ITEM_ENGINE_KEY_ENTITY, (Vector2) {2900, 1500}, &gameItems->items[ENGINE_KEY], 32.f, true);
	gameEntities->itemsEntities[ITEM_ROPE_ENTITY] = *GameItemsEntities_new(ITEM_ROPE_ENTITY, (Vector2) {2290, 2617}, &gameItems->items[ROPE], 32.f, true);	
	gameEntities->itemsEntities[ITEM_MAGNET_CARD_GREEN_ENTITY] = *GameItemsEntities_new(ITEM_MAGNET_CARD_GREEN_ENTITY, (Vector2) {4035, 2335}, &gameItems->items[MAGNET_CARD_GREEN], 32.f, true);
	gameEntities->itemsEntities[ITEM_MAGNET_CARD_RED_ENTITY] = *GameItemsEntities_new(ITEM_MAGNET_CARD_RED_ENTITY, (Vector2) {2867, 541}, &gameItems->items[MAGNET_CARD_RED], 32.f, true);
    gameEntities->itemsEntities[ITEM_AMMONIUM_NITRATE_ENTITY] = *GameItemsEntities_new(ITEM_AMMONIUM_NITRATE_ENTITY, (Vector2) {2413, 2863}, &gameItems->items[AMMONIUM_NITRATE], 32.f, true);
	gameEntities->itemsEntities[ITEM_USB_KEY_ENTITY] = *GameItemsEntities_new(ITEM_USB_KEY_ENTITY, (Vector2) {4073, 775}, &gameItems->items[USB_KEY], 32.f, true);
    gameEntities->itemsEntities[ITEM_MAGNET_CARD_GREEN_ENTITY_2] = *GameItemsEntities_new(ITEM_MAGNET_CARD_GREEN_ENTITY_2, (Vector2) {3960, 1984}, &gameItems->items[MAGNET_CARD_GREEN], 32.f, true);
}

void GameEntities_update(Game * game, GameEntities * gameEntities) {
	for (int i = 0; i < MAX_ENTITIES_ITEMS; i++) GameItemsEntities_update(game, &gameEntities->itemsEntities[i]);
}

void GameEntities_control(Game * game, GameEntities * gameEntities) {
	if (IsKeyDown(KEY_F))
		for (int i = 0; i < MAX_ENTITIES_ITEMS; i++) GameItemsEntities_control(game, &gameEntities->itemsEntities[i]);
}

void GameEntities_draw(GameEntities * gameEntities) {
	for (int i = 0; i < MAX_ENTITIES_ITEMS; i++) if (gameEntities->itemsEntities[i].visible) GameItemsEntities_draw(&gameEntities->itemsEntities[i]);
}
