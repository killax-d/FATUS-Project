#ifndef INVENTORY_H
#define INVENTORY_H
#include "raylib.h"
#include "stdlib.h"
#include "./Item.h"
#define INVENTORY_SIZE 9 /**< MAX Inventory size */
#define TEXT_SELECTED_ITEM_BUFFER_LENGTH 50 /**< The selected Item Text Buffer length */

/**
* Struct to represent the Inventory
**/
typedef struct Inventory {
	Item * items[INVENTORY_SIZE]; /**< An array containing all the Items */
	int selected; /**< Index of the currently selected Item */
	int nbItems; /**< The number of Items the player has */
	char selectedText[TEXT_SELECTED_ITEM_BUFFER_LENGTH]; /**< Name of the current selected Item */
} Inventory;

/**
 * Returns a pointer to the Inventory
 * @return A pointer to the Inventory
 */
Inventory * Inventory_new();

/**
 * Draws the Inventory at specific coordinates
 * @param x The X location on the game to draw
 * @param y The Y location on the game to draw
 * @param inv The Inventory to draw
 */
void Inventory_draw(int x, int y, Inventory * inv);

/**
 * Checks if a specific Item is in the Inventory via it's id
 * @param inv The Inventory to check
 * @param id The Item ID to check;
 * @return Item id is present in Inventory ?
 */
bool Inventory_contain(Inventory * inv, int id);

/**
 * Checks if a specific Item has been correctly added to the Inventory
 * @param inv The Inventory to check
 * @param item The Item to add
 * @return The Item has been added to Inventory without error ?
 */
bool Inventory_addItem(Inventory * inv, Item * item);

/**
 * Removes an Item from the Inventory through its id
 * @param inv The Inventory to check
 * @param id The ID of Item to remove
 */
void Inventory_removeItem(Inventory * inv, int id);

#endif