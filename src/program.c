#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "./includes/game.h"
#define COORDS_BUFFER_LENGTH 30
#define WINDOW_BASE_WIDTH 800
#define WINDOW_BASE_HEIGHT 600

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
// Initialize game
static void InitGame(Camera2D * camera, Game * game, Player * player);
// Update game (one frame)
static void UpdateGame(Camera2D * camera, Game * game, Player * player, char coords[COORDS_BUFFER_LENGTH]);
// Update player (one frame)
static void UpdatePlayer(Camera2D * camera, Game * game, Player * player, float delta);
// Draw game (one frame)
static void DrawGame(Camera2D * camera, Game * game, Player * player, char coords[COORDS_BUFFER_LENGTH]);
// Unload game
static void UnloadGame(void); 
// Update and Draw (one frame)
static void UpdateDrawFrame(Camera2D * camera, Game * game, Player * player, char coords[COORDS_BUFFER_LENGTH]);
// Update camera position
static void UpdateCameraCenter(Camera2D * camera, Player * player);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Player player;
    Camera2D camera = {0};
    Game game;
    char coords[COORDS_BUFFER_LENGTH];

    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogCallback(logger);
    InitWindow(WINDOW_BASE_WIDTH, WINDOW_BASE_HEIGHT, "50NuancesDeCodes - by IMT GRAY TEAM");

    Player_init(&player);
    InitGame(&camera, &game, &player);

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
        UpdateDrawFrame(&camera, &game, &player, coords);
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
void InitGame(Camera2D * camera, Game * game, Player * player) {
    camera->target = player->position;
    camera->offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;

    // INIT MAP
    Game_initMap(game);
    Player_init(player);

    player->inventory->items[0] = (Item) {0, "Prison Key", true, LoadTexture("assets/prison_key.png")};
}

// Update game (one frame)
void UpdateGame(Camera2D * camera, Game * game, Player * player, char coords[COORDS_BUFFER_LENGTH]) {
    float deltaTime = GetFrameTime();
    UpdatePlayer(camera, game, player, deltaTime);
    UpdateCameraCenter(camera, player);
    sprintf(coords, "X: %.2f\nY: %.2f", camera->target.x, camera->target.y);
}

