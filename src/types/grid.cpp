#include "grid.hpp"

Grid::Grid(u32 width, u32 height)
{
    WIDTH = width;
    HEIGHT = height;
    grid = NULL;
}

Grid::~Grid()
{
    delete[] grid;
}

void Grid::set(iXY xy, Block block)
{
    grid[xy.x + WIDTH * xy.y] = block;
}

Block Grid::get(iXY xy)
{
    return grid[xy.x + WIDTH * xy.y];
}
