#ifndef ITEM_H
#define ITEM_H
#include "raylib.h"
#include "stdlib.h"
#define ITEM_TEXTURE_SCALE 40 /**< The texture size of an item */

/**
* Struct to represent an Item
**/
typedef struct Item { 
    int id; /**< The ID of the Item */
    char * name; /**< The name of the Item */
    bool hasTexture; /**< Does the Item has a texture? */
    Texture2D texture; /**< The texture of the Item */
    Sound pickupSound; /**< The sound of the Item when it is picked up */
} Item;


/**
 * Returns a pointer to an Item and intialize some variables
 * @param id The ID of the Item
 * @param name The name of the Item
 * @param hasTexture Does the Item has a texture?
 * @param texture The texture of the Item
 * @param pickupSound The sound pf the Item when it is picked up4
 * @return A pointer to an Item
 */
Item * Item_new(int id, char * name, bool hasTexture, Texture2D texture, Sound pickupSound);

/**
 * Draws an Item at specific coordinates
 * @param x The X coordinate of the Item to draw
 * @param y The Y coordinate of the Item to draw
 * @param item The Item to draw
 */
void Item_draw(int x, int y, Item * item);

#endif