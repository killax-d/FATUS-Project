#include "raylib.h"
#include "stdio.h"

int main(void)
{
    int screenWidth = 800;
    int screenHeight = 600;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "50NuancesDeCodes - by IMT GREY TEAM");

    Camera camera = { 0 };
    camera.position = (Vector3){ -5.0f, 1.0f, -5.0f };
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    char coords[50];
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);
        sprintf(coords, "X: %.2f\nY: %.2f\nZ: %.2f", camera.position.x, camera.position.y, camera.position.z);

        if (IsWindowResized())
        {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                for (int x = 0; x < 16; x++) {
                    for (int y = 0; y < 16; y++) {
                        for (int z = 0; z < 16; z++) {
                            DrawCube((Vector3){x*5, y, z*5}, 1, 1, 1, LIGHTGRAY);
                            DrawCubeWires((Vector3){x*5, y, z*5}, 1, 1, 1, BLACK);
                        }
                    }
                }
            EndMode3D();

            sprintf(coords, "X: %.2f\nY: %.2f\nZ: %.2f", camera.position.x, camera.position.y, camera.position.z);
            DrawLine(screenWidth/2 - 10, screenHeight/2 - 1, screenWidth/2 + 10, screenHeight/2 + 1, BLACK);
            DrawLine(screenWidth/2 - 1, screenHeight/2 - 10, screenWidth/2 + 1, screenHeight/2 + 10, BLACK);
            DrawText(coords, 10, screenHeight-(24*3)-14, 20, BLACK);
            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}