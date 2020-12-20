#ifndef SPRITE_H
#define SPRITE_H

typedef struct Sprite {
    Rectangle rect;
    bool blocking;
    Color color;
    bool hasTexture;
    Texture2D texture;
} Sprite;

Sprite* Sprite_new(Rectangle rect, bool blocking, Color color, bool hasTexture, Texture2D texture) {
    Sprite* s = malloc(sizeof(Sprite));
    s->rect = rect;
    s->blocking = blocking;
    s->color = color;
    s->hasTexture = hasTexture;
    s->texture = texture;
    return s;
}

void Sprite_delete(Sprite s) {
    free(&s);
}

#endif