#ifndef SPRITE_H
#define SPRITE_H

typedef struct Sprite {
    Rectangle rect;
    int blocking;
    Color color;
} Sprite;

Sprite* Sprite_new(Rectangle rect, int blocking, Color color) {
    Sprite* s = malloc(sizeof(Sprite));
    s->rect = rect;
    s->blocking = blocking;
    s->color = color;
    return s;
}

void Sprite_delete(Sprite s) {
    free(&s);
}

#endif