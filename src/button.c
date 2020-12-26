#include "includes/button.h"

Button * Button_new(Rectangle rect, char * text, Sound sound, bool focused, Action handle) {
	Button * button = malloc(sizeof(Button));
	button->rect = rect;
	button->text = text;
    button->sound = sound;
    button->focused = focused;
    button->handle = handle;
    return button;
}

void Button_hover(Button * button, Vector2 vector) {
    button->focused = CheckCollisionPointRec(vector, button->rect);
    if (!button->focused) PlaySound(button->sound);
}

void Button_handle(Button * button, Game * game) {
    if (button->focused) button->handle(game);
}

void Button_draw(Button * button) {
	DrawRectangleGradientH(button->rect.x, button->rect.y, button->rect.width, button->rect.height, WHITE, button->focused ? (Color) {255, 255, 255, 200} : (Color) {255, 255, 255, 20});
	DrawText(button->text, button->rect.x + 2, button->rect.y + 2, button->rect.height - 4, button->focused ? BLACK : GRAY);
}