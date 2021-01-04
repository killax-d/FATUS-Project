#include "includes/gameentities.h"

void GameEntities_init(GameEntities * gameEntities, GameItems * gameItems, Assets * assets) {
	for (int i = 0; i < MAX_ENTITIES_ITEMS; i++)
		gameEntities->itemsEntities[i] = 0x0;
	for (int i = 0; i < MAX_ENTITIES_IA; i++)
		gameEntities->iaEntities[i] = 0x0;


	int r = rand() % 2; // rendre aléatoire le placement de la magnet card blue
	
	if (r == 1)
		gameEntities->itemsEntities[ITEM_MAGNET_CARD_BLUE_ENTITY] = GameItemsEntities_new(ITEM_MAGNET_CARD_BLUE_ENTITY, (Vector2) {374, 2110}, gameItems->items[MAGNET_CARD_BLUE], 32.f, true);
	else
		gameEntities->itemsEntities[ITEM_MAGNET_CARD_BLUE_ENTITY] = GameItemsEntities_new(ITEM_MAGNET_CARD_BLUE_ENTITY, (Vector2) {408, 1068}, gameItems->items[MAGNET_CARD_BLUE], 32.f, true);

	gameEntities->itemsEntities[ITEM_ENGINE_KEY_ENTITY] = GameItemsEntities_new(ITEM_ENGINE_KEY_ENTITY, (Vector2) {2900, 1500}, gameItems->items[ENGINE_KEY], 32.f, true);
	gameEntities->itemsEntities[ITEM_ROPE_ENTITY] = GameItemsEntities_new(ITEM_ROPE_ENTITY, (Vector2) {2290, 2617}, gameItems->items[ROPE], 32.f, true);	
	gameEntities->itemsEntities[ITEM_MAGNET_CARD_GREEN_ENTITY] = GameItemsEntities_new(ITEM_MAGNET_CARD_GREEN_ENTITY, (Vector2) {4035, 2335}, gameItems->items[MAGNET_CARD_GREEN], 32.f, true);
	gameEntities->itemsEntities[ITEM_MAGNET_CARD_RED_ENTITY] = GameItemsEntities_new(ITEM_MAGNET_CARD_RED_ENTITY, (Vector2) {2867, 541}, gameItems->items[MAGNET_CARD_RED], 32.f, true);
    gameEntities->itemsEntities[ITEM_AMMONIUM_NITRATE_ENTITY] = GameItemsEntities_new(ITEM_AMMONIUM_NITRATE_ENTITY, (Vector2) {2413, 2863}, gameItems->items[AMMONIUM_NITRATE], 32.f, true);
	gameEntities->itemsEntities[ITEM_USB_KEY_ENTITY] = GameItemsEntities_new(ITEM_USB_KEY_ENTITY, (Vector2) {4073, 775}, gameItems->items[USB_KEY], 32.f, true);
    gameEntities->itemsEntities[ITEM_MAGNET_CARD_YELLOW_ENTITY] = GameItemsEntities_new(ITEM_MAGNET_CARD_YELLOW_ENTITY, (Vector2) {3960, 1984}, gameItems->items[MAGNET_CARD_YELLOW], 32.f, true);

	gameEntities->iaEntities[0] = GameIAEntities_new(0, assets->textures[ALIEN_TEXTURE], (Vector2) {4049, 2400}, (Vector2) {150.f, 150.f}, 160.f, true);
	gameEntities->iaEntities[1] = GameIAEntities_new(1, assets->textures[ALIEN_TEXTURE], (Vector2) {4021, 1966}, (Vector2) {150.f, 150.f}, 160.f, true);
	gameEntities->iaEntities[2] = GameIAEntities_new(2, assets->textures[ALIEN_TEXTURE], (Vector2) {2855, 1347}, (Vector2) {150.f, 150.f}, 160.f, true);
    gameEntities->iaEntities[3] = GameIAEntities_new(3, assets->textures[ALIEN_TEXTURE], (Vector2) {1530, 1601}, (Vector2) {150.f, 150.f}, 160.f, true);
	// gameEntities->iaEntities[4] = *GameIAEntities_new(4, assets->textures[ALIEN_TEXTURE], (Vector2) {2997, 723}, (Vector2) {150.f, 150.f}, 160.f, true);
	gameEntities->iaEntities[4] = GameIAEntities_new(4, assets->textures[ALIEN_TEXTURE], (Vector2) {2870, 435}, (Vector2) {150.f, 150.f}, 160.f, true);
	gameEntities->iaEntities[5] = GameIAEntities_new(5, assets->textures[ALIEN_TEXTURE], (Vector2) {3852, 790}, (Vector2) {150.f, 150.f}, 160.f, true);
	gameEntities->iaEntities[6] = GameIAEntities_new(6, assets->textures[ALIEN_TEXTURE], (Vector2) {522, 1080}, (Vector2) {150.f, 150.f}, 160.f, true);
	gameEntities->iaEntities[7] = GameIAEntities_new(7, assets->textures[ALIEN_TEXTURE], (Vector2) {540, 2118}, (Vector2) {150.f, 150.f}, 160.f, true);
	gameEntities->iaEntities[8] = GameIAEntities_new(8, assets->textures[ALIEN_TEXTURE], (Vector2) {4640, 1586}, (Vector2) {150.f, 150.f}, 160.f, true);
	gameEntities->iaEntities[9] = GameIAEntities_new(9, assets->textures[ALIEN_TEXTURE], (Vector2) {1999, 1747}, (Vector2) {150.f, 150.f}, 160.f, true);
	gameEntities->iaEntities[10] = GameIAEntities_new(10, assets->textures[ALIEN_TEXTURE], (Vector2) {4528, 1973}, (Vector2) {150.f, 150.f}, 160.f, true);
}

void GameEntities_update(Game * game, GameEntities * gameEntities, float delta) {
	for (int i = 0; i < MAX_ENTITIES_ITEMS; i++) GameItemsEntities_update(game, gameEntities->itemsEntities[i]);
	for (int i = 0; i < MAX_ENTITIES_IA; i++) GameIAEntities_update(game, gameEntities->iaEntities[i], delta);
}

void GameEntities_control(Game * game, GameEntities * gameEntities) {
	if (IsKeyDown(KEY_F)) 
		for (int i = 0; i < MAX_ENTITIES_ITEMS; i++) GameItemsEntities_control(game, gameEntities->itemsEntities[i]);
	for (int i = 0; i < MAX_ENTITIES_IA; i++) GameIAEntities_control(game, gameEntities->iaEntities[i]);
}

void GameEntities_draw(GameEntities * gameEntities) {
	for (int i = 0; i < MAX_ENTITIES_ITEMS; i++) if (gameEntities->itemsEntities[i] && gameEntities->itemsEntities[i]->visible) GameItemsEntities_draw(gameEntities->itemsEntities[i]);
	for (int i = 0; i < MAX_ENTITIES_IA; i++) if (gameEntities->iaEntities[i] && gameEntities->iaEntities[i]->visible) GameIAEntities_draw(gameEntities->iaEntities[i]);
}
