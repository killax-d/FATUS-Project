#include "raylib.h"
#include "stdio.h"
#include <time.h>

#include "./includes/player.h"
#include "./includes/item.h"
#include "./includes/inventory.h"
#include "./includes/game.h"
#include "./includes/sprite.h"
#include "./includes/map.h"

#define G 400
#define PLAYER_JUMP_SPD 350.0f

// SPRITES
#define TEXTURE_SCALE 48
#define OFFSET 96
GameMap map;

const int screenWidth = 800;
const int screenHeight = 600;
Player player = {(Vector2){OFFSET + 6.5 * TEXTURE_SCALE, OFFSET + 13 * TEXTURE_SCALE}, (Vector2){100.f, 100.f}, 1.75f, 0.f, (Vector2){1.f, 1.f}, (Color){125, 125, 125, 255}, (Inventory){{},0 , 0, ""}, -1};
Camera2D camera = { 0 };
char coords[30];

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
static void UpdateCameraCenter();

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

    logger(LOG_INFO, "Initializing sprites", "");

    // INIT SPRITES
    Sprite sprite[] = {
        {{0, 0, 0, 0 }, 0, BLACK },
        {{ OFFSET + 1 * TEXTURE_SCALE, OFFSET + 8 * TEXTURE_SCALE, 12 * TEXTURE_SCALE, 10 * TEXTURE_SCALE }, 0, LIGHTGRAY },
        {{ OFFSET + 1 * TEXTURE_SCALE, OFFSET + 24 * TEXTURE_SCALE, 12 * TEXTURE_SCALE, 10 * TEXTURE_SCALE }, 0, LIGHTGRAY },
        {{ OFFSET + 13 * TEXTURE_SCALE, OFFSET + 8 * TEXTURE_SCALE, 14 * TEXTURE_SCALE, 26 * TEXTURE_SCALE }, 0, LIGHTGRAY },
        {{ OFFSET + 27 * TEXTURE_SCALE, OFFSET + 13 * TEXTURE_SCALE, 59 * TEXTURE_SCALE, 16 * TEXTURE_SCALE }, 0, LIGHTGRAY },
        {{ OFFSET + 40 * TEXTURE_SCALE, OFFSET + 1 * TEXTURE_SCALE, 25 * TEXTURE_SCALE, 12 * TEXTURE_SCALE }, 0, LIGHTGRAY },
        {{ OFFSET + 40 * TEXTURE_SCALE, OFFSET + 29 * TEXTURE_SCALE, 25 * TEXTURE_SCALE, 12 * TEXTURE_SCALE }, 0, LIGHTGRAY },
        {{ OFFSET + 34 * TEXTURE_SCALE, OFFSET + 1 * TEXTURE_SCALE, 6 * TEXTURE_SCALE, 5 * TEXTURE_SCALE }, 0, LIGHTGRAY },
        {{ OFFSET + 34 * TEXTURE_SCALE, OFFSET + 36 * TEXTURE_SCALE, 6 * TEXTURE_SCALE, 5 * TEXTURE_SCALE }, 0, LIGHTGRAY },
        {{ OFFSET + 0 * TEXTURE_SCALE, OFFSET + 7 * TEXTURE_SCALE, 28 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 0 * TEXTURE_SCALE, OFFSET + 34 * TEXTURE_SCALE, 28 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 0 * TEXTURE_SCALE, OFFSET + 18 * TEXTURE_SCALE, 12 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 0 * TEXTURE_SCALE, OFFSET + 23 * TEXTURE_SCALE, 12 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 28 * TEXTURE_SCALE, OFFSET + 12 * TEXTURE_SCALE, 20 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 28 * TEXTURE_SCALE, OFFSET + 29 * TEXTURE_SCALE, 20 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 56 * TEXTURE_SCALE, OFFSET + 12 * TEXTURE_SCALE, 31 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 56 * TEXTURE_SCALE, OFFSET + 29 * TEXTURE_SCALE, 31 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 33 * TEXTURE_SCALE, OFFSET + 0 * TEXTURE_SCALE, 33 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 33 * TEXTURE_SCALE, OFFSET + 41 * TEXTURE_SCALE, 33 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 33 * TEXTURE_SCALE, OFFSET + 6 * TEXTURE_SCALE, 7 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 33 * TEXTURE_SCALE, OFFSET + 35 * TEXTURE_SCALE, 7 * TEXTURE_SCALE, 1 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 0 * TEXTURE_SCALE, OFFSET + 8 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 10 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 0 * TEXTURE_SCALE, OFFSET + 24 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 10 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 12 * TEXTURE_SCALE, OFFSET + 8 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 3 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 12 * TEXTURE_SCALE, OFFSET + 31 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 3 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 12 * TEXTURE_SCALE, OFFSET + 15 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 12 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 27 * TEXTURE_SCALE, OFFSET + 8 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 10 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 27 * TEXTURE_SCALE, OFFSET + 24 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 10 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 33 * TEXTURE_SCALE, OFFSET + 1 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 5 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 33 * TEXTURE_SCALE, OFFSET + 36 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 5 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 39 * TEXTURE_SCALE, OFFSET + 7 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 5 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 39 * TEXTURE_SCALE, OFFSET + 30 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 5 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 65 * TEXTURE_SCALE, OFFSET + 1 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 17 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 65 * TEXTURE_SCALE, OFFSET + 24 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 17 * TEXTURE_SCALE }, 1, GRAY },
        {{ OFFSET + 86 * TEXTURE_SCALE, OFFSET + 13 * TEXTURE_SCALE, 1 * TEXTURE_SCALE, 16 * TEXTURE_SCALE }, 1, GRAY }
    };

    logger(LOG_INFO, "Initializing sprites ended", "");
    logger(LOG_INFO, "Initializing map", "");
    map = (GameMap){sizeof(sprite)/sizeof(sprite[0])};
    logger(LOG_INFO, "Copying sprites...", "");
    for (int i = 0; i < map.size; i++) map.sprite[i] = sprite[i];
    logger(LOG_INFO, "Initializing map ended", "");
}

