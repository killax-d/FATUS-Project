#ifndef ITEM_H
#define ITEM_H
#include "raylib.h"
#include "stdlib.h"
#define ITEM_TEXTURE_SCALE 40

typedef struct Item {
    int id;
    char * name;
    bool hasTexture;
    Texture2D texture;
} Item;

Item * Item_new(int id, char * name, bool hasTexture, Texture2D texture);

void Item_draw(int x, int y, Item item);

#endif