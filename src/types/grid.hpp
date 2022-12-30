#ifndef GRID_HPP
#define GRID_HPP
#include "block.hpp"
#include "types.hpp"
#include "xy.hpp"

class Grid
{
      public:
    u32 WIDTH;
    u32 HEIGHT;
    Block* grid;

    /// make a newi32 array of X*Y size
    Grid(u32 width, u32 height);
    ~Grid();

    void set(iXY xy, Block block);
    Block get(iXY xy);

    /// print grid to console
    void print();
};


#endif  // !GRID_HPP
