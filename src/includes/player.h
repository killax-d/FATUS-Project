/**
 * @file player.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Player of the game with all the necessary to play
 *
 * This file contains all declarations and function regarding Player
 *
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "stdlib.h"
#include "collider.h"
#include "inventory.h"
#include "map.h"
#include "assets.h"
#include <math.h>
#define FRAME_RATE 8 /**< How many frames before switching animations */
#define PLAYER_SIZE 40 /**< The Player Sprite size */
#define PLAYER_MAX_LIFE 3 /**< The Max Life points of a Player */
#define INVULNERABILITY_COOLDOWN 300 /**< The Invulnerability cooldown of a Player */

/**
 * Struct to represent a Player
 */
typedef struct Player {
    Vector2 position;/**< The Player position in 2D */
    Vector2 speed;/**< The Player speed in 2D */
    float acceleration;/**< The Player acceleration boost when sprinting */
    Collider * collider;/**< The Player Collider used to block movements when obstacle in front */
    Inventory * inventory;/**< The Player Inventory to hold picked up Item */
    int life;/**< The Player life start with PLAYER_MAX_LIFE */
    int invulnerabilityCooldown;/**< The Player invulnerability cooldown after taking damage */
    bool invulnerable;/**< Is the Player Invulnerable ? */
    bool sprinting;/**< Is the Player pressing Shift ? */
    int direction;/**< Is the Player looking to the left or to the right */
    int walkSprite;/**< Current Sprite in animation */
    Texture2D texture;/**< The Player texture */
    Sound damageSound;/**< The Damage sound played when the player is attacked */
} Player;

/**
 * Return a pointer to a Player and intialize some variables
 * @return A pointer to the Player
 */
Player * Player_new();

/**
 * Initialize some variables of a Player
 * @param player The Player to intialize
 * @param assets The Assets manager to retrieve required assets
 */
void Player_init(Player * player, Assets * assets);

/**
 * Draw a Player with Raylib
 * @param player The Player to draw
 */
void Player_draw(Player * player);

/**
 * Draw Player Life with Raylib
 * @param x The X location on the game to draw
 * @param y The Y location on the game to draw
 * @param player The Player to draw his current life points
 * @param assets The Assets manager to retrieve required assets
 */
void Player_drawLife(int x, int y, Player * player, Assets * assets);

/**
 * Handle control of Player (pressing button)
 * @param player The Player to handle
 */
void Player_control(Player * player);

/**
 * Switch the current player item
 * @param player The Player to handle
 * @param selected The selected index
 */
void Player_switchItem(Player * player, int selected);

/**
 * Move the player in the map
 * @param map The GameMap to check obstacles
 * @param player The Player to move
 * @param delta The delta time between the previous frame and the current
 */
void Player_move(GameMap * map, Player * player, float delta);

/**
 * Check the player in the map and update the Collider
 * @param map The GameMap to check obstacles
 * @param player The Player trying to move
 * @param speed The current speed of the player
 */
void Player_collisions(GameMap * map, Player * player, Vector2 speed);

/**
 * Damage the life of a Player
 * @param player The Player to damage
 */
void Player_damage(Player * player);

#endif