#include "includes/item.h"

Item * Item_new(int id, char * name, bool hasTexture, Texture2D texture, Sound pickupSound) {
	Item * item = malloc(sizeof(Item));
	item->id = id;
	item->name = name;
	item->hasTexture = hasTexture;
	item->texture = texture;
	item->pickupSound = pickupSound;
	return item;
}

void Item_draw(int x, int y, Item * item) {
    if (item && item->hasTexture) DrawTexture(item->texture, x+4, y+4, WHITE);
    else DrawRectangle(x+4, y+4, ITEM_TEXTURE_SCALE, ITEM_TEXTURE_SCALE, PINK);
}