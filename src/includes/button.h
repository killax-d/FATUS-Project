#ifndef BUTTON_H
#define BUTTON_H
#include "raylib.h"
#include "game.h"

#define BUTTON_WIDTH 400
#define BUTTON_HEIGHT 80

typedef void (*Action)(Game * game);

typedef struct Button {
	Rectangle rect;
	char * text;
    Sound sound;
    bool focused;
    Action handle;
} Button;

Button * Button_new(Rectangle rect, char * text, Sound sound, bool focused, Action action);

void Button_hover(Button * button, Vector2 vector);

void Button_handle(Button * button, Game * game);

void Button_draw(Button * button);

#endif