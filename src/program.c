#include "raylib.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

#include "./includes/game.h"
#include "./includes/gameitems.h"
#define COORDS_BUFFER_LENGTH 30
#define WINDOW_BASE_WIDTH 800
#define WINDOW_BASE_HEIGHT 600

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
static void InitGame(Camera2D * camera, Game * game, GameItems * gamesItems);
// Update game (one frame)
static void UpdateGame(Camera2D * camera, Game * game, GameItems * gamesItems, char coords[COORDS_BUFFER_LENGTH]);
// Update player (one frame)
static void UpdatePlayer(Camera2D * camera, Game * game, float delta);
// Draw game (one frame)
static void DrawGame(Camera2D * camera, Game * game, char coords[COORDS_BUFFER_LENGTH]);
// Unload game
static void UnloadGame(Camera2D * camera, Game * game); 
// Update and Draw (one frame)
static void UpdateDrawFrame(Camera2D * camera, Game * game, GameItems * gamesItems, char coords[COORDS_BUFFER_LENGTH]);
// Update camera position
static void UpdateCameraCenter(Camera2D * camera, Game * game);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Camera2D camera = {0};
    Game game;
    GameItems gameItems;
    char coords[COORDS_BUFFER_LENGTH];

    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogCallback(logger);
    InitWindow(WINDOW_BASE_WIDTH, WINDOW_BASE_HEIGHT, "50NuancesDeCodes - by IMT GRAY TEAM");

    InitGame(&camera, &game, &gameItems);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame(&camera, &game, &gameItems, coords);
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
void InitGame(Camera2D * camera, Game * game, GameItems * gamesItems) {
    camera->target = game->player->position;
    camera->offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;

    GameItems_init(gamesItems);
    // INIT GAME
    Game_init(game);

    // ADD ITEMS FOR TEST
    game->player->inventory->items[0] = gamesItems->items[PRISON_KEY];
    game->player->inventory->items[1] = gamesItems->items[MAGNET_CARD];
    game->player->inventory->items[2] = gamesItems->items[FLINT];
}

// Update game (one frame)
void UpdateGame(Camera2D * camera, Game * game, GameItems * gamesItems, char coords[COORDS_BUFFER_LENGTH]) {
    float deltaTime = GetFrameTime();
    GameItems_control(game, gamesItems);
    UpdatePlayer(camera, game, deltaTime);
    UpdateCameraCenter(camera, game);
    sprintf(coords, "X: %.2f\nY: %.2f", camera->target.x, camera->target.y);
}

// Update player (one frame)
void UpdatePlayer(Camera2D * camera, Game * game, float delta) {
    Player_control(camera, game->player);
    Player_move(game->map, game->player, delta);
}

// Draw game (one frame)
void DrawGame(Camera2D * camera, Game * game, char coords[COORDS_BUFFER_LENGTH]) {
    BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(*camera);
            // DRAW MAP
            Map_draw(game->map);

            // DRAW PLAYER
            Player_draw(game->player);
        EndMode2D();

        // DRAW INVENTORY
        Inventory_draw(20, GetScreenHeight() - 20 - 48, game->player->inventory);

        DrawFPS(GetScreenWidth()-80, 10);
        DrawText("Touches :", 20, 20, 10, WHITE);
        DrawText("- ZQSD ou Flèches pour se diriger", 40, 40, 10, WHITE);
        DrawText("- Shift pour sprinter", 40, 60, 10, WHITE);
        DrawText("- Molette pour changer d'item", 40, 80, 10, WHITE);
        DrawText("- Ctrl + Molette pour zoomer", 40, 100, 10, WHITE);
        DrawText(coords, GetScreenWidth()-60, 40, 10, DARKGRAY);

    EndDrawing();
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
void UpdateDrawFrame(Camera2D * camera, Game * game, GameItems * gamesItems, char coords[COORDS_BUFFER_LENGTH])
{
    UpdateGame(camera, game, gamesItems, coords);
    DrawGame(camera, game, coords);
}

void UpdateCameraCenter(Camera2D * camera, Game * game)
{
    camera->target = game->player->position;
    camera->offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
}
