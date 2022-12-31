#include "block.hpp"

Block::Block(fXY visualPos)
{
    positionVisualCurrent = visualPos;
    positionVisualTarget = visualPos;
}

Block::Block()
{
}

Block::~Block()
{
}

void Block::print()
{

    std::cout << "\n--- --- --- [" << pseudoUniqueID << "]\n";

    std::cout << "[" << exist << "]" << bucketPos.x << ":" << bucketPos.y << "\n";

    std::cout << "--- *** ---\ncXY: " << positionVisualCurrent.x << ", " << positionVisualCurrent.y << " | "
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

void Block::forceUpdateVisualPos()
{
    updateTaregtPos(bucketPos);
    positionVisualCurrent = positionVisualTarget;
}

void Block::step(f96 deltaTime)
{
    updateTaregtPos(bucketPos);
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
        if(std::abs(positionVisualCurrent.x - positionVisualTarget.x) < movementSpeed * deltaTime)
        {
            positionVisualCurrent.x = positionVisualTarget.x;
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
        if(std::abs(positionVisualCurrent.y - positionVisualTarget.y) < movementSpeed * deltaTime)
        {
            positionVisualCurrent.y = positionVisualTarget.y;
        }
    }
    // std::cout << std::abs(positionVisualCurrent.x - positionVisualTarget.x) << std::endl;
    //  print();
}

void Block::draw()
{
    if(exist)
    {
        // draw block
        i32 posX = positionVisualCurrent.x + OFFSET.x;
        i32 posY = positionVisualCurrent.y + OFFSET.y;
        DrawRectangle(posX, posY, blockVisualSize, blockVisualSize, BaseColor);
        DrawRectangle(posX + 4, posY + 4, blockVisualSize - 8, blockVisualSize - 8, Color { 0, 0, 0, 50 });
        DrawRectangleLinesEx(Rectangle {
                                 (f32)(posX + 4),
                                 (f32)(posY + 4),
                                 (f32)(blockVisualSize - 8),
                                 (f32)(blockVisualSize - 8),
                             },
                             1.f, GRAY);
        DrawRectangleLinesEx(Rectangle {
                                 (f32)(posX),
                                 (f32)(posY),
                                 (f32)(blockVisualSize),
                                 (f32)(blockVisualSize),
                             },
                             1.f, DARKGRAY);

        // draw special
        if(Special > 0)
        {
            DrawRectangle(posX + 4, posY + 4, blockVisualSize - 8, blockVisualSize - 8, Color { 0, 0, 0, 50 });
            // DrawText(std::to_string(Special).c_str(), posX + 4, posY + 4, 16, Color { 0, 0, 0, 255 });
            char sym[2];
            sym[0] = Special + 64;
            sym[1] = '\0';
            DrawText(sym, posX + 9, posY + 6, 20, Color { 255, 255, 255, 255 });
        }
    }
}
