#include "RayGameMain.h"
#include "raylib.h"
#include "WwiseManager.h"

WwiseManager wwiseManager;

int RayGame::RunRayLib()
{
    InitWindow(800, 450, "raylib [core] example - basic window");

    wwiseManager.RunWwise();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("IT'S WORKING!", 320, 200, 20, LIGHTGRAY);

        if (IsKeyPressed(KEY_SPACE))
        {
            wwiseManager.CustomPostEvent("Play_Z_Stun");
        }
        wwiseManager.ProcessAudio();

        EndDrawing();
    }
    wwiseManager.shutdownSoundEngine();
    CloseWindow();

    return 0;
}
