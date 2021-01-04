#include "includes/menu.h"
#include "includes/env.h"

void playHandle(Game * game) {
	game->state = 0;
}

void settingsHandle(Game * game) {
	logger(LOG_DEBUG, "Settings are not implemented yet!", NULL);
}

void Menu_init(Menu * menu, Assets * assets) {
	Button * play = Button_new(
		(Rectangle) 
		{
			20,
			150,
			BUTTON_WIDTH,
			BUTTON_HEIGHT
		},
		"Play",
		assets->sounds[BUTTON_HOVER_SOUND],
		playHandle
	);
	Button * settings = Button_new(
		(Rectangle) 
		{
			20,
			150 + BUTTON_HEIGHT,
			BUTTON_WIDTH,
			BUTTON_HEIGHT
		},
		"Settings",
		assets->sounds[BUTTON_HOVER_SOUND],
		settingsHandle
	);
	menu->buttons[0] = play;
	menu->buttons[1] = settings;
}

void Menu_update(Menu * menu, Game * game) {
	for (int i = 0; i < BUTTONS_COUNT; i++)
		Button_hover(menu->buttons[i], GetMousePosition());

	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		for (int i = 0; i < BUTTONS_COUNT; i++)
			Button_handle(menu->buttons[i], game);
}

void Menu_draw(Menu * menu) {
    ClearBackground(LIGHTGRAY);

	for (int i = 0; i < BUTTONS_COUNT; i++) Button_draw(menu->buttons[i]);
}