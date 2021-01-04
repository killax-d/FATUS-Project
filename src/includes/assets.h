/**
 * @file assets.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Assets manager, all textures and sounds are loaded here
 *
 * This file contains all declarations and function regarding Assets
 *
 */

#ifndef ASSETS_H
#define ASSETS_H
#include "raylib.h"

#define MAP_TEXTURES_BUFFER_SIZE 131
// Map textures

#define TEXTURES_BUFFER_SIZE 23
// TEXTURES
#define PLAYER_TEXTURE 0
#define ENGINE_KEY_TEXTURE 1
#define MAGNET_CARD_BLUE_TEXTURE 2
#define FLINT_TEXTURE 3
#define FLINT_ACTIVE_TEXTURE 4
#define NOTES_TEXTURE 5
#define AMMONIUM_NITRATE_TEXTURE 6
#define CELL_KEY_TEXTURE 7
#define MAGNET_CARD_GREEN_TEXTURE 8
#define MAGNET_CARD_YELLOW_TEXTURE 9
#define MAGNET_CARD_RED_TEXTURE 10
#define BOMB_TEXTURE 11
#define ROPE_TEXTURE 12 
#define USB_KEY_TEXTURE 13
#define PLAYER_HEART_TEXTURE 14
#define PLAYER_HEART_DARK_TEXTURE 15
#define OBJECTIVES_BACKGROUND_TEXTURE 16
#define OBJECTIVE_TEXTURE 17
#define OBJECTIVE_TICKED_TEXTURE 18
#define ALIEN_TEXTURE 19

#define USE_AREA_TEXTURE 20
#define DOOR_TEXTURE 21
#define DOOR_OPEN_TEXTURE 22



#define SOUNDS_BUFFER_SIZE 9
// SOUNDS
#define BUTTON_HOVER_SOUND 0
#define DOOR_OPEN_SOUND 1
#define DOOR_ENGINE_OPEN_SOUND 2
#define DOOR_CLOSE_SOUND 3
#define ITEM_PICKUP_SOUND 4
#define KEY_PICKUP_SOUND 5
#define CRAFT_SOUND 6
#define BOMB_SOUND 7
#define TAKE_DAMAGE_SOUND 8

/**
 * Struct to represent a Assets
 */
typedef struct Assets {
	Texture2D mapTextures[MAP_TEXTURES_BUFFER_SIZE];/**< The Map Textures array */
	Texture2D textures[TEXTURES_BUFFER_SIZE];/**< The Textures array */
	Sound sounds[SOUNDS_BUFFER_SIZE];/**< The Sounds array */
} Assets;

/**
 * Return a pointer to a Assets
 * @return A pointer to the Assets
 */
Assets * Assets_new();

/**
 * Initialize some variables of a Assets, Load Textures & Sounds
 * @param assets The Assets to intialize
 */
void Assets_init(Assets * assets);

/**
 * Unload all textures and sounds
 * @param assets The Assets to unload
 */
void Assets_unload(Assets * assets);

#endif