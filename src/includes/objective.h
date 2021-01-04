/**
 * @file objective.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Objective is a success to complete
 *
 * This file contains all declarations and function regarding Objective
 *
 */

#ifndef OBJECTIVE_H
#define OBJECTIVE_H
#include "raylib.h"
#include <stdlib.h>

/**
 * Struct to represent a Objective
 */
typedef struct Objective {
	int id;/**< The Objective ID */
	char * text;/**< The Objective Description */
	Texture2D objectiveTexture;/**< The unticked case texture */
	Texture2D objectiveFinishedTexture;/**< The ticked case texture */
	int lines_count;/**< The number of lines in Objective text (description) */
	bool finished;/**< Is the Objective ended ? */
	bool visible;/**< Is the Objective currently visible ? */
} Objective;

/**
 * Return a pointer to an Objective and intialize some variables
 * @param id The Objective ID
 * @param text The Objective Description
 * @param objective The unticked case texture
 * @param objectiveFinished The ticked case texture
 * @return A pointer to the Objective
 */
Objective * Objective_new(int id, char * text, Texture2D objective, Texture2D objectiveFinished);

/**
 * Draw an Objective with Raylib
 * @param x The X location on the game to draw
 * @param y The Y location on the game to draw
 * @param objective The Objective to draw
 */
void Objective_draw(int x, int y, Objective * objective);

/**
 * Set an Objective visible
 * @param objective The Objective to reveal
 */
void Objective_reveal(Objective * objective);

/**
 * Set an Objective to end state
 * @param objective The Objective to reveal
 */
void Objective_finish(Objective * objective);

#endif