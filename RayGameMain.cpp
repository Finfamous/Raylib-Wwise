#include "RayGameMain.h"
#include "raylib.h"
#include "WwiseManager.h"
#include "Game.h"

WwiseManager wwiseManager;

double   LastUpdateTime = 0;

bool EventTriggered(double Interval)
{
    double CurrentTime = GetTime();
    if (CurrentTime - LastUpdateTime >= Interval)
    {
        LastUpdateTime = CurrentTime; 
        return true;
    }
    return false;
}


int RayGame::RunRayLib()
{
    InitWindow(300, 600, "raylib Tetris");

    wwiseManager.RunWwise();

    Game game(wwiseManager);
    Grid grid(wwiseManager);
    grid.Print();
   
    wwiseManager.CustomPostEvent("Play_Connected");

    while (!WindowShouldClose())
    {
        game.HandleInput();
        if(EventTriggered(0.25))
        {
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(DARKBLUE);
        game.Draw();
        
        //Temporary audio tester
        if (IsKeyPressed(KEY_UP))
        {
            //wwiseManager.CustomPostEvent("Play_Notes");
        }
        wwiseManager.ProcessAudio();

        EndDrawing();
    }
    wwiseManager.shutdownSoundEngine();
    CloseWindow();

    return 0;
}
