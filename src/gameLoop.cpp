#include "gameLoop.hpp"
#include <iostream>
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
    }
    // move right
    else if(IsKeyPressed(KEY_RIGHT))
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
            Block tmp = shapeTemplate.shape_L.grid[i];
            tmp.bucketPos.x = tmp.bucketPos.x + 3;
            tmp.bucketPos.y = tmp.bucketPos.y - 4;
            tmp.forceUpdateVisualPos();
            shape->grid[i] = tmp;
        }
    }

    bool skipWaiting = false;
    if(moveSide != 0 || rotate != 0 || drop)
    {
        if(moveSide != 0 && shape != NULL)
        {
            if(canFit(iXY(moveSide, 0)))
            {
                std::cout << "can move" << std::endl;
                shape->addVisualOffset({ moveSide, 0 });
                skipWaiting = true;
                continuesMoves++;
            }
        }
        // TODO: only skip wait if valid move
        resetInput();
    }

    if(time - lastTick > interval || skipWaiting)
    {
        std::cout << "[TICK] - " << std::to_string(time) << " - " << std::endl;
        lastTick = time;
        // check if we skipWaiting, if we did then do not drop down, if we did not then drop down
        if(!skipWaiting || continuesMoves > maxContinuesMoves)
        {
            if(canFit(iXY(0, 1)))
            {
                std::cout << "going DOWN" << std::endl;
                shape->addVisualOffset({ 0, 1 });
                continuesMoves = 0;
            }
            else
            {
                std::cout << "can not go DOWN, we hit THE BOTTOM" << std::endl;
            }
        }

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

bool GameLoop::canFit(iXY xy)
{
    if(bucket == NULL || shape == NULL)
    {
        return false;
    }
    for(i32 x = 0; x < shape->WIDTH; x++)
    {
        for(i32 y = 0; y < shape->HEIGHT; y++)
        {
            // if activeBlock cell is empty skip
            if(!shape->get(iXY(x, y)).exist)
            {
                continue;
            }
            // if activeBlock is outside grid return false
            i32 _x = shape->get(iXY(x, y)).bucketPos.x;
            i32 _y = shape->get(iXY(x, y)).bucketPos.y;
            if(bucket != NULL)
            {
                if(-3 + 1 >= bucket->HEIGHT)
                {
                    std::cout << "y: " << _y << " xy: " << xy.y << std::endl;
                }
            }
            if(xy.x + _x < 0 || xy.x + _x >= bucket->WIDTH || xy.y + _y < -4 || xy.y + _y >= bucket->HEIGHT)
            {
                std::cout << "out of bounds" << std::endl;
                return false;
            }
            if(bucket->get(iXY(xy.x + _x, xy.y + _y)).exist)
            {
                std::cout << "collision" << std::endl;
                return false;
            }
        }
    }
    return true;
}

void GameLoop::drawBackground()
{
    bool colorFlipFlop = true;
    unsigned char shade = 150;
    unsigned char shade2 = 180;
    Color color1 = { shade, shade, shade, 255 };
    Color color2 = { shade2, shade2, shade2, 255 };
    for(i32 x = 0; x < bucket->WIDTH; x++)
    {
        for(i32 y = 0; y < bucket->HEIGHT; y++)
        {
            if(colorFlipFlop)
            {
                DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, color1);
            }
            else
            {
                DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, color2);
            }
            colorFlipFlop = !colorFlipFlop;
        }
        colorFlipFlop = !colorFlipFlop;
    }
}
