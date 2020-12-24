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

#endif