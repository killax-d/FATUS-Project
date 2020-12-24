#ifndef ITEM_H
#define ITEM_H
#include "raylib.h"
#include "stdlib.h"

typedef struct Item {
    int id;
    char * name;
    bool hasTexture;
    Texture2D texture;
} Item;

void Item_draw(int x, int y, Item item);

void Item_draw(int x, int y, Item item) {
	DrawTexture(item.texture, x+4, y+4, (Color) {125,125,125,100});
}

#endif