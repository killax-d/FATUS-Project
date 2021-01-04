#include "includes/sprite.h"

Sprite * Sprite_new(Rectangle rect, bool blocking, bool hasTexture, Texture2D texture) {
	Sprite * sprite = malloc(sizeof(Sprite));
	sprite->rect = rect;
	sprite->blocking = blocking;
	sprite->hasTexture = hasTexture;
	sprite->texture = texture;
	return sprite;
}