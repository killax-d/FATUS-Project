#include "includes/gameitems.h"
#include "includes/env.h"

// Engine key function
void useEngineKey(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    logger(LOG_DEBUG, "Using engine key!", "");
    if (Door_open(game->map, game->doors[MOTOR1_DOOR], game->player->position, true) & Door_open(game->map, game->doors[MOTOR2_DOOR], game->player->position, true)) {
        Inventory_removeItem(game->player->inventory, ENGINE_KEY);
        ObjectivesNotes_finish(objectives,FIND_ENGINES_KEY);
    }
}

// Magnet card function
void useMagnetCardBlue(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    logger(LOG_DEBUG, "Using magnet card!", "");
    if (Door_open(game->map, game->doors[MAGNET_DOOR2], game->player->position, true)) {
        Inventory_removeItem(game->player->inventory, MAGNET_CARD_BLUE);
        ObjectivesNotes_finish(objectives, FIND_BLUE_MAGNET_CARD);
    }
}

void useMagnetCardGreen(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    logger(LOG_DEBUG, "Using magnet card!", "");
    if (Door_open(game->map, game->doors[MAGNET_DOOR1], game->player->position, true)) {
        Inventory_removeItem(game->player->inventory, MAGNET_CARD_GREEN);
        ObjectivesNotes_finish(objectives, FIND_GREEN_MAGNET_CARD);
    }
}

void useMagnetCardYellow(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    logger(LOG_DEBUG, "Using magnet card!", "");
    if (Door_open(game->map, game->doors[MAGNET_DOOR], game->player->position, true)) {
        Inventory_removeItem(game->player->inventory, MAGNET_CARD_YELLOW);
        ObjectivesNotes_finish(objectives, FIND_YELLOW_MAGNET_CARD);
    }        
}

void useMagnetCardRed(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    logger(LOG_DEBUG, "Using magnet card!", "");
    if (Door_open(game->map, game->doors[MAGNET_DOOR3], game->player->position, true)) {
        Inventory_removeItem(game->player->inventory, MAGNET_CARD_RED);
        ObjectivesNotes_finish(objectives, FIND_RED_MAGNET_CARD);
    }
}

// Flint inactive function
void useFlint(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    logger(LOG_DEBUG, "Using inactive flint!", "");
    Inventory_removeItem(game->player->inventory, FLINT);
    Inventory_addItem(game->player->inventory, items[FLINT_ACTIVE]);
}

// Flint inactive function
void useFlintActive(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    logger(LOG_DEBUG, "Using active flint!", "");
    Inventory_removeItem(game->player->inventory, FLINT_ACTIVE);
    Inventory_addItem(game->player->inventory, items[FLINT]);
}

// Notes function
void useNotes(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    logger(LOG_DEBUG, "Using notes!", "");
    objectives->visible = !objectives->visible;
}

// Ammonium Nitrate function
void craftBomb(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    if (Inventory_contain(game->player->inventory, ROPE) && Inventory_contain(game->player->inventory, AMMONIUM_NITRATE)) {
        Inventory_removeItem(game->player->inventory, ROPE);
        Inventory_removeItem(game->player->inventory, AMMONIUM_NITRATE);
        Inventory_addItem(game->player->inventory, items[BOMB]);
        PlaySound(assets->sounds[CRAFT_SOUND]);
    }
    else
        logger(LOG_DEBUG, "You must have the Rope and Ammonium Nitrate!", "");
}

// Bomb function
void useBomb(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    logger(LOG_DEBUG, "Using bomb!", "");
    if (Door_open(game->map, game->doors[CELL_DOOR], game->player->position, true)) {
        logger(LOG_DEBUG, "Cell door is open!", "");
        Inventory_removeItem(game->player->inventory, BOMB);
        PlaySound(assets->sounds[BOMB_SOUND]);
        ObjectivesNotes_finish(objectives, OPEN_CELL_OBJECTIVE);
    }
}

// USB Key function

void useUSBKey(Game * game, Item * items[MAX_ITEMS], Assets * assets, ObjectivesNotes * objectives) {
    logger(LOG_DEBUG, "Using USB Key!", "");
    ObjectivesNotes_finish(objectives,FIND_USB_KEY);

    if(CheckCollisionPointCircle(game->player->position, (Vector2) {5580, 1672}, 96.f))
        Game_end(game);
}

GameItems * GameItems_new() {
	GameItems * gi = malloc(sizeof(GameItems));
    return gi;
}

void GameItems_init(GameItems * gameItems, Assets * assets) {
    // SIGNATURE :
    // Item_new(int id, char * name, bool hasTexture, Texture2D texture)
    gameItems->items[ENGINE_KEY] = Item_new(ENGINE_KEY, "Engines Key", true, assets->textures[ENGINE_KEY_TEXTURE], assets->sounds[KEY_PICKUP_SOUND]);
    gameItems->use[ENGINE_KEY] = useEngineKey;

    gameItems->items[MAGNET_CARD_BLUE] = Item_new(MAGNET_CARD_BLUE, "Magnet Card", true, assets->textures[MAGNET_CARD_BLUE_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[MAGNET_CARD_BLUE] = useMagnetCardBlue;

    gameItems->items[FLINT] = Item_new(FLINT, "Flint", true, assets->textures[FLINT_ACTIVE_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[FLINT] = useFlint;

    gameItems->items[FLINT_ACTIVE] = Item_new(FLINT_ACTIVE, "Flint", true, assets->textures[FLINT_ACTIVE_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[FLINT_ACTIVE] = useFlintActive;

    gameItems->items[NOTES] = Item_new(NOTES, "Notes", true, assets->textures[NOTES_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[NOTES] = useNotes;

    gameItems->items[AMMONIUM_NITRATE] = Item_new(AMMONIUM_NITRATE, "Ammonium Nitrate", true, assets->textures[AMMONIUM_NITRATE_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[AMMONIUM_NITRATE] = craftBomb;

    gameItems->items[MAGNET_CARD_GREEN] = Item_new(MAGNET_CARD_GREEN, "Green Magnet Card", true, assets->textures[MAGNET_CARD_GREEN_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[MAGNET_CARD_GREEN] = useMagnetCardGreen;

    gameItems->items[MAGNET_CARD_YELLOW] = Item_new(MAGNET_CARD_YELLOW, "Yellow Magnet Card", true, assets->textures[MAGNET_CARD_YELLOW_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[MAGNET_CARD_YELLOW] = useMagnetCardYellow;

    gameItems->items[MAGNET_CARD_RED] = Item_new(MAGNET_CARD_RED, "Red Magnet Card", true, assets->textures[MAGNET_CARD_RED_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[MAGNET_CARD_RED] = useMagnetCardRed;

    gameItems->items[ROPE] = Item_new(ROPE, "Rope", true, assets->textures[ROPE_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[ROPE] = craftBomb;
    
    gameItems->items[BOMB] = Item_new(BOMB, "Bomb", true, assets->textures[BOMB_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[BOMB] = useBomb;

    gameItems->items[USB_KEY] = Item_new(USB_KEY, "USB Key", true, assets->textures[USB_KEY_TEXTURE], assets->sounds[ITEM_PICKUP_SOUND]);
    gameItems->use[USB_KEY] = useUSBKey;

}

void GameItems_control(Game * game, GameItems * gameItems, Assets * assets, ObjectivesNotes * objectives) {
	Item * item = game->player->inventory->items[game->player->inventory->selected];
	if (IsKeyPressed(KEY_E) && item != 0x0) gameItems->use[item->id](game, gameItems->items, assets, objectives);
}
