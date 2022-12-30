#include "gameLoop.hpp"
#include <string>

GameLoop::GameLoop()
{
    bucket = new Grid(10, 20);
}

GameLoop::~GameLoop()
{
}

void GameLoop::readKeyboard()
{
    // move left
    if(IsKeyPressed(KEY_LEFT))
    {
        moveSide = -1;
        std::cout << "left" << std::endl;
    }
    // move right
    else if(IsKeyPressed(KEY_RIGHT))
    {
        moveSide = 1;
        std::cout << "right" << std::endl;
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
    if(IsKeyDown(KEY_SPACE))
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

    // if there is no falling shape and we are not in animation freeze then make new one
    if(shape == NULL && !inAnimationFreeze)
    {
        shape = new Grid(3, 3);
        for(i32 i = 0; i < shape->WIDTH * shape->HEIGHT; i++)
        {
            shape->grid[i] = shapeTemplate.shape_L.grid[i];
        }
    }

    bool skipWaiting = false;
    if(moveSide != 0 || rotate != 0 || drop)
    {
        if(moveSide != 0 && shape != NULL)
        {
            shape->addVisualOffset({ moveSide, 0 });
            skipWaiting = true;
        }
        // TODO: only skip wait if valid move
        resetInput();
    }

    if(time - lastTick > interval || skipWaiting)
    {
        std::cout << "[TICK] - " << std::to_string(time) << " - " << std::endl;
        lastTick = time;
        resetInput();
    }

    resetInput();
}

void GameLoop::tickMovement()
{
    if(bucket == NULL)
    {
        return;
    }
    bucket->stepAllBlocks(deltaTime);

    if(shape == NULL)
    {
        return;
    }
    shape->stepAllBlocks(deltaTime);
}

void GameLoop::draw()
{
    if(bucket == NULL)
    {
        return;
    }
    bucket->drawBlocks();

    if(shape == NULL)
    {
        return;
    }
    shape->drawBlocks();
}
