#ifndef ITEM_H
#define ITEM_H
#include "raylib.h"
#include "stdlib.h"

typedef struct Item {
    int id;
    char name;
    char texture;
} Item;

Item* Item_new(int id, char name, char texture) {
    Item* i = malloc(sizeof(Item));
    i->id = id;
    i->name = name;
    i->texture = texture;
    return i;
}

void Item_delete(Item i) {
    free(&i);
}

#endif