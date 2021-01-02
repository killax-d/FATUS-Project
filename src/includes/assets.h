#ifndef ASSETS_H
#define ASSETS_H
#include "raylib.h"

#define MAP_TEXTURES_BUFFER_SIZE 135
// Map textures

#define TEXTURES_BUFFER_SIZE 20
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
#define MAGNET_CARD_RED_TEXTURE 9
#define BOMB_TEXTURE 10
#define ROPE_TEXTURE 11 
#define USB_KEY_TEXTURE 12

#define USE_AREA_TEXTURE 13
#define DOOR_TEXTURE 14
#define DOOR_OPEN_TEXTURE 15



#define SOUNDS_BUFFER_SIZE 10
// SOUNDS
#define BUTTON_HOVER_SOUND 0
#define DOOR_OPEN_SOUND 1
#define DOOR_ENGINE_OPEN_SOUND 2
#define DOOR_CLOSE_SOUND 3
#define ITEM_PICKUP_SOUND 4
#define KEY_PICKUP_SOUND 5
#define CRAFT_SOUND 6
#define BOMB_SOUND 7

typedef struct Assets {
	Texture2D mapTextures[MAP_TEXTURES_BUFFER_SIZE];
	Sound sounds[SOUNDS_BUFFER_SIZE];
	Texture2D textures[TEXTURES_BUFFER_SIZE];
} Assets;

Assets * Assets_new();

void Assets_init(Assets * assets);

void Assets_unload(Assets * assets);

#endif