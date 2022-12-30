#include "gameLoop.hpp"
#include <string>

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
}

void GameLoop::readKeyboard()
{
    // move left
    if(IsKeyDown(KEY_LEFT))
    {
        moveSide = -1;
    }
    // move right
    else if(IsKeyDown(KEY_RIGHT))
    {
        moveSide = 1;
    }
    // rotate
    if(IsKeyPressed(KEY_UP))
    {
        rotate = 1;
    }
    else if(IsKeyPressed(KEY_DOWN))
    {
        rotate = -1;
    }
    // drop
    if(IsKeyPressed(KEY_SPACE))
    {
        drop = true;
    }
}

void GameLoop::resetInput()
{
    moveSide = 0;
    rotate = 0;
    drop = false;
}

void GameLoop::tickLogic()
{
    // icrease tick speed if down is held
    f96 interval = drop ? tickIntervalFast : tickInterval;

    if(time - lastTick > interval || skipWaiting)
    {
        std::cout << "[TICK] - " << std::to_string(time) << " - " << std::endl;
        lastTick = time;
        resetInput();
    }

    resetInput();
}
