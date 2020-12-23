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
	char selectedText[60];
} Inventory;

void Inventory_draw(int x, int y, Inventory inv);

#endif