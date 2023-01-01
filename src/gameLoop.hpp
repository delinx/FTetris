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
    void newShape();

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
    Grid *bucket = nullptr;
    Grid *shape = nullptr;
    iXY shapeXY;
    Shape shapeTemplate;
    i32 unmovedTicks = 0;
    bool checkSolvedLines();
    i32 specialChance = 5;  // 1% chance
    i32 specialRange = 3;   // A B
    void animateRemovedRows();
    void moveRowsDown();
    i32 yOfRemovedRow = 0;
    void checkIfReadyToResume();

    // graphics
    Color clr1 = Color { 100, 201, 211, 255 };
    Color clr2 = Color { 68, 98, 165, 255 };
    Color clr3 = Color { 240, 175, 205, 255 };
    Color clr4 = Color { 230, 230, 70, 255 };
    Color clr5 = Color { 100, 190, 90, 255 };
    Color clr6 = Color { 140, 90, 170, 255 };
    Color clr7 = Color { 230, 65, 55, 255 };
    Color randomColor();
    i32 blocksStillAnimating = 0;

    // sounds
    Sound sfx_coin;

    void tickLogic();
    void tickMovement();
    void draw();
    void drawBackground();
    void bakeShape();

    bool canFit(iXY xy);
    bool canFit(iXY xy, Grid *_shape);

    GameLoop();
    ~GameLoop();
};

#endif  // !GAME_LOOP_HPP
