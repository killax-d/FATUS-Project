#include "raylib.h"
#include "stdio.h"
#include <time.h>

#include "./includes/player.h"
#include "./includes/item.h"
#include "./includes/inventory.h"
#include "./includes/game.h"

#define G 400
#define PLAYER_JUMP_SPD 350.0f

const int screenWidth = 800;
const int screenHeight = 600;
Player player = {(Vector2){200, 200}, (Vector2){100.f, 100.f}, 1.75f, 0.f, (Vector2){1.f, 1.f}, (Color){125, 125, 125, 255}, (Inventory){{}, 0, ""}, -1};
Camera2D camera = { 0 };
char coords[20];

// Custom logger
static void logger(int msgType, const char *text, va_list args)
{
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);

    switch (msgType)
    {
        case LOG_INFO: printf("[INFO] : "); break;
        case LOG_ERROR: printf("[ERROR]: "); break;
        case LOG_WARNING: printf("[WARN] : "); break;
        case LOG_DEBUG: printf("[DEBUG]: "); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);                                 // Initialize game
static void UpdateGame(void);                               // Update game (one frame)
static void UpdatePlayer(float delta);                      // Update player (one frame)
static void DrawGame(void);                                 // Draw game (one frame)
static void UnloadGame(void);                               // Unload game
static void UpdateDrawFrame(void);                          // Update and Draw (one frame)
void UpdateCameraCenter(Camera2D *camera, Player *player, int width, int height);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogCallback(logger);
    InitWindow(screenWidth, screenHeight, "50NuancesDeCodes - by IMT GRAY TEAM");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Initialize game variables
void InitGame() {
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2, screenHeight/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

}

// Update game (one frame)
void UpdateGame(void) {
    float deltaTime = GetFrameTime();
    UpdatePlayer(deltaTime);
    UpdateCameraCenter(&camera, &player, screenWidth, screenHeight);
    sprintf(coords, "X: %.2f\nY: %.2f", player.position.x, player.position.y);
}

// Update player (one frame)
void UpdatePlayer(float delta) {
	if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) player.sprinting = 0;
	else player.sprinting = -1;

	// Note: Keyboard mapping is only QWERTY
    // LEFT AND RIGHT
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.position.x -= player.speed.x * ((player.sprinting) ? 1.f : player.acceleration) * delta;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.position.x += player.speed.x * ((player.sprinting) ? 1.f : player.acceleration) * delta;
    // UP AND DOWN
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) player.position.y -= player.speed.y * ((player.sprinting) ? 1.f : player.acceleration) * delta;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) player.position.y += player.speed.y * ((player.sprinting) ? 1.f : player.acceleration) * delta;
}

// Draw game (one frame)
void DrawGame(void) {
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
        DrawRectangle(player.position.x, player.position.y, 48, 96, GREEN);
        DrawRectangleLines(player.position.x, player.position.y, 48, 96, RED);

        DrawFPS(10, 10);
        DrawText(coords, 10, 32, 16, WHITE);

    EndDrawing();
}

// Unload game
void UnloadGame(void) {

}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

// Camera center
void UpdateCameraCenter(Camera2D *camera, Player *player, int width, int height)
{
    camera->offset = (Vector2){ width/2, height/2 };
    camera->target = player->position;
}
