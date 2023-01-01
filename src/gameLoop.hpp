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
    bool DEBUG = false;

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
    Shape shapeTemplate;
    i32 unmovedTicks = 0;
    bool checkSolvedLines();
    i32 specialChance = 10;  // 10% chance
    i32 specialRange = 4;    // A B C
    void animateRemovedRows();
    void moveRowsDown();
    void checkIfReadyToResume();
    bool lost = false;
    void checkIfLost();

    // new game
    void newGame();

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
    Sound sfx_coinPre;
    Sound sfx_fall;
    Sound sfx_coinLowPitch;
    Sound sfx_lost;

    // score counter
    i128 currentScore = 0;
    i128 finalScore = 0;
    void tickScore();
    void drawScore();
    f96 lastScoreTick = 0.0f;
    f96 tickScoreInterval = 0.00075f;
    f96 scoreSoundPitch = 1.0f;
    const f96 scoreSondPitchStep = 0.02f;
    const f96 scoreSoundPitchDefault = 1.0f;
    const f96 scoreSoundPitchMax = 2.0f;
    i128 HighScore = 0;

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
