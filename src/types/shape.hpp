#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "grid.hpp"
#include "types.hpp"

struct Shape
{
    Grid shape_I = Grid(4, 4);
    Grid shape_J = Grid(3, 3);
    Grid shape_L = Grid(3, 3);
    Grid shape_O = Grid(2, 2);
    Grid shape_S = Grid(3, 3);
    Grid shape_T = Grid(3, 3);
    Grid shape_Z = Grid(3, 3);
    Shape();
};

#endif  // !SHAPE_HPP
