#include "grid.hpp"

Grid::Grid(u32 width, u32 height)
{
    WIDTH = width;
    HEIGHT = height;
    grid = new Block[WIDTH * HEIGHT];
    for(u32 i = 0; i < WIDTH * HEIGHT; i++)
    {
        Block block;
        block.exist = false;
        grid[i] = block;
    }
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

void Grid::print()
{
    for(i32 y = 0; y < HEIGHT; y++)
    {
        for(i32 x = 0; x < WIDTH; x++)
        {
            Block block = get({ x, y });
            if(block.exist)
            {
                std::cout << "X";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}
