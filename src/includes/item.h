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

Item* Item_new(int id, char * name, Texture2D texture) {
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
    if (item.hasTexture) DrawTexture(item.texture, x+4, y+4, WHITE);
    else DrawRectangle(x+4, y+4, 40, 40, PINK);
}

#endif