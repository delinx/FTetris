#ifndef XY_HPP
#define XY_HPP
#include "types.hpp"

struct iXY
{
    i32 x;
    i32 y;
    iXY(i32 x, i32 y)
    {
        this->x = x;
        this->y = y;
    }
    iXY()
    {
        this->x = 0;
        this->y = 0;
    }
};

struct fXY
{
    f32 x;
    f32 y;
    fXY(f32 x, f32 y)
    {
        this->x = x;
        this->y = y;
    }
    fXY()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }
};

#endif  // !XY_HPP
