#include "includes/inventory.h"

Inventory * Inventory_new() {
	Inventory * inv = malloc(sizeof(Inventory));
	inv->selected = 0;
	inv->nbItems = 0;
	for(int i = 0; i < INVENTORY_SIZE; i++)
		inv->items[i].name = 0x0;
	return inv;
}

void Inventory_draw(int x, int y, Inventory * inv) {
	for (int i = 0; i < INVENTORY_SIZE; i++) {
		// Draw case
		DrawRectangle(x + ((48+4) * i), y, 48, 48, (Color) {65,105,225,200});
		// Draw selected rectangle
		if (i == inv->selected) {
			if (inv->items[i].name != 0x0) DrawText(inv->selectedText, x, y + 48 + 2, 10, WHITE);
			DrawRectangleLinesEx((Rectangle) {x + ((48+4) * i), y, 48, 48}, 2, (Color) {255,255,255,200});
			DrawRectangleRec((Rectangle) {x + ((48+4) * i), y, 48, 48}, (Color) {255,255,255,50});
		}
		// Draw item
		if (inv->items[i].hasTexture) Item_draw(x + ((48+4) * i), y, inv->items[i]);
	}
}