/**
 * @file objectivesnotes.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief ObjectivesNotes is the objectives list drawed when you use the "Notes" item
 *
 * This file contains all declarations and function regarding ObjectivesNotes
 *
 */

#ifndef OBJECTIVESNOTES_H
#define OBJECTIVESNOTES_H
#include "raylib.h"
#include "objective.h"
#include "assets.h"


#define OBJECTIVES_NOTES_TEXTURE_WIDTH 454/**< The Objectives List background Texture WIDTH needed to center the draw */
#define OBJECTIVES_NOTES_TEXTURE_HEIGHT 600/**< The Objectives List background Texture HEIGHT needed to center the draw */
#define OBJECTIVES_NOTES_PADDING_TOP 79/**< The Objectives List background Texture padding top to write the Objective text */
#define OBJECTIVES_NOTES_PADDING_LEFT 109/**< The Objectives List background Texture padding left to write the Objective text */
#define OBJECTIVES_COUNT 7

#define OPEN_CELL_OBJECTIVE 0
#define FIND_GREEN_MAGNET_CARD 1
#define FIND_YELLOW_MAGNET_CARD 2
#define FIND_ENGINES_KEY 3 
#define FIND_BLUE_MAGNET_CARD 4
#define FIND_RED_MAGNET_CARD 5
#define FIND_USB_KEY 6

/**
 * Struct to represent a ObjectivesNotes
 */
typedef struct ObjectivesNotes {
	Texture2D background;/**< The Objectives List background */
	bool visible;/**< Is the Objectives List currently visible ? */
	Objective * objectives[OBJECTIVES_COUNT];/**< Objectives List */
} ObjectivesNotes;

/**
 * Initialize some variables of a ObjectivesNotes, creation of Objective in that function
 * @param objectives The ObjectivesNotes to intialize
 * @param assets The Assets manager to retrieve required assets
 */
void ObjectivesNotes_init(ObjectivesNotes * objectives, Assets * assets);

/**
 * Draw an Objectives List with Raylib
 * @param x The X location on the game to draw
 * @param y The Y location on the game to draw
 * @param objectives The Objectives List to draw
 */
void ObjectivesNotes_draw(int x, int y, ObjectivesNotes * objectives);

/**
 * Set an Objective to end state and reveal the next one
 * @param objectives The ObjectivesNotes containing all Objectives
 * @param id The Objective ID to finish
 */
void ObjectivesNotes_finish(ObjectivesNotes * objectives, int id);

#endif