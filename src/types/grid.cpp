#include "grid.hpp"

Grid::Grid(u32 width, u32 height)
{
    WIDTH = width;
    HEIGHT = height;
    grid = new Block[WIDTH * HEIGHT];

    for(i32 x = 0; x < WIDTH; x++)
    {
        for(i32 y = 0; y < HEIGHT; y++)
        {
            Block block;
            block.exist = false;
            block.OFFSET = OFFSET;
            block.bucketPos = { x, y };
            block.forceUpdateVisualPos();
            set({ x, y }, block);
        }
    }
}

Grid::~Grid()
{
    delete[] grid;
}

void Grid::setVisualOffset(fXY offset)
{
    OFFSET = offset;
    for(u32 i = 0; i < WIDTH * HEIGHT; i++)
    {
        grid[i].OFFSET = OFFSET;
    }
}

void Grid::addVisualOffset(iXY offset)
{
    for(u32 i = 0; i < WIDTH * HEIGHT; i++)
    {
        iXY tmp = grid[i].bucketPos;
        tmp.x += offset.x;
        tmp.y += offset.y;
        grid[i].bucketPos = tmp;
    }
}

void Grid::set(iXY xy, Block block)
{
    grid[xy.x + WIDTH * xy.y] = block;
}

Block Grid::get(iXY xy)
{
    return grid[xy.x + WIDTH * xy.y];
}

void Grid::swap(iXY xy1, iXY xy2)
{
    Block temp = grid[xy1.x + WIDTH * xy1.y];
    grid[xy1.x + WIDTH * xy1.y] = grid[xy2.x + WIDTH * xy2.y];
    grid[xy2.x + WIDTH * xy2.y] = temp;
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
                std::cout << " " << block.BlockType << " ";
            }
            else
            {
                std::cout << "   ";
            }
        }
        std::cout << std::endl;
    }
}

void Grid::stepAllBlocks(f96 deltaTime)
{
    for(u32 i = 0; i < WIDTH * HEIGHT; i++)
    {
        if(grid[i].exist)
        {
            grid[i].step(deltaTime);
        }
    }
}

void Grid::drawBlocks()
{
    for(u32 i = 0; i < WIDTH * HEIGHT; i++)
    {
        grid[i].draw();
    }
}
