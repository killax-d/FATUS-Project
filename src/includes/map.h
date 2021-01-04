/**
 * @file map.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Map contains all case to draw
 *
 * This file contains all declarations and function regarding Map
 *
 */

#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "sprite.h"
#include "assets.h"
#define MAP_TEXTURE_SCALE 32 /**< Map Texture scale (used to draw tiles) */
#define MAP_WIDTH 178 /**< The Map array WIDTH */
#define MAP_HEIGHT 102 /**< The Map array HEIGHT */

typedef struct GameMap {
    Sprite * sprite[MAP_HEIGHT][MAP_WIDTH]; /**< Map Sprite List */
} GameMap;

/**
 * Convert the int Map to Sprite Map
 * @param map The GameMap to store
 * @param array The int map to convert
 * @param assets The Assets manager to retrieve required assets
 */
void IntArrayToSpriteMap(GameMap * map, int array[MAP_HEIGHT][MAP_WIDTH], Assets * assets);

/**
 * Draw a GameMap with Raylib
 * @param map The GameMap to draw
 * @param position The position centered from where to calcul necessary draw
 */
void Map_draw(GameMap * map, int position[2]);

#endif