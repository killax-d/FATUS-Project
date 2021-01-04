/**
 * @file minimap.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Minimap is a radar map to see where you can go
 *
 * This file contains all declarations and function regarding Minimap
 *
 */

#ifndef MINIMAP_H
#define MINIMAP_H
#include "raylib.h"
#include "game.h"

#define ZOOM_COUNT 3 /**< Maximum zoom levels to calculate */

typedef struct Minimap {
	int x; /**< The X coordinates where the Minimap should be drawed */
	int y; /**< The Y coordinates where the Minimap should be drawed */
	int size; /**< The size of the Minimap (Square) */
	int scale; /**< The Minimap scale (calculated with the zoom), used to draw with enough space inside the square */
	int zoom; /**< The current zoom level */
	int zooms_availables[ZOOM_COUNT]; /**< The zooms availables */
} Minimap;

/**
 * Initialize some variables of a Minimap (ex: Initialize zooms availables calculation)
 * @param minimap The Minimap to intialize
 */
void Minimap_init(Minimap * minimap);

/**
 * Handle the Minimap control (pressing key or mouse wheel)
 * @param minimap The Minimap to control
 */
void Minimap_control(Minimap * minimap);

/**
 * Draw a Minimap with Raylib
 * @param minimap The Minimap to draw
 * @param game The Game to retrieve GameMap data & Player data
 */
void Minimap_draw(Minimap * minimap, Game * game);

#endif