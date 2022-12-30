#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP
#include "raylib.h"
#include "types/types.hpp"
#include "types/xy.hpp"

class GameLoop
{
      public:
    f96 time = 0.0f;
    f96 deltaTime = 0.0f;
    f96 lastTick = 0.0f;
    f96 tickInterval = 0.4f;
    f96 tickIntervalFast = 0.1f;
    bool DEBUG = true;

    // input
    i32 moveSide = 0;
    i32 rotate = 0;
    bool drop = false;
    bool skipWaiting = false;

    void readKeyboard();
    void resetInput();

    void tickLogic();

    GameLoop();
    ~GameLoop();
};

#endif  // !GAME_LOOP_HPP
