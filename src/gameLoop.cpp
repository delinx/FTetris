#include "gameLoop.hpp"
#include <iostream>
#include <raylib.h>
#include <string>

GameLoop::GameLoop()
{
    bucket = new Grid(10, 20);
    for(i32 x = 0; x < bucket->WIDTH; x++)
    {
        for(i32 y = 0; y < bucket->HEIGHT; y++)
        {
            // std::cout << " Y: " << bucket->get({ x, y }).bucketPos.y << std::endl;
        }
    }

    InitAudioDevice();
    sfx_coin = LoadSound("sfx_coin.wav");
    SetSoundVolume(sfx_coin, 0.8f);
    sfx_coinPre = LoadSound("sfx_coinPre.wav");
    SetSoundVolume(sfx_coinPre, 4.0f);
    sfx_fall = LoadSound("sfx_fall.wav");
    SetSoundVolume(sfx_fall, 1.5f);
    sfx_coinLowPitch = LoadSound("sfx_coin_lowPitch.wav");
    sfx_lost = LoadSound("sfx_lost.wav");

    PlaySound(sfx_coin);
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
    checkIfLost();

    if(lost)
    {
        return;
    }

    if(inAnimationFreeze)
    {
        // if there is no unsolved lines left, unfreeze
        if(blocksStillAnimating <= 0)
        {
            blocksStillAnimating = 0;
            while(checkSolvedLines())
            {
                moveRowsDown();
            }
            inAnimationFreeze = false;
        }
    }

    // icrease tick speed if down is held
    f96 interval = drop ? tickIntervalFast : tickInterval;

    // if there is no falling shape and we are not in animation freeze then make new one
    if(shape == nullptr && !inAnimationFreeze)
    {
        newShape();
    }

    bool skipWaiting = false;
    if(moveSide != 0 || rotate != 0 || drop)
    {
        if(moveSide != 0 && shape != nullptr)
        {
            if(canFit(iXY(moveSide, 0)))
            {
                std::cout << "can move" << std::endl;
                shape->addVisualOffset({ moveSide, 0 });
                skipWaiting = true;
                continuesMoves++;
            }
        }
        if(rotate != 0 && shape != nullptr)
        {
            Grid *rotated = new Grid(shape->WIDTH, shape->HEIGHT);

            // copy shape to rotated shape Grid while rotating
            // get origin of shape in global space
            iXY origin = shape->get(iXY(0, 0)).bucketPos;
            std::cout << "origin: " << origin.x << ", " << origin.y << std::endl;

            for(i32 Sx = 0; Sx < shape->WIDTH; Sx++)
            {
                for(i32 Sy = 0; Sy < shape->HEIGHT; Sy++)
                {
                    if(rotate > 0)
                    {
                        Block block = shape->get(iXY(Sy, shape->WIDTH - 1 - Sx));
                        block.bucketPos = iXY(Sx + origin.x, Sy + origin.y);
                        //  block.forceUpdateVisualPos();
                        rotated->set(iXY(Sx, Sy), block);
                    }
                    else
                    {
                        Block block = shape->get(iXY(shape->HEIGHT - 1 - Sy, Sx));
                        block.bucketPos = iXY(Sx + origin.x, Sy + origin.y);
                        // block.forceUpdateVisualPos();
                        rotated->set(iXY(Sx, Sy), block);
                    }
                }
            }
            // check if rotated shape can fit
            if(canFit(iXY(0, 0), rotated))
            {
                std::cout << "can rotate" << std::endl;
                for(i32 Sx = 0; Sx < shape->WIDTH; Sx++)
                {
                    for(i32 Sy = 0; Sy < shape->HEIGHT; Sy++)
                    {
                        shape->set(iXY(Sx, Sy), rotated->get(iXY(Sx, Sy)));
                    }
                }
                skipWaiting = true;
                continuesMoves++;
            }
            delete rotated;
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
            if(shape != nullptr)
            {
                if(canFit(iXY(0, 1)))
                {
                    shape->addVisualOffset({ 0, 1 });
                    continuesMoves = 0;
                    unmovedTicks = 0;
                }
                else
                {
                    unmovedTicks++;
                    if(unmovedTicks > 1)
                    {
                        bakeShape();
                        // check if we have any lines to clear
                        if(checkSolvedLines())
                        {
                            std::cout << "SOLVED LINES FOUND" << std::endl;
                            inAnimationFreeze = true;
                            animateRemovedRows();
                        }

                        unmovedTicks = 0;
                    }
                    // TODO: add counter, if we hit bottom twice in a row, we BAKE
                    std::cout << "can not go DOWN, we hit THE BOTTOM" << std::endl;
                }
            }
        }
        resetInput();
    }
    resetInput();
}

