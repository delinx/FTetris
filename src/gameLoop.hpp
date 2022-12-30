#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP
#include "raylib.h"
#include "types/grid.hpp"
#include "types/shape.hpp"
#include "types/types.hpp"
#include "types/xy.hpp"

class GameLoop
{
      private:
    i32 blockSize = 30;

      public:
    f96 time = 0.0f;
    f96 deltaTime = 0.0f;
    f96 lastTick = 0.0f;
    f96 tickInterval = 0.4f;
    f96 tickIntervalFast = 0.1f;
    bool DEBUG = true;

    bool inAnimationFreeze = false;

    // input
    i32 moveSide = 0;
    i32 rotate = 0;
    bool drop = false;
    void readKeyboard();
    void resetInput();
    i32 continuesMoves = 0;
    i32 maxContinuesMoves = 2;

    // Tetris logic
    Grid *bucket = NULL;
    Grid *shape = NULL;
    iXY shapeXY;
    Shape shapeTemplate;

    void tickLogic();
    void tickMovement();
    void draw();
    void drawBackground();

    bool canFit(iXY xy);

    GameLoop();
    ~GameLoop();
};

#endif  // !GAME_LOOP_HPP
