#include "block.hpp"

Block::Block(fXY visualPos)
{
    positionVisualCurrent = visualPos;
    positionVisualTarget = visualPos;
}

Block::~Block()
{
}

void Block::print()
{

    std::cout << "\n--- --- --- [" << pseudoUniqueID << "]\n"
              << "--- *** ---\ncXY: " << positionVisualCurrent.x << ", " << positionVisualCurrent.y << " | "
              << "gXY: " << positionVisualTarget.x << ", " << positionVisualTarget.y << " (" << movementSpeed << ")\n"
              << "Animation: b" << playingAnimation << " | Del: b" << deleteAfterAnimating << " | " << animationTimestampCurrent
              << " | (" << animationSpeed << ")\n"
              << std::endl;
}

void Block::updateTaregtPos(iXY targetPos)
{
    positionVisualTarget.x = targetPos.x * blockVisualSize;
    positionVisualTarget.y = targetPos.y * blockVisualSize;
}

void Block::step(f96 deltaTime)
{
    // check if block needs to be animated
    if(playingAnimation)
    {
        animationTimestampCurrent += animationSpeed * deltaTime;
        if(animationTimestampCurrent > 100.f)
        {
            animationTimestampCurrent = 100.f;
        }
    }
    // check if block needs to be moved in X or Y
    if(positionVisualCurrent.x != positionVisualTarget.x)
    {
        if(positionVisualCurrent.x > positionVisualTarget.x)
        {
            positionVisualCurrent.x -= movementSpeed * deltaTime;
        }
        if(positionVisualCurrent.x < positionVisualTarget.x)
        {
            positionVisualCurrent.x += movementSpeed * deltaTime;
        }
        if(std::abs(positionVisualCurrent.x - positionVisualTarget.x) < 1.f)
        {
            positionVisualTarget.x = positionVisualTarget.x;
        }
    }
    if(positionVisualCurrent.y != positionVisualTarget.y)
    {
        if(positionVisualCurrent.y > positionVisualTarget.y)
        {
            positionVisualCurrent.y -= movementSpeed * deltaTime;
        }
        if(positionVisualCurrent.y < positionVisualTarget.y)
        {
            positionVisualCurrent.y += movementSpeed * deltaTime;
        }
        if(std::abs(positionVisualCurrent.y - positionVisualTarget.y) < 1.f)
        {
            positionVisualTarget.y = positionVisualTarget.y;
        }
    }
    print();
}
