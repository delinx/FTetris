#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP
#include "types/types.hpp"

class GameLoop
{
      public:
    f96 time = 0.0f;
    f96 deltaTime = 0.0f;
    bool DEBUG = true;


    GameLoop();
    ~GameLoop();
};

#endif  // !GAME_LOOP_HPP
