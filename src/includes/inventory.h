#ifndef INVENTORY_H
#define INVENTORY_H
#include "raylib.h"
#include "stdlib.h"
#include "./item.h"
#define INVENTORY_SIZE 9
#define TEXT_SELECTED_ITEM_BUFFER_LENGTH 50

typedef struct Inventory {
	Item items[INVENTORY_SIZE];
	int selected;
	int nbItems;
	char * notes;
	char selectedText[TEXT_SELECTED_ITEM_BUFFER_LENGTH];
} Inventory;

Inventory * Inventory_new();

void Inventory_draw(int x, int y, Inventory * inv);

void Inventory_draw(int x, int y, Inventory inv) {
	for (int i = 0; i < 9; i++) {
		// Draw case
        DrawRectangle(x + ((48+4) * i), y, 48, 48, (Color) {65,105,225,200});
        // Draw selected rectangle
        if (i == inv.selected) DrawRectangleLinesEx((Rectangle) {x + ((48+4) * i), y, 48, 48}, 2, (Color) {255,255,255,200});
        // Draw item
		Item_draw(x + ((48+4) * i), y, inv.items[i]);
	}
}

#endif