#ifndef INVENTORY_H
#define INVENTORY_H
#include "raylib.h"
#include "stdlib.h"
#include "./item.h"

typedef struct Inventory {
    Item items[10];
    int nbItems;
    char notes;
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

#endif