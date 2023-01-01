#ifndef BLOCK_HPP
#define BLOCK_HPP
#include "types.hpp"
#include "xy.hpp"
#include <iostream>
#include <random>
#include <raylib.h>

class Block
{
      private:
    i32 pseudoUniqueID = rand() % 1000;

      public:
    bool exist = false;

    i32 BlockType = 1;
    i32 Special = 0;

    iXY bucketPos;
    fXY positionVisualCurrent;
    fXY positionVisualTarget;
    f32 movementSpeed = 200.0f;
    fXY OFFSET = fXY(0.0f, 0.0f);

    i32 blockVisualSize = 30;

    bool playingAnimation = false;
    bool deleteAfterAnimating = false;
    f32 animationTimestampCurrent = 0.0f;
    const f32 animationTimestampEnd = 100.0f;

    // animation hack
    i32* blocksStillAnimatingPtr = nullptr;

    f32 animationSpeed = 100.0f;

    Color BaseColor = GREEN;

    void draw();

    void print();
    void updateTaregtPos(iXY targetPos);
    void forceUpdateVisualPos();
    void step(f96 deltaTime);

    Block& operator=(const Block& other)
    {
        this->exist = other.exist;
        this->BlockType = other.BlockType;
        this->Special = other.Special;
        this->bucketPos = other.bucketPos;
        this->positionVisualCurrent = other.positionVisualCurrent;
        this->positionVisualTarget = other.positionVisualTarget;
        this->movementSpeed = other.movementSpeed;
        this->OFFSET = other.OFFSET;
        this->blockVisualSize = other.blockVisualSize;
        this->playingAnimation = other.playingAnimation;
        this->deleteAfterAnimating = other.deleteAfterAnimating;
        this->animationTimestampCurrent = other.animationTimestampCurrent;
        this->blocksStillAnimatingPtr = other.blocksStillAnimatingPtr;
        this->animationSpeed = other.animationSpeed;
        this->BaseColor = other.BaseColor;

        return *this;
    }

    Block();
    Block(fXY visualPos);
    ~Block();
};

#endif  // !BLOCK_HPP
