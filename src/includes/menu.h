#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include "./game.h"
#include "./button.h"

#define BUTTON_COUNT 2

typedef struct Menu {
	Button * buttons[BUTTON_COUNT];
} Menu;

void playHandle(Game * game);
void settingsHandle(Game * game);

void Menu_init(Menu * menu);

void Menu_update(Menu * menu, Game * game);

void Menu_draw(Menu * menu);

#endif