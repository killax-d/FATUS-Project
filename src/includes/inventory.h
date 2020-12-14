#ifndef INVENTORY_H
#define INVENTORY_H
#include "raylib.h"
#include "stdlib.h"
#include "./item.h"

typedef struct Inventory {
    Item items[9];
    int selected;
    int nbItems;
    char * notes;
} Inventory;

Inventory* Inventory_new() {
    Inventory* i = malloc(sizeof(Inventory));
    i->nbItems = 0;
    i->notes = "";
    return i;
}

void Inventory_delete(Inventory i) {
    free(&i);
}

void Inventory_draw(int x, int y, Inventory inv) {
	for (int i = 0; i < 9; i++) {
		// Draw case
        DrawRectangle(x + ((48+4) * i), y, 48, 48, (Color) {65,105,225,200});
        // Draw selected rectangle
        if (i == inv.selected) DrawRectangleLines(x + ((48+4) * i), y, 48, 48, (Color) {255,255,255,200});
        // Draw item
		Item_draw(x + ((48+4) * i), y, inv.items[i]);
	}
}

#endif