/**
 * @file menu.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Menu is the Main Menu of the game, showed on game startup
 *
 * This file contains all declarations and function regarding Menu
 *
 */

#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include "game.h"
#include "button.h"
#include "assets.h"

#define BUTTONS_COUNT 2 /**< The number of Button present in Main Menu */

typedef struct Menu {
	Button * buttons[BUTTONS_COUNT]; /**< The Button List */
} Menu;


/**
 * See Action in button.h
 */
void playHandle(Game * game);
/**
 * See Action in button.h
 */
void settingsHandle(Game * game);


/**
 * Initialize some variables of a Menu
 * @param menu The Menu to intialize
 * @param assets The Assets manager to retrieve required assets
 */
void Menu_init(Menu * menu, Assets * assets);

/**
 * Update state of Button in List
 * @param menu The Menu with the Button list
 * @param game The Game to change the state or variable by button
 */
void Menu_update(Menu * menu, Game * game);

/**
 * Draw a Menu with Raylib
 * @param menu The Menu to draw
 */
void Menu_draw(Menu * menu);

#endif