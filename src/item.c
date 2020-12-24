#include "includes/item.h"

void Item_draw(int x, int y, Item item) {
    if (item.hasTexture) DrawTexture(item.texture, x+4, y+4, WHITE);
    else DrawRectangle(x+4, y+4, 40, 40, PINK);
}