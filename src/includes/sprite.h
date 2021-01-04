/**
 * @file sprite.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Sprite is a part of the map
 *
 * This file contains all declarations and function regarding Sprite
 *
 */

#ifndef SPRITE_H
#define SPRITE_H
#include "raylib.h"
#include <stdlib.h>

/**
 * Struct to represent a Sprite
 */
typedef struct Sprite {
    Rectangle rect;/**< The Rectangle where the sprite are drawed */
    bool blocking;/**< Player can walk on it ? */
    bool hasTexture;/**< Does the Sprite has a texture ? */
    Texture2D texture;/**< The Sprite Texture */
} Sprite;

/**
 * Return a pointer to an Sprite and intialize some variables
 * @param rect The Rectangle where the Sprite should be drawed
 * @param blocking The Player can walk on that Sprite ?
 * @param hasTexture Does the Sprite has a texture ?
 * @param texture The Sprite texture
 * @return A pointer to the Sprite
 */
Sprite * Sprite_new(Rectangle rect, bool blocking, bool hasTexture, Texture2D texture);

#endif