// Update game (one frame)
void UpdateGame(void) {
    float deltaTime = GetFrameTime();
    UpdatePlayer(deltaTime);
    UpdateCameraCenter();
    sprintf(coords, "X: %.2f\nY: %.2f", camera.target.x, camera.target.y);
}

// Update player (one frame)
void UpdatePlayer(float delta) {
    if (IsKeyDown(KEY_ONE)) player.inventory.selected = 0;
    if (IsKeyDown(KEY_TWO)) player.inventory.selected = 1;
    if (IsKeyDown(KEY_THREE)) player.inventory.selected = 2;
    if (IsKeyDown(KEY_FOUR)) player.inventory.selected = 3;
    if (IsKeyDown(KEY_FIVE)) player.inventory.selected = 4;
    if (IsKeyDown(KEY_SIX)) player.inventory.selected = 5;
    if (IsKeyDown(KEY_SEVEN)) player.inventory.selected = 6;
    if (IsKeyDown(KEY_EIGHT)) player.inventory.selected = 7;
    if (IsKeyDown(KEY_NINE)) player.inventory.selected = 8;

    if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
        camera.zoom += ((float)GetMouseWheelMove()*0.05f);
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f) camera.zoom = 0.25f;
    } else {
        player.inventory.selected -= GetMouseWheelMove();
        if (player.inventory.selected < 0) player.inventory.selected = 0;
        if (player.inventory.selected > 8) player.inventory.selected = 8;
    }

	if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) player.sprinting = 0;
	else player.sprinting = -1;

    Vector2 speed = {player.speed.x * ((player.sprinting) ? 1.f : player.acceleration) * delta,
                    player.speed.y * ((player.sprinting) ? 1.f : player.acceleration) * delta};

    int collisions[] = {0, 0, 0, 0}; // NORTH EAST SOUTH WEST

    for (int i = 0; i < map.size; i++) {
        Sprite ei = map.sprite[i];
        Vector2 p = player.position;
        if (ei.blocking &&
            ei.rect.y + ei.rect.height <= p.y+20 &&
            ei.rect.y + ei.rect.height >= p.y-20 &&
            ei.rect.x <= p.x+20-speed.x &&
            ei.rect.x + ei.rect.width >= p.x-20+speed.x)
        {
            collisions[0] = 1;
        }
        if (ei.blocking &&
            ei.rect.x <= p.x+20 &&
            ei.rect.x > p.x-20 &&
            ei.rect.y <= p.y+20-speed.y &&
            ei.rect.y + ei.rect.height >= p.y-20+speed.y)
        {
            collisions[1] = 1;
        }
        if (ei.blocking &&
            ei.rect.y <= p.y+20 &&
            ei.rect.y > p.y-20 &&
            ei.rect.x <= p.x+20-speed.x &&
            ei.rect.x + ei.rect.width >= p.x-20+speed.x)
        {
            collisions[2] = 1;
        }
        if (ei.blocking &&
            ei.rect.x + ei.rect.width <= p.x+20 &&
            ei.rect.x + ei.rect.width >= p.x-20 &&
            ei.rect.y <= p.y+20-speed.y &&
            ei.rect.y + ei.rect.height >= p.y-20+speed.y)
        {
            collisions[3] = 1;
        }
    }

	// Note: Keyboard mapping is only QWERTY
    // UP AND DOWN
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && !collisions[0]) player.position.y -= speed.y;
    if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && !collisions[2]) player.position.y += speed.y;
    // RIGHT AND LEFT
    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && !collisions[1]) player.position.x += speed.x;
    if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && !collisions[3]) player.position.x -= speed.x;
    camera.offset = player.position;
}

// Draw game (one frame)
void DrawGame(void) {
    BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera);
            // DRAW MAP
            for (int i = 0; i < map.size; i++) DrawRectangleRec(map.sprite[i].rect, map.sprite[i].color);

            DrawRectangle(player.position.x - 20, player.position.y - 20, 40, 40, RED);
        EndMode2D();

        Inventory_draw(20, GetScreenHeight() - 20 - 48, player.inventory);

        DrawFPS(GetScreenWidth()-80, 10);
        DrawText("Touches :", 20, 20, 10, WHITE);
        DrawText("- ZQSD ou Flèches pour se diriger", 40, 40, 10, WHITE);
        DrawText("- Shift pour sprinter", 40, 60, 10, WHITE);
        DrawText("- Molette changer d'item", 40, 80, 10, WHITE);
        DrawText("- Ctrl + Molette pour zoomer", 40, 100, 10, WHITE);
        DrawText(coords, GetScreenWidth()-60, 40, 10, DARKGRAY);

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

void UpdateCameraCenter()
{
    camera.target = player.position;
    camera.offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
}
