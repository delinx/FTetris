#include "shape.hpp"

Shape::Shape()
{
    // list of all possible shapes in the default rotation
    // 0 I       1 S     2 Z     3 T     4 O   5 L     6 J
    // . . . .   . . .   . . .   . X .   X X   . . X   X . .
    // X X X X   . O X   X O .   X O X   X X   X O X   X O X
    // . .o. .   X X .   . X X   . . .         . . .   . . .
    // . . . .

    Block block;
    block.exist = true;
    block.visible = true;

    block.bucketPos = iXY(0, 1);
    block.forceUpdateVisualPos();
    shape_I->set(iXY(0, 1), block);
    block.bucketPos = iXY(1, 1);
    block.forceUpdateVisualPos();
    shape_I->set(iXY(1, 1), block);
    block.bucketPos = iXY(2, 1);
    block.forceUpdateVisualPos();
    shape_I->set(iXY(2, 1), block);
    block.bucketPos = iXY(3, 1);
    block.forceUpdateVisualPos();
    shape_I->set(iXY(3, 1), block);

    block.bucketPos = iXY(0, 0);
    block.forceUpdateVisualPos();
    shape_J->set(iXY(0, 0), block);
    block.bucketPos = iXY(0, 1);
    block.forceUpdateVisualPos();
    shape_J->set(iXY(0, 1), block);
    block.bucketPos = iXY(1, 1);
    block.forceUpdateVisualPos();
    shape_J->set(iXY(1, 1), block);
    block.bucketPos = iXY(2, 1);
    block.forceUpdateVisualPos();
    shape_J->set(iXY(2, 1), block);

    block.bucketPos = iXY(2, 0);
    block.forceUpdateVisualPos();
    shape_L->set(iXY(2, 0), block);
    block.bucketPos = iXY(0, 1);
    block.forceUpdateVisualPos();
    shape_L->set(iXY(0, 1), block);
    block.bucketPos = iXY(1, 1);
    block.forceUpdateVisualPos();
    shape_L->set(iXY(1, 1), block);
    block.bucketPos = iXY(2, 1);
    block.forceUpdateVisualPos();
    shape_L->set(iXY(2, 1), block);

    block.bucketPos = iXY(0, 0);
    block.forceUpdateVisualPos();
    shape_O->set(iXY(0, 0), block);
    block.bucketPos = iXY(1, 0);
    block.forceUpdateVisualPos();
    shape_O->set(iXY(1, 0), block);
    block.bucketPos = iXY(0, 1);
    block.forceUpdateVisualPos();
    shape_O->set(iXY(0, 1), block);
    block.bucketPos = iXY(1, 1);
    block.forceUpdateVisualPos();
    shape_O->set(iXY(1, 1), block);

    block.bucketPos = iXY(0, 2);
    block.forceUpdateVisualPos();
    shape_S->set(iXY(0, 2), block);
    block.bucketPos = iXY(1, 2);
    block.forceUpdateVisualPos();
    shape_S->set(iXY(1, 2), block);
    block.bucketPos = iXY(1, 1);
    block.forceUpdateVisualPos();
    shape_S->set(iXY(1, 1), block);
    block.bucketPos = iXY(2, 1);
    block.forceUpdateVisualPos();
    shape_S->set(iXY(2, 1), block);

    block.bucketPos = iXY(1, 0);
    block.forceUpdateVisualPos();
    shape_T->set(iXY(1, 0), block);
    block.bucketPos = iXY(0, 1);
    block.forceUpdateVisualPos();
    shape_T->set(iXY(0, 1), block);
    block.bucketPos = iXY(1, 1);
    block.forceUpdateVisualPos();
    shape_T->set(iXY(1, 1), block);
    block.bucketPos = iXY(2, 1);
    block.forceUpdateVisualPos();
    shape_T->set(iXY(2, 1), block);

    block.bucketPos = iXY(0, 1);
    block.forceUpdateVisualPos();
    shape_Z->set(iXY(0, 1), block);
    block.bucketPos = iXY(1, 1);
    block.forceUpdateVisualPos();
    shape_Z->set(iXY(1, 1), block);
    block.bucketPos = iXY(1, 2);
    block.forceUpdateVisualPos();
    shape_Z->set(iXY(1, 2), block);
    block.bucketPos = iXY(2, 2);
    block.forceUpdateVisualPos();
    shape_Z->set(iXY(2, 2), block);
};

Shape::~Shape()
{
    std::cout << "XXXXXXXX"
              << "ShapeTemplate was destroyed, WHY?"
              << "XXXXXXXX" << std::endl;
}
