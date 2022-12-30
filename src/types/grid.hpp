#ifndef GRID_HPP
#define GRID_HPP
#include "block.hpp"
#include "types.hpp"
#include "xy.hpp"

class Grid
{
      public:
    i32 WIDTH;
    i32 HEIGHT;
    Block* grid;
    fXY OFFSET = fXY(0.0f, 0.0f);

    /// make a newi32 array of X*Y size
    Grid(u32 width, u32 height);
    ~Grid();

    void set(iXY xy, Block block);
    Block get(iXY xy);
    void swap(iXY xy1, iXY xy2);
    void setVisualOffset(fXY offset);
    void addVisualOffset(iXY offset);

    /// print grid to console
    void print();

    void stepAllBlocks(f96 deltaTime);
    void drawBlocks();
};


#endif  // !GRID_HPP
