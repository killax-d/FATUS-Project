#include "includes/menu.h"

void Menu_update(Game * game) {
	Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, (Rectangle) {GetScreenWidth()/2-50, GetScreenHeight()/2-25, 100, 50}))
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        	game->state = 0;

}

void Menu_draw() {
    BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangle(GetScreenWidth()/2-50, GetScreenHeight()/2-25, 100, 24, WHITE);
        DrawText("Start", GetScreenWidth()/2-48, GetScreenHeight()/2-23, 20, BLACK);

    EndDrawing();
}