void GameLoop::tickMovement()
{
    if(bucket == nullptr)
    {
        return;
    }
    bucket->stepAllBlocks(deltaTime);

    if(shape == nullptr)
    {
        return;
    }
    shape->stepAllBlocks(deltaTime);
}

void GameLoop::draw()
{
    if(bucket == nullptr)
    {
        return;
    }
    bucket->drawBlocks();

    if(shape == nullptr)
    {
        return;
    }
    shape->drawBlocks();
}


bool GameLoop::canFit(iXY xy)
{
    return canFit(xy, shape);
}

bool GameLoop::canFit(iXY xy, Grid *_shape)
{
    if(bucket == nullptr || _shape == nullptr)
    {
        return false;
    }
    for(i32 x = 0; x < _shape->WIDTH; x++)
    {
        for(i32 y = 0; y < _shape->HEIGHT; y++)
        {
            // if activeBlock cell is empty skip
            if(!_shape->get(iXY(x, y)).exist)
            {
                continue;
            }
            // if activeBlock is outside grid return false
            i32 _x = _shape->get(iXY(x, y)).bucketPos.x;
            i32 _y = _shape->get(iXY(x, y)).bucketPos.y;
            if(xy.x + _x < 0 || xy.x + _x >= bucket->WIDTH || xy.y + _y < -4 || xy.y + _y >= bucket->HEIGHT)
            {
                std::cout << _y << " - " << xy.y << " - " << bucket->HEIGHT << std::endl;
                std::cout << "out of bounds" << std::endl;
                if(_y < 20 && _y > -5)
                {
                    std::cout << "this _y was allowed through" << std::endl;
                    return false;
                }
            }
            if(_y >= 0 && _y < 20 && _x >= 0 && _x < 10)
            {
                if(bucket->get(iXY(xy.x + _x, xy.y + _y)).exist)
                {
                    std::cout << "collision" << std::endl;
                    return false;
                }
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

void GameLoop::bakeShape()
{
    if(shape == nullptr)
    {
        return;
    }
    for(i32 x = 0; x < shape->WIDTH; x++)
    {
        for(i32 y = 0; y < shape->HEIGHT; y++)
        {
            if(shape->get(iXY(x, y)).exist)
            {
                if(shape->get(iXY(x, y)).bucketPos.y < -1)
                {
                    lost = true;
                    PlaySound(sfx_lost);
                    delete shape;
                    shape = nullptr;
                    return;
                }
                std::cout << "baking shape" << std::endl;
                std::cout << shape->get(iXY(x, y)).bucketPos.x << " - " << shape->get(iXY(x, y)).bucketPos.y << std::endl;
                std::cout << shape->get(iXY(x, y)).exist << std::endl;
                std::cout << std::to_string(shape->get(iXY(x, y)).BaseColor.r) << std::to_string(shape->get(iXY(x, y)).BaseColor.g) << std::to_string(shape->get(iXY(x, y)).BaseColor.b) << std::endl;
                std::cout << shape->get(iXY(x, y)).deleteAfterAnimating << std::endl;
                shape->get(iXY(x, y)).print();
                bucket->set(iXY(shape->get(iXY(x, y)).bucketPos.x, shape->get(iXY(x, y)).bucketPos.y), shape->get(iXY(x, y)));
            }
        }
    }
    delete shape;
    shape = nullptr;
}

void GameLoop::newShape()
{
    Grid *newShape;
    switch(rand() % 7)
    {
        case 0:
            newShape = shapeTemplate.shape_S;
            break;
        case 1:
            newShape = shapeTemplate.shape_Z;
            break;
        case 2:
            newShape = shapeTemplate.shape_L;
            break;
        case 3:
            newShape = shapeTemplate.shape_J;
            break;
        case 4:
            newShape = shapeTemplate.shape_I;
            break;
        case 5:
            newShape = shapeTemplate.shape_O;
            break;
        case 6:
            newShape = shapeTemplate.shape_T;
            break;
    }

    Color rndColor = randomColor();
    shape = new Grid(newShape->WIDTH, newShape->HEIGHT);
    for(i32 i = 0; i < newShape->WIDTH * newShape->HEIGHT; i++)
    {
        Block tmp = newShape->grid[i];
        tmp.visible = true;
        tmp.bucketPos.x = tmp.bucketPos.x + 3;
        tmp.bucketPos.y = tmp.bucketPos.y - 4;
        tmp.BaseColor = rndColor;
        i32 special = rand() % 100;
        if(special <= specialChance)
        {
            std::cout << special << std::endl;
            tmp.Special = rand() % specialRange + 1;
        }

        tmp.forceUpdateVisualPos();
        std::cout << "assigning new shape block" << std::endl;
        tmp.print();
        shape->grid[i] = tmp;
    }
}

Color GameLoop::randomColor()
{
    Color tmp;
    switch(rand() % 7)
    {
        case 0:
            tmp = clr1;
            break;
        case 1:
            tmp = clr2;
            break;
        case 2:
            tmp = clr3;
            break;
        case 3:
            tmp = clr4;
            break;
        case 4:
            tmp = clr5;
            break;
        case 5:
            tmp = clr6;
            break;
        case 6:
            tmp = clr7;
            break;
    }
    return tmp;
}

bool GameLoop::checkSolvedLines()
{
    for(i32 y = 0; y < bucket->HEIGHT; y++)
    {
        bool solved = true;
        for(i32 x = 0; x < bucket->WIDTH; x++)
        {
            if(!bucket->get(iXY(x, y)).exist)
            {
                solved = false;
                break;
            }
        }
        if(solved)
        {
            return true;
        }
    }
    return false;
}


void GameLoop::animateRemovedRows()
{
    for(i32 y = 0; y < bucket->HEIGHT; y++)
    {
        bool solved = true;
        for(i32 x = 0; x < bucket->WIDTH; x++)
        {
            if(!bucket->get(iXY(x, y)).exist)
            {
                solved = false;
                break;
            }
        }
        if(solved)
        {
            // mark blocks in row to play delete animation
            for(i32 rowX = 0; rowX < bucket->WIDTH; rowX++)
            {
                Block tmp = bucket->get(iXY(rowX, y));
                tmp.playingAnimation = true;
                tmp.scoreIncrement = ((19 - tmp.bucketPos.y) * 10) + 50;
                tmp.bucketPos.y = -1;
                tmp.bucketPos.x = 16 - (rand() % 6);
                tmp.movementSpeed = float((rand() % 500) + 1000);
                tmp.deleteAfterAnimating = true;
                // tmp.inAnimationFreezePtr = inAnimationFreezePtr;
                //  tmp.animationType = 1;
                // counter to know when all blocks finished animating
                blocksStillAnimating += 1;
                tmp.blocksStillAnimatingPtr = &blocksStillAnimating;
                tmp.scorePtr = &finalScore;
                tmp.sfx_coin = &sfx_coin;
                bucket->set(iXY(rowX, y), tmp);
            }
            PlaySound(sfx_coinPre);
        }
    }
}

void GameLoop::moveRowsDown()
{
    for(i32 y = 0; y < bucket->HEIGHT; y++)
    {
        bool solved = true;
        for(i32 x = 0; x < bucket->WIDTH; x++)
        {
            if(!bucket->get(iXY(x, y)).exist)
            {
                solved = false;
                break;
            }
        }
        if(solved)
        {
            // move all blocks above down
            for(i32 remainingRows = y; remainingRows > 0; remainingRows--)
            {
                for(i32 x = 0; x < bucket->WIDTH; x++)
                {
                    // copy block above into temporary var
                    Block tmp = bucket->get(iXY(x, remainingRows - 1));
                    if(tmp.exist)
                    {
                        // std::cout << "moving block " << x << " " << remainingRows - 1 << std::endl;
                        tmp.bucketPos.y = remainingRows;
                        bucket->set(iXY(x, remainingRows), tmp);
                    }
                    else
                    {
                        // std::cout << "block does not exist " << x << " " << remainingRows - 1 << std::endl;
                        // but the same block in place, just disable visablility
                        Block emptyBlock;
                        emptyBlock.exist = false;
                        emptyBlock.bucketPos.x = x;
                        emptyBlock.bucketPos.y = remainingRows;
                        emptyBlock.forceUpdateVisualPos();
                        bucket->set(iXY(x, remainingRows), emptyBlock);
                    }
                }
            }
            PlaySoundMulti(sfx_fall);
        }
    }
}



void GameLoop::tickScore()
{


    if(currentScore < finalScore)
    {
        if(time - lastScoreTick > tickScoreInterval)
        {
            lastScoreTick = time;
            currentScore += 5;
            if(currentScore % 150 == 0)
            {
                scoreSoundPitch += scoreSondPitchStep;
                if(scoreSoundPitch > scoreSoundPitchMax)
                {
                    scoreSoundPitch = scoreSoundPitchMax;
                }
                SetSoundPitch(sfx_coinLowPitch, scoreSoundPitch);
                PlaySound(sfx_coinLowPitch);
            }
        }
    }
    else
    {
        if(scoreSoundPitch != scoreSoundPitchDefault)
        {
            scoreSoundPitch = scoreSoundPitchDefault;
            SetSoundPitch(sfx_coin, scoreSoundPitch);
        }
    }
}


void GameLoop::drawScore()
{
    std::string s = std::to_string(currentScore);
    s.insert(0, 8 - s.length(), '0');
    DrawText(s.c_str(), 305, 5, 40, GOLD);

    std::string hs = std::to_string(HighScore);
    hs.insert(0, 8 - hs.length(), '0');
    DrawText("High Score", 420, 50, 10, WHITE);
    DrawText(hs.c_str(), 400, 60, 20, WHITE);
}


void GameLoop::checkIfLost()
{
    if(lost)
    {
        return;
    }
    for(i32 x = 0; x < bucket->WIDTH; x++)
    {
        if(bucket->get(iXY(x, 0)).exist && bucket->get(iXY(x, 0)).bucketPos.x == x && bucket->get(iXY(x, 0)).bucketPos.y == 0)
        {
            std::cout << "lost" << std::endl;
            lost = true;
            PlaySound(sfx_lost);
            break;
            // PlaySoundMulti(sfx_lose);
        }
    }
}


void GameLoop::newGame()
{
    delete bucket;
    delete shape;
    bucket = nullptr;
    shape = nullptr;
    bucket = new Grid(10, 20);
    if(finalScore > HighScore)
    {
        HighScore = finalScore;
    }
    currentScore = 0;
    finalScore = 0;
    lost = false;
    inAnimationFreeze = false;
    resetInput();
    continuesMoves = 0;
    unmovedTicks = 0;
    blocksStillAnimating = 0;
    PlaySound(sfx_coin);
}
