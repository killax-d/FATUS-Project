#include "raylib.h"
#include "stdio.h"
#include <time.h>
#include <math.h>

#include "./includes/game.h"

const int screenWidth = 800;
const int screenHeight = 600;
Player player = {(Vector2){MAP_TEXTURE_SCALE * (MAP_WIDTH/2), MAP_TEXTURE_SCALE * (MAP_HEIGHT/2)}, (Vector2){200.f, 200.f}, 1.75f, 0.f, (Vector2){1.f, 1.f}, (Color){125, 125, 125, 255}, (Inventory){{},0 , 0, "", ""}, -1, 0, -1, {}};
Camera2D camera = { 0 };
Game game = (Game) {};
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
    player.texture = LoadTexture("assets/sprite_player.png");

    // INIT MAP
    Game_initMap(&game);

    player.inventory.items[0] = (Item) {0, "Prison Key", true, LoadTexture("assets/prison_key.png")};
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

    sprintf(player.inventory.selectedText, "Selected: %s", player.inventory.items[player.inventory.selected].name);

	player.sprinting = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    Vector2 speed = {player.speed.x * ((player.sprinting) ? player.acceleration : 1.f) * delta,
                    player.speed.y * ((player.sprinting) ? player.acceleration : 1.f) * delta};

    int collisions[] = {0, 0, 0, 0}; // NORTH EAST SOUTH WEST

    for (int i = -1; i <= 1; i++) {
        int location[2] = {(int) (player.position.x/32), (int) (player.position.y/32)};

        Vector2 p = player.position;
        Sprite ei = game.map.sprite[location[1]-1][location[0]+i];
        if (ei.blocking &&
            ei.rect.y + ei.rect.height <= p.y+20 &&
            ei.rect.y + ei.rect.height >= p.y-20 &&
            ei.rect.x <= p.x+20-speed.x &&
            ei.rect.x + ei.rect.width >= p.x-20+speed.x)
        {
            collisions[0] = 1;
        }
        ei = game.map.sprite[location[1]+i][location[0]+1];
        if (ei.blocking &&
            ei.rect.x <= p.x+20 &&
            ei.rect.x > p.x-20 &&
            ei.rect.y <= p.y+20-speed.y &&
            ei.rect.y + ei.rect.height >= p.y-20+speed.y)
        {
            collisions[1] = 1;
        }
        ei = game.map.sprite[location[1]+1][location[0]+i];
        if (ei.blocking &&
            ei.rect.y <= p.y+20 &&
            ei.rect.y > p.y-20 &&
            ei.rect.x <= p.x+20-speed.x &&
            ei.rect.x + ei.rect.width >= p.x-20+speed.x)
        {
            collisions[2] = 1;
        }
        ei = game.map.sprite[location[1]+i][location[0]-1];
        if (ei.blocking &&
            ei.rect.x + ei.rect.width <= p.x+20 &&
            ei.rect.x + ei.rect.width >= p.x-20 &&
            ei.rect.y <= p.y+20-speed.y &&
            ei.rect.y + ei.rect.height >= p.y-20+speed.y)
        {
            collisions[3] = 1;
        }
    }

    bool UP = (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W));
    bool DOWN = (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S));
    bool LEFT = (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A));
    bool RIGHT = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D));

    // Limit diagonal movements
    if ((UP || DOWN) 
        && (LEFT || RIGHT)
        && !(LEFT && RIGHT))
    {
        speed = (Vector2) {(speed.x*0.7), (speed.y*0.7)};
    }

	// Note: Keyboard mapping is only QWERTY
    // UP AND DOWN
    if (UP && !collisions[0]) player.position.y -= speed.y;
    if (DOWN && !collisions[2]) player.position.y += speed.y;
    // RIGHT AND LEFT
    if (RIGHT && !collisions[1]) player.position.x += speed.x;
    if (LEFT && !collisions[3]) player.position.x -= speed.x;

    // Anim sprite if moving
    if (UP | DOWN | LEFT | RIGHT)
    {
        player.walkSprite += 1;
        player.walkSprite %= FRAME_RATE*3;
    }

    // Change sprite direction
    if (LEFT) player.direction = 1;
    else if (RIGHT) player.direction = 0;

    camera.offset = player.position;
}

// Draw game (one frame)
void DrawGame(void) {
    BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera);
            // DRAW MAP
            Map_draw(&game.map);

            // DRAW PLAYER
            Player_draw(&player);
        EndMode2D();

        // DRAW INVENTORY
        Inventory_draw(20, GetScreenHeight() - 20 - 48, player.inventory);

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
