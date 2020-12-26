#include "raylib.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

#include "./includes/game.h"
#include "./includes/gameitems.h"
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
static void InitGame(Camera2D * camera, Menu * menu, Game * game, GameItems * gamesItems);
// Update game (one frame)
static void UpdateGame(Camera2D * camera, Menu * menu, Game * game, GameItems * gamesItems);
// Update player (one frame)
static void UpdatePlayer(Camera2D * camera, Game * game, float delta);
// Draw game (one frame)
static void DrawGame(Camera2D * camera, Menu * menu, Game * game);
// Unload game
static void UnloadGame(Camera2D * camera, Game * game); 
// Update and Draw (one frame)
static void UpdateDrawFrame(Camera2D * camera, Menu * menu, Game * game, GameItems * gamesItems);
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

    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogCallback(logger);
    InitWindow(WINDOW_BASE_WIDTH, WINDOW_BASE_HEIGHT, "50NuancesDeCodes - by IMT GRAY TEAM");
    InitAudioDevice();
    
    InitGame(&camera, &menu, &game, &gameItems);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame(&camera, &menu, &game, &gameItems);
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame(&camera, &game);     // Unload loaded data (textures, sounds, models...)
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Initialize game variables
void InitGame(Camera2D * camera, Menu * menu, Game * game, GameItems * gamesItems) {
    // INIT GAME
    Menu_init(menu);
    Game_init(game);
    GameItems_init(gamesItems);

    // INIT CAMERA
    camera->target = game->player->position;
    camera->offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
    
    // ADD ITEMS FOR TEST
    game->player->inventory->items[0] = gamesItems->items[PRISON_KEY];
    game->player->inventory->items[1] = gamesItems->items[MAGNET_CARD];
    game->player->inventory->items[2] = gamesItems->items[FLINT];
    game->player->inventory->items[3] = gamesItems->items[NOTES];
}

// Update game (one frame)
void UpdateGame(Camera2D * camera, Menu * menu, Game * game, GameItems * gamesItems) {
    if (game->state == -1) Menu_update(menu, game);
    else {
        float deltaTime = GetFrameTime();
        GameItems_control(game, gamesItems);
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
void DrawGame(Camera2D * camera, Menu * menu, Game * game) {
    if (game->state == -1) Menu_draw(menu);
    if (game->state == 0) Game_draw(camera, game);
}

// Unload game
void UnloadGame(Camera2D * camera, Game * game) {
    free(&camera);
    free(&game->player->inventory);
    free(&game->player->collider);
    free(&game->player);
    free(&game->map);
    free(&game);
}

// Update and Draw (one frame)
void UpdateDrawFrame(Camera2D * camera, Menu * menu, Game * game, GameItems * gamesItems)
{
    UpdateGame(camera, menu, game, gamesItems);
    DrawGame(camera, menu, game);
}

void UpdateCameraCenter(Camera2D * camera, Game * game)
{
    camera->target = game->player->position;
    camera->offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
}
