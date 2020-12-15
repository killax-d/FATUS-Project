#ifndef ITEM_H
#define ITEM_H
#include "raylib.h"
#include "stdlib.h"

typedef struct Item {
    int id;
    char name;
    Texture2D texture;
} Item;

Item* Item_new(int id, char name, Texture2D texture) {
    Item* i = malloc(sizeof(Item));
    i->id = id;
    i->name = name;
    i->texture = texture;
    return i;
}

void Item_delete(Item i) {
    free(&i);
}

void Item_draw(int x, int y, Item item) {
	DrawTexture(item.texture, x+4, y+4, (Color) {125,125,125,100});
}

#endif