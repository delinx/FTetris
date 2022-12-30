#include "raylib.h"
#include "types/types.hpp"

#ifdef UNIT_TEST
#include "uTest.cpp"
#else

#include <iostream>

int main(int argc, char *argv[])
{

    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(120);

    f96 time = 0.0f;

    bool DEBUG = true;

    while(!WindowShouldClose())
    {
        time += GetFrameTime();

        BeginDrawing();
        ClearBackground(GRAY);
        DrawFPS(10, 10);
        DrawText("FTetris", 190, 200, 20, LIGHTGRAY);
        EndDrawing();

        // debug toggle
        if(IsKeyReleased(KEY_TAB))
        {
            DEBUG = !DEBUG;
        }
    }

    CloseWindow();

    std::cout << "End" << std::endl;
    return 0;
}

#endif
