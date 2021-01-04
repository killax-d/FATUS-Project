/**
 * @file button.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Button is used in Main Menu
 *
 * This file contains all declarations and function regarding Button
 *
 */

#ifndef BUTTON_H
#define BUTTON_H
#include "raylib.h"
#include "game.h"

#define BUTTON_WIDTH 400
#define BUTTON_HEIGHT 80

/**
 * Struct to represent a Action of a Button
 */
typedef void (*Action)(Game * game);

/**
 * Struct to represent a Button
 */
typedef struct Button {
	Rectangle rect;/**< The Rectangle where the button should be */
	char * text;/**< The Text to draw in the button */
    Sound sound;/**< The Sound used when the mouse Hover the button */
    bool focused;/**< Is the Button focused ? */
    Action handle;/**< The Action performed when the Button is pressed */
} Button;

/**
 * Return a pointer to a Door and intialize some variables
 * @param rect The Rectangle where the button should be
 * @param text The Text to draw in the button
 * @param sound The Sound used when the mouse Hover the button
 * @param action The Action performed when the Button is pressed
 * @return A pointer to the Button
 */
Button * Button_new(Rectangle rect, char * text, Sound sound, Action action);

/**
 * Check if the Button is hovered by the mouse position
 * @param button The Button to check
 * @param vector The mouse position
 */
void Button_hover(Button * button, Vector2 vector);

/**
 * Handle the Button click
 * @param button The Button to check
 * @param game The Game to change the state to "ingame"
 */
void Button_handle(Button * button, Game * game);

/**
 * Draw a Button
 * @param button The Button to draw
 */
void Button_draw(Button * button);

#endif