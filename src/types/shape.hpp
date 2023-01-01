#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "block.hpp"
#include "grid.hpp"
#include "types.hpp"

struct Shape
{
    Grid *shape_I = new Grid(4, 4);
    Grid *shape_J = new Grid(3, 3);
    Grid *shape_L = new Grid(3, 3);
    Grid *shape_O = new Grid(2, 2);
    Grid *shape_S = new Grid(3, 3);
    Grid *shape_T = new Grid(3, 3);
    Grid *shape_Z = new Grid(3, 3);
    Shape();
    ~Shape();
};

#endif  // !SHAPE_HPP
