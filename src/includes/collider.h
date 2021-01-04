/**
 * @file collider.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Collider used for player movements check
 *
 * This file contains all declarations and function regarding Collider
 *
 */

#ifndef COLLIDER_H
#define COLLIDER_H
#include "raylib.h"

/**
 * Struct to represent a Collider
 */
typedef struct Collider {
    bool UP;/**< The UP position is available */
    bool RIGHT;/**< The RIGHT position is available */
    bool DOWN;/**< The DOWN position is available */
    bool LEFT;/**< The LEFT position is available */
} Collider;

/**
 * Return a pointer to a Collider
 * @return A pointer to the Collider
 */
Collider * Collider_new();

/**
 * Reset a Collider (set all position to false)
 * @param collider The Collider to reset
 */
void Collider_reset(Collider * collider);

#endif