// Update player (one frame)
void UpdatePlayer(Camera2D * camera, Game * game, Player * player, float delta) {
    // Key switch (inventory)
    if (IsKeyDown(KEY_ONE)) player->inventory->selected = 0;
    if (IsKeyDown(KEY_TWO)) player->inventory->selected = 1;
    if (IsKeyDown(KEY_THREE)) player->inventory->selected = 2;
    if (IsKeyDown(KEY_FOUR)) player->inventory->selected = 3;
    if (IsKeyDown(KEY_FIVE)) player->inventory->selected = 4;
    if (IsKeyDown(KEY_SIX)) player->inventory->selected = 5;
    if (IsKeyDown(KEY_SEVEN)) player->inventory->selected = 6;
    if (IsKeyDown(KEY_EIGHT)) player->inventory->selected = 7;
    if (IsKeyDown(KEY_NINE)) player->inventory->selected = 8;

    if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
        // Zoom control
        camera->zoom += ((float)GetMouseWheelMove()*0.05f);
        if (camera->zoom > 3.0f) camera->zoom = 3.0f;
        else if (camera->zoom < 0.25f) camera->zoom = 0.25f;
    } else { 
        // Mouse Wheel switch (inventory)
        player->inventory->selected -= GetMouseWheelMove();
        if (player->inventory->selected < 0) player->inventory->selected = 0;
        if (player->inventory->selected > 8) player->inventory->selected = 8;
    }

    // Update selected item (inventory draw the name of item)
    if (player->inventory->items[player->inventory->selected].name != 0x0)
        sprintf(player->inventory->selectedText, "Selected: %s", player->inventory->items[player->inventory->selected].name);

    // Is player sprinting ?
	player->sprinting = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    // Save temporary the speed with sprinting calculated, if need to decrease (diagonal speed fix)
    Vector2 speed = {player->speed.x * ((player->sprinting) ? player->acceleration : 1.f) * delta,
                    player->speed.y * ((player->sprinting) ? player->acceleration : 1.f) * delta};

    // Save collisions with directions
    int collisions[] = {0, 0, 0, 0}; // NORTH EAST SOUTH WEST

    // Check all collisions with 3 blocs width
    for (int i = -1; i <= 1; i++) {
        // Retrieve the player position in the map 2D Array
        int location[2] = {(int) (player->position.x/32), (int) (player->position.y/32)};

        // Retrieve current position of player
        Vector2 p = player->position;
        // NORTH
        /*
        [x, x, x]
        [ , p,  ]
        [ ,  ,  ]
        */
        Sprite ei = game->map->sprite[location[1]-1][location[0]+i];
        if (ei.blocking &&
            ei.rect.y + ei.rect.height <= p.y+20 &&
            ei.rect.y + ei.rect.height >= p.y-20 &&
            ei.rect.x <= p.x+20-speed.x &&
            ei.rect.x + ei.rect.width >= p.x-20+speed.x)
        {
            collisions[0] = 1;
        }
        // EAST
        /*
        [ ,  , x]
        [ , p, x]
        [ ,  , x]
        */
        ei = game->map->sprite[location[1]+i][location[0]+1];
        if (ei.blocking &&
            ei.rect.x <= p.x+20 &&
            ei.rect.x > p.x-20 &&
            ei.rect.y <= p.y+20-speed.y &&
            ei.rect.y + ei.rect.height >= p.y-20+speed.y)
        {
            collisions[1] = 1;
        }
        // SOUTH
        /*
        [ ,  ,  ]
        [ , p,  ]
        [x, x, x]
        */
        ei = game->map->sprite[location[1]+1][location[0]+i];
        if (ei.blocking &&
            ei.rect.y <= p.y+20 &&
            ei.rect.y > p.y-20 &&
            ei.rect.x <= p.x+20-speed.x &&
            ei.rect.x + ei.rect.width >= p.x-20+speed.x)
        {
            collisions[2] = 1;
        }
        // WEST
        /*
        [x,  ,  ]
        [x, p,  ]
        [x,  ,  ]
        */
        ei = game->map->sprite[location[1]+i][location[0]-1];
        if (ei.blocking &&
            ei.rect.x + ei.rect.width <= p.x+20 &&
            ei.rect.x + ei.rect.width >= p.x-20 &&
            ei.rect.y <= p.y+20-speed.y &&
            ei.rect.y + ei.rect.height >= p.y-20+speed.y)
        {
            collisions[3] = 1;
        }
    }

    // Check movements
    bool UP = (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W));
    bool DOWN = (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S));
    bool LEFT = (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A));
    bool RIGHT = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D));

    // Limit diagonal movements
    if ((UP || DOWN) 
        && (LEFT || RIGHT)
        && !(LEFT && RIGHT))
    {
        // remove 30% of the saved speed
        speed = (Vector2) {(speed.x*0.7), (speed.y*0.7)};
    }

	// Note: Keyboard mapping is only QWERTY
    // UP AND DOWN
    if (UP && !collisions[0]) player->position.y -= speed.y;
    if (DOWN && !collisions[2]) player->position.y += speed.y;
    // RIGHT AND LEFT
    if (RIGHT && !collisions[1]) player->position.x += speed.x;
    if (LEFT && !collisions[3]) player->position.x -= speed.x;

    // Anim sprite if moving
    if (UP | DOWN | LEFT | RIGHT)
    {
        player->walkSprite += 1;
        player->walkSprite %= FRAME_RATE*3;
    }

    // Change sprite direction
    if (LEFT) player->direction = 1;
    else if (RIGHT) player->direction = 0;
}

// Draw game (one frame)
void DrawGame(Camera2D * camera, Game * game, Player * player, char coords[COORDS_BUFFER_LENGTH]) {
    BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(*camera);
            // DRAW MAP
            Map_draw(game->map);

            // DRAW PLAYER
            Player_draw(player);
        EndMode2D();

        // DRAW INVENTORY
        Inventory_draw(20, GetScreenHeight() - 20 - 48, player->inventory);

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
void UpdateDrawFrame(Camera2D * camera, Game * game, Player * player, char coords[COORDS_BUFFER_LENGTH])
{
    UpdateGame(camera, game, player, coords);
    DrawGame(camera, game, player, coords);
}

void UpdateCameraCenter(Camera2D * camera, Player * player)
{
    camera->target = player->position;
    camera->offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
}
