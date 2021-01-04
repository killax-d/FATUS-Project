/**
 * @file door.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Game Door representation
 *
 * This file contains all declarations and function regarding Door
 *
 */

#ifndef DOOR_H
#define DOOR_H
#include "raylib.h"
#include "map.h"

#define MAGNET_DOOR 0
#define MOTOR1_DOOR 1
#define CELL_DOOR 2
#define MAGNET_DOOR1 3
#define MAGNET_DOOR2 4
#define MAGNET_DOOR3 5
#define MOTOR2_DOOR 6

/**
 * Struct to represent a Door
 */
typedef struct Door {
	Rectangle bounds;/**< The door bounds to draw the closed Door */
	Rectangle useArea;/**< The area where the player should be to open the Door */
	Sound openSound;/**< The sound played when the Door open */
	Sound closeSound;/**< The sound played when the Door close */
	Texture2D doorCloseTexture;/**< The Door close texture */
	Texture2D doorOpenTexture;/**< The Door open texture */
	Texture2D doorUseAreaTexture;/**< The use area texture (only drawed in DEBUG mode) */
	bool open;/**< Is the Door open ? */
} Door;

/**
 * Return a pointer to a Door and intialize some variables
 * @param map The GameMap to draw Door on it
 * @param bounds The door bounds to draw the closed Door
 * @param useArea The area where the player should be to open the Door
 * @param openSound The sound played when the Door open
 * @param closeSound The sound played when the Door close
 * @param doorCloseTexture The Door close texture
 * @param doorOpenTexture The Door open texture
 * @param doorUseAreaTexture The use area texture (only drawed in DEBUG mode)
 * @return A pointer to the Door
 */
Door * Door_new(GameMap * map, Rectangle bounds, Rectangle useArea, Sound openSound, Sound closeSound, Texture2D doorCloseTexture, Texture2D doorOpenTexture, Texture2D doorUseAreaTexture);

/**
 * Open a Door
 * @param map The GameMap to edit the Door
 * @param door The Door to open
 * @param vector The position where the player are (needed to check useArea)
 * @param needCheck Force use area check
 * @return If the door successfully open
 */
bool Door_open(GameMap * map, Door * door, Vector2 vector, bool needCheck);

/**
 * Close a Door
 * @param map The GameMap to edit the Door
 * @param door The Door to close
 * @param vector The position where the player are (needed to check useArea)
 * @param needCheck Force use area check
 */
void Door_close(GameMap * map, Door * door, Vector2 vector, bool needCheck);

#endif