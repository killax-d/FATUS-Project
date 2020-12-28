#include "raylib.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

#include "./includes/game.h"
#include "./includes/gameitems.h"
#include "./includes/minimap.h"
#include "./includes/menu.h"
#define WINDOW_BASE_WIDTH 800
#define WINDOW_BASE_HEIGHT 600

#define DEBUG 0

// Custom logger
void logger(int msgType, const char *text, va_list args)
{
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);

    switch (msgType)
    {
        case LOG_INFO: printf("[INFO] : "); break;
        case LOG_ERROR: printf("[ERROR] : "); break;
        case LOG_WARNING: printf("[WARN] : "); break;
        case LOG_DEBUG: printf("[DEBUG] : "); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
// Initialize game
static void InitGame(Camera2D * camera, Minimap * minimap, Menu * menu, Game * game, GameItems * gameItems);
// Update game (one frame)
static void UpdateGame(Camera2D * camera, Minimap * minimap, Menu * menu, Game * game, GameItems * gameItems);
// Update player (one frame)
static void UpdatePlayer(Camera2D * camera, Game * game, float delta);
// Draw game (one frame)
static void DrawGame(Camera2D * camera, Minimap * minimap, Menu * menu, Game * game);
// Unload game
static void UnloadGame(Camera2D * camera, Minimap * minimap, Menu * menu, Game * game, GameItems * gameItems); 
// Update and Draw (one frame)
static void UpdateDrawFrame(Camera2D * camera, Minimap * minimap, Menu * menu, Game * game, GameItems * gameItems);
// Update camera position
static void UpdateCameraCenter(Camera2D * camera, Game * game);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Camera2D camera = {0};
    Game game;
    Menu menu;
    GameItems gameItems;
    Minimap minimap = { 20, 20, 200, 200 };

    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogCallback(logger);
    InitWindow(WINDOW_BASE_WIDTH, WINDOW_BASE_HEIGHT, "50NuancesDeCodes - by IMT GRAY TEAM");
    
    InitGame(&camera, &minimap, &menu, &game, &gameItems);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame(&camera, &minimap, &menu, &game, &gameItems);
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame(&camera, &minimap, &menu, &game, &gameItems);     // Unload loaded data (textures, sounds, models...)
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Initialize game variables
void InitGame(Camera2D * camera, Minimap * minimap, Menu * menu, Game * game, GameItems * gameItems) {
    InitAudioDevice();

    // INIT GAME
    Menu_init(menu);
    Game_init(game);
    GameItems_init(gameItems);
    Minimap_init(minimap);

    // INIT CAMERA
    camera->target = game->player->position;
    camera->offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
    camera->rotation = 0.0f;
    camera->zoom = 0.5f;
    
    // ADD ITEMS FOR TEST
    game->player->inventory->items[0] = gameItems->items[PRISON_KEY];
    game->player->inventory->items[1] = gameItems->items[MAGNET_CARD];
    game->player->inventory->items[2] = gameItems->items[FLINT];
    game->player->inventory->items[3] = gameItems->items[NOTES];
}

// Update game (one frame)
void UpdateGame(Camera2D * camera, Minimap * minimap, Menu * menu, Game * game, GameItems * gameItems) {
    if (game->state == -1) Menu_update(menu, game);
    else {
        float deltaTime = GetFrameTime();
        Minimap_control(minimap);
        GameItems_control(game, gameItems);
        UpdatePlayer(camera, game, deltaTime);
        UpdateCameraCenter(camera, game);
    }
}

// Update player (one frame)
void UpdatePlayer(Camera2D * camera, Game * game, float delta) {
    Player_control(camera, game->player);
    Player_move(game->map, game->player, delta);
    sprintf(game->coordsText, "X: %d / %.2f\nY: %d / %.2f", 
            (int) game->player->position.x/MAP_TEXTURE_SCALE, 
            game->player->position.x, 
            (int) game->player->position.y/MAP_TEXTURE_SCALE, 
            game->player->position.y);
}

// Draw game (one frame)
void DrawGame(Camera2D * camera, Minimap * minimap, Menu * menu, Game * game) {
    BeginDrawing();
    if (game->state == -1) Menu_draw(menu);
    if (game->state == 0) {
        Game_draw(camera, game);
        Minimap_draw(minimap, game);
    }
    EndDrawing();
}

// Unload game
void UnloadGame(Camera2D * camera, Minimap * minimap, Menu * menu, Game * game, GameItems * gameItems) {
    UnloadTexture(game->player->texture);
    for (int i = 0; i < MAX_ITEMS; i++) {
        UnloadTexture(gameItems->items[i].texture);
        free(&gameItems->items[i]);
    }
    for (int i = 0; i < BUTTONS_COUNT; i++) {
        UnloadSound(menu->buttons[i]->sound);
        free(&menu->buttons[i]);
    }
    for (int y = 0; y < MAP_HEIGHT; y++)
        for(int x = 0; x < MAP_WIDTH; x++)
            free(&game->map->sprite[y][x]);
    free(&camera);
    free(&minimap);
    free(&game->player->inventory);
    free(&game->player->collider);
    free(&game->player);
    free(&game->map);
    free(&game);
    CloseAudioDevice();
}

// Update and Draw (one frame)
void UpdateDrawFrame(Camera2D * camera, Minimap * minimap, Menu * menu, Game * game, GameItems * gameItems)
{
    UpdateGame(camera, minimap, menu, game, gameItems);
    DrawGame(camera, minimap, menu, game);
}

void UpdateCameraCenter(Camera2D * camera, Game * game)
{
    camera->target = game->player->position;
    camera->offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
}
