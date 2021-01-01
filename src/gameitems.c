#include "includes/gameitems.h"
#include "includes/env.h"

// Engine key function
void useEngineKey(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]) {
    logger(LOG_DEBUG, "Using engine key!", "");
    if (Door_open(game->map, &game->doors[MOTOR1_DOOR], game->player->position, true))
        logger(LOG_DEBUG, "Engine room door is open!", "");
    if (Door_open(game->map, &game->doors[MOTOR2_DOOR], game->player->position, true))
        logger(LOG_DEBUG, "Engine room door is open!", "");

    
    
}

// Magnet card function
void useMagnetCardBlue(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]) {
    logger(LOG_DEBUG, "Using magnet card!", "");
    if (Door_open(game->map, &game->doors[MAGNET_DOOR2], game->player->position, true))
        Inventory_removeItem(game->player->inventory, MAGNET_CARD_BLUE);
}

void useMagnetCardGreen(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]) {
    logger(LOG_DEBUG, "Using magnet card!", "");
    if (Door_open(game->map, &game->doors[MAGNET_DOOR], game->player->position, true)) 
        Inventory_removeItem(game->player->inventory, MAGNET_CARD_GREEN);
    if (Door_open(game->map, &game->doors[MAGNET_DOOR1], game->player->position, true)) 
        Inventory_removeItem(game->player->inventory, MAGNET_CARD_GREEN);
}

void useMagnetCardRed(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]) {
    logger(LOG_DEBUG, "Using magnet card!", "");
    if (Door_open(game->map, &game->doors[MAGNET_DOOR3], game->player->position, true))
        Inventory_removeItem(game->player->inventory, MAGNET_CARD_RED);
}

// Flint inactive function
void useFlint(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]) {
    logger(LOG_DEBUG, "Using inactive flint!", "");
    Inventory_removeItem(game->player->inventory, FLINT);
    Inventory_addItem(game->player->inventory, items[FLINT_ACTIVE]);
}

// Flint inactive function
void useFlintActive(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]) {
    logger(LOG_DEBUG, "Using active flint!", "");
    Inventory_removeItem(game->player->inventory, FLINT_ACTIVE);
    Inventory_addItem(game->player->inventory, items[FLINT]);
}

// Notes function
void useNotes(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]) {
    logger(LOG_DEBUG, "Using Notes!", "");
    if (Inventory_contain(game->player->inventory, FLINT_ACTIVE)) {
        Inventory_removeItem(game->player->inventory, NOTES);
        Inventory_addItem(game->player->inventory, items[AMMONIUM_NITRATE]);
    }
    else
        logger(LOG_DEBUG, "You can't do that: Flint is not active!", "");
}

// Ammonium Nitrate function
void craftBomb(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]) {
    if (Inventory_contain(game->player->inventory, ROPE) && Inventory_contain(game->player->inventory, AMMONIUM_NITRATE)) {
        Inventory_removeItem(game->player->inventory, ROPE);
        Inventory_removeItem(game->player->inventory, AMMONIUM_NITRATE);
        Inventory_addItem(game->player->inventory, items[BOMB]);
        PlaySound(sounds[CRAFT_SOUND]);
    }
    else
        logger(LOG_DEBUG, "You must have the Rope and Ammonium Nitrate!", "");
}

// Bomb function
void useBomb(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]) {
    logger(LOG_DEBUG, "Using bomb!", "");
    if (Door_open(game->map, &game->doors[CELL_DOOR], game->player->position, true)) {
        logger(LOG_DEBUG, "Cell door is open!", "");
        Inventory_removeItem(game->player->inventory, BOMB);
        PlaySound(sounds[BOMB_SOUND]);
    }
}

// USB Key function

void useUSBKey(Game * game, Item items[MAX_ITEMS], Sound sounds[SOUND_COUNT]) {
    logger(LOG_DEBUG, "Using USB Key!", "");
}


GameItems * GameItems_new() {
	GameItems * gi = malloc(sizeof(GameItems));
    return gi;
}

void GameItems_init(GameItems * gameItems) {
    Sound item_pickup_sound = LoadSound("assets/item_pickup.mp3");
    Sound key_pickup_sound = LoadSound("assets/key_pickup.mp3");
    gameItems->sounds[CRAFT_SOUND] = LoadSound("assets/craft.mp3");
    gameItems->sounds[BOMB_SOUND] = LoadSound("assets/bomb.mp3");

    // SIGNATURE :
    // Item_new(int id, char * name, bool hasTexture, Texture2D texture)
    gameItems->items[ENGINE_KEY] = *Item_new(ENGINE_KEY, "Engines Key", true, LoadTexture("assets/prison_key.png"), key_pickup_sound);
    gameItems->use[ENGINE_KEY] = useEngineKey;

    gameItems->items[MAGNET_CARD_BLUE] = *Item_new(MAGNET_CARD_BLUE, "Magnet Card", true, LoadTexture("assets/blue_magnet_card.png"), item_pickup_sound);
    gameItems->use[MAGNET_CARD_BLUE] = useMagnetCardBlue;

    gameItems->items[FLINT] = *Item_new(FLINT, "Flint", true, LoadTexture("assets/flint.png"), item_pickup_sound);
    gameItems->use[FLINT] = useFlint;

    gameItems->items[FLINT_ACTIVE] = *Item_new(FLINT_ACTIVE, "Flint", true, LoadTexture("assets/flint_active.png"), item_pickup_sound);
    gameItems->use[FLINT_ACTIVE] = useFlintActive;

    gameItems->items[NOTES] = *Item_new(NOTES, "Notes", true, LoadTexture("assets/instructions.png"), item_pickup_sound);
    gameItems->use[NOTES] = useNotes;

    gameItems->items[MAGNET_CARD_GREEN] = *Item_new(MAGNET_CARD_GREEN, "Green Magnet Card", true, LoadTexture("assets/green_magnet_card.png"), item_pickup_sound);
    gameItems->use[MAGNET_CARD_GREEN] = useMagnetCardGreen;

    gameItems->items[MAGNET_CARD_RED] = *Item_new(MAGNET_CARD_RED, "Red Magnet Card", true, LoadTexture("assets/red_magnet_card.png"), item_pickup_sound);
    gameItems->use[MAGNET_CARD_RED] = useMagnetCardRed;

    gameItems->items[AMMONIUM_NITRATE] = *Item_new(AMMONIUM_NITRATE, "Ammonium Nitrate", true, LoadTexture("assets/ammonium_nitrate.png"), item_pickup_sound);
    gameItems->use[AMMONIUM_NITRATE] = craftBomb;

    gameItems->items[ROPE] = *Item_new(ROPE, "Rope", true, LoadTexture("assets/rope.png"), item_pickup_sound);
    gameItems->use[ROPE] = craftBomb;
    
    gameItems->items[BOMB] = *Item_new(BOMB, "Bomb", true, LoadTexture("assets/bomb.png"), item_pickup_sound);
    gameItems->use[BOMB] = useBomb;

    gameItems->items[USB_KEY] = *Item_new(USB_KEY, "USB Key", true, LoadTexture("assets/usb_key.png"), item_pickup_sound);
    gameItems->use[USB_KEY] = useUSBKey;

}

void GameItems_control(Game * game, GameItems * gameItems) {
	Item item = game->player->inventory->items[game->player->inventory->selected];
	if (IsKeyPressed(KEY_E) && item.name != 0x0) gameItems->use[item.id](game, gameItems->items, gameItems->sounds);
}
