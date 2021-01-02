#include "includes/gameitemsentities.h"
#include "includes/env.h"

GameItemsEntities * GameItemsEntities_new(int id, Vector2 position, Item * item, float radiusPickup, bool visible) {
	GameItemsEntities * itemEntity = malloc(sizeof(GameItemsEntities));
	itemEntity->id = id;
	itemEntity->position = position;
	itemEntity->item = item;
	itemEntity->radiusPickup = radiusPickup;
	itemEntity->canPickup = false;
	itemEntity->visible = visible;
	return itemEntity;
}

void GameItemsEntities_update(Game * game, GameItemsEntities * gameItemsEntity) {
	if (!gameItemsEntity->visible) return;
	gameItemsEntity->canPickup = CheckCollisionPointCircle(game->player->position, gameItemsEntity->position, gameItemsEntity->radiusPickup);
}

void GameItemsEntities_control(Game * game, GameItemsEntities * gameItemsEntity) {
	if (!gameItemsEntity->visible) return;
	if (gameItemsEntity->canPickup)
		if(Inventory_addItem(game->player->inventory, *gameItemsEntity->item)) {
			gameItemsEntity->visible = false;
			PlaySound(gameItemsEntity->item->pickupSound);
		}
}

void GameItemsEntities_draw(GameItemsEntities * gameItemsEntity) {
	if (!gameItemsEntity->visible) return;
	// Debug radius
	if (DEBUG)
		DrawCircle(gameItemsEntity->position.x, gameItemsEntity->position.y, gameItemsEntity->radiusPickup, PINK);// (Color) { 255, 109, 194, 75 });  

	if(gameItemsEntity->canPickup) {
		// Can pickup background
		DrawCircle(gameItemsEntity->position.x, gameItemsEntity->position.y, (ITEM_TEXTURE_SCALE + 8) / 2, (Color) { 80, 80, 80, 125 });  
		DrawCircleLines(gameItemsEntity->position.x, gameItemsEntity->position.y, (ITEM_TEXTURE_SCALE + 8) / 2, (Color) { 0, 82, 172, 200 });  
	}

	// Draw item
	DrawTexture(gameItemsEntity->item->texture, gameItemsEntity->position.x - (ITEM_TEXTURE_SCALE/2), gameItemsEntity->position.y - (ITEM_TEXTURE_SCALE/2), WHITE);
}