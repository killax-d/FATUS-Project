#include "includes/assets.h"
#include <stdlib.h>

Assets * Assets_new() {
	Assets * assets = malloc(sizeof(Assets));
	return assets;
}

void Assets_init(Assets * assets) {
	Texture2D tmp_map_textures[MAP_TEXTURES_BUFFER_SIZE] = {
		{0},
		LoadTexture("assets/Tiles/Default/Floor.png"),
		LoadTexture("assets/Tiles/Default/Wall.png"),
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		LoadTexture("assets/Tiles/Light/image_part_001.png"),
		LoadTexture("assets/Tiles/Light/image_part_002.png"),
		LoadTexture("assets/Tiles/Light/image_part_003.png"),
		LoadTexture("assets/Tiles/Light/image_part_004.png"),
		LoadTexture("assets/Tiles/Light/image_part_004.png"),
		LoadTexture("assets/Tiles/Bench/image_part_001.png"),
		LoadTexture("assets/Tiles/Bench/image_part_002.png"),
		LoadTexture("assets/Tiles/Bench/image_part_003.png"),
		LoadTexture("assets/Tiles/Bench/image_part_004.png"),
		LoadTexture("assets/Tiles/Bed/image_part_001.png"),
		LoadTexture("assets/Tiles/Bed/image_part_002.png"),
		LoadTexture("assets/Tiles/Bed/image_part_003.png"),
		LoadTexture("assets/Tiles/Bed/image_part_004.png"),
		LoadTexture("assets/Tiles/Bed/image_part_005.png"),
		LoadTexture("assets/Tiles/Bed/image_part_006.png"),
		LoadTexture("assets/Tiles/Bed/image_part_007.png"),
		LoadTexture("assets/Tiles/Bed/image_part_008.png"),
		LoadTexture("assets/Tiles/Long desk/image_part_001.png"),
		LoadTexture("assets/Tiles/Long desk/image_part_002.png"),
		LoadTexture("assets/Tiles/Long desk/image_part_003.png"),
		LoadTexture("assets/Tiles/Long desk/image_part_004.png"),
		LoadTexture("assets/Tiles/Long desk/image_part_005.png"),
		LoadTexture("assets/Tiles/Long desk/image_part_006.png"),
		LoadTexture("assets/Tiles/Long desk/image_part_007.png"),
		LoadTexture("assets/Tiles/Long desk/image_part_008.png"),
		{0},
		{0},
		{0},
		{0},
		LoadTexture("assets/Tiles/Wardrobe/image_part_001.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_002.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_003.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_004.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_005.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_006.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_007.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_008.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_009.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_010.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_011.png"),
		LoadTexture("assets/Tiles/Wardrobe/image_part_012.png"),
		{0},
		{0},
		{0},
		{0},
		LoadTexture("assets/Tiles/Long cabinet/image_part_001.png"),
		LoadTexture("assets/Tiles/Long cabinet/image_part_002.png"),
		LoadTexture("assets/Tiles/Long cabinet/image_part_003.png"),
		LoadTexture("assets/Tiles/Long cabinet/image_part_004.png"),
		LoadTexture("assets/Tiles/Long cabinet/image_part_005.png"),
		LoadTexture("assets/Tiles/Long cabinet/image_part_006.png"),
		LoadTexture("assets/Tiles/Long cabinet/image_part_007.png"),
		LoadTexture("assets/Tiles/Long cabinet/image_part_008.png"),
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		LoadTexture("assets/Tiles/Engine/image_part_001.png"),
		LoadTexture("assets/Tiles/Engine/image_part_002.png"),
		LoadTexture("assets/Tiles/Engine/image_part_003.png"),
		LoadTexture("assets/Tiles/Engine/image_part_004.png"),
		LoadTexture("assets/Tiles/Engine/image_part_005.png"),
		LoadTexture("assets/Tiles/Engine/image_part_006.png"),
		LoadTexture("assets/Tiles/Engine/image_part_007.png"),
		LoadTexture("assets/Tiles/Engine/image_part_008.png"),
		LoadTexture("assets/Tiles/Engine/image_part_009.png"),
		LoadTexture("assets/Tiles/Engine/image_part_010.png"),
		LoadTexture("assets/Tiles/Engine/image_part_011.png"),
		LoadTexture("assets/Tiles/Engine/image_part_012.png"),
		LoadTexture("assets/Tiles/Engine/image_part_013.png"),
		LoadTexture("assets/Tiles/Engine/image_part_014.png"),
		LoadTexture("assets/Tiles/Engine/image_part_015.png"),
		LoadTexture("assets/Tiles/Engine/image_part_016.png"),
		LoadTexture("assets/Tiles/Engine/image_part_017.png"),
		LoadTexture("assets/Tiles/Engine/image_part_018.png"),
		LoadTexture("assets/Tiles/Engine/image_part_019.png"),
		LoadTexture("assets/Tiles/Engine/image_part_020.png"),
		LoadTexture("assets/Tiles/Engine/image_part_021.png"),
		LoadTexture("assets/Tiles/Engine/image_part_022.png"),
		LoadTexture("assets/Tiles/Engine/image_part_023.png"),
		LoadTexture("assets/Tiles/Engine/image_part_024.png"),
		LoadTexture("assets/Tiles/Engine/image_part_025.png"),
		LoadTexture("assets/Tiles/Engine/image_part_026.png"),
		LoadTexture("assets/Tiles/Engine/image_part_027.png"),
		LoadTexture("assets/Tiles/Engine/image_part_028.png"),
		LoadTexture("assets/Tiles/Engine/image_part_029.png"),
		LoadTexture("assets/Tiles/Engine/image_part_030.png"),
		LoadTexture("assets/Tiles/Screen/3/image_part_004.png"),
		LoadTexture("assets/Tiles/Screen/3/image_part_001.png"),
		LoadTexture("assets/Tiles/Screen/3/image_part_002.png"),
		LoadTexture("assets/Tiles/Screen/3/image_part_003.png"),
		LoadTexture("assets/Tiles/Screen/2/image_part_004.png"),
		LoadTexture("assets/Tiles/Screen/2/image_part_001.png"),
		LoadTexture("assets/Tiles/Screen/2/image_part_002.png"),
		LoadTexture("assets/Tiles/Screen/2/image_part_003.png"),
		{0},
		{0},
		{0},
		LoadTexture("assets/Tiles/Screen/1/image_part_008.png"),
		LoadTexture("assets/Tiles/Screen/1/image_part_001.png"),
		LoadTexture("assets/Tiles/Screen/1/image_part_002.png"),
		LoadTexture("assets/Tiles/Screen/1/image_part_003.png"),
		LoadTexture("assets/Tiles/Screen/1/image_part_004.png"),
		LoadTexture("assets/Tiles/Screen/1/image_part_005.png"),
		LoadTexture("assets/Tiles/Screen/1/image_part_006.png"),
		LoadTexture("assets/Tiles/Screen/1/image_part_007.png")
	};

	for (int i = 0; i < MAP_TEXTURES_BUFFER_SIZE; i++) assets->mapTextures[i] = tmp_map_textures[i];
	for (int i = 0; i < TEXTURES_BUFFER_SIZE; i++) assets->textures[i] = (Texture2D) {0};
	for (int i = 0; i < SOUNDS_BUFFER_SIZE; i++) assets->sounds[i] = (Sound) {0};

	assets->textures[PLAYER_TEXTURE] = LoadTexture("assets/sprite_player.png");
	assets->textures[ENGINE_KEY_TEXTURE] = LoadTexture("assets/prison_key.png");
	assets->textures[MAGNET_CARD_BLUE_TEXTURE] = LoadTexture("assets/blue_magnet_card.png");
	assets->textures[FLINT_TEXTURE] = LoadTexture("assets/flint.png");
	assets->textures[FLINT_ACTIVE_TEXTURE] = LoadTexture("assets/flint_active.png");
	assets->textures[NOTES_TEXTURE] = LoadTexture("assets/instructions.png");
	assets->textures[AMMONIUM_NITRATE_TEXTURE] = LoadTexture("assets/ammonium_nitrate.png");
	assets->textures[CELL_KEY_TEXTURE] = LoadTexture("assets/cell_key.png");
	assets->textures[MAGNET_CARD_GREEN_TEXTURE] = LoadTexture("assets/green_magnet_card.png");
	assets->textures[MAGNET_CARD_RED_TEXTURE] = LoadTexture("assets/red_magnet_card.png");
	assets->textures[BOMB_TEXTURE] = LoadTexture("assets/bomb.png");
	assets->textures[ROPE_TEXTURE] = LoadTexture("assets/rope.png");
	assets->textures[USB_KEY_TEXTURE] = LoadTexture("assets/usb_key.png");

	assets->textures[USE_AREA_TEXTURE] = LoadTexture("assets/Tiles/Default/Use_Area.png");
	assets->textures[DOOR_TEXTURE] = LoadTexture("assets/Tiles/Default/Door.png");
	assets->textures[DOOR_OPEN_TEXTURE] = LoadTexture("assets/Tiles/Default/Door_Open.png");
	
	
	assets->sounds[BUTTON_HOVER_SOUND] = LoadSound("assets/button_hover.mp3");
	assets->sounds[DOOR_OPEN_SOUND] = LoadSound("assets/door_open.mp3");
	assets->sounds[DOOR_ENGINE_OPEN_SOUND] = LoadSound("assets/engine_door_open.mp3");
	assets->sounds[DOOR_CLOSE_SOUND] = LoadSound("assets/door_close.mp3");
	assets->sounds[ITEM_PICKUP_SOUND] = LoadSound("assets/item_pickup.mp3");
    assets->sounds[KEY_PICKUP_SOUND] = LoadSound("assets/key_pickup.mp3");
	assets->sounds[CRAFT_SOUND] = LoadSound("assets/craft.mp3");
	assets->sounds[BOMB_SOUND] = LoadSound("assets/bomb.mp3");
	
}

void Assets_unload(Assets * assets) {
	for (int i = 0; i < MAP_TEXTURES_BUFFER_SIZE; i++) UnloadTexture(assets->mapTextures[i]);
	for (int i = 0; i < TEXTURES_BUFFER_SIZE; i++) UnloadTexture(assets->textures[i]);
	for (int i = 0; i < SOUNDS_BUFFER_SIZE; i++) UnloadSound(assets->sounds[i]);
}