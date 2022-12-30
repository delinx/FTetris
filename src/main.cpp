#include "gameLoop.hpp"
#include "raylib.h"
#include "types/grid.hpp"
#include "types/types.hpp"

#ifdef UNIT_TEST
#include "uTest.cpp"
#else

#include <iostream>

int main(int argc, char *argv[])
{

    int screenWidth = 400;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(200);

    GameLoop gameLoop;

    Block z;
    z.exist = true;
    z.BaseColor = RED;
    z.bucketPos = iXY(5, 10);
    z.forceUpdateVisualPos();
    gameLoop.bucket->set(iXY(5, 10), z);

    while(!WindowShouldClose())
    {
        gameLoop.DEBUG = IsKeyReleased(KEY_TAB) ? !gameLoop.DEBUG : gameLoop.DEBUG;

        gameLoop.time += GetFrameTime();
        gameLoop.deltaTime = GetFrameTime();
        gameLoop.readKeyboard();

        gameLoop.tickLogic();
        gameLoop.tickMovement();

        BeginDrawing();
        ClearBackground(GRAY);
        DrawText("FTetris", 190, 200, 20, LIGHTGRAY);
        gameLoop.drawBackground();
        gameLoop.draw();

        if(gameLoop.DEBUG)
        {
            DrawFPS(10, 10);
        }
        // debug toggle
        EndDrawing();
    }

    CloseWindow();

    std::cout << "End" << std::endl;
    return 0;
}

#endif
