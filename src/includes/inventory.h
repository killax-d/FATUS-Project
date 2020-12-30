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

bool Inventory_contain(Inventory * inv, int id);

bool Inventory_addItem(Inventory * inv, Item item);

void Inventory_removeItem(Inventory * inv, int id);

